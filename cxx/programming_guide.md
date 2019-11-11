---
title: C++ Programming Guide
toc: true
---

This page provides programming guidelines for the C++ programming language.

<div class="alert alert-warning">
  <strong>This page is still work in progress.</strong>
</div>

### Think Immutable

#### Const As Much As Possible

#### Const Ref Pitfall By Simple Types

#### Reduce Copies And Reassignments

### Compiler Issues

### Portable Code

### Consider Your Return Types

### Use Smart Pointer

#### Avoid Raw Memory Access

#### Prefer `std::unique_ptr`

### Use C++-style Casts

### Avoid Macros

### Avoid Boolean Parameters

### Avoid `<iostream>`

### Never Use `std::bind`

### Never Use `using namespace` In Header Files

### Rules Of Thumb

#### Use `auto` Keyword

#### Prefer Pre-Increment To Post-Increment

#### Difference Between Char And String

#### Use Early Exits

### Includes

### Classes

#### Default Values With Brace Initialization

#### Initializer List

#### Single Parameter Constructors

#### Conversion Operators

#### Use `noexcept` And `const` On Functions

#### Rule Of Five

#### Use Copy-And-Swap Idiom

### Loop Pitfalls

#### Beware Of Unnecessary Copies

#### Beware Of `end()` Evaluation Every Time

### Use C++17 Language Features If Possible

#### Constexpr Lambda

#### Nested Namespaces

#### Structured Bindings

#### Statements with Initializer

#### New Standard Attributes

#### Non-Owning Reference To String - `std::string_view`

#### Standard For Filesystem Interaction - `std::filesystem`

#### Representing Data As Byte - `std::byte`
