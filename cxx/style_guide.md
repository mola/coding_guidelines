---
title: C++ Style Guide
toc: true
---

This page provides style guidelines for the C++ programming language.

<div class="alert alert-warning">
  <strong>This page is still work in progress.</strong>
</div>

### Source Code Column Limit

The source code must not exceed 100 character. This limit allows to have two
splits open and still see the whole source code without resizing. The most used
column width is 80 which is a little bit too short for C++ with lengthy types
and function names.

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
  begin with a capital letter and end with a period, question mark, or exclamation
  point.
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

### Braces

- Opening braces should go on the same line **except for functions**.

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

<div class="alert alert-warning">
  <strong>TODO:</strong> describe why 'snake_case' is the preferred naming convention.
</div>

Use descriptive names, and be consistent in the style. In general, use
`CamelCase` for 'type-level' constructs (classes and enums) and `snake_case`
for 'value-level' constructs (functions and variables). More precisely:

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

- **Constant variables** should be uppercase and `SNAKE_CASE`

  ```cpp
  static constexpr char PATH_SEPARATOR = '/';
  ```

- **Macros** and **Macro-Functions** should be uppercase and `SNAKE_CASE`

  ```cpp
  #define PI 3.14
  #define LOG_ERROR(...)
  ```

<div class="alert alert-warning">
  <strong>TODO:</strong> define naming convention for 'namespaces' and
  'enumerators'!
</div>
