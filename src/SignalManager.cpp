#include <bits/types/sigset_t.h>
#include <cerrno>
#include <cstring>
#include <system_error>
#include "SignalManager.h"

SignalManager *SignalManager::instance_ = nullptr;

void SignalManager::ProgressHandler(int signum) {
  show_progress_ = !show_progress_;
}

void SignalManager::ProgressHandlerCaller(int signum) {
  instance_->ProgressHandler(signum);
}

void SignalManager::ConfigureSignals() {
  // Catch, ignore and handle signals
  // Block all signals except SIGTERM, SIGINT, SIGUSR1
  sigset_t sig_mask;
  sigfillset(&sig_mask);
  sigdelset(&sig_mask, SIGTERM);
  sigdelset(&sig_mask, SIGINT);
  sigdelset(&sig_mask, SIGUSR1);
  sigprocmask(SIG_SETMASK, &sig_mask, NULL);

  // Assigning handler to signal
  struct sigaction action_usr1;
  memset(&action_usr1, 0, sizeof(action_usr1));
  action_usr1.sa_handler = SignalManager::ProgressHandlerCaller;
  action_usr1.sa_flags |= SA_RESTART;
  int ret;
  ret = sigaction(SIGUSR1, &action_usr1, NULL);
  if (ret < 0) {
    throw std::system_error(std::error_code(errno, std::system_category()), std::strerror(errno));
  }
}
SignalManager *SignalManager::GetInstance() {
  if (instance_ == nullptr) {
    instance_ = new SignalManager();
  }
  return instance_;
}
void SignalManager::Destroy() {
  delete instance_;
  instance_ = nullptr;
}
SignalManager::SignalManager() = default;
bool SignalManager::ShowProgress() const {
  return show_progress_;
}
