#include <gtest/gtest.h>
#include "../src/Socket.h"
#include "../src/Utils.h"

TEST(Connect, InvalidDomain) {
  Socket socket;
  std::string domain = "!@#$%@#FCSDBDBNCVBWATWEssdfglkj123123";
  ASSERT_THROW(socket.Connect(domain), std::system_error);
}

TEST(Connect_Shutdown, ValidDomain) {
  Socket socket;
  std::string domain = "google.com";
  ASSERT_NO_THROW(socket.Connect(domain));
  ASSERT_NO_THROW(socket.Shutdown());
}

TEST(Send, GetRequest_1) {
  std::string domain = "google.com";
  std::string file_path = "/";
  Socket socket;
  socket.Connect(domain);
  std::string request = url_utils::CreateGetHttpRequest(domain, file_path);
  std::size_t sent_bytes = 0;

  ASSERT_NO_THROW(sent_bytes = socket.Send(request.c_str(), request.size()));
  ASSERT_EQ(sent_bytes, request.size());
  socket.Shutdown();
}

TEST(Send, GetRequest_2) {
  std::string domain = "speedtest.ftp.otenet.gr";
  std::string file_path = "/files/test100Mb.db";
  Socket socket;
  socket.Connect(domain);
  std::string request = url_utils::CreateGetHttpRequest(domain, file_path);
  std::size_t sent_bytes = 0;

  ASSERT_NO_THROW(sent_bytes = socket.Send(request.c_str(), request.size()));
  ASSERT_EQ(sent_bytes, request.size());
  socket.Shutdown();
}

TEST(Recv, GetRequest) {
  std::string domain = "google.com";
  std::string file_path = "/";
  char buffer[4096];
  Socket socket;
  socket.Connect(domain);
  std::string request = url_utils::CreateGetHttpRequest(domain, file_path);
  socket.Send(request.c_str(), request.size());

  std::size_t bytes_received = socket.Recv(buffer, sizeof(buffer));
  ASSERT_GT(bytes_received, 0);
  socket.Shutdown();
}