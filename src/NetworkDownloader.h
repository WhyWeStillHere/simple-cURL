#ifndef MY_CURL__NETWORKDOWNLOADER_H_
#define MY_CURL__NETWORKDOWNLOADER_H_

#include <string>
#include "Socket.h"

class NetworkDownloader {
 public:
  void Download(const std::string &url, const std::string &destination_filepath);

 private:
  Socket socket_;
};

#endif //MY_CURL__NETWORKDOWNLOADER_H_
