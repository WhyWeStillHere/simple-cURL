# Simple curl tool
Basic tool to download files via http

## Installation
```
cd $PRODJECT_FOLDER_PATH
cmake ./CMakeLists.txt 
make
```

## Usage
```
./my_cURL <file url> [filename after download]
```
#### Signals:
You can send SIGUSR1 to show progress bar. Send SIGUSR1 again to hide progress bar. <br>
Send SIGTERM and SIGINT to turn off the program.  <br>
Other signals are ignored.

## Testing 
#### Run tests:
```
// Run unit tests
./my_cURL_tests 
// Run integration tests
bash tests/integrational_tests.sh 
```
#### About tests:
Integration tests download files of different size via standard curl and my realization. <br>
It compares two files (if they different it will write error) and print work time of my curl tool and standard curl tool.
