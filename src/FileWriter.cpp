#include <fcntl.h>
#include <cstdio>
#include <string>
#include <system_error>
#include <cstring>
#include "FileWriter.h"
#include "SignalManager.h"
#include "Logger.h"

FileWriter::FileWriter(const std::string &file_path) {
  file_ = fopen(file_path.c_str(), "wb");
  if (file_ == NULL) {
    LOG_FATAL("Can't open file for writing\n");
  }
}

void FileWriter::Write(const char *buffer, std::size_t buffer_size) {
  std::size_t total_bytes_wrote = 0;
  if (progress_bar_.has_value()) {
    RedrawProgressBar();
  }
  while (buffer_size > total_bytes_wrote) {
    std::size_t bytes_wrote = fwrite(buffer, 1, buffer_size, file_);
    if (bytes_wrote == 0) {
      if (ferror(file_)) {
        LOG_FATAL("Error while writing to file");
      }
      break;
    }
    if (progress_bar_.has_value()) {
      progress_bar_->AddProgress(bytes_wrote);
      RedrawProgressBar();
    }
    total_bytes_wrote += bytes_wrote;
  }
}

FileWriter::~FileWriter() {
  if (progress_bar_.has_value()) {
    progress_bar_.value().FinishDrawing();
  }
  fclose(file_);
}

void FileWriter::AddProgressBar(ProgressBar progress_bar) {
  progress_bar_.emplace(progress_bar);
}
void FileWriter::RedrawProgressBar() {
  if (SignalManager::GetInstance()->ShowProgress()) {
    progress_bar_.value().DrawProgress();
  } else {
    progress_bar_.value().ClearLineIfNeeded();
  }
}
