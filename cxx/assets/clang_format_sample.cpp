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
