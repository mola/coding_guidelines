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

#### Do Not Use Whitespace For Alignment

Idiomatic code should not use extra whitespace in the middle of a line to
provide alignment.

```cmake
# GOOD
set(meta_project_name "sample_project")
set(meta_project_description "description for sample_project")

# BAD
set(meta_project_name        "sample_project")
set(meta_project_description "description for sample_project")
```

### Indentation

- In general, reduce indentation wherever possible.
- **Indent** values **according to** the properties they belong, as this helps
  to see on the first glance which values are for which property.

  ```cmake
  # GOOD
  install(
      TARGETS
          ${sample_target}
      RUNTIME
          DESTINATION ${CMAKE_INSTALL_BINDIR}
      LIBRARY
          DESTINATION ${CMAKE_INSTALL_LIBDIR}
      ARCHIVE
          DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

  # BAD
  install(
      TARGETS
      ${sample_target}
      RUNTIME
      DESTINATION ${CMAKE_INSTALL_BINDIR}
      LIBRARY
      DESTINATION ${CMAKE_INSTALL_LIBDIR}
      ARCHIVE
      DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
  ```
