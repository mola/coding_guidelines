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
          ${target_sample}
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
      ${target_sample}
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
  set_target_properties(${target_sample}
      PROPERTIES
          CXX_EXTENSIONS OFF
  )

  # BAD
  set_target_properties(${target_sample}
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

- Use `list(APPEND <var> ...)` over `set(<var> "${<var>} ...")` as this appends
  to the variable instead of overwriting the original content.

  ```cmake
  # GOOD
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

  # BAD
  set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake")
  ```

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

- For more information on 'When to quote variables' see
  https://stackoverflow.com/questions/35847655/when-should-i-quote-variables/35853080#35853080

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

#### Use Variable For Target

To make the CMake code more readable and less error-prone, on later target name
related changes, a **separated variable** should be used to **define a target
name**. This has the benefit that the code can reference back to this variable
and spelling errors can not occur when a target name is needed multiple times,
e.g. on target configuration, install step, etc.

```cmake
# GOOD
set(target_foo "foo")

add_library(${target_foo})
add_library(foo::${target_foo} ALIAS ${target_foo})
target_source(${target_foo} PUBLIC foo.hpp PRIVATE foo.cpp)

# BAD
add_library(foo)
add_library(foo::foo ALIAS foo)
target_source(foo PUBLIC foo.hpp PRIVATE foo.cpp)
```

### Naming Conventions

Poorly-chosen names can mislead the reader and cause bugs. Pick names that match
the semantics and role of the underlying entities, withing reason. Avoid
abbreviations unless they are well known e.g from a protocol specification.

- **Commands** should be lowercase and `snake_case`.

  ```cmake
  add_executable()
  install()
  if()
  else()
  endif()

  function(do_something) ... endfunction()
  ```

- **CMake provided variables** should be uppercase and `SNAKE_CASE`.

  ```cmake
  CMAKE_MODULE_PATH
  CMAKE_CURRENT_BINARY_DIR
  CMAKE_SOURCE_DIR
  PROJECT_SOURCE_DIR
  ```

- **Local variables** should be lowercase and `snake_case`.

  ```cmake
  my_var
  my_compiler_flags
  ```

- **Variables holding a target name** should be prefixed with `target_` and
  follow otherwise the local variable naming.

  ```cmake
  set(target_foo "libfoo")
  set(target_bar_baz "bar_baz")
  ```

- **Cache variables** should be prefixed with the project name and follow
  otherwise the local variable naming.

  ```cmake
  project("libfoo")

  set(libfoo_enable_tests OFF
    CACHE
        BOOL "Enable tests which can be run with 'ctest' ..."
    FORCE
  )
  ```

- **Properties / Function Keywords** should be uppercase and `SNAKE_CASE`.

  ```cmake
  if("..." STREQUAL "...")
  install(TARGETS ... DESTINATION ... OPTIONAL ...)
  ```

- **Module filenames** should be lowercase and `snake_case`.

  ```cmake
  build_type_handler.cmake
  clang_tidy.cmake
  git_revision_description.cmake
  ```

### Comments

- CMake files should **always** be documented **properly**.
- Add a **describing comment** at the **beginning** of a module file e.g. what
  is the purpose of the file, which variables will be globally defined, which
  targets will be provided etc.

  ```cmake
  # Finds the Foo library.
  #
  # This module provides the following imported targets, if found:
  #     Foo::Foo - The Foo library
  #
  # This will define the following variables:
  #     Foo_FOUND - True if the system has the Foo library.
  #     Foo_VERSION - The version of the Foo library which was found.
  #     ...
  #
  # The following cache variables may also be set:
  #     Foo_INCLUDE_DIR - The directory containing 'foo.hpp'.
  #     Foo_LIBRARY - The path to the Foo library.
  ```

- Add a **describing comment** in front of a function in the following style:
  - Use **multiline** comments for function/macro documentation.
  - **Variables** should be enclosed in angled brackets. (e.g. `<var>`)
  - **Optional fields** should be enclosed in brackets.
    (e.g. `[RESULT <result>]`)
  - **List fields** should be indicated with three dots at the end.
    (e.g. `LANGUAGES <lang>...`)
  - **XOR dependencies** should be separated with a 'bar' character.
    (e.g. `TYPE <SHARED|MODULE|STATIC>`)

  ```cmake
  #[[

  Define sample module with given name and specific language.

  sample_add_library(<name>
                    [TYPE <SHARED|MODULE|STATIC>]
                    LANGUAGE <language>
                    [NO_PROXY]
                    [OUTPUT_DIR <directory>]
                    SOURCES <file>...
  )

  Here can follow a longer and more detailed documentation.

  - TYPE
  ...

  - LANGUAGE
  Specify the target language.

  - NO_PROXY
  Prevent the generation of the wrapper layer.

  - OUTPUT_DIR
  Specify where to write the language specific files.

  - SOURCES
  List of sources for the library.

  #]]
  ```
