/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** Network.test
*/

#include <gtest/gtest.h>
#include <array>
#include "Commands.hpp"
#include "Input.hpp"

class NetworkTest : public ::testing::Test {

};

struct test_1_t {
    int a;
    int b;
    char c;
};

TEST_F(NetworkTest, BasicSerializationAndDeserialization) {  
    test_1_t payload = {123, 456, 'a'};
    std::array<uint8_t, 1024> message =
            network::game::Commands<test_1_t>::toArray(payload, 1, 1);
    input_t parsed_payload = network::game::unpack(sizeof(message), message);
    network::game::Commands<test_1_t> cmd_handler = network::game::Commands<test_1_t>(parsed_payload);
    test_1_t result = cmd_handler.getCommand();
    EXPECT_EQ(result.a, 123);
    EXPECT_EQ(result.b, 456);
    EXPECT_EQ(result.c, 'a');
}

struct test_2_t {
    float a;
    double b;
    int d;
    char e[10];
};


TEST_F(NetworkTest, BigDataSerialization) {
    test_2_t payload = {123.54, 456.3214, 42, "hello"};
    std::array<uint8_t, 1024> message =
            network::game::Commands<test_2_t>::toArray(payload, 1, 1);
    input_t parsed_payload = network::game::unpack(sizeof(message), message);
    network::game::Commands<test_2_t> cmd_handler = network::game::Commands<test_2_t>(parsed_payload);
    test_2_t result = cmd_handler.getCommand();
    EXPECT_FLOAT_EQ(result.a, 123.54);
    EXPECT_DOUBLE_EQ(result.b, 456.3214);
    EXPECT_EQ(result.d, 42);
    EXPECT_STREQ(result.e, "hello");
}

struct test_3_t {
    char data[2000];
};

TEST_F(NetworkTest, ArrayOverflowException) {
    test_3_t largeCmd = {0};
    EXPECT_THROW(
        {
            try {
                network::game::Commands<test_3_t>::toArray(largeCmd, 1, 123);
            } catch (const std::runtime_error& e) {
                EXPECT_STREQ(e.what(), "Combined data size exceeds array capacity");
                throw;
            }
        },
        std::runtime_error
    );
}

