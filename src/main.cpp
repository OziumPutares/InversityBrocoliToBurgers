
#include "listAccess.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <print>
#include <sstream>
#include <string>
#include <vector>

std::string tolower(std::string &buf) {
  for (auto index = 0; index < buf.size(); index++) {
    buf[index] = std::tolower(buf[index]);
  }
  return buf;
}
int main() {

  std::string line;
  std::stringstream activeList;
  std::ifstream searchTerms("searchTerms.txt");
  std::vector<std::string> searchTermList;
  while (std::getline(searchTerms, line))
    searchTermList.emplace_back(line);

  get_page("https://easylist.to/easylist/easylist.txt", "blockingList.txt");
  std::ifstream List("blockingList.txt");
  for (auto Line = 0; Line < 18; Line++) {
    std::getline(List, line);
  }

  while (std::getline(List, line)) {
    tolower(line);
    if (std::ranges::any_of(searchTermList,
                            [line](auto i) { return line.contains(i); }))
      activeList << line << '\n';
  }
  std::ofstream("blockingListA.txt") << activeList.str();
}
