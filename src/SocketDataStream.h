#ifndef MY_CURL__SOCKETDATASTREAM_H_
#define MY_CURL__SOCKETDATASTREAM_H_

#include "Socket.h"
#include "FileWriter.h"

class SocketDataStream {
 public:
  explicit SocketDataStream(const Socket &socket);
  char NextValue(bool &reached_eof);
  void SaveToFile(FileWriter &writer, long long file_size);

 private:
  static const std::size_t kBufferSize = 4096 * 4;
  char buffer_[kBufferSize];
  std::size_t buffer_index_ = 0;
  std::size_t current_buffer_size_ = 0;
  const Socket &socket_;
};

#endif //MY_CURL__SOCKETDATASTREAM_H_
