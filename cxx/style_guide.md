---
title: C++ Style Guide
toc: true
---

This page provides style guidelines for the C++ programming language.

### Source Code Column Limit

The source code must not exceed **100 character per line**. This limit allows to
have two splits open and still see the whole source code without resizing. The
most used column width is 80 which is a little bit too short for C++ with
lengthy types and function names.

### Whitespace

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

#### Do Not Use Whitespace For Alignment

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

### Indentation

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

### Always Use Trailing Return Type

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

### Opening Braces Always Go On The Same Line

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

### Comments

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

- Add a comment to the **end of a namespace** which helps the readability and
  makes it easier to find out which brace closes a namespace.

  ```cpp
  namespace foo {
  ...
  namespace bar {
  ...
  } // namespace bar
  } // namespace foo
  ```

#### Use Doxygen For Documentation Comments

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

### Naming Conventions

Poorly-chosen names can mislead the reader and cause bugs. Pick names that match
the semantics and role of the underlying entities, withing reason. Avoid
abbreviations unless they are well known e.g from a protocol specification.

#### General Conventions

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

- **Global variables** should be prefixed with `g_` and follow otherwise the
  normal variable naming.

  ```cpp
  static char constexpr g_path_separator = '/';
  ```

- **Enumerators** should be prefixed with `e_` and follow otherwise the normal
  variable naming.

  ```cpp
  enum class Status {
      e_error,
      e_success,
      e_idle,
      e_in_progress
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

#### Variable/Function Prefixes

- Simple boolean predicates should be prefixed with `is_` or another short
  question word, e.g. `is_empty`.
- Converter functions should be prefixed with `as_` / `to_` / `from_` depending
  on the cost and direction, e.g. `as_bytes` / `to_string` / `from_uint`.
  - Prefix `as_` has no costs and gives a view to the data, which is a no-op.
  - Prefix `to_` is expensive because it copies the data to a new type.

#### Getter/Setter Methods

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

#### class/struct Keywords

In C++, the `class` and `struct` keywords can be used almost interchangeably.
The only difference is in the default access scope. The `struct` keyword should
be used for POD (Plain Old Data), meaning a data structure which does not
contain any logic on his own.

```cpp
struct SomeData {
    std::uint32_t address;
    std::uint16_t reserved;
    std::uint16_t count;
};
```

#### File Naming / Extensions

- **File names** should be written lowercase and `snake_case`.
- **User-generated** files should use `.cpp` and `.hpp` extensions, which are
  widely recognized by various editors and tools.
- **Tool-generated** files should use `.cxx` and `.hxx` extensions, which helps
  to differentiate them from normal files.

#### Avoid Redundant Namespace/Filename Prefixes

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

### Includes

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

#### Include Guards

Header files must contain a **distinctly-named** include guard to avoid problems
with including the same header multiple times and to prevent conflicts with
headers from other projects. With **C-style** header guards this can be quiet
**error-prone**. Because of that `#pragma once` should be used which is
quasi-standard across many compilers. It is short and makes the intent clear.

- Use `#pragma once` instead of C-style header guards.

### Specifier Placement

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

### Format Lambdas Like Blocks Of Code

- Try to format lambdas like normal blocks of code.
- If useful define the return type of the lambda with the
  *trailing return type syntax*.

  ```cpp
  auto foo = [&](Foo a, Foo b) -> bool {
      return a < b;
  };
  ```

### Sample Of Formatted Source Code

The source file can be found under [cxx/assets/clang\_format\_sample.cpp](https://git.sr.ht/~sblumentritt/coding_guidelines/tree/master/cxx/assets/clang_format_sample.cpp).

```cpp
// This is a sample file to demonstrate the clang-format config.

// NOTE: This sample does not necessarily conform to every aspect
// of the style guidelines, as this would require clang-tidy
// which needs a working source file. Things like naming
// convention, return types or always braces may not be consistent.

// IncludeBlocks: Preserve
// SortIncludes: true
#include <cstdlib>
#include <iostream>

#include <algorithm>
#include <cstdio>
#include <ctime>
#include <functional>
#include <iterator>
#include <map>
#include <string>
#include <vector>

// IndentPPDirectives: BeforeHash
#ifdef FOO
    #ifdef BAR
        #include <foo>
    #endif
#endif

// AlignConsecutiveMacros: false
#define BIT_MASK 0xDEADBEAF
#define SHORT_NAME 42
#define LONGER_NAME 0x007f
#define EVEN_LONGER_NAME (2)
#define FOO(x) ((x) * (x))
#define BAR(y, z) ((y) + (z))

// AlignEscapedNewlines: Left
#define MULTILINE_DEF(a, b)           \
    if ((a) > 2) {                    \
        auto temp = (b) / 2;          \
        (b) += 10;                    \
        some_function_call((a), (b)); \
    }

// CompactNamespaces: false
// NamespaceIndentation: None
namespace level_one_namespace {
namespace level_two_namespace {

namespace {
int g_anonymous;
} // namespace

// AlwaysBreakTemplateDeclarations: Yes
template <typename T, int size>
auto is_sorted(T (&array)[size]) -> bool {
    return std::adjacent_find(array, array + size, std::greater<T>()) == array + size;
}

// AlwaysBreakAfterReturnType: None
// BinPackParameters: false
auto do_somethings_and_return(std::uint32_t long_name_for_parameter_1,
                              double long_name_for_parameter_2,
                              float const& long_name_for_parameter_3,
                              std::map<std::string, std::int32_t> const& long_name_for_parameter_4)
    -> std::vector<uint32_t> {
    // ReflowComments: true
    // This is a really really long comment which does not fit on one line and needs to be reflowed
    // to not break the restrictions of 100 character per line.

    // AlignConsecutiveDeclarations: false
    int decl_aaa = 12;
    float decl_b = 23;
    std::string delc_ccc = "23";

    // AlignConsecutiveAssignments: false
    auto assign_aaaa = 12;
    auto assign_b = 23;
    auto assign_ccc = 23;

    // AlignTrailingComments: false
    int trail_a; // comment for trail_a
    int trail_b = 2; // comment for trail_b

    // AllowShortLambdasOnASingleLine: Empty
    auto lambda = []([[maybe_unused]] int a) {};
    auto lambda2 = [](int a) {
        return a;
    };

    // PointerAlignment: Left
    char const* some_pointer = "Hello";

    // SpacesInAngles: false
    std::vector<std::pair<std::string, int>> list;

    // SpaceBeforeParens: ControlStatements
    if (long_name_for_parameter_1 == 0) { // comment: SpacesBeforeTrailingComments: 1
        // SpaceAfterCStyleCast: true
        // SpacesInCStyleCastParentheses: false
        auto some_nonconst_pointer = (char*) some_pointer;
    } else if (3456 % 7 == 3) {
        std::cout << "You are in the 'else if' branch."
                  << "Say: '" << some_pointer << "' three times" << '\n'
                  << std::flush;
    } // some weird trailing else comment that clang-format does not touch
    else {
        // ...
    }

    // AllowShortIfStatementsOnASingleLine: Never
    if (decl_aaa == 'a') {
        decl_aaa = 'b';
    }

    // AllowShortLoopsOnASingleLine: false
    while (decl_b < 5) {
        decl_b++;
    }

    // AlignOperands: true
    auto long_name_for_local_variable_1 = long_name_for_parameter_1
                                          + static_cast<std::uint32_t>(long_name_for_parameter_3);

    auto long_name_for_local_variable_2 = long_name_for_local_variable_1 * 7 + 4 % 235124 > 275645
                                              ? long_name_for_parameter_1 + 897234
                                              : static_cast<std::uint32_t>(
                                                    long_name_for_parameter_3)
                                                    % 1293402;

    auto very_very_very_very_very_very_very_long_name = std::uint32_t{0};

    // BreakBeforeTernaryOperators: true
    auto break_val = very_very_very_very_very_very_very_long_name ? 42
                                                                  : long_name_for_local_variable_1;

    // BreakBeforeBinaryOperators: All
    break_val = (very_very_very_very_very_very_very_long_name * 2 == long_name_for_local_variable_1)
                && (long_name_for_parameter_3 > long_name_for_local_variable_2);

    if (decl_b > 5. && decl_aaa != 42 && (decl_aaa <= decl_b || assign_b > assign_ccc)
        || assign_aaaa % 42 || long_name_for_local_variable_1 % 873 && assign_aaaa % 42
        || long_name_for_local_variable_2 % 873 || decl_aaa * 12312 % 23485 != 9873
        || some_pointer != nullptr) {
        printf("Huh!\n");
    }

    switch (delc_ccc[0]) {
    // AllowShortCaseLabelsOnASingleLine: false
    // IndentCaseLabels: false
    case 'a':
        delc_ccc[0] = 'q';
        break;
    case 'y':
    case 'z':
        // Do something here
        break;
    default: {
        [[maybe_unused]] auto cycle = 'd';
        break;
    }
    }

    // SpaceBeforeRangeBasedForLoopColon: true
    for (auto const& i : long_name_for_parameter_4) {
        printf("A short function call %s %s %d - %d\n", "short", "ext", i.second, BIT_MASK);

        // BinPackArguments: false
        // AlignAfterOpenBracket: Align
        printf("A long function call %s %s %d - %d\n",
               "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
               "yyyyyyyyyyyyyyyyyy",
               i.second,
               BIT_MASK);
    }

    return {};
}

// FixNamespaceComments: true
} // namespace level_two_namespace
} // namespace level_one_namespace

class SampleClass {
    // AccessModiferOffset: -4
public:
    // BreakConstructorInitializers: BeforeComma
    // ConstructorInitializerAllOnOneLineOrOnePerLine: false
    // ConstructorInitializerIndentWidth: 2
    SampleClass()
      : m_a_variable{4}
      , m_b_variable{4} {}

    explicit SampleClass(int a)
      : m_a_variable{a}
      , m_b_variable{42}
      , m_a_really_really_long_variable_name{4} {
        printf("Hello ");
    }

    ~SampleClass() noexcept = default;

    // AllowShortFunctionsOnASingleLine: Empty
    auto do_nothing() -> void {}

    auto get_one_line_function() -> int {
        return 0;
    }

    // long function declarations
    auto many_parameter_in_funtion(unsigned arg_with_long_name,
                                   char arg2,
                                   unsigned long long another_long_name) -> int;

    auto many_long_parameter_in_funtion(
        unsigned a_really_really_long_variable_name,
        char a_really_long_variable_name,
        unsigned long long another_really_really_long_variable_name_to_trigger_wrapping) -> int;

protected:
    struct {
        std::string secret_name;
        std::uint8_t hidden_age;
    } protected_secrets;

private:
    int m_a_variable;
    long m_b_variable;
    short m_c_variable{49};
    long m_a_really_really_long_variable_name;
};

namespace test::runner {
auto main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) -> int {
    // preferred over return 0
    return EXIT_SUCCESS;
}
} // namespace test::runner
```
