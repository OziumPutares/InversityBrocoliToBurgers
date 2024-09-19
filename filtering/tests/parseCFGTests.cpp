#include "parseConfig.hpp"

#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>

TEST_CASE("PARSING_REQUIRED_TOKENS", "[Load]") {
  REQUIRE(ParseRequiredSearchTermLine(Line("")).empty());
  REQUIRE(ParseRequiredSearchTermLine(Line("fd")) == "fd");
  REQUIRE(ParseRequiredSearchTermLine(Line("fd!fds")) == "fd");
  REQUIRE(ParseRequiredSearchTermLine(Line("fd!fds!fda")) == "fd");
}

TEST_CASE("PARSING_FORBIDDEN_TOKENS", "[Load]") {
  REQUIRE(ParseForbiddenSearchTermLine(Line("")).empty());
  REQUIRE(ParseForbiddenSearchTermLine(Line("fd")).empty());
  REQUIRE(ParseForbiddenSearchTermLine(Line("fd!fds")) ==
          std::vector{std::string("fds")});
  REQUIRE(ParseForbiddenSearchTermLine(Line("fd!fds!fda")) ==
          std::vector<std::string>{"fds", "fda"});
}
TEST_CASE("REQUIRED_TERM_CLASS", "[Load]") {
  REQUIRE(RequiredTerm(Line("")).ContainsRequiredTerm(Line("")));
  REQUIRE(RequiredTerm(Line("el!de")).ContainsRequiredTerm(Line("el")));
  REQUIRE(RequiredTerm(Line("el!de!fd!fe"))
              .ContainsRequiredTerm(Line("elfdskjfk")));
}
TEST_CASE("FORBIDDEN_TERM_CLASS", "[Load]") {
  // REQUIRE(RequiredTerm("").ContainsRequiredTerm(""));
  REQUIRE_THROWS(ForbiddenTerm(Line("el")).ContainsForbiddenTerm(Line("")));
  REQUIRE(!ForbiddenTerm(Line("el!de!fd!fe"))
               .ContainsForbiddenTerm(Line("elfdskjfk")));
  REQUIRE_THROWS(
      ForbiddenTerm(Line("el!de"), 1).ContainsForbiddenTerm(Line("el")));
  REQUIRE(ForbiddenTerm(Line("el!de!fd!fe"), 1)
              .ContainsForbiddenTerm(Line("elfdskjfk")));
}
TEST_CASE("FORBIDDEN_TERMS_CLASS", "[Load]") {
  // REQUIRE(!ForbiddenTerm("el!de").ContainsForbiddenTerm("el"));
  REQUIRE(!ForbiddenTerms(Line("")).ContainsAForbiddenTerm(Line("")));
  REQUIRE(!ForbiddenTerms(Line("")).ContainsAForbiddenTerm(Line("ef")));
  REQUIRE(!ForbiddenTerms(Line("f")).ContainsAForbiddenTerm(Line("")));
  REQUIRE(!ForbiddenTerms(Line("f!e")).ContainsAForbiddenTerm(Line("f")));
  REQUIRE(ForbiddenTerms(Line("f!e")).ContainsAForbiddenTerm(Line("fe")));
  REQUIRE(ForbiddenTerms(Line("f!e")).ContainsAForbiddenTerm(Line("efe")));
  REQUIRE(ForbiddenTerms(Line("f!e")).ContainsAForbiddenTerm(Line("ef")));
  REQUIRE(ForbiddenTerms(Line("el!de!fd!fe"))
              .ContainsAForbiddenTerm(Line("elfdskjfk")));
  REQUIRE(!ForbiddenTerms(Line("el!de!fd!fe"))
               .ContainsAForbiddenTerm(Line("zzzzzzzzzz")));
}
TEST_CASE("CONFIG_CLASS", "[Load]") {

  {
    Config test("/home/Eugene/Git/Inversity/InversityBrocoliToBurgers/tests/"
                "ParseTest.txt");
    std::stringstream ss;
    REQUIRE(test.FilterList(ss).empty());
  }
  {
    Config test("/home/Eugene/Git/Inversity/InversityBrocoliToBurgers/tests/"
                "ParseTest.txt");
    std::stringstream ss("eat");
    REQUIRE(test.FilterList(ss) == "eat\n");
  }
  {
    Config test("/home/Eugene/Git/Inversity/InversityBrocoliToBurgers/tests/"
                "ParseTest.txt");
    std::stringstream ss("eat\nfeature\nfeat\nhello");
    REQUIRE(test.FilterList(ss) == "eat\nfeat\n");
  }
}
