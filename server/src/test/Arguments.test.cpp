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
#include "macro.hpp"
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
  EXPECT_EQ(args.get_game_port(), PORT_GAME);
  EXPECT_EQ(args.get_lobby_port(), PORT_LOBBY);
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
  EXPECT_EQ(args.get_lobby_port(), PORT_LOBBY);
  EXPECT_EQ(args.get_game_port(), PORT_GAME);
}

TEST_F(ArgumentsTest, DebugFlag) {
  const char *argv[] = {"r-type_server", "-v"};
  int argc           = 2;

  rtype::Arguments args(argc, argv);
  args.parse();

  EXPECT_TRUE(args.get_debug());
  EXPECT_FALSE(args.get_help());
  EXPECT_EQ(args.get_lobby_port(), PORT_LOBBY);
  EXPECT_EQ(args.get_game_port(), PORT_GAME);
}

TEST_F(ArgumentsTest, GamePortFlag) {
  const char *argv[] = {"r-type_server", "-gp", "12345"};
  int argc           = 3;

  rtype::Arguments args(argc, argv);
  args.parse();

  EXPECT_EQ(args.get_game_port(), 12345);
  EXPECT_EQ(args.get_lobby_port(), PORT_LOBBY);
  EXPECT_FALSE(args.get_help());
  EXPECT_FALSE(args.get_debug());
}

TEST_F(ArgumentsTest, LobbyPortFlag) {
  const char *argv[] = {"r-type_server", "-lp", "12345"};
  int argc           = 3;

  rtype::Arguments args(argc, argv);
  args.parse();

  EXPECT_EQ(args.get_lobby_port(), 12345);
   EXPECT_EQ(args.get_game_port(), PORT_GAME);
  EXPECT_FALSE(args.get_help());
  EXPECT_FALSE(args.get_debug());
}

TEST_F(ArgumentsTest, InvalidPortNonNumeric) {
  const char *argv[] = {"r-type_server", "-gp", "abc"};
  int argc           = 3;

  rtype::Arguments args(argc, argv);
  EXPECT_THROW(args.parse(), ServerError);
}

TEST_F(ArgumentsTest, InvalidPortOutOfRange) {
  const char *argv[] = {"r-type_server", "-gp", "70000"};
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
  const char *argv[] = {"r-type_client", "-gp"};
  int argc           = 2;

  rtype::Arguments args(argc, argv);
  EXPECT_THROW(args.parse(), ServerError);
}

TEST_F(ArgumentsTest, FollowingEmptyFlag) {
  const char *argv[] = {"r-type_client", "-gp", "-v"};
  int argc           = 3;

  rtype::Arguments args(argc, argv);
  EXPECT_THROW(args.parse(), ServerError);
}

TEST_F(ArgumentsTest, AllArgs) {
  const char *argv[] = {"r-type_client", "-gp", "45555", "-v", "-h", "-lp", "35555"};
  int argc           = 7;

  rtype::Arguments args(argc, argv);
  args.parse();
  EXPECT_EQ(args.get_game_port(), 45555);
  EXPECT_EQ(args.get_lobby_port(), 35555);
  EXPECT_TRUE(args.get_help());
  EXPECT_TRUE(args.get_debug());
}
