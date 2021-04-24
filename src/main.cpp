#include "NetworkDownloader.h"
#include "SignalManager.h"
#include "ArgParser.h"

int main(int argc, char *argv[]) {
  const std::string default_filename = "downloaded_data";
  // Parsing command line arguments
  ArgParser arg_parser;
  arg_parser.Parse(argc, argv);
  std::string file_path = "./" + (arg_parser.GetFilename().empty() ? default_filename : arg_parser.GetFilename());

  // Initializing Signal Manager and configuring signals
  SignalManager *signal_manager = SignalManager::GetInstance();
  signal_manager->ConfigureSignals();

  // Downloading needed file
  NetworkDownloader downloader;
  downloader.Download(arg_parser.GetUrl(), file_path);

  // Destroying singleton object
  SignalManager::Destroy();
  return 0;
}
