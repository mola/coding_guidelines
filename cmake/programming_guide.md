---
title: CMake Programming Guide
toc: true
---

This page provides programming guidelines for the CMake programming language.

<div class="alert alert-warning">
  <strong>This page is still work in progress.</strong>
</div>

### General

#### Minimum CMake Version

- **Prefer** the **latest** version of CMake.
- **Do not** target any CMake version less than 3.0, as earlier versions of
  CMake did not provide target-based configurations.

#### Treat CMake Code Like Production Code

The 'CMake language' is a programming language. Therefore, it should use the
same principles as the rest of the codebase. This means it should be written in
a simple, structured, documented and readable form.

#### Think In Targets And Properties

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
