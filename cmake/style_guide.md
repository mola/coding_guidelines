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

### Rules Of Thumb

- On multiline commands **put** the closing parenthesis on a **separate line**
  and align it with the command.

  ```cmake
  # GOOD
  set_target_properties(${sample_target}
      PROPERTIES
          CXX_EXTENSIONS OFF
  )

  # BAD
  set_target_properties(${sample_target}
      PROPERTIES
          CXX_EXTENSIONS OFF)
  ```

- To make the code easier to read and less error-prone on code changes, use
  empty commands for `endforeach`, `endif`, `endfunction`, `endmacro`,
  `endwhile` and `else`.

  ```cmake
  # GOOD
  function(do_something)
      if(FOOVAR)
          some_command(...)
      else()
          another_command(...)
      endif()
  endfunction()

  # BAD
  function(do_something)
      if(FOOVAR)
          some_command(...)
      else()
          another_command(...)
      endif(FOOVAR)
  endfunction(do_something)
  ```

- Use `include_guard([DIRECTORY|GLOBAL])` to prevent the processing of a CMake
  file multiple time. It provides a similar functionality as the C++ `#pragma
  once`.
- When storing paths in variables, **do not** have the variable end up with a
  slash.

  ```cmake
  # GOOD
  set(foo_path "path/to/foo")
  set(var_path "${foo_path}/${my_var}")

  # BAD
  set(foo_path "path/to/foo/")
  set(var_path "${foo_path}${my_var}")
  ```

- Use `list(APPEND <var> ...)` over `set(<var> "${<var>} ..."` as this appends
  to the variable instead of overwriting the original content.

  ```cmake
  # GOOD
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

  # BAD
  set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake")
  ```

- Functions with multiple arguments should use `cmake_parse_arguments`.
  - See documentation: https://cmake.org/cmake/help/latest/command/cmake_parse_arguments.html

#### Quotes

- **Always** use quotes around variables that represent a string.

  ```cmake
  set(my_var "foo")

  if("${my_var}" STREQUAL "bar")
      ...
  endif()
  ```

- **Do not** use quotes around variables that are booleans.

  ```cmake
  set(my_var ON)

  if(${my_var})
      ...
  endif()
  ```

- Read https://stackoverflow.com/questions/35847655/when-should-i-quote-variables/35853080#35853080

#### Conditions

- Use `if(DEFINED <var>)` to check if a variable is set.

  ```cmake
  if(DEFINED my_var)
      ...
  endif()
  ```

- Use `if(<var>)` to check if a variable has a non-empty value.

  ```cmake
  if(my_var)
      ...
  endif()
  ```
