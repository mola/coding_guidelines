---
title: CMake Style Guide
toc: true
---

This page provides style guidelines for the CMake programming language.

<div class="alert alert-warning">
  <strong>This page is still work in progress.</strong>
</div>

### Source Code Column Limit

The source code must not exceed **100 character per line**. This limit allows to
have two splits open and still see the whole source code without resizing.

### Whitespace

- Use **spaces** instead of tabs.
- Use **4 spaces** for indentation and do not re-indent a whole source file if
  you prefer a different indentation level.
- Do not commit changes that include trailing whitespace at the end of lines or
  files. Let your editor of choice automatically remove trailing whitespace when
  saving a file.
- **Do not** put a space between a command and the opening parenthesis.

  ```cmake
  # GOOD
  add_executable(...)

  if(FOOVAR)
      some_command(...)
  endif()

  # BAD
  add_executable (...)

  if (FOOVAR)
      some_command (...)
  endif ()
  ```
