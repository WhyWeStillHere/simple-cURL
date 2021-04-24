#ifndef MY_CURL__ARGPARSER_H_
#define MY_CURL__ARGPARSER_H_

#include <string>

class ArgParser {
 public:
  void Parse(int argc, char **argv);
  std::string GetUrl() const;
  std::string GetFilename() const;

 private:
  std::string url_;
  std::string filename_;
};

#endif //MY_CURL__ARGPARSER_H_
