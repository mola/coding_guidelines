# Coding Guidelines

[[_TOC_]]

This repository holds guidelines for a range of different programming languages.
These guidelines consist of a **style guide** which defines the general source
code format and naming of e.g. variables. Furthermore there is a **programming
guide** which defines general rules, do's and don'ts to follow when writing
source code.

> The purpose of this repository is to help developers to achieve a more uniform
> style across code bases.

## Golden Rule

Use common sense and be consistent. If your are extending, enhancing, or bug
fixing existing source code, use the style that is already being used.
This allows the source code to stay uniform and easy to follow. The point of
having coding guidelines is to have a common base for writing code. It should
help to provide a uniform code base across a project or organization/company
and help other developers to understand the code base more efficiently.

## Guides

For C++:

- [Style Guide](cxx/style_guide.md)
- [Programming Guide](cxx/programming_guide.md)
- [Tool Guide](cxx/tool_guide.md)

For CMake:

- [Style Guide](cmake/style_guide.md)
- [Programming Guide](cmake/programming_guide.md)

## Inspiration

These coding guidelines were inspired by other already available guidelines
namely:

For C++:

- [LLVM Code Standards](https://llvm.org/docs/CodingStandards.html)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [Chromium C++ style guide](https://chromium.googlesource.com/chromium/src/+/master/styleguide/c++/c++.md)
- [C++ Best Practices](https://lefticus.gitbooks.io/cpp-best-practices/content/)
- [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md)
- [Rust Style Guidelines](https://doc.rust-lang.org/1.12.0/style/README.html)

For CMake:

- [cmake-developer](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html)
- [cmake-language](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html)
- [KDE CMake Coding Style](https://community.kde.org/Policies/CMake_Coding_Style)
- [ROS CMake Coding Standards](https://docs.ros.org/jade/api/catkin/html/user_guide/standards.html)
- [boost-cmake](https://github.com/boost-cmake/bcm/wiki/Cmake-best-practices-and-guidelines)
- [Modern CMake](https://cliutils.gitlab.io/modern-cmake/)
- [Effective Modern CMake](https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1)
- [Professional CMake](https://crascit.com/professional-cmake/)

## License

The project is licensed under the MIT license. See [LICENSE](LICENSE) for more information.
