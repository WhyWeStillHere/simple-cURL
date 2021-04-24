#include <algorithm>
#include "ProgressBar.h"

ProgressBar::ProgressBar(long long size) : size_(size) {
}

void ProgressBar::AddProgress(long long progress) {
  progress_ = std::min(size_, progress_ + progress);
}

void ProgressBar::ClearCurrentLine() {
  printf("\33[2K\r");
  fflush(stdout);
}

void ProgressBar::DrawProgress() {
  if (!clear_line) {
    ClearCurrentLine();
  } else {
    clear_line = false;
  }
  const std::string prefix = "Progress: [";
  const std::string suffix = "] %.2f%%";

  std::size_t progress_width = kProgressBarWidth - prefix.size() - suffix.size();
  std::size_t current_progress = progress_ * progress_width / size_;

  printf("%s", prefix.c_str());
  for (std::size_t i = 0; i < current_progress; ++i) {
    printf("#");
  }
  for (std::size_t i = current_progress; i < progress_width; ++i) {
    printf(" ");
  }
  printf(suffix.c_str(), static_cast<float>(progress_) * 100 / size_);
  fflush(stdout);
}

void ProgressBar::ClearLineIfNeeded() {
  if (!clear_line) {
    ClearCurrentLine();
    ClearCurrentLine();
    clear_line = true;
  }
}

void ProgressBar::FinishDrawing() {
  if (!clear_line) {
    printf("\n");
  }
}

