#ifndef MY_CURL__PROGRESSBAR_H_
#define MY_CURL__PROGRESSBAR_H_

#include <cstdio>

class ProgressBar {
 public:
  explicit ProgressBar(long long size);
  void AddProgress(long long progress);
  void DrawProgress();
  void ClearLineIfNeeded();
  void FinishDrawing();

 private:
  const std::size_t kProgressBarWidth = 72;

 private:
  static void ClearCurrentLine();

  long long size_ = 1;
  long long progress_ = 0;
  bool clear_line = true;
};

#endif //MY_CURL__PROGRESSBAR_H_
