#include <iostream>
#include "NetworkDownloader.h"
#include "Utils.h"
#include "SocketDataStream.h"
#include "FileWriter.h"
#include "Logger.h"

using namespace url_utils;
using namespace socket_stream_utils;

void NetworkDownloader::Download(const std::string &url, const std::string &destination_filepath) {
  FileWriter writer(destination_filepath);

  // Connecting to server
  const std::string domain = GetDomain(url);
  try {
    socket_.Connect(domain);
  } catch (...) {
    LOG_FATAL("Can't connect to given domain\n");
  }

  // Sending get http request
  std::string http_request = CreateGetHttpRequest(domain, GetFilepath(url));
  try {
    socket_.Send(http_request.c_str(), http_request.size());
  } catch (...) {
    LOG_FATAL("Error while sending http request\n");
  }

  // Receive and parse header
  SocketDataStream stream(socket_);
  HttpHeader header;
  try {
    header = GetHeader(stream);
  } catch (...) {
    LOG_FATAL("Invalid HTTP response\n");
  }
  if (header.status_code.empty()) {
    LOG_FATAL("Invalid HTTP response\n");
  }
  if (std::stoi(header.status_code) < 200 || std::stoi(header.status_code) >= 300) {
    LOG_FATAL("Status of HTTP response is not OK\n");
  }

  // Write data from http request to file
  long long file_size = std::stoll(header.fields["Content-Length"]);
  writer.AddProgressBar(ProgressBar(file_size));
  try {
    stream.SaveToFile(writer, file_size);
  } catch (std::system_error &e) {
    LOG_FATAL("Error while downloading data\n");
  } catch (std::runtime_error &e) {
    LOG_FATAL("Invalid server data\n");
  } catch (...) {
    LOG_FATAL("Something went wrong\n");
  }

  // Finish work with server
  socket_.Shutdown();
}

