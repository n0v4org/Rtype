/*
** EPITECH PROJECT, 2024
** client
** File description:
** Arguments.test
*/

#include "Arguments.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "ClientError.hpp"

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
  const char *argv[] = {"r-type_client"};
  int argc           = 1;

  client::Arguments args(argc, argv);
  EXPECT_EQ(args.get_port(), 50001);
  EXPECT_EQ(args.get_ip(), "127.0.0.1");
  EXPECT_FALSE(args.get_help());
}

TEST_F(ArgumentsTest, HelpFlag) {
  const char *argv[] = {"r-type_client", "-h"};
  int argc           = 2;

  client::Arguments args(argc, argv);
  args.parse();
  EXPECT_TRUE(args.get_help());
  EXPECT_EQ(args.get_ip(), "127.0.0.1");
  EXPECT_EQ(args.get_port(), 50001);
}

TEST_F(ArgumentsTest, IpFlag) {
  const char *argv[] = {"r-type_client", "-ip", "10.255.14"};
  int argc           = 3;

  client::Arguments args(argc, argv);
  args.parse();

  EXPECT_EQ(args.get_ip(), "10.255.14");
  EXPECT_FALSE(args.get_help());
  EXPECT_EQ(args.get_port(), 50001);
}

TEST_F(ArgumentsTest, PortFlag) {
  const char *argv[] = {"r-ClientError", "-p", "12345"};
  int argc           = 3;

  client::Arguments args(argc, argv);
  args.parse();

  EXPECT_EQ(args.get_port(), 12345);
  EXPECT_FALSE(args.get_help());
  EXPECT_EQ(args.get_ip(), "127.0.0.1");
}

TEST_F(ArgumentsTest, InvalidPortNonNumeric) {
  const char *argv[] = {"r-type_client", "-p", "abc"};
  int argc           = 3;

  client::Arguments args(argc, argv);
  EXPECT_THROW(args.parse(), ClientError);
}

TEST_F(ArgumentsTest, InvalidPortOutOfRange) {
  const char *argv[] = {"r-type_client", "-p", "70000"};
  int argc           = 3;

  client::Arguments args(argc, argv);
  EXPECT_THROW(args.parse(), ClientError);
}

TEST_F(ArgumentsTest, UnknownFlag) {
  const char *argv[] = {"r-type_client", "-x"};
  int argc           = 2;

  client::Arguments args(argc, argv);
  EXPECT_THROW(args.parse(), ClientError);
}

TEST_F(ArgumentsTest, EmptyFlag) {
  const char *argv[] = {"r-type_client", "-p"};
  int argc           = 2;

  client::Arguments args(argc, argv);
  EXPECT_THROW(args.parse(), ClientError);
}

TEST_F(ArgumentsTest, FollowingEmptyFlag) {
  const char *argv[] = {"r-type_client", "-p", "-ip"};
  int argc           = 3;

  client::Arguments args(argc, argv);
  EXPECT_THROW(args.parse(), ClientError);
}

TEST_F(ArgumentsTest, AllArgs) {
  const char *argv[] = {"r-type_client", "-p", "45555", "-ip", "127.0.45.1", "-h"};
  int argc           = 6;

  client::Arguments args(argc, argv);
  args.parse();
  EXPECT_EQ(args.get_port(), 45555);
  EXPECT_TRUE(args.get_help());
  EXPECT_EQ(args.get_ip(), "127.0.45.1");
}
