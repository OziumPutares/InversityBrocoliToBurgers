#include <algorithm>
#include <cassert>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
auto ParseRequiredSearchTermLine(std::string const &line) -> std::string;
class RequiredTerm {
  std::string RequiredTerm_;

 public:
  explicit RequiredTerm(std::string const &line) {
    RequiredTerm_ = ParseRequiredSearchTermLine(line);
  }
  auto ContainsRequiredTerm(std::string const &val) const {
    return val.contains(RequiredTerm_);
  }
};
auto ParseForbiddenSearchTermLine(std::string const &line)
    -> std::vector<std::string>;
class ForbiddenTerm {
  std::string ForbiddenTerm_;

 public:
  explicit ForbiddenTerm(std::string const &line,
                         unsigned int indexOfForbiddenTerm = 0) {
    ForbiddenTerm_ = ParseForbiddenSearchTermLine(line)[indexOfForbiddenTerm];
  }
  constexpr auto ContainsForbiddenTerm(std::string const &val) const -> bool {
    return val.contains(ForbiddenTerm_);
  }
};
class ForbiddenTerms {
  std::vector<ForbiddenTerm> ForbiddenTerms_;

 public:
  explicit ForbiddenTerms(std::string const &line) {
    for (auto const &ForbiddenToken : ParseForbiddenSearchTermLine(line)) {
      ForbiddenTerms_.emplace_back(ForbiddenToken);
    }
  }
  [[nodiscard]] auto ContainsAForbiddenTerm(std::string const &strToCheck) const
      -> bool {
    return std::ranges::none_of(
        ForbiddenTerms_, [&](ForbiddenTerm const &token) {
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
    std::string Line;
    while (std::getline(InputFile, Line)) {
      FilterList_.emplace_back(RequiredTerm(Line), ForbiddenTerms(Line));
    }
  }
  auto FilterList(std::stringstream &fileConfig) -> std::string {
    std::string List;
    std::string Line;
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
