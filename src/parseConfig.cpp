#include "parseConfig.hpp"

#include <sstream>
#include <string>
#include <vector>

auto ParseRequiredSearchTermLine(std::string const &Line) -> std::string {
  if (Line.starts_with('!') || Line.starts_with('#') || Line.empty()) {
    return {};
  }
  return Line.substr(0, Line.find('!'));
}

auto ParseForbiddenSearchTermUnsafe(std::string const &line)
    -> std::vector<std::string> {
  std::stringstream LineSS(line);
  std::string Token;
  std::vector<std::string> SearchTermList;
  std::getline(LineSS, Token, '!');
  while (std::getline(LineSS, Token, '!')) {
    SearchTermList.emplace_back(Token);
  }
  return SearchTermList;
}
auto ParseForbiddenSearchTermLine(std::string const &line)
    -> std::vector<std::string> {
  if (line.starts_with('#') || !line.contains("!")) {
    return {};
  }
  return ParseForbiddenSearchTermUnsafe(line);
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
