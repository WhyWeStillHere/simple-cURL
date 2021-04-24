//
// Created by whywestillhere on 22.04.2021.
//

#include <string>
#include <sstream>
#include "Utils.h"
#include "SocketDataStream.h"

std::string_view TrimUrl(std::string_view url) {
  const std::string domain_start = "://";
  std::size_t domain_start_pos = url.find(domain_start);
  if (domain_start_pos == std::string::npos) {
    domain_start_pos = 0;
  } else {
    domain_start_pos += domain_start.size();
  }

  return url.substr(domain_start_pos);
}

namespace url_utils {
std::string CreateGetHttpRequest(const std::string &server_name, const std::string &filepath) {
  std::stringstream ss;
  ss << "GET " << filepath << " HTTP/1.0\r\n";
  ss << "Host: " << server_name << "\r\n\r\n";
  return ss.str();
}

std::string GetDomain(const std::string &url) {
  std::string_view trimmed_domain = TrimUrl(url);
  return std::string(trimmed_domain.substr(0, trimmed_domain.find('/')));
}

std::string GetFilepath(const std::string &url) {
  std::string_view trimmed_domain = TrimUrl(url);
  std::size_t filepath_start = trimmed_domain.find('/');
  if (filepath_start == std::string::npos) {
    return "/";
  }
  return std::string(trimmed_domain.substr(filepath_start));
}

std::string GetFilename(const std::string &url) {
  std::string_view trimmed_domain = TrimUrl(url);
  std::size_t filename_start = trimmed_domain.find_last_of('/');
  if (filename_start == std::string::npos) {
    return "";
  }
  return std::string(trimmed_domain.substr(filename_start + 1));
}
} // namespace url_utils

namespace socket_stream_utils {
std::string ReadUntilDelimiter(SocketDataStream &stream, const std::string &delimiter) {
  bool reached_eof = false;
  std::string result;
  std::size_t delimiter_index = 0;
  char current_symbol;
  while (true) {
    current_symbol = stream.NextValue(reached_eof);
    if (reached_eof) {
      break;
    }

    if (current_symbol == delimiter[delimiter_index]) {
      ++delimiter_index;
      if (delimiter_index == delimiter.size()) {
        break;
      }
      continue;
    } else if (delimiter_index > 0) {
      result += delimiter.substr(0, delimiter_index);
      delimiter_index = 0;
    }
    result.push_back(current_symbol);
  }
  return result;
}

HttpHeader GetHeader(SocketDataStream &stream) {
  HttpHeader header;
  header.protocol_type = ReadUntilDelimiter(stream, " ");
  header.status_code = ReadUntilDelimiter(stream, " ");
  header.status = ReadUntilDelimiter(stream, "\r\n");
  while (true) {
    std::string row;
    row = ReadUntilDelimiter(stream, "\r\n");
    if (row.empty()) {
      break;
    }
    std::size_t delimiter_index = row.find(": ");
    if (delimiter_index == std::string::npos) {
      throw std::runtime_error("Incorrect server response");
    }
    header.fields[row.substr(0, delimiter_index)] = row.substr(delimiter_index + 2);
  }
  return header;
}
} // namespace socket_stream_utils
