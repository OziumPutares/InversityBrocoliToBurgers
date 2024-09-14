
#include "listAccess.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <print>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

auto Tolower(std::string &buf) -> std::string {
  for (char &index : buf) {
    index = std::tolower(index);
  }
  return buf;
}
auto LoadSearchTerms() -> std::vector<std::string> {
  std::string Line;
  std::ifstream SearchTerms("searchTerms.txt");
  std::vector<std::string> SearchTermList;
  while (std::getline(SearchTerms, Line)) {
    if (Line[0] == '#') {
      continue;
    }
    SearchTermList.emplace_back(Line);
  }
  return SearchTermList;
}
auto main() -> int {

  std::stringstream ActiveList;

  std::string Line;
  get_page("https://easylist.to/easylist/easylist.txt", "blockingList.txt");
  std::ifstream List("blockingList.txt");
  for (auto LineNum = 0; LineNum < 18; LineNum++) {
    std::getline(List, Line);
  }

  while (std::getline(List, Line)) {
    Tolower(Line);
    if (std::ranges::any_of(SearchTermList,
                            [Line](std::string_view FilterElem) {
                              if (FilterElem.starts_with('!')) {
                                return false;
                              }
                              return Line.contains(FilterElem);
                            }) &&
        std::ranges::all_of(
            SearchTermList, [Line](std::string_view FilterElem) {
              if (FilterElem.starts_with('!')) {
                return Line.contains(FilterElem.substr(1, FilterElem.size()));
              }
              return true;
            })) {
      ActiveList << Line << '\n';
    }
  }
  std::ofstream("blockingListA.txt") << ActiveList.str();
}
