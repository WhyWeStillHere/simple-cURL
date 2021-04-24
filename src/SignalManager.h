#ifndef MY_CURL__SIGNALMANAGER_H_
#define MY_CURL__SIGNALMANAGER_H_

#include <csignal>

class SignalManager {
 private:
  SignalManager();
  static SignalManager *instance_;

 public:
  SignalManager(SignalManager &other) = delete;
  void operator=(const SignalManager &) = delete;

  static SignalManager *GetInstance();
  static void Destroy();
  static void ProgressHandlerCaller(int signum);

  void ConfigureSignals();
  bool ShowProgress() const;

 private:
  void ProgressHandler(int signum);
  volatile sig_atomic_t show_progress_ = 0;
};

#endif //MY_CURL__SIGNALMANAGER_H_
