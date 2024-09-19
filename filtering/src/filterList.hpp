
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

// auto FilterOutForbiddenTerms(std::stringstream& list,
//                              std::vector<std::string> forbiddenTerms)
//     -> std::string&;
auto FilterOutForbiddenTerms(
    std::stringstream& list,
    std::vector<std::string_view> const& forbiddenTerms) -> std::string;
