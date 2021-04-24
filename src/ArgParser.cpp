#include "ArgParser.h"
#include "Utils.h"
#include "Logger.h"

void ArgParser::Parse(int argc, char **argv) {
  if (argc < 2) {
    LOG_FATAL("To few program arguments\n");
  }
  url_ = argv[1];

  std::string file_path;
  if (argc == 2) {
    filename_ = url_utils::GetFilename(url_);
  } else {
    filename_ = argv[2];
  }
}
std::string ArgParser::GetUrl() const {
  return url_;
}
std::string ArgParser::GetFilename() const {
  return filename_;
}

