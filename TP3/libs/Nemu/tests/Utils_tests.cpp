#include <catch2/catch_test_macros.hpp>

#include <Nemu/Utils.h>

#include <string_view>

TEST_CASE("get_version returns an string correctly.", "[Utils]")
{
  std::string_view version = get_version();

  REQUIRE(version.data() != nullptr);

  // 0.0.1 -> 5 chars
  REQUIRE(version.size() >= 5);

  int num_of_periods = 0;

  for (auto ch : version) {
    if (ch == '.') { ++num_of_periods; }
  }

  REQUIRE(num_of_periods == 2);
}

TEST_CASE("get_short_sha1 returns an string correctly.", "[Utils]")
{
  std::string_view sha1 = get_short_sha1();

  REQUIRE(sha1.data() != nullptr);
  REQUIRE(sha1.size() == 8);
}
