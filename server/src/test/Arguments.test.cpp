#include <gtest/gtest.h>
#include "Arguments.hpp"
#include "ServerError.hpp"

class ArgumentsTest : public ::testing::Test {
protected:
    std::vector<const char*> createArgs(const std::vector<std::string>& args) {
        std::vector<const char*> cArgs;
        for (const auto& arg : args) {
            cArgs.push_back(arg.c_str());
        }
        return cArgs;
    }
};

TEST_F(ArgumentsTest, DefaultValues) {
    const char* argv[] = {"program"};
    int argc = 1;

    Arguments args(argc, const_cast<char**>(argv));
    EXPECT_EQ(args.get_port(), 50000);
    EXPECT_FALSE(args.get_help());
    EXPECT_FALSE(args.get_debug());
}

TEST_F(ArgumentsTest, HelpFlag) {
    auto argv = createArgs({"program", "-h"});
    int argc = argv.size();

    Arguments args(argc, const_cast<char**>(argv.data()));
    args.parse();

    EXPECT_TRUE(args.get_help());
    EXPECT_FALSE(args.get_debug());
    EXPECT_EQ(args.get_port(), 50000);
}

TEST_F(ArgumentsTest, DebugFlag) {
    auto argv = createArgs({"program", "-v"});
    int argc = argv.size();

    Arguments args(argc, const_cast<char**>(argv.data()));
    args.parse();

    EXPECT_TRUE(args.get_debug());
    EXPECT_FALSE(args.get_help());
    EXPECT_EQ(args.get_port(), 50000);
}

TEST_F(ArgumentsTest, PortFlag) {
    auto argv = createArgs({"program", "-p", "12345"});
    int argc = argv.size();

    Arguments args(argc, const_cast<char**>(argv.data()));
    args.parse();

    EXPECT_EQ(args.get_port(), 12345);
    EXPECT_FALSE(args.get_help());
    EXPECT_FALSE(args.get_debug());
}

TEST_F(ArgumentsTest, InvalidPortNonNumeric) {
    auto argv = createArgs({"program", "-p", "abc"});
    int argc = argv.size();

    Arguments args(argc, const_cast<char**>(argv.data()));
    EXPECT_THROW(args.parse(), ServerError);
}

TEST_F(ArgumentsTest, InvalidPortOutOfRange) {
    auto argv = createArgs({"program", "-p", "70000"});
    int argc = argv.size();

    Arguments args(argc, const_cast<char**>(argv.data()));
    EXPECT_THROW(args.parse(), ServerError);
}

TEST_F(ArgumentsTest, UnknownFlag) {
    auto argv = createArgs({"program", "-x"});
    int argc = argv.size();

    Arguments args(argc, const_cast<char**>(argv.data()));
    EXPECT_THROW(args.parse(), ServerError);
}