#include "parseConfig.hpp"
#include <sstream>
#include <string>

auto LoadRequiredTerms::ParseRequiredSearchTerms(
    std::stringstream configuration) -> void {
  std::string Line;
  std::vector<std::string> SearchTermList;
  while (std::getline(configuration, Line)) {
    if (Line.starts_with('#')) {
      continue;
    }
    if (Line.starts_with('!')) {
      continue;
    }
    SearchTermList.emplace_back(Line.substr(0, Line.find('!')));
  }
  RequiredTerms_ = SearchTermList;
}

auto LoadForbiddenTerms::ParseForbiddenSearchTerms(
    std::stringstream configuration) -> void {
  std::string Line;
  std::vector<std::string> SearchTermList;
  while (std::getline(configuration, Line)) {
    if (Line.starts_with('#')) {
      continue;
    }
    std::stringstream LineSS(Line);
    std::string Token;
    if (Line.contains("!")) {
      std::getline(LineSS, Token, '!');
      while (std::getline(LineSS, Token, '!')) {
        SearchTermList.emplace_back(Token);
      }
    }
  }
  ForbiddenTerms_ = SearchTermList;
}

auto Tolower(std::string &buf) -> std::string;
// auto LoadRequiredTerms::FilterFile(std::string const
// &FileNameOfFileToFilter,
//                                    std::string const &outputFileName) -> void
//                                    {
//   std::ifstream FileToFilter(FileNameOfFileToFilter);
//   std::ofstream OutputFile(outputFileName);
//   std::string Line;
//   while (std::getline(FileToFilter, Line)) {
//     Tolower(Line);
//     if (std::ranges::any_of(RequiredTerms_,
//                             [Line](std::string_view FilterElem) {
//                               return Line.contains(FilterElem);
//                             }) &&
//         std::ranges::none_of(
//             ForbiddenTerms_, [Line](std::string_view FilterElem) {
//               return Line.contains(FilterElem.substr(1, FilterElem.size()));
//             })) {
//       OutputFile << Line << '\n';
//     }
//   }
//   OutputFile.close();
// }
