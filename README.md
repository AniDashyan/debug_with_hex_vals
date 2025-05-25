Got it. Here's the updated `README.md` content with the correct project title:

---

# Debugging with hex values

## Overview

**Debugging with hex values** is a cross-platform C++ demo that intentionally triggers a segmentation fault and analyzes the resulting crash using platform-specific mechanisms. It identifies the faulting address pattern (such as `0xDEADBEEF`, NULL, or low address values) and prints a simple backtrace on Unix-like systems. This tool helps developers understand and debug invalid pointer dereference issues effectively.

## Build & Run

To build and run the project, follow these steps:

```bash
# 1. Clone the repository
git clone https://github.com/AniDashyan/debug_with_hex_vals.git
cd debug_with_hex_vals

# 2. Generate build files and compile
cmake -S . -B build
cmake --build build

# 3. Run the executable
./build/hex_vals
```

## Example Output

```
=== Segfault Hex Debugging Demo ===
Dereferencing 0xDEADBEEF...

=== HEX ANALYSIS ===
Fault Address: 0xDEADBEEF
Pattern: DEADBEEF (debug marker)

Stack trace (5 frames):
[0] 0x55f37d1b32d3
[1] 0x55f37d1b2f85
[2] 0x7f1b14a37d90
[3] 0x7f1b14a38e40
[4] 0x55f37d1b2e15

Analysis complete. Exiting...
```

## Explanation

The program works as follows:

* It registers a crash handler using platform-specific APIs (`sigaction` on Linux/macOS or `SetUnhandledExceptionFilter` on Windows).
* It deliberately dereferences an invalid pointer (`0xDEADBEEF`) to cause a segmentation fault or access violation.
* When the crash occurs:

  * The handler captures the faulting address and passes it to `analyze_hex_address()`.
  * The analysis function classifies the address (e.g., NULL, known debug pattern, low address range) and prints details.