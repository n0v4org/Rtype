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
    const char* argv[] = {"r-type_server"};
    int argc = 1;

    Arguments args(argc, argv);
    EXPECT_EQ(args.get_port(), 50000);
    EXPECT_FALSE(args.get_help());
    EXPECT_FALSE(args.get_debug());
}

TEST_F(ArgumentsTest, HelpFlag) {
    const char *argv[] = {"r-type_server", "-h"};
    int argc = 2;

    Arguments args(argc, argv);
    args.parse();
    EXPECT_TRUE(args.get_help());
    EXPECT_FALSE(args.get_debug());
    EXPECT_EQ(args.get_port(), 50000);
}

TEST_F(ArgumentsTest, DebugFlag) {
    const char *argv[] = {"r-type_server", "-v"};
    int argc = 2;

    Arguments args(argc, argv);
    args.parse();

    EXPECT_TRUE(args.get_debug());
    EXPECT_FALSE(args.get_help());
    EXPECT_EQ(args.get_port(), 50000);
}

TEST_F(ArgumentsTest, PortFlag) {
    const char *argv[] = {"r-type_server", "-p", "12345"};
    int argc = 3;

    Arguments args(argc, argv);
    args.parse();
 
    EXPECT_EQ(args.get_port(), 12345);
    EXPECT_FALSE(args.get_help());
    EXPECT_FALSE(args.get_debug());
}

TEST_F(ArgumentsTest, InvalidPortNonNumeric) {
    const char *argv[] = {"r-type_server", "-p", "abc"};
    int argc = 3;

    Arguments args(argc, argv);
    EXPECT_THROW(args.parse(), ServerError);
}

TEST_F(ArgumentsTest, InvalidPortOutOfRange) {
    const char *argv[] = {"r-type_server", "-p", "70000"};
    int argc = 3;

    Arguments args(argc, argv);
    EXPECT_THROW(args.parse(), ServerError);
}

TEST_F(ArgumentsTest, UnknownFlag) {
    const char *argv[] = {"r-type_server", "-x"};
    int argc = 2;

    Arguments args(argc, argv);
    EXPECT_THROW(args.parse(), ServerError);
}