#include <iostream>
#include <iomanip>
#include <csignal>
#include <cstdint>
#include <cstdlib> 

#ifdef _WIN32
#include <windows.h>
#else
#include <execinfo.h>
#endif

void analyze_hex_address(uintptr_t addr) {
    std::cout << "\n=== HEX ANALYSIS ===\n";
    std::cout << "Fault Address: 0x" << std::hex << std::uppercase << addr << "\n";
    
    if (addr == 0x0) {
        std::cout << "Pattern: NULL pointer\n";
    } else if (addr == 0xDEADBEEF) {
        std::cout << "Pattern: DEADBEEF (debug marker)\n";
    } else if (addr < 0x1000) {
        std::cout << "Pattern: Low address (likely null + offset)\n";
    } else {
        std::cout << "Pattern: Custom address\n";
    }
}

#ifdef _WIN32
LONG WINAPI crash_handler(EXCEPTION_POINTERS* ep) {
    if (ep->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION) {
        analyze_hex_address(ep->ExceptionRecord->ExceptionInformation[1]);
        std::cout << "\nAnalysis complete. Exiting...\n";
    }
    return EXCEPTION_EXECUTE_HANDLER;
}
#else
void crash_handler(int sig, siginfo_t* info, void*) {
    analyze_hex_address(reinterpret_cast<uintptr_t>(info->si_addr));
    
    // Simple stack trace
    void* buffer[5];
    int frames = backtrace(buffer, 5);
    std::cout << "\nStack trace (" << frames << " frames):\n";
    for (int i = 0; i < frames; i++) {
        std::cout << "[" << i << "] 0x" << std::hex << buffer[i] << "\n";
    }
    
    std::cout << "\nAnalysis complete. Exiting...\n";
    _exit(1);  // Force program termination
}
#endif

void setup_handler() {
#ifdef _WIN32
    SetUnhandledExceptionFilter(crash_handler);
#else
    struct sigaction sa;
    sa.sa_sigaction = crash_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGSEGV, &sa, nullptr);
#endif
}

int main() {
    std::cout << "=== Segfault Hex Debugging Demo ===\n";
    
    setup_handler();
    
    int* bad_ptr = reinterpret_cast<int*>(0xDEADBEEF);
    std::cout << "Dereferencing 0xDEADBEEF...\n";
    
    *bad_ptr = 42;
    
    return 0;
}