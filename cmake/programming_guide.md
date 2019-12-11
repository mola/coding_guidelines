---
title: CMake Programming Guide
toc: true
---

This page provides programming guidelines for the CMake programming language.

<div class="alert alert-warning">
  <strong>This page is still work in progress.</strong>
</div>

### Minimum CMake Version

- **Prefer** the **latest** version of CMake.
- **Do not** target any CMake version less than 3.0, as earlier versions of
  CMake did not provide target-based configurations.

### Treat CMake Code Like Production Code

The 'CMake language' is a programming language. Therefore, it should use the
same principles as the rest of the codebase. This means it should be written in
a simple, structured, documented and readable form.

### Think In Targets And Properties

By defining properties in terms of targets, it helps developers to reason about
the system at the target level. The developers do not need to understand the
whole system in order reason about a single target. Furthermore can a target
handle its properties (e.g. compile definitions, features, dependencies)
differently to the rest of the project without pollution the global scope.

- **Do not** use **global** functions like `include_directories`,
  `link_directories`, and similar.
- **Do not** add **unneeded** `PUBLIC` requirements, to avoid forcing something
  on users that are not required (e.g. '-Wall' compiler flag).
- Keep **internal** properties `PRIVATE`.
- **Prefer** to link against namespaced targets.

  ```cmake
  # GOOD (if namespaced target is available)
  target_link_libraries(${foo_target} Bar::Bar)

  # BAD (if namespaced target is available)
  target_include_directories(${foo_target} PRIVATE ${Bar_INCLUDE_DIRS})
  target_link_libraries(${foo_target} ${Bar_LIBRARY})
  ```

- Make `ALIAS` targets to keep the usage consistent.

  ```cmake
  add_library(Foo::Bar ALIAS Bar)
  ```

### Functions And Macros

**Prefer function** over **macros** whenever reasonable. In addition to
directory-base scope, CMake function have their own scope. This means variables
set inside functions are not visible in the parent scope, which is not true for
macros.

The most important part is to combine **common functionality** into clearly
**documented** functions or macros.

#### Argument Handling

**Do not** reinvent the wheel for argument handling. Use `cmake_parse_arguments`
as this is the recommended way to handle complex argument-based behaviors or
optional arguments in any function.

See https://cmake.org/cmake/help/latest/command/cmake_parse_arguments.html for
more informations regarding the `cmake_parse_arguments` command.

### Avoid Message Pollution

- **Do not** print every information with `STATUS` or `NOTICE` if the
  information only serves as a debug message (e.g. file entries). Normal users
  do not care which file is currently processed or what happens internally.
  It is therefore discouraged to pollute the output for the user.

  ```cmake
  # GOOD
  message(DEBUG "[${PROJECT_NAME}] -- Processing ${CMAKE_CURRENT_LIST_FILE}")

  # BAD
  message(STATUS "[${PROJECT_NAME}] -- Processing ${CMAKE_CURRENT_LIST_FILE}")
  ```

- See https://cmake.org/cmake/help/latest/command/message.html

### Do Not Use `file(GLOB)`

CMake is a build system generator, not a build system. It evaluates the `GLOB`
expression to a list of files when generating the build system. The build system
then operates on this list of files. Therefore, the build system cannot detect
that something changed on the file system.


