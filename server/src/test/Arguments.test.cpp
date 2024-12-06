/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Arguments.test
*/

#include "Arguments.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "ServerError.hpp"

class ArgumentsTest : public ::testing::Test {
protected:
  std::vector<const char *> createArgs(const std::vector<std::string> &args) {
    std::vector<const char *> cArgs;
    for (const auto &arg : args) {
      cArgs.push_back(arg.c_str());
    }
    return cArgs;
  }
};

TEST_F(ArgumentsTest, DefaultValues) {
  const char *argv[] = {"r-type_server"};
  int argc           = 1;

  rtype::Arguments args(argc, argv);
  EXPECT_EQ(args.get_port(), 50000);
  EXPECT_FALSE(args.get_help());
  EXPECT_FALSE(args.get_debug());
}

TEST_F(ArgumentsTest, HelpFlag) {
  const char *argv[] = {"r-type_server", "-h"};
  int argc           = 2;

  rtype::Arguments args(argc, argv);
  args.parse();
  EXPECT_TRUE(args.get_help());
  EXPECT_FALSE(args.get_debug());
  EXPECT_EQ(args.get_port(), 50000);
}

TEST_F(ArgumentsTest, DebugFlag) {
  const char *argv[] = {"r-type_server", "-v"};
  int argc           = 2;

  rtype::Arguments args(argc, argv);
  args.parse();

  EXPECT_TRUE(args.get_debug());
  EXPECT_FALSE(args.get_help());
  EXPECT_EQ(args.get_port(), 50000);
}

TEST_F(ArgumentsTest, PortFlag) {
  const char *argv[] = {"r-type_server", "-p", "12345"};
  int argc           = 3;

  rtype::Arguments args(argc, argv);
  args.parse();

  EXPECT_EQ(args.get_port(), 12345);
  EXPECT_FALSE(args.get_help());
  EXPECT_FALSE(args.get_debug());
}

TEST_F(ArgumentsTest, InvalidPortNonNumeric) {
  const char *argv[] = {"r-type_server", "-p", "abc"};
  int argc           = 3;

  rtype::Arguments args(argc, argv);
  EXPECT_THROW(args.parse(), ServerError);
}

TEST_F(ArgumentsTest, InvalidPortOutOfRange) {
  const char *argv[] = {"r-type_server", "-p", "70000"};
  int argc           = 3;

  rtype::Arguments args(argc, argv);
  EXPECT_THROW(args.parse(), ServerError);
}

TEST_F(ArgumentsTest, UnknownFlag) {
  const char *argv[] = {"r-type_server", "-x"};
  int argc           = 2;

  rtype::Arguments args(argc, argv);
  EXPECT_THROW(args.parse(), ServerError);
}

TEST_F(ArgumentsTest, EmptyFlag) {
  const char *argv[] = {"r-type_client", "-p"};
  int argc           = 2;

  rtype::Arguments args(argc, argv);
  EXPECT_THROW(args.parse(), ServerError);
}

TEST_F(ArgumentsTest, FollowingEmptyFlag) {
  const char *argv[] = {"r-type_client", "-p", "-v"};
  int argc           = 3;

  rtype::Arguments args(argc, argv);
  EXPECT_THROW(args.parse(), ServerError);
}

TEST_F(ArgumentsTest, AllArgs) {
  const char *argv[] = {"r-type_client", "-p", "45555", "-v", "-h"};
  int argc           = 5;

  rtype::Arguments args(argc, argv);
  args.parse();
  EXPECT_EQ(args.get_port(), 45555);
  EXPECT_TRUE(args.get_help());
  EXPECT_TRUE(args.get_debug());
}
