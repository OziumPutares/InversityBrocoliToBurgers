#include "filterList.hpp"
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <string_view>

#define TESTING
TEST_CASE("FILTERING", "[Load]") {
  {
    std::stringstream ss;
    std::vector<std::string_view> testVec{};
    REQUIRE(FilterOutForbiddenTerms(ss, testVec).empty());
  }
  {
    std::stringstream ss("fd");
    std::vector<std::string_view> testVec{};
    REQUIRE(FilterOutForbiddenTerms(ss, testVec) == "fd\n");
  }
  {
    std::stringstream ss("fd\nfdk!j");
    std::vector<std::string_view> testVec{};
    REQUIRE(FilterOutForbiddenTerms(ss, testVec) == "fd\nfdk!j\n");
  }
  {
    std::stringstream ss("fd\nfdk!j");
    std::vector<std::string_view> testVec{"f"};
    REQUIRE(FilterOutForbiddenTerms(ss, testVec) == "");
  }
  {
    std::stringstream ss("fd\nfdk!j");
    std::vector<std::string_view> testVec{"j"};
    REQUIRE(FilterOutForbiddenTerms(ss, testVec) == "fd\n");
  }
  {
    std::stringstream ss("fnd\nfdk!j");
    std::vector<std::string_view> testVec{"z", "n"};
    REQUIRE(FilterOutForbiddenTerms(ss, testVec) == "fdk!j\n");
  }
  {
    std::stringstream ss("fnd\nfdk!j");
    std::vector<std::string_view> testVec{"f", "n"};
    REQUIRE(FilterOutForbiddenTerms(ss, testVec) == "");
  }
}
