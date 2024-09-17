#include "filterList.hpp"

#include <algorithm>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

auto FilterOutForbiddenTerms(
    std::stringstream &list,
    std::vector<std::string_view> const &forbiddenTerms) -> std::string {
  std::string Line;
  std::string PermittedLines;
  while (std::getline(list, Line)) {
    if (std::ranges::none_of(
            forbiddenTerms, [&](auto token) { return Line.contains(token); })) {
      PermittedLines += Line + '\n';
    }
  }
  return PermittedLines;
}
