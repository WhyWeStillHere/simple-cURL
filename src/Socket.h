#ifndef MY_CURL__SOCKET_H_
#define MY_CURL__SOCKET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <string>

class Socket {
 public:
  Socket();
  ~Socket();
  void Connect(const std::string &domain);
  std::size_t Send(const char *buffer, std::size_t buffer_size) const;
  std::size_t Recv(char *buffer, std::size_t buffer_size) const;
  void Shutdown();

 private:
  const int kPort = 80;
  int socket_fd_;
};

#endif //MY_CURL__SOCKET_H_
