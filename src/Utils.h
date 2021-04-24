#ifndef MY_CURL__UTILS_H_
#define MY_CURL__UTILS_H_

#include "HttpHeader.h"
#include "SocketDataStream.h"

namespace url_utils {
std::string CreateGetHttpRequest(const std::string &server_name, const std::string &filepath);
std::string GetDomain(const std::string &url);
std::string GetFilepath(const std::string &url);
std::string GetFilename(const std::string &url);
} // namespace url_utils

namespace socket_stream_utils {
std::string ReadUntilDelimiter(SocketDataStream &stream, const std::string &delimiter);
HttpHeader GetHeader(SocketDataStream &stream);
} // namespace socket_stream_utils

#endif //MY_CURL__UTILS_H_
