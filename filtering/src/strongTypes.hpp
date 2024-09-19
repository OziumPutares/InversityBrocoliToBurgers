// Struct == Class but public by default which is better for strong types
#include <stdexcept>
#include <string>
#ifndef STRONG_TYPES
#define STRONG_TYPES
struct FileName : std::string {
  explicit FileName(std::string fileName) : std::string{std::move(fileName)} {}
};
struct Line : std::string {
  explicit Line(std::string Line) : std::string{std::move(Line)} {
    if (Line.contains('\n')) {
      throw std::invalid_argument("Line class can't have a new line character");
    }
  }
};
struct C_URL {
  explicit C_URL(char const* url) : Url_{url} {}
  char const* Url_;
};
struct C_FileName {
  explicit C_FileName(char const* fileName) : C_FileName_{fileName} {}
  explicit C_FileName(const FileName& fileName)
      : C_FileName_{fileName.c_str()} {}
  char const* C_FileName_;
};
#endif
