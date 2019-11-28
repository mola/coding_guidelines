---
title: C++ Style Guide
toc: true
---

This page provides style guidelines for the C++ programming language.

<div class="alert alert-warning">
  <strong>This page is still work in progress.</strong>
</div>

<div class="alert alert-warning">
  <strong>TODO:</strong> add '.clang-format' and '.clang-tidy' and describe why
  and how to use them.
</div>

### Source Code Column Limit

The source code must not exceed 100 character per line. This limit allows to
have two splits open and still see the whole source code without resizing. The
most used column width is 80 which is a little bit too short for C++ with
lengthy types and function names.

- Source Code Column Limit: 100

### Whitespace

- Use **spaces** instead of tabs
- Use **4 spaces** for indentation and do not re-indent a whole source file if
  you prefer a different indentation level.
- Do not commit changes that include trailing whitespace at the end of lines or
  files. Let your editor of choice automatically remove trailing whitespace when
  saving a file.
- Use **space** before opening parenthesis in control flow statements.

  ```cpp
  if (true) { ... }
  while (true) { ... }
  for (...) { ... }
  ```

### Comments

#### General

- Avoid C style block comments (`/* ... */`), which have have nesting problems.
- Prefer C++ style comments (`//` for normal comments, `///` for documentation
  comments)
- Commenting out large blocks of code is highly discouraged. Use `#if 0` and
  `#endif` but only for debugging purpose.
- Header files should be documented properly with Doxygen comments.
  This helps other people to figure out the use of the interface without
  reading the actual implementation.
- Add a comment to the end of a namespace

  ```cpp
  namespace foo {
      ...
  namespace bar {
      ...
  } // namespace bar
  } // namespace foo
  ```

#### Doxygen

- Doxygen comments are prefixed with three slashes (`///`)
- Use Latex-style `\` instead of Javadoc-style `@` for Doxygen commands.
- The first line should be a single-line short sentence providing a summary of
  the code. The `\brief` specifier should not be added because Doxygen already
  interprets the first sentence as description.
- All describing documentation comments (summary line/long description) should
  begin with a capital letter and end with a period, question mark, or
  exclamation point.
- Prefer full sentences to fragments.
- Add an empty line between description, parameter and return documentation.
- Wrap non-inline code examples in `\code` / `\endcode`.

  ```cpp
  /// Check if the given Foo is valid.
  ///
  /// Typical usage:
  /// \code
  ///   auto valid = is_valid(foo);
  /// \endcode
  ///
  /// \param foo Foo object which should be checked
  ///
  /// \returns true if foo is valid
  bool is_valid(Foo foo);
  ```

### Trailing Return Type

**Always** use **trailing return type** to be consistent with all use cases e.g.
lambdas, templates where the return type depends on the argument type.

```cpp
// requires 'trailing return type' to compile/work
template<class T, class U>
auto multiply(T const& lhs, U const& rhs) -> decltype(lhs * rhs) {
  return lhs * rhs;
}

// can only use 'trailing return type' to indicate return type
auto foo = [&](Foo a, Foo b) -> bool {
  return a < b;
};

// use 'trailing return type' to be consistent
auto do_something() -> void {
	...
}
```

### Braces

Opening braces should **always** go on the **same line**. This reduces 'wasted'
line because lines with only an opening brace do not help with the readability
and distort the source code in its length.

  ```cpp
  namespace foo {

  class X : public Y {
      ...
  }

  void bar()
  {
      ...

      if (x) {
          ...
      } else {
          ...
      }
  }
  } // namespace foo
  ```

### Naming Conventions

#### General Conventions

Use descriptive names, and be consistent in the style. In general, use
`CamelCase` for 'type-level' constructs (classes and enums) and `snake_case`
for 'value-level' constructs (functions and variables). The advantage of
`snake_case` is that it can also work with spell checkers.

- **Variables** should be lowercase and `snake_case`

  ```cpp
  int number_of_bytes;
  std::string name;
  ```

- **Private member variables** should be prefixed with `m_` to distinguish them
  from normal variables.

  ```cpp
  class Foo {
      int m_number_of_bytes;
      std::string m_name;
  };
  ```

- **Global variables** should be prefixed with `g_` and follow otherwise the
  normal variable naming.

  ```cpp
  static char constexpr g_path_separator = '/';
  ```

- **Enumerators** should be prefixed with `e_` and follow otherwise the normal
  variable naming.

  ```cpp
  enum Status {
      e_error,
      e_success,
      e_idle,
      e_in_progress
  }
  ```

- **Type names** (including classes, structs, enums, typedefs, etc.) should
  start with a uppercase letter and follow `CamelCase` afterwards

  ```cpp
  class Foo { ... }
  struct FooBar { ... }
  enum Buz { ... }
  ```

- **Template parameter** should start with a uppercase letter and follow
  `CamelCase` afterwards. Usually they are single uppercase letter.

  ```cpp
  template <typename T>
  template <typename InputIterator, typename ResultType>
  ```

- **Functions** should be lowercase and `snake_case`

  ```cpp
  void clear();
  void open_file();
  void very_long_foo_bar();
  ```

- **Namespaces** should be lowercase and `snake_case`

  ```cpp
  namespace foo {
  ...
  namespace bar {
  ...
  } // namespace bar
  } // namespace foo
  ```

- **Macros** and **Macro-Functions** should be uppercase and `SNAKE_CASE`

  ```cpp
  #define PI 3.14
  #define LOG_ERROR(...)
  ```

> In 'CamelCase', acronyms count as on word: use `Uuid` rather than `UUID`.

> In 'snake\_case' or 'SNAKE\_CASE', a word should never consist of a single
> letter unless it is the last word. So, write `btree_map` rather than
> `b_tree_map`, but `PI_2` rather than `PI2`. Prefixes are not part of a word
> and must stay separated.

#### Avoid Redundant Prefixes

- Names of items within a namespace should not be prefixed with that namespace's
  name.

  ```cpp
  // GOOD
  namespace foo {
      struct Error { ... }
  } // namespace foo

  // BAD
  namespace foo {
      struct FooError { ... }
  } // namespace foo
  ```

- Names of files within a library should not be prefixed with that library's
  name.

  ```cpp
  // GOOD
  .
  └── libutil
     ├── converter.hpp
     ├── enums.hpp
     └── strings.hpp

  // BAD
  .
  └── libutil
     ├── libutil_converter.hpp
     ├── libutil_enums.hpp
     └── libutil_strings.hpp
  ```

This convention avoids stuttering (like io::IoError). Library clients can rename
the namespace and define the include style to avoid clashes.

#### Getter/Setter Methods

- **Getter methods** should **not** be prefixed with `get_`, instead just use
  the corresponding variable name.
- **Setter methods** should be prefixed with `set_`.

  ```cpp
  class Error {
      int m_error_code;
  public:
      int error_code() const noexcept
      {
          return m_error_code;
      }

      void set_error_code(int value) noexcept
      {
          m_error_code = value;
      }
  }
  ```

#### Variable/Function Prefixes

- Simple boolean predicates should be prefixed with `is_` or another short
  question word, e.g. `is_empty`.
- Converter functions should be prefixed with `as_` / `to_` / `from_` depending
  on the cost and direction, e.g. `as_bytes` / `to_string` / `from_uint`.
  - Prefix `as_` has no costs and gives a view to the data, which is a no-op.
  - Prefix `to_` is expensive because it copies the data to a new type.

#### File Naming / Extensions

- **File names** should be written lowercase and `snake_case`
- **User-generated** files should use `.cpp` and `.hpp` extensions, which are
  widely recognized by various editors and tools.
- **Tool-generated** files should use `.cxx` and `.hxx` extensions, which helps
  to differentiate them from normal files.

### Includes

- Use double quotes for *local header* and angle brackets for *system header*
- Preferred **#include** order:
  - "main" header (`#include "foo/foo.hpp"`)
  - "project" header (`#include "foo/bar.hpp"`)
  - "dependency" header (`#include "util/util.hpp"`)
  - \<system\> header (`#include <iostream>`)
- Separate each header section with an empty line:

  ```cpp
  #include "foo/foo.hpp"

  #include "foo/bar.hpp"
  #include "foo/buz.hpp"

  #include "util/util.hpp"

  #include <iostream>
  #include <memory>
  #include <cstdlib>
  ```

- Do not include *internal* header in public module header files. Only include
  them in the implementation file (.cpp).

### Include Guards

Header files must contain a distinctly-named include guard to avoid problems
with including the same header multiple times and to prevent conflicts with
headers from other projects. With C-style header guards this can be quiet
error-prone. Because of that `#pragma once` should be used which is
quasi-standard across many compilers. It is short and makes the intent clear.

- Use `#pragma once` instead of C-style header guards.

### Indentation

- In general, reduce indentation wherever possible.
- Do not indent source code inside namespaces. This can avoid some deeply
  nesting and makes it easier to understand the source code.

  ```cpp
  namespace foo {
  class Sample { ... };

  namespace detail {
  class InternalSample { ... };
  } // namespace detail

  bool is_valid() noexcept;
  } // namespace foo
  ```

- Indent preprocessor directives with the `#` character. Pre-ANSI C compiler
  would not allow this but these days they are non-existent.

  ```cpp
  #if defined(__linux__)
      #ifdef DEBUGGING == 1
          #if defined (pic18f2480)
              #define FLASH_MEMORY_END 0x3DC0
          #elif defined (pic18f2580)
              #define FLASH_MEMORY_END 0x7DC0
          #else
              #error "Can't set  up flash memory end!"
          #endif
      #else
          #define FLASH_MEMORY_END 0x7DC0
      #endif

  extern "C"
  {
      #include <sys/ioctl.h>
      #include <sys/socket.h>
      #include <sys/types.h>
  }
  #endif
  ```

- In **functions** align preprocessor directives to the left and do not indent
  them (if they are not nested).

  ```cpp
  int some_functions(...) noexcept
  {
      auto some_value = int{100};

  #if defined(__linux__)
      some_value += 77;
  #elif defined(WIN32)
      some_value -= 25;
  #else
      #error Platform not supported!
  #endif

      return some_value;
  }
  ```

### class/struct Keywords

In C++, the `class` and `struct` keywords can be used almost interchangeably.
The only difference is in the default access scope. The `struct` keyword should
be used for POD (Plain Old Data), meaning a data structure which does not
contain any logic on his own.

```cpp
struct SomeData
{
    std::uint32_t address;
    std::uint16_t reserved;
    std::uint16_t count;
};
```

### Lambda Formatting

- Try to format lambdas like normal blocks of code.
- If useful define the return type of the lambda with the
  *trailing return type syntax*.

  ```cpp
  auto foo = [&](Foo a, Foo b) -> bool {
      return a < b;
  };
  ```

### Specifier Placement

- Put `*` and `&` by the type rather than the variable name.

  ```cpp
  int* foo;
  void bar(Foo const& a);
  ```

- Use East-const instead of West-const (easier to read from right to left).

  ```cpp
  Foo const* const*& foo = make();
  // Ref to pointer, to a const pointer, to a const Foo

  auto constexpr separator = '|';
  ```

- When overriding functions only use the `override` specifier and not `virtual`.

  ```cpp
  // on base class
  virtual void foo(Foo a, Foo b) = 0;

  // at derived class
  void foo(Foo a, Foo b) override;
  ```
