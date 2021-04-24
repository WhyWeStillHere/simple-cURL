#!/bin/bash

URLS="http://speedtest.ftp.otenet.gr/files/test100k.db"
URLS="${URLS} http://speedtest.ftp.otenet.gr/files/test1Mb.db"
URLS="${URLS} http://speedtest.ftp.otenet.gr/files/test10Mb.db"
#URLS="${URLS} http://speedtest.ftp.otenet.gr/files/test100Mb.db"

mkdir integrational_test_dir
cd integrational_test_dir

echo "Building project"

cmake ../..
make

echo ""
echo "Start tests"
echo "You can send SIGUSR1 to check download progress for my cURL"
echo ""

for url in $URLS
do
    echo "Downloading: ${url}"

    start=$SECONDS
    ./my_cURL "$url" my_cURL_download
    my_cURL_time=$(( SECONDS - start ))
    echo "My curl download time: ${my_cURL_time} s"

    start=$SECONDS
    curl -o cURL_download "$url" --silent
    cURL_time=$(( SECONDS - start ))
    echo "Standard curl download time: ${cURL_time} s"

    if ! diff -q my_cURL_download cURL_download >/dev/null; then
        echo "File ${url} corrupted while downloading!"
    fi

    echo ""
done

cd ..
rm -r integrational_test_dir