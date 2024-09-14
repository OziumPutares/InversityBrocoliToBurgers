#include <cctype>
#include <fstream>
#include <iostream>
#include <ostream>
#include <print>
#include <sstream>
#include <string>

#include "listAccess.hpp"
#include "parseConfig.hpp"

auto Tolower(std::string &buf) -> std::string {
  for (char &Index : buf) {
    Index = std::tolower(Index);
  }
  return buf;
}
auto ReadFileInput(std::string const &fileName) -> std::stringstream {
  return std::stringstream() << std::ifstream(fileName).rdbuf();
}

std::string const kFileInput = "searchTerms.txt";
auto main() -> int {
  std::string Line;
  std::ifstream List("blockingList.txt");
  GetPage("https://easylist.to/easylist/easylist.txt", "blockingList.txt");
  for (auto LineNum = 0; LineNum < 18; LineNum++) {
    std::getline(List, Line);
  }

  std::cout << std::endl;
}

// auto TempFunc() {
//   std::stringstream ActiveList;
//
//   std::string Line;
//   LoadSearchTerms();
//
//   get_page("https://easylist.to/easylist/easylist.txt", "blockingList.txt");
//   std::ifstream List("blockingList.txt");
//   for (auto LineNum = 0; LineNum < 18; LineNum++) {
//     std::getline(List, Line);
//   }
//
//   while (std::getline(List, Line)) {
//     Tolower(Line);
//     if (std::ranges::any_of(SearchTermList,
//                             [Line](std::string_view FilterElem) {
//                               if (FilterElem.starts_with('!')) {
//                                 return false;
//                               }
//                               return Line.contains(FilterElem);
//                             }) &&
//         std::ranges::all_of(
//             SearchTermList, [Line](std::string_view FilterElem) {
//               if (FilterElem.starts_with('!')) {
//                 return Line.contains(FilterElem.substr(1,
//                 FilterElem.size()));
//               }
//               return true;
//             })) {
//       ActiveList << Line << '\n';
//     }
//   }
//   std::ofstream("blockingListA.txt") << ActiveList.str();
// }
