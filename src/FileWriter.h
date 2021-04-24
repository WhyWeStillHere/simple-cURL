#ifndef MY_CURL__FILEWRITER_H_
#define MY_CURL__FILEWRITER_H_

#include <optional>
#include "ProgressBar.h"

class FileWriter {
 public:
  explicit FileWriter(const std::string &file_path);
  ~FileWriter();
  void Write(const char *buffer, std::size_t buffer_size);
  void AddProgressBar(ProgressBar progress_bar);

 private:
  FILE *file_;
  std::optional<ProgressBar> progress_bar_;

 private:
  void RedrawProgressBar();
};

#endif //MY_CURL__FILEWRITER_H_
