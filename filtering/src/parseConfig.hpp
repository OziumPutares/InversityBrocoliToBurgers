#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "strongTypes.hpp"

auto ParseRequiredSearchTermLine(Line const &line) -> std::string;
class RequiredTerm {
  std::string RequiredTerm_;

 public:
  explicit RequiredTerm(Line const &line) {
    RequiredTerm_ = ParseRequiredSearchTermLine(line);
  }
  auto ContainsRequiredTerm(Line const &val) const {
    return val.contains(RequiredTerm_);
  }
};
auto ParseForbiddenSearchTermLine(Line const &line) -> std::vector<std::string>;
class ForbiddenTerm {
  std::string ForbiddenTerm_;

 public:
  explicit ForbiddenTerm(Line const &line,
                         unsigned int indexOfForbiddenTerm = 0) {
    auto Output = ParseForbiddenSearchTermLine(line);
    if (indexOfForbiddenTerm >= std::size(Output)) {
      throw std::out_of_range(
          "Make sure indexOfForbiddenTerm is not greater than the number");
    }
    ForbiddenTerm_ = Output[indexOfForbiddenTerm];
  }
  explicit ForbiddenTerm(std::string term) : ForbiddenTerm_{std::move(term)} {}

  constexpr auto ContainsForbiddenTerm(std::string const &val) const -> bool {
    return val.contains(ForbiddenTerm_);
  }
};

class ForbiddenTerms {
  std::vector<ForbiddenTerm> ForbiddenTerms_;

 public:
  explicit ForbiddenTerms(Line const &line) {
    for (auto const &ForbiddenToken : ParseForbiddenSearchTermLine(line)) {
      ForbiddenTerms_.emplace_back(ForbiddenToken);
    }
  }
  [[nodiscard]] constexpr auto ContainsAForbiddenTerm(
      std::string const &strToCheck) const -> bool {
    return std::ranges::any_of(ForbiddenTerms_,
                               [&](ForbiddenTerm const &token) {
                                 return token.ContainsForbiddenTerm(strToCheck);
                               });
  }
};

// Now complete ISP and combine
using CFG = std::vector<std::pair<RequiredTerm, ForbiddenTerms>>;
class Config {
  CFG FilterList_;

 public:
  explicit Config(std::string const &fileName) {
    std::fstream InputFile(fileName);
    Line Line{""};
    while (std::getline(InputFile, Line)) {
      FilterList_.emplace_back(RequiredTerm(Line), ForbiddenTerms(Line));
    }
  }
  auto FilterList(std::stringstream &fileConfig) -> std::string {
    std::string List;
    Line Line{""};
    while (std::getline(fileConfig, Line)) {
      for (const auto &CFGLine : FilterList_) {
        if (CFGLine.first.ContainsRequiredTerm(Line) &&
            !CFGLine.second.ContainsAForbiddenTerm(Line)) {
          List += Line + '\n';
        }
      }
    }
    return List;
  }
};
