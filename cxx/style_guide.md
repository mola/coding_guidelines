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
  namespace foo
  {
      ...
  namespace bar
  {
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
