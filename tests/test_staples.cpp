#include <gtest/gtest.h>
#include "../lib_staples/staples.h"


TEST(Brackets, CorrectSimple) {
    EXPECT_NO_THROW(check_breckets("()"));
    EXPECT_NO_THROW(check_breckets("[]"));
    EXPECT_NO_THROW(check_breckets("{}"));
}

TEST(Brackets, CorrectNested) {
    EXPECT_NO_THROW(check_breckets("{[()]}"));
    EXPECT_NO_THROW(check_breckets("[(()){()()()}]"));
}

TEST(Brackets, CorrectMixedText) {
    EXPECT_NO_THROW(check_breckets("a(b[c]{d}e)f"));
    EXPECT_NO_THROW(check_breckets("x{y[z]}(q)"));
}

TEST(Brackets, CorrectEmptyString) {
    EXPECT_NO_THROW(check_breckets(""));
}

TEST(Brackets, MissingOpening) {
    EXPECT_THROW(check_breckets("())"), std::invalid_argument);
}

TEST(Brackets, MissingClosing) {
    EXPECT_THROW(check_breckets("((("), std::invalid_argument);
}

TEST(Brackets, WrongOrder) {
    EXPECT_THROW(check_breckets("([)]"), std::invalid_argument);
}

TEST(Brackets, ExtraClosingFirst) {
    EXPECT_THROW(check_breckets(")()"), std::invalid_argument);
}

TEST(Brackets, ExtraClosingMiddle) {
    EXPECT_THROW(check_breckets("(()))(()"), std::invalid_argument);
}

TEST(Brackets, UnbalancedComplex) {
    EXPECT_THROW(check_breckets("([{}])({[)]}"), std::invalid_argument);
}

TEST(Brackets, DeepNesting) {
    std::string s(1000, '(');
    s += std::string(1000, ')');
    EXPECT_NO_THROW(check_breckets(s));
}

TEST(Brackets, DeepNestingMissingOne) {
    std::string s(1000, '(');
    s += std::string(999, ')');
    EXPECT_THROW(check_breckets(s), std::invalid_argument);
}
