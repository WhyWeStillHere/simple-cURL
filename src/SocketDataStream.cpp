#include <optional>
#include "SocketDataStream.h"
#include "FileWriter.h"

SocketDataStream::SocketDataStream(const Socket &socket) : socket_(socket) {
}

void SocketDataStream::SaveToFile(FileWriter &writer, long long file_size) {
  uint64_t bytes_wrote = 0;

  // Saving leftovers from buffer
  if (buffer_index_ < current_buffer_size_) {
    writer.Write(buffer_ + buffer_index_, current_buffer_size_ - buffer_index_);
    bytes_wrote += current_buffer_size_ - buffer_index_;
    buffer_index_ = 0;
    current_buffer_size_ = 0;
  }

  // Loading new data
  while (bytes_wrote < file_size) {
    current_buffer_size_ = socket_.Recv(buffer_, kBufferSize);
    if (current_buffer_size_ == 0) {
      throw std::runtime_error("Incomplete server data");
    }
    writer.Write(buffer_, current_buffer_size_);
    bytes_wrote += current_buffer_size_;
  }
}

char SocketDataStream::NextValue(bool &reached_eof) {
  if (buffer_index_ >= current_buffer_size_) {
    current_buffer_size_ = socket_.Recv(buffer_, kBufferSize);
    if (current_buffer_size_ == 0) {
      reached_eof = true;
      return 0;
    }
    buffer_index_ = 0;
  }

  return buffer_[buffer_index_++];
}