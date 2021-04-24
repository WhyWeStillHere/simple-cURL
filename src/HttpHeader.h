#ifndef MY_CURL__HTTPHEADER_H_
#define MY_CURL__HTTPHEADER_H_

#include <unordered_map>

struct HttpHeader {
  std::string status;
  std::string protocol_type;
  std::string status_code;
  std::unordered_map<std::string, std::string> fields;
};

#endif //MY_CURL__HTTPHEADER_H_
