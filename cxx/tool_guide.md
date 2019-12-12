---
title: C++ Tool Guide
toc: true
---

This page provides tools with can and should be used to improve the C++ source
code.

<div class="alert alert-warning">
  <strong>This page is still work in progress.</strong>
</div>

### Compiler

It is advised to compile and test the source code with **multiple** different
compilers. Each compiler implements the standard slightly differently and
supporting multiple compiler will help ensure the most portable, most reliable
code.

#### Clang / GCC Compiler Flags

- `-pedantic` issues warnings whenever there are compiler extensions
  non-compliant to the ISO C or C++ standard.
- `-pedantic-errors` turns warnings into errors for `-pedantic`.
- `-Wall` turns on lots of useful compiler flags.
- `-Wextra` turns on more useful compiler flags which are not enabled with
  `-Wall`.
- `-Wdouble-promotion` warns if `float` is implicit promoted to `double`.
- `-Wundef` warns if something is not `defined`.
- `-Wshadow` warns if a variable declaration shadows one from a parent context.
- `-Wnull-dereference` warns if a null dereference is detected.
- `-Wzero-as-null-pointer-constant` warns if a zero is used as a null pointer
  constant.
- `-Wno-gnu-zero-variadic-macro-arguments` do not warn if zero arguments are
  given to a variadic macro.
- `-Wunused` warns on anything being unused.
- `-Wold-style-cast` warns for C-style casts.
- `-Wsign-compare` warns about comparing integers of different signs.
- `-Wunreachable-code` warns if code will never be executed.
- `-Wunreachable-code-break` warns if `break` will never be executed.
- `-Wunreachable-code-return` warns if `return` will never be executed.
- `-Wextra-semi-stmt` warns if unnecessary `;` is given to an empty expression
  statement which has no effect.
- `-Wreorder` warns if class fields will be initialized in a different order.
- `-Wcast-qual` warns if cast drops `const`/`volatile` qualifier.
- `-Wconversion` warns on type conversions that may lose data.
- `-Wfour-char-constants` warns on multi-character character constant.
- `-Wformat=2` warns on security issues around functions that format output (e.g
  `printf`).
- `-Wheader-hygiene` warns on using namespace directive in global context in a
  header.
- `-Wnon-virtual-dtor` warns if a class with virtual functions has a non-virtual
  destructor. This helps to catch hard track down memory errors.
- `-Wnewline-eof` warns if there is no newline at the end of the file.
- `-Wpointer-arith` warns on illegal pointer arithmetic.
- `-Wfloat-equal` warns on comparing floating point with `==` or `!=` as this is
  unsafe.
- `-Wpragmas` turns on compiler flags which warn about `#pragma` missuses.
- `-Wreserved-user-defined-literal` warns on invalid suffix on literal.
- `-Wsuper-class-method-mismatch` warns if method parameter type does not match
  super class method parameter type.
- `-Wswitch-enum` warns if a `switch` does not handle all enumerators
  explicitly.
- `-Wcovered-switch-default` warns if a `default` label is in a `switch` which
  covers all enumerators.
- `-Wthread-safety` turns on compiler flags which warn about thread safety
  problem which can occur.
- `-Wunused-exception-parameter` warns on unused exception parameter.
- `-Wvector-conversion` warns on incompatible vector types.
- `-Wkeyword-macro` warns if a keyword is hidden by a macro definition.
- `-Wformat-pedantic` warns if format specifies a type but the argument has a
  different type.
- `-Woverlength-strings` warns on string literal of a length which exceeds the
  maximum length that C++ compilers are required to support.
- `-Wdocumentation` turns on compiler flags which warn about problems with the
  provided documentation e.g. parameter mismatch, missing parameter
  documentation, etc.

#### MSVC Compiler Flags

- `/permissive-` specifies standard conformance mode to the compiler.
- `/W4` turns on a lot of reasonable warnings.
- `/w14640` warns on thread un-safe static member initialization.
- `/w14265` warns if class has virtual functions but destructor is not virtual.
- `/w14826` warns if conversion from one type to another is sign-extended. This
  may cause unexpected runtime behavior.
- `/w14928` warns on illegal copy-initialization.

#### Treat Warnings As Errors

To enforce the compiler flags it is advised to treat the warnings given by the
compilers as errors. Use `-Werror` with Clang/GCC and `/Wx` with MSVC which will
turn all warnings into errors.

#### Sanitizer

These tools provide runtime code analysis that can detect memory leaks, race
conditions, and other associated problems. The sanitizers are built into the
**Clang** and **GCC** compiler and to do not require extra tooling.

- [Clang AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html)
- [Clang ThreadSanitizer](https://clang.llvm.org/docs/ThreadSanitizer.html)
- [Clang MemorySanitizer](https://clang.llvm.org/docs/MemorySanitizer.html)
- [Clang UndefinedBehaviorSanitizer](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html)
- [Clang DataFlowSanitizer](https://clang.llvm.org/docs/DataFlowSanitizer.html)
- [Clang LeakSanitizer](https://clang.llvm.org/docs/LeakSanitizer.html)

### LLVM-based Tools

LLVM-based tools work best with a build system that can output a compile
commands database. For other build systems there is
[Build EAR](https://github.com/rizsotto/Bear) which will hook into the build
system and generate a compile command database.

```sh
# cmake example on how to enable compile commands output
$ cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```

#### Include-What-You-Use

The **include-what-you-use tool** is a program that can be built with the clang
libraries in order to analyze `#include` of source files to find
**include-what-you-use violations**.

> *Include what you use* means: for every symbol (type, function variable, or
> macro) that is used in `foo.cpp`, either `foo.cpp` or `foo.hpp` should
> `#include` a header file that exports the declaration of that symbol.

The main goal of the **include-what-you-use tool** is to remove superfluous
`#includes`. It does this both by figuring out what `#includes` are not actually
needed for the give file (both `.cpp` and `.hpp` files), and replacing
`#includes` with **forward declarations** when possible.

- Website: https://include-what-you-use.org/

#### Clang-Format

The **clang-format** standalone tool is built on top of **LibFormat**, which is
a library that implements automatic source code formatting based on **Clang**.

- Website: https://clang.llvm.org/docs/ClangFormat.html

The **clang-format** tool **can** help with:

- Alignment
- Column Limit
- Brace Placement
- Space Placement
- Include Sorting
- Indentation

The **clang-format** tool **can not** help with:

- Naming Convention
- Trailing Return Type
- East-/West-Const
- Function Prefixes
- Access Specifier
- Braces Around Statements
- Comment Style

#### Clang-Tidy

**clang-tidy** is a clang-based C++ *linter* tool. Its purpose is to provide an
extensible framework for diagnosing and fixing typical programming errors, like
style violations, interface misuse, or bugs that can be deduced via static
analysis.

- Website: https://clang.llvm.org/extra/clang-tidy/

The **clang-tidy** tool **can** help with:

- Naming Convention
- Braces Around Statements
- Trailing Return Types
- Use of modern constructs (e.g. constants over macros, no C-style casts,
  noexcept, etc.)
- No `else` after control flow interrupts
- Finding typical programming error

The **clang-tidy** tool **can not** help with:

- Think Immutable (making thing as much `const` as possible)
- Pointer Order Usage
- `auto` Keyword Enforcement
- East-/West-Const
- Function Prefixes
- Access Specifier
- Comment Style

#### Clazy

**clazy** is a Qt oriented code checker based on the clang framework. It has
more than 50 Qt related compiler warnings, ranging from unneeded memory
allocations to misusage of the API.

- Website: https://github.com/KDE/clazy

### Cppcheck

**Cppcheck** is a static analysis tool for C and C++ code. It provides unique
code analysis to detect bugs and focuses on detecting undefined behavior and
dangerous coding constructs.

- Website: http://cppcheck.sourceforge.net/

### Heaptrack

**heaptrack** is a heap memory profiler for Linux. It traces all memory
allocations and annotates these events with stack traces.

- Website: https://github.com/KDE/heaptrack

### Testing

**CMake** has a built in framework for executing test. The **ctest** executable
is the CMake test driver program. It can run the test added with `add_test()`
and report the results.

- Website: https://cmake.org/cmake/help/latest/manual/ctest.1.html

To further aid in executing test, consider a specialized library to help
organizing the tests. A few well known test frameworks:

- [Doctest](https://github.com/onqtam/doctest)
- [Catch2](https://github.com/catchorg/Catch2)
- [Google Test](https://github.com/google/googletest)
- [CppUTest](https://github.com/cpputest/cpputest)
- [Boost.Test](https://www.boost.org/doc/libs/1_72_0/libs/test/doc/html/index.html)

#### Code Coverage Analysis

A coverage analysis tool shall be run when tests are executed to make sure the
entire application is being tested.

- [gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html)
- [gcovr](https://gcovr.com/en/stable/)
- [kcov](https://simonkagstrom.github.io/kcov/index.html)
- [llvm-cov](https://llvm.org/docs/CommandGuide/llvm-cov.html)
- [Clang Source-based Code Coverage](https://clang.llvm.org/docs/SourceBasedCodeCoverage.html)
