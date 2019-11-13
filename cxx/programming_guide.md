---
title: C++ Programming Guide
toc: true
---

This page provides programming guidelines for the C++ programming language.

<div class="alert alert-warning">
  <strong>This page is still work in progress.</strong>
</div>

### Think Immutable

By default, every object in C++ is mutable, which means it could change anytime.
But race conditions can not occur on constants and it is easier to reason about
a program when object cannot change their values. Immutability also helps the
compiler to optimize the code.

- Immutable objects and methods are easier to reason about, so make objects
  non-const only when there is a need to change their value.
- Prevents accidental or hard-to-notice change of values.

#### Const As Much As Possible

- Tell the compiler with `const` that a variable or method is immutable.
- Use const ref (`const&`) to prevent the compiler from copying data unnecessarily.
- By default, make **member functions** `const`, unless it changes the object's
  observable state.

  ```cpp
  class Foo {
      int m_size;
  public:
      int size() const // does not modify the object's state
      {
          return m_size;
      }
  }
  ```

- Mark **member variables** `const` if they are not expected to change after
  initialization.

  ```cpp
  class Bar {
      int const m_identifier{0};
  public:
      explicit Bar(int identifier)
        : m_identifier{identifier}
      {}
  }
  ```

> Since a const member variable cannot be assigned a new value, such a class may
> not have a meaningful copy assignment operator.

- Define **objects** with values that **do not change after construction** `const`

  ```cpp
  void f()
  {
      auto x = int{7};
      auto const y = int{9};

      // As x is not const, we must assume that it is modified somewhere in the
      // function ...
  }
  ```

- If possible, pass and return by const ref (`const&`)

  ```cpp
  void do_something(std::string const& str);
  std::string const& return_something();
  ```

- Use `constexpr` for values/functions that can be computed at compile time

  ```cpp
  static constexpr char PATH_SEPARATOR = '/';
  constexpr double z = calc(2); // if calc(2) is a constexpr function
  ```

#### Const Ref Pitfall For Simple Types

Passing and returning by reference leads to pointer operations instead by
much faster passing values in processor registers.

- Do not pass and return simple types by const ref.

#### Reduce Moves, Copies And Reassignments

- Reduce temporary object, which will prevent the compiler from performing a
  move operation.

  ```cpp
  // instead of:
  auto x = foo();
  auto y = bar();
  do_something(x, y);

  // consider:
  do_something(foo(), bar());
  ```

- For simple cases, use the **ternary operator** to reduce reassignments.

  ```cpp
  // GOOD
  auto const some_value = std::string{case_a ? "Value A" : "Value B"};

  // BAD
  std::string some_value;

  if (case_a) {
      some_value = "Value A";
  } else {
      some_value = "Value B";
  }
  ```

- For complex cases, use an **immediately-invoked lambda** to reduce reassignments.

  ```cpp
  // GOOD
  auto const some_value = [&]() -> std::string {
      if (case_a) {
        return "Value A";
      }

      if (case_b) {
        return "Value B";
      }

      return "Value C";
  }();

  // BAD
  std::string some_value;

  if (case_a) {
      some_value = "Value A";
  } else if (case_b) {
      some_value = "Value B";
  } else {
      some_value = "Value C";
  }
  ```

### Compiler Issues

Start with very strict warning settings from the beginning. Trying to raise the
warning level after the project is underway can be painful. Also consider using
the **treat warnings as errors** settings, at least for the CI/CD setup.

- If your code has compiler warnings, something is most probably wrong.
  - e.g. casting values incorrectly, having 'questionable' constructs
- Compiler warnings can cover up legitimate errors in output and make dealing
  with a translation unit difficult.
- Do not use compiler specific extensions like GCC extensions or
  `#pragma region`
- `#pragma clang diagnostic ignored "-Wshadow"` is ok behind compiler checks
- **Use every available and reasonable set of warning options and treat these
  compiler warnings like errors.**

### Portable Code

In almost all cases, it is possible and within reason to write completely
portable code. If there are cases where it isn't possible to write portable
code, isolate it behind a well defined and well documented interface.

- Try to write your code **as portable as possible**.

### Consider Your Return Types

- Returning by **reference** (`&` or `const&`) can have significant performance
  savings when the normal use of the returned value is only for observation.
- Returning by **value** is better for **thread safety** and if the normal use
  of the returned value is to make a copy anyhow, there is no performance lost.
- If your API uses **covariant return types**, they must be returned by `&` or
  `*`.
- **Temporaries** and **local values** should always returned by value.

### Pointer

It is best to avoid using pointers as much as possible. The use of pointers can
lead to confusion of ownership which can directly or indirectly lead to memory
leaks. Also, by avoiding the use of pointers common security holes such as
buffer overruns can be avoided and sometimes eliminated.

Consider the following order for pointers:

- Reference to T (`T&`)
- Unique pointer (`std::unique_ptr<T>`)
- Weak pointer (`std::weak_ptr<T>`)
- Shared pointer (`std::shared_ptr<T>`)
- raw pointer (`T*`)
  - Useful for non owning access where the lifetime of the pointer is guaranteed
  to outlive the object

#### Avoid Raw Memory Access

Raw memory access, allocation and deallocation, are difficult to get correct
without risking memory errors and leaks.

- **Avoid raw memory** and use **smart pointer** instead.

#### Prefer `std::unique_ptr`

The `std::unique_ptr` does not need to keep track of its copies because it is
not copyable. This makes it more efficient than the `std::shared_ptr`.

- If possible use `std::unique_ptr` instead of `std::shared_ptr`.
- Return `std::unique_ptr` from factory functions, then convert the
  `std::unique_ptr` to a `std::shared_ptr` if necessary.

  ```cpp
  std::unique_ptr<FooImpl> factory();

  auto shared_foo = std::shared_ptr<FooImpl>{factory()};
  ```

#### Avoid `std::shared_ptr` Copies

Objects of type `std::shared_ptr` are much more expensive to copy than one would
think. This is because the **reference count** must be **atomic** and
**thread-safe**.

- Avoid temporaries and too many copies of objects.

### Use C++-style Casts

- **Always** use **C++\-style casts** and never use C-style casts.
- C++\-style casts allow more compiler checks and are considerably safer.
- C++\-style casts are also more visible and have the possibility to search for
  them.

  ```cpp
  auto x = double{1.5};

  // GOOD
  auto i = static_cast<int>(x);

  // BAD
  auto i = (int)x;
  ```

### Avoid Macros

Compiler definitions and macros are replaced/removed during preprocessing before the
compiler is ever run. This can make debugging very difficult because the
debugger does not know where the source came from. Furthermore are macros not
obeying scope, type and argument passing rules.

- If not necessary, avoid writing macros and try to decrease the usage of
  macros as much as possible.
- Use **enumerations** over macros.

  ```cpp
  // instead of:
  #define RED 0
  #define BLUE 1
  #define GREEN 2

  // use:
  enum class Color {
      RED = 0,
      BLUE = 1,
      GREEN = 2
  };
  ```

- Use **static constants** over macros.

  ```cpp
  // instead of:
  #define PI 3.14

  // use:
  namespace my_project {
  static constexpr double PI = 3.14;
  } // namespace my_project
  ```

### Avoid Boolean Parameters

- They do not provide any additional meaning while reading the code.
- Either create a **separate function** or pass an **enumeration** that makes the
  meaning more clear.

<div class="alert alert-warning">
  <strong>TODO:</strong> provide a source code example.
</div>

### Avoid `<iostream>`

- Avoid `#include <iostream>` if possible, because many common implementations
  transparently inject a static constructor into every translation unit that
  includes it.
- If `<iostream>` is used avoid `std::endl` which most of the time unnecessarily
  flushes the output stream.
- Alternative to `std::endl` without a flush: **End string with** `'\n'`
  - Use `std::flush` if a flush is required

### Never Use `std::bind`

- `std::bind` is almost always way more overhead (both compile time and runtime)
  than needed.
- Use **lambdas** instead.

  ```cpp
  // GOOD
  auto f = [](std::string const& s) {
      return my_function("hello", s);
  };
  f("world");

  // BAD
  auto f = std::bind(&my_function, "hello", std::placeholders::_1);
  f("world");
  ```

### Never Use `using namespace` In Header Files

- Pollutes the namespace of any source file that `#include`s the header.
- It could lead to namespace clashes, name collisions and decrease portability.
- **Do not** use `using namespace XXX` anywhere in **global scope**.
- Use the `using namespace XXX` directive only in **function scope** if
  necessary.

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

- The **special member function** are the default constructor, copy/move
  constructor, copy/move assignment operator and destructor.
- Declaring any special member function (expect default constructor), even as
  `= default` or `= delete`, will suppress the implicit declaration of a move
  constructor and assignment operator.
- Follow the [Rule of five](https://en.cppreference.com/w/cpp/language/rule_of_three#Rule_of_five)
  and define all special functions even if they will be defaulted. This avoids
  unwanted effect like turning all potential moves into more expensive copies,
  or making a class move-only.

  ```cpp
  class Foo {
  public:
      /// Constructor.
      Foo();
      /// Destructor.
      ~Foo() noexcept = default;

      /// Copy constructor.
      Foo(Foo const& other) = default;
      /// Copy assignment.
      Foo& operator=(Foo const& other) = default;

      /// Move constructor.
      Foo(Foo&& other) noexcept = default;
      /// Move assignment.
      Foo& operator=(Foo&& other) noexcept = default;
  };
  ```

#### Use Copy-And-Swap Idiom

The copy-and-swap idiom is the solution, and elegantly assists the assignment
operator in achieving two things: avoiding code duplication, and providing a
strong exception guarantee.

```cpp
#include <cstddef>
#include <utility>

class DumbArray {
    std::size_t m_size;
    int* m_array;
public:
    DumbArray() = default;
    DumbArray(DumbArray const&) = default;

    DumbArray(DumbArray&& other) noexcept
        : DumbArray()
    {
        swap(*this, other);
    }

    friend void swap(DumbArray& first, DumbArray& second) noexcept
    {
        using std::swap; // enable ADL

        swap(first.m_size, second.m_size);
        swap(first.m_array, second.m_array);
    }

    DumbArray& operator=(DumbArray other) noexcept
    {
        swap(*this, other);
        return *this;
    }

    DumbArray& operator=(DumbArray const& other) noexcept
    {
        DumbArray temp(other);
        swap(*this, temp);
        return *this;
    }
};
```

For more detailed informations see the following stackoverflow post:
https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom

### Loop Pitfalls

#### Beware Of Unnecessary Copies

#### Beware Of `end()` Evaluation Every Time

### Use C++17 Language Features If Possible

#### Constexpr Lambda

- See https://github.com/AnthonyCalandra/modern-cpp-features/blob/master/CPP17.md#constexpr-lambda

#### Nested Namespaces

- See https://github.com/AnthonyCalandra/modern-cpp-features/blob/master/CPP17.md#nested-namespaces

#### Structured Bindings

- See https://github.com/AnthonyCalandra/modern-cpp-features/blob/master/CPP17.md#structured-bindings
- See https://en.cppreference.com/w/cpp/language/structured_binding

#### Statements with Initializer

- See https://github.com/AnthonyCalandra/modern-cpp-features/blob/master/CPP17.md#selection-statements-with-initializer
- See https://en.cppreference.com/w/cpp/language/if

#### New Standard Attributes

- See https://github.com/AnthonyCalandra/modern-cpp-features/blob/master/CPP17.md#new-standard-attributes
- See https://en.cppreference.com/w/cpp/language/attributes

#### Non-Owning Reference To String - `std::string_view`

- See https://github.com/AnthonyCalandra/modern-cpp-features/blob/master/CPP17.md#stdstring_view
- See https://en.cppreference.com/w/cpp/string/basic_string_view

#### Standard For Filesystem Interaction - `std::filesystem`

- See https://github.com/AnthonyCalandra/modern-cpp-features/blob/master/CPP17.md#stdfilesystem
- See https://en.cppreference.com/w/cpp/filesystem

#### Representing Data As Byte - `std::byte`

- See https://github.com/AnthonyCalandra/modern-cpp-features/blob/master/CPP17.md#stdbyte
- See https://en.cppreference.com/w/cpp/types/byte
