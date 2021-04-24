#include <gtest/gtest.h>
#include "../src/Socket.h"
#include "../src/Utils.h"

using namespace socket_stream_utils;

TEST(ReadUntilDelimiter, Redirect) {
  std::string domain = "google.com";
  std::string file_path = "/";
  Socket socket;
  socket.Connect(domain);
  std::string request = url_utils::CreateGetHttpRequest(domain, file_path);
  socket.Send(request.c_str(), request.size());

  SocketDataStream stream(socket);
  ASSERT_EQ(ReadUntilDelimiter(stream, " "), "HTTP/1.0");
  ASSERT_EQ(ReadUntilDelimiter(stream, " "), "301");
  ASSERT_EQ(ReadUntilDelimiter(stream, "\r\n"), "Moved Permanently");
}

TEST(ReadUntilDelimiter, OkStatus) {
  std::string domain = "speedtest.ftp.otenet.gr";
  std::string file_path = "/files/test100Mb.db";
  Socket socket;
  socket.Connect(domain);
  std::string request = url_utils::CreateGetHttpRequest(domain, file_path);
  socket.Send(request.c_str(), request.size());

  SocketDataStream stream(socket);
  ASSERT_EQ(ReadUntilDelimiter(stream, " "), "HTTP/1.1");
  ASSERT_EQ(ReadUntilDelimiter(stream, " "), "200");
  ASSERT_EQ(ReadUntilDelimiter(stream, "\r\n"), "OK");
}


TEST(GetHeader, Redirect) {
  std::string domain = "google.com";
  std::string file_path = "/";
  Socket socket;
  socket.Connect(domain);
  std::string request = url_utils::CreateGetHttpRequest(domain, file_path);
  socket.Send(request.c_str(), request.size());

  SocketDataStream stream(socket);
  HttpHeader http_header = GetHeader(stream);
  ASSERT_EQ(http_header.protocol_type, "HTTP/1.0");
  ASSERT_EQ(http_header.status_code, "301");
  ASSERT_EQ(http_header.status, "Moved Permanently");
  ASSERT_TRUE(http_header.fields.find("Server") != http_header.fields.end());
}

TEST(GetHeader, OkStatus) {
  std::string domain = "speedtest.ftp.otenet.gr";
  std::string file_path = "/files/test100Mb.db";
  Socket socket;
  socket.Connect(domain);
  std::string request = url_utils::CreateGetHttpRequest(domain, file_path);
  socket.Send(request.c_str(), request.size());

  SocketDataStream stream(socket);
  HttpHeader http_header = GetHeader(stream);
  ASSERT_EQ(http_header.protocol_type, "HTTP/1.1");
  ASSERT_EQ(http_header.status_code, "200");
  ASSERT_EQ(http_header.status, "OK");
  ASSERT_TRUE(http_header.fields.find("Server") != http_header.fields.end());
}