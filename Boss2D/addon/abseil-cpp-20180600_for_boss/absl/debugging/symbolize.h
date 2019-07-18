// Copyright 2018 The Abseil Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// -----------------------------------------------------------------------------
// File: symbolize.h
// -----------------------------------------------------------------------------
//
// This file configures the Abseil symbolizer for use in converting instruction
// pointer addresses (program counters) into human-readable names (function
// calls, etc.) within Abseil code.
//
// The symbolizer may be invoked from several sources:
//
//   * Implicitly, through the installation of an Abseil failure signal handler.
//     (See failure_signal_handler.h for more information.)
//   * By calling `Symbolize()` directly on a program counter you obtain through
//     `absl::GetStackTrace()` or `absl::GetStackFrames()`. (See stacktrace.h
//     for more information.
//   * By calling `Symbolize()` directly on a program counter you obtain through
//     other means (which would be platform-dependent).
//
// In all of the above cases, the symbolizer must first be initialized before
// any program counter values can be symbolized. If you are installing a failure
// signal handler, initialize the symbolizer before you do so.
//
// Example:
//
//   int main(int argc, char** argv) {
//     // Initialize the Symbolizer before installing the failure signal handler
//     absl::InitializeSymbolizer(argv[0]);
//
//     // Now you may install the failure signal handler
//     absl::FailureSignalHandlerOptions options;
//     absl::InstallFailureSignalHandler(options);
//
//     // Start running your main program
//     ...
//     return 0;
//  }
//
#ifndef ABSL_DEBUGGING_SYMBOLIZE_H_
#define ABSL_DEBUGGING_SYMBOLIZE_H_

#include BOSS_ABSEILCPP_U_absl__debugging__internal__symbolize_h //original-code:"absl/debugging/internal/symbolize.h"

namespace absl {
inline namespace lts_2018_06_20 {

// InitializeSymbolizer()
//
// Initializes the program counter symbolizer, given the path of the program
// (typically obtained through `main()`s `argv[0]`). The Abseil symbolizer
// allows you to read program counters (instruction pointer values) using their
// human-readable names within output such as stack traces.
//
// Example:
//
// int main(int argc, char *argv[]) {
//   absl::InitializeSymbolizer(argv[0]);
//   // Now you can use the symbolizer
// }
void InitializeSymbolizer(const char* argv0);

// Symbolize()
//
// Symbolizes a program counter (instruction pointer value) `pc` and, on
// success, writes the name to `out`. The symbol name is demangled, if possible.
// Note that the symbolized name may be truncated and will be NUL-terminated.
// Demangling is supported for symbols generated by GCC 3.x or newer). Returns
// `false` on failure.
//
// Example:
//
//   // Print a program counter and its symbol name.
//   static void DumpPCAndSymbol(void *pc) {
//     char tmp[1024];
//     const char *symbol = "(unknown)";
//     if (absl::Symbolize(pc, tmp, sizeof(tmp))) {
//       symbol = tmp;
//     }
//     absl::PrintF("%*p  %s\n", pc, symbol);
//  }
bool Symbolize(const void *pc, char *out, int out_size);

}  // inline namespace lts_2018_06_20
}  // namespace absl

#endif  // ABSL_DEBUGGING_SYMBOLIZE_H_
