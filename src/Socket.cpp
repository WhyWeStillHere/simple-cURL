#include <system_error>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include "Socket.h"

Socket::Socket() {
  socket_fd_ = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd_ < 0) {
    throw std::system_error(std::error_code(errno, std::system_category()), std::strerror(errno));
  }
}
Socket::~Socket() {
  close(socket_fd_);
}
void Socket::Connect(const std::string &domain) {
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(kPort);

  struct hostent *hosts = gethostbyname(domain.data());
  if (hosts == NULL) {
    throw std::system_error(std::error_code(errno, std::system_category()), std::strerror(errno));
  }
  memcpy(&addr.sin_addr, hosts->h_addr_list[0], sizeof(addr.sin_addr));

  int connect_ret = connect(socket_fd_, (struct sockaddr *) &addr, sizeof(addr));
  if (connect_ret == -1) {
    throw std::system_error(std::error_code(errno, std::system_category()), std::strerror(errno));
  }
}
std::size_t Socket::Send(const char *buffer, std::size_t buffer_size) const {
  std::size_t total_bytes_wrote = 0;
  while (buffer_size > total_bytes_wrote) {
    ssize_t bytes_wrote = write(
        socket_fd_,
        static_cast<const void *>(buffer + total_bytes_wrote),
        buffer_size - total_bytes_wrote);
    if (bytes_wrote < 0) {
      if (errno == EAGAIN) {
        continue;
      }
      throw std::system_error(std::error_code(errno, std::system_category()), std::strerror(errno));
    }
    if (bytes_wrote == 0) {
      break;
    }

    total_bytes_wrote += bytes_wrote;
  }
  return total_bytes_wrote;
}
void Socket::Shutdown() {
  shutdown(socket_fd_, SHUT_RDWR);
}
std::size_t Socket::Recv(char *buffer, std::size_t buffer_size) const {
  std::size_t total_bytes_read = 0;
  while (buffer_size > total_bytes_read) {
    ssize_t bytes_read = read(
        socket_fd_,
        static_cast<void *>(buffer + total_bytes_read),
        buffer_size - total_bytes_read);
    if (bytes_read < 0) {
      if (errno == EAGAIN) {
        continue;
      }
      throw std::system_error(std::error_code(errno, std::system_category()), std::strerror(errno));
    }
    if (bytes_read == 0) {
      break;
    }

    total_bytes_read += bytes_read;
  }
  return total_bytes_read;
}
