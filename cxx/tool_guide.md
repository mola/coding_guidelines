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
