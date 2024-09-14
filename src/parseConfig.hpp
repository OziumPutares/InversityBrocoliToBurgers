#include <fstream>
#include <sstream>
#include <string>
#include <vector>
class LoadRequiredTerms {
  auto ParseRequiredSearchTerms(std::stringstream configuration) -> void;

public:
  std::vector<std::string> RequiredTerms_;
  explicit LoadRequiredTerms(std::string const &fileName) {
    ParseRequiredSearchTerms(std::stringstream()
                             << std::fstream(fileName).rdbuf());
  }
};
class LoadForbiddenTerms {
  auto ParseForbiddenSearchTerms(std::stringstream configuration) -> void;

public:
  explicit LoadForbiddenTerms(std::string const &fileName) {

    ParseForbiddenSearchTerms(std::stringstream()
                              << std::fstream(fileName).rdbuf());
  }
  std::vector<std::string> ForbiddenTerms_;
};
class LoadTerms : LoadRequiredTerms, LoadForbiddenTerms {
public:
  explicit LoadTerms(std::string const &fileName)
      : LoadRequiredTerms(fileName), LoadForbiddenTerms(fileName) {}
};
