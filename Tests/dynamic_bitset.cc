#include "../Source/dynamic_bitset.hpp"

#include <gtest/gtest.h>

#undef ASSERT_FALSE
#undef ASSERT_ALL

// Testfor int
TEST(int_to_bit, BasicAssertions) {
  std::vector<bool> expected = {1, 0, 1, 0};
  dynamic_bitset<> x = 10;
  EXPECT_EQ(expected, x.get());

  dynamic_bitset<5> y = expected;
  expected = {0, 1, 0, 1, 0};
  EXPECT_EQ(expected, y.get());
}

TEST(int_to_bit_padding, BasicAssertions) {
  std::vector<bool> expected = {1, 0, 1, 0};
  dynamic_bitset<> x = 10;
  EXPECT_EQ(expected, x.get());

  expected = {0, 1, 0, 1, 0};
  dynamic_bitset<5> y = 10;
  EXPECT_EQ(expected, y.get());

  expected = {0, 0, 1, 0, 1, 0};

  dynamic_bitset<6> z = {0, 1, 0, 1, 0};
  EXPECT_EQ(expected, z.get());
}

TEST(reverse, BasicAssertions) {
  std::vector<bool> expected = {1, 1, 0, 1, 0};
  dynamic_bitset<5> x = 11;
  EXPECT_EQ(expected, x.reverse().get());
}

TEST(get, BasicAssertions) {
  dynamic_bitset<> x = 11;
  EXPECT_EQ(0, x[1]);
}

TEST(subscript, BasicAssertions) {
  dynamic_bitset<> x = 11;
  x[0] = 0;
  x[2] = 0;
  std::vector<bool> expected = {0, 0, 0, 1};
  EXPECT_EQ(expected, x.get());
}

TEST(all, BasicAssertions) {
  dynamic_bitset<> x = 3;
  EXPECT_EQ(true, x.all());

  dynamic_bitset<> z = 4;
  EXPECT_EQ(false, z.all());
}

TEST(any, BasicAssertions) {
  dynamic_bitset<> x = 4;
  EXPECT_EQ(true, x.any());

  dynamic_bitset<30> y;
  EXPECT_EQ(false, y.any());
}

TEST(none, BasicAssertions) {
  dynamic_bitset<> x = 4;
  EXPECT_EQ(false, x.none());

  dynamic_bitset<15> y;
  EXPECT_EQ(true, y.none());
}

TEST(string_to_binary, BasicAssertions) {
  std::vector<bool> expected = {0, 1, 0, 1, 0, 1};

  dynamic_bitset<6> y = std::string("10101");
  EXPECT_EQ(expected, y.get());
}

TEST(left_shift_operator, BasicAssertions) {
  std::vector<bool> expected = {1, 0, 1, 0, 0};

  dynamic_bitset<> y = std::string("10101");
  y <<= 2;
  EXPECT_EQ(expected, y.get());
}

TEST(right_shift_operator, BasicAssertions) {
  std::vector<bool> expected = {0, 0, 1, 0, 1};

  dynamic_bitset<> y = std::string("10101");
  y >>= 2;
  EXPECT_EQ(expected, y.get());
}

TEST(input_stream, BasicAssertions) {
  dynamic_bitset<> x;
  std::istringstream stream("10101");
  stream >> x;
  std::vector<bool> expected = {1, 0, 1, 0, 1};
  EXPECT_EQ(expected, x.get());
}

TEST(set, BasicAssertions) {
  dynamic_bitset<6> x = "10101";
  std::vector<bool> expected = {0, 0, 0, 0, 0, 0};
  x.set(false);
  EXPECT_EQ(expected, x.get());

  x.set(true);
  expected = {1, 1, 1, 1, 1, 1};
  EXPECT_EQ(expected, x.get());
}

TEST(to_string, BasicAssertions) {
  dynamic_bitset<6> x = "10101";
  std::string expected = "010101";
  EXPECT_EQ(expected, x.to_string());
  EXPECT_EQ(expected, std::string(x));
}

TEST(to_ulong, BasicAssertions) {
  dynamic_bitset<6> x = "10101";
  std::size_t expected = 21;
  EXPECT_EQ(expected, x.to_ulong());
  EXPECT_EQ(expected, std::size_t(x));
}

TEST(and_operator, BasicAssertions) {
  dynamic_bitset<5> x = "10001";
  dynamic_bitset<5> y = "10101";

  std::string expected = "10001";
  auto z = x & y;
  EXPECT_EQ(expected, z.to_string());

  x &= y;
  EXPECT_EQ(expected, x.to_string());

  dynamic_bitset<> f = "010010";
  dynamic_bitset<> e = "10101";
  auto g = f & e;
  expected = "00001";
  EXPECT_EQ(expected, g.to_string());
}

TEST(or_operator, BasicAssertions) {
  dynamic_bitset<5> x = "10001";
  dynamic_bitset<5> y = "10101";

  std::string expected = "10101";
  auto z = x | y;
  EXPECT_EQ(expected, z.to_string());
  x |= y;
  EXPECT_EQ(expected, x.to_string());

  dynamic_bitset<> f = "010010";
  dynamic_bitset<> e = "10101";
  auto g = f | e;
  expected = "11101";
  EXPECT_EQ(expected, g.to_string());
}

TEST(xor_opreator, BasicAssertions) {
  dynamic_bitset<5> x = "10001";
  dynamic_bitset<5> y = "10101";

  std::string expected = "00100";
  auto z = x ^ y;
  EXPECT_EQ(expected, z.to_string());

  x ^= y;
  EXPECT_EQ(expected, x.to_string());
  dynamic_bitset<> f = "010010";
  dynamic_bitset<> e = "10101";
  auto g = f ^ e;
  expected = "11100";
  EXPECT_EQ(expected, g.to_string());
}
