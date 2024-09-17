#include "parseConfig.hpp"

#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>

TEST_CASE("PARSING_REQUIRED_TOKENS", "[Load]") {
  REQUIRE(ParseRequiredSearchTermLine("").empty());
  REQUIRE(ParseRequiredSearchTermLine("fd") == "fd");
  REQUIRE(ParseRequiredSearchTermLine("fd!fds") == "fd");
  REQUIRE(ParseRequiredSearchTermLine("fd!fds!fda") == "fd");
}

TEST_CASE("PARSING_FORBIDDEN_TOKENS", "[Load]") {
  REQUIRE(ParseForbiddenSearchTermLine("").empty());
  REQUIRE(ParseForbiddenSearchTermLine("fd").empty());
  REQUIRE(ParseForbiddenSearchTermLine("fd!fds") ==
          std::vector{std::string("fds")});
  REQUIRE(ParseForbiddenSearchTermLine("fd!fds!fda") ==
          std::vector<std::string>{"fds", "fda"});
}
TEST_CASE("REQUIRED_TERM_CLASS", "[Load]") {
  REQUIRE(RequiredTerm("").ContainsRequiredTerm(""));
  REQUIRE(RequiredTerm("el!de").ContainsRequiredTerm("el"));
  REQUIRE(RequiredTerm("el!de!fd!fe").ContainsRequiredTerm("elfdskjfk"));
}
TEST_CASE("FORBIDDEN_TERM_CLASS", "[Load]") {
  // REQUIRE(RequiredTerm("").ContainsRequiredTerm(""));
  REQUIRE(ForbiddenTerm("el").ContainsForbiddenTerm(""));
  REQUIRE(!ForbiddenTerm("el!de!fd!fe").ContainsForbiddenTerm("elfdskjfk"));
  REQUIRE(ForbiddenTerm("el!de!fd!fe", 1).ContainsForbiddenTerm("elfdskjfk"));
}
TEST_CASE("FORBIDDEN_TERMS_CLASS", "[Load]") {
  // REQUIRE(!ForbiddenTerm("el!de").ContainsForbiddenTerm("el"));
  REQUIRE(!ForbiddenTerm("el!de!fd!fe").ContainsForbiddenTerm("elfdskjfk"));
  REQUIRE(ForbiddenTerm("el!de!fd!fe", 1).ContainsForbiddenTerm("elfdskjfk"));
}

//{
//  Config test("/home/Eugene/Git/Inversity/InversityBrocoliToBurgers/tests/"
//              "ParseTest.txt");
//  std::stringstream ss;
//  REQUIRE(test.FilterList(ss).empty());
//}

//{
//  Config test("/home/Eugene/Git/Inversity/InversityBrocoliToBurgers/tests/"
//              "ParseTest.txt");
//  std::stringstream ss("fd");
//  REQUIRE(test.FilterList(ss) == "fd");
//}
