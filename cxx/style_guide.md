This page provides style guidelines for the C++ programming language.

[[_TOC_]]

# Source Code Column Limit

The source code must not exceed **100 character per line**. This limit allows to
have two splits open and still see the whole source code without resizing. The
most used column width is 80 which is a little bit too short for C++ with
lengthy types and function names.

# Whitespace

- Use **spaces** instead of tabs.
- Use **4 spaces** for indentation and do not re-indent a whole source file if
  you prefer a different indentation level.
- Do not commit changes that include trailing whitespace at the end of lines or
  files. Let your editor of choice automatically remove trailing whitespace when
  saving a file.
- Use a **space** before opening parenthesis in control flow statements.

  ```cpp
  if (true) { ... }
  while (true) { ... }
  for (...) { ... }
  ```

- Use **spaces** around binary operations, including the equals sign.

  ```cpp
  auto foo = (1 << 8) | 2;

  auto bar = x + y;

  if (foo || x < 0) { ... }
  ```

- Use a **space** after colons and commas.

  ```cpp
  class Foo: public Bar {};

  foo(bar, baz);
  ```

- Use a **space** after the opening and before the closing brace for single line
  blocks.

  ```cpp
  auto do_something() -> int { return 42; }

  struct Foo { int x{0}; int y{1}; }
  ```

## Do Not Use Whitespace For Alignment

Idiomatic code should not use extra whitespace in the middle of a line to
provide alignment.

```cpp
// GOOD
struct Foo {
    int x = 42;
    float some_value = 0.42f;
};

auto y = 0;
auto tmp = 1;

// BAD
struct Foo {
    int x            = 42;
    float some_value = 0.42f;
};

auto y   = 0;
auto tmp = 1;
```

# Indentation

- In general, reduce indentation wherever possible.
- **Do not** indent source code **inside** namespaces. This can avoid some
  deeply nesting and makes it easier to understand the source code.

  ```cpp
  namespace foo {
  class Sample { ... };

  namespace detail {
  class InternalSample { ... };
  } // namespace detail

  auto is_valid() noexcept -> bool;
  } // namespace foo
  ```

- Indent preprocessor directives with the `#` character. Pre-ANSI C compiler
  would not allow this but these days they are non-existent.

  ```cpp
  #if defined(__linux__)
      #ifdef DEBUGGING == 1
          #if defined(pic18f2480)
              #define FLASH_MEMORY_END 0x3DC0
          #elif defined(pic18f2580)
              #define FLASH_MEMORY_END 0x7DC0
          #else
              #error "Can't set  up flash memory end!"
          #endif
      #else
          #define FLASH_MEMORY_END 0x7DC0
      #endif

  extern "C" {
      #include <sys/ioctl.h>
      #include <sys/socket.h>
      #include <sys/types.h>
  }
  #endif
  ```

- In **functions** align preprocessor directives to the left and do not indent
  them (if they are not nested).

  ```cpp
  auto some_functions(...) noexcept -> int
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

# Always Use Trailing Return Type

**Always** use **trailing return type** to be consistent with all use cases e.g.
lambdas / templates where the return type depends on the argument type.

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

# Opening Braces Always Go On The Same Line

Opening braces should **always** go on the **same line**. This reduces 'wasted'
line because lines with only an opening brace do not help with the readability
and distort the source code in its length.

```cpp
namespace foo {

class X : public Y {
    ...
}

auto bar() -> void {
    ...

    if (x) {
        ...
    } else {
        ...
    }

    do {
      ...
    } while (y);
}
} // namespace foo
```

# Comments

- Avoid C style block comments (`/* ... */`), which have nesting problems.
- Prefer C++ style comments (`//` for normal comments, `///` for documentation
  comments).
- Commenting out large blocks of code is highly discouraged. Use `#if 0` and
  `#endif` but only for debugging purpose.

  ```cpp
  // GOOD
  auto do_something() -> std::string {
  #if 0
      std::string some_value;
      if (case_a) {
          some_value = "Value A";
      } else {
          some_value = "Value B";
      }
  #endif

      return "42";
  }

  // BAD
  auto do_something() -> std::string {
  /*
      std::string some_value;
      if (case_a) {
          some_value = "Value A";
      } else {
          some_value = "Value B";
      }
  */

      return "42";
  }
  ```

- Add a comment to the **end of a namespace** which helps to improve the
  readability as it is easier to find out which brace closes a namespace.

  ```cpp
  namespace foo {
  ...
  namespace bar {
  ...
  } // namespace bar
  } // namespace foo
  ```

## Use Doxygen For Documentation Comments

- Header files should **always** be documented **properly** with Doxygen
  comments. This helps other people to figure out the use of the interface
  without reading the actual implementation.
- Doxygen comments are prefixed with **three slashes** (`///`)
- Use Latex-style `\` instead of Javadoc-style `@` for Doxygen commands.
- The first line should be a single-line short sentence providing a summary of
  the code. The `\brief` specifier **should not be added** because Doxygen
  already interprets the first sentence as description.
- All describing documentation comments (summary line/long description) should
  begin with a capital letter and end with a period, question mark, or
  exclamation point.
- Prefer **full sentences** to fragments.
- Add an **empty line** between description, parameter and return documentation.
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
  auto is_valid(Foo foo) -> bool;
  ```

# Naming Conventions

Poorly-chosen names can mislead the reader and cause bugs. Pick names that match
the semantics and role of the underlying entities, within reason. Avoid
abbreviations unless they are well known e.g from a protocol specification.

## General Conventions

Use descriptive names, and be consistent in the style. In general, use
`CamelCase` for 'type-level' constructs (classes and enums) and `snake_case`
for 'value-level' constructs (functions and variables). The advantage of
`snake_case` is that it can also work with spell checkers.

- **Variables** should be lowercase and `snake_case`.

  ```cpp
  int number_of_bytes;
  std::string name;
  ```

- **Private member variables** should be prefixed with `m_` to distinguish them
  from normal variables.

  ```cpp
  class Foo {
  private:
      int m_number_of_bytes;
      std::string m_name;
  };
  ```

- **Function arguments with the same name as public member** should be prefixed
  with `a_` (as in argument).

  ```cpp
  struct Dimension {
    int width;
    int height;

    Dimension(int a_width, int a_height) : width{a_width}, height{a_height} {}
  };
  ```

- **Global / Static variables** should follow the normal variable naming.

  ```cpp
  static char constexpr path_separator = '/';
  ```

- **Enumerators** should follow the normal variable naming.

  ```cpp
  enum class Status {
      error,
      success,
      idle,
      in_progress
  }
  ```

- **Type names** (including classes, structs, enums, typedefs, etc.) should
  start with a uppercase letter and follow `CamelCase` afterwards.

  ```cpp
  class Foo { ... }
  struct FooBar { ... }
  enum class Buz { ... }
  ```

- **Template parameter** should start with a uppercase letter and follow
  `CamelCase` afterwards. Usually they are single uppercase letter.

  ```cpp
  template <typename T>
  template <typename InputIterator, typename ResultType>
  ```

- **Functions** should be lowercase and `snake_case`.

  ```cpp
  auto clear() -> void;
  auto open_file() -> void;
  auto very_long_foo_bar() -> void;
  ```

- **Namespaces** should be lowercase and `snake_case`.

  ```cpp
  namespace foo {
  ...
  namespace bar_baz {
  ...
  } // namespace bar_baz
  } // namespace foo
  ```

- **Macros** and **Macro-Functions** should be uppercase and `SNAKE_CASE`.

  ```cpp
  #define PI 3.14
  #define LOG_ERROR(...)
  ```

> In 'CamelCase', acronyms count as on word: use `Uuid` rather than `UUID`.

> In 'snake\_case' or 'SNAKE\_CASE', a word should never consist of a single
> letter unless it is the last word. So, write `btree_map` rather than
> `b_tree_map`, but `PI_2` rather than `PI2`. Prefixes are not part of a word
> and must stay separated.

## Variable/Function Prefixes

- Simple boolean predicates should be prefixed with `is_` / `has_` or another
  short question word, e.g. `is_empty` / `has_bytes`.
- Converter functions should be prefixed with `as_` / `to_` / `from_` / `into_`
  depending on the cost and direction, e.g. `as_bytes` / `to_string` /
  `from_uint` / `into_raw_fd`.
  - Prefix `as_` has no costs and gives a view to the data, which is a no-op.
  - Prefix `to_` is expensive because it copies the data to a new type.
  - Prefix `from_` conversion from another type.
  - Prefix `into_` potentially expensive conversion which consumes the data.

## Getter/Setter Methods

- **Getter methods** should **not** be prefixed with `get_`, instead just use
  the corresponding variable name.
- **Setter methods** should be prefixed with `set_`.

  ```cpp
  class Error {
  public:
      auto error_code() const noexcept -> int {
          return m_error_code;
      }

      auto set_error_code(int value) noexcept -> void {
          m_error_code = value;
      }

  private:
      int m_error_code;
  }
  ```

## class/struct Keywords

In C++, the `class` and `struct` keywords can be used almost interchangeably.
From a language perspective `class` and `struct` differ only in the default
visibility of their members.

Most guidelines define that the `struct` keyword should only be used for POD
(Plain Old Data), meaning a data structure which does not contain any logic on
his own.

```cpp
struct SomeData {
    std::uint32_t address;
    std::uint16_t reserved;
    std::uint16_t count;
};
```

Personally the `class` keyword should be avoided and only be used in conjunction
with the `enum` keyword. As the preferred scope order is `public` -> `protected`
-> `private` and most of the time an inheritance is `public` the `class` keyword
usage needs more writing in total which can be avoided with the `struct`
keyword.

```cpp
struct Derived : Base {
  Derived(int x, int y);
  ~Derived() = default;

  auto do_something() -> void;

private:
  int m_x;
  int m_y;
};

// vs.

class Derived : public Base {
public:
  Derived(int x, int y);
  ~Derived() = default;

  auto do_something() -> void;

private:
  int m_x;
  int m_y;
};
```

## File Naming / Extensions

- **File names** should be written lowercase and `snake_case`.
- **User-generated** files should use `.cpp` and `.hpp` extensions, which are
  widely recognized by various editors and tools.
- **Tool-generated** files should use `.cxx` and `.hxx` extensions, which helps
  to differentiate them from normal files.

## Avoid Redundant Namespace/Filename Prefixes

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

# Includes

- Use double quotes for *local header* and angle brackets for *system header*.
- Preferred **#include** order:
  1. "main" header (`#include "foo/foo.hpp"`)
  2. "project" header (`#include "foo/bar.hpp"`)
  3. "dependency" header (`#include "util/util.hpp"`)
  4. \<system\> header (`#include <iostream>`)
- **Separate** each header section with an **empty line**.

  ```cpp
  #include "foo/foo.hpp"

  #include "foo/bar.hpp"
  #include "foo/buz.hpp"

  #include "util/util.hpp"

  #include <iostream>
  #include <memory>
  #include <cstdlib>
  ```

- **Do not** include *internal* header in public module header files. Only
  include them in the implementation file (.cpp).

## Include Guards

Header files must contain a **distinctly-named** include guard to avoid problems
with including the same header multiple times and to prevent conflicts with
headers from other projects. With **C-style** header guards this can be quiet
**error-prone**. Because of that `#pragma once` should be used which is
quasi-standard across many compilers. It is short and makes the intent clear.

- Use `#pragma once` instead of C-style header guards.

# Specifier Placement

- Put `*` and `&` by the type rather than the variable name.

  ```cpp
  int* foo;
  auto bar(Foo const& a) -> void;
  ```

- Use **East-const** instead of **West-const** (easier to read from right to
  left).

  ```cpp
  Foo const* const*& foo = make();
  // Ref to pointer, to a const pointer, to a const Foo

  auto constexpr separator = '|';
  ```

- When overriding functions only use the `override` specifier and not `virtual`.

  ```cpp
  // on base class
  virtual auto foo(Foo a, Foo b) -> void = 0;

  // at derived class
  auto foo(Foo a, Foo b) override -> void;
  ```

- **Access specifier** must only be used once per class and should be used in
  the following order:
  1. `public`
  2. `protected`
  3. `private`

  ```cpp
  // GOOD
  class Foo {
  public:
      Foo() = default;
      auto do_something() -> void;
      ...

  protected:
      ...

  private:
      int m_bar{1};
      ...
  };

  // BAD
  class Foo {
      int m_bar{1};

  public:
      Foo() = default;
      ...

  protected:
      ...

  public:
      auto do_something() -> void;

  private:
      ...
  };
  ```

# Format Lambdas Like Blocks Of Code

- Try to format lambdas like normal blocks of code.
- If useful define the return type of the lambda with the
  *trailing return type syntax*.

  ```cpp
  auto foo = [&](Foo a, Foo b) -> bool {
      return a < b;
  };
  ```

# Automation And Sample Of Formatted Source Code

Most of the mentioned guidelines can be automated with [clang-format][]. A
config file for clang-format can be found under [cxx/assets/.clang-format](assets/.clang-format)
and a source file to demonstrate the usage can be found under
[cxx/assets/clang\_format\_sample.cpp](assets/clang_format_sample.cpp).

[clang-format]: https://clang.llvm.org/docs/ClangFormat.html
