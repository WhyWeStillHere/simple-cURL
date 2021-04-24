#include <gtest/gtest.h>
#include "../src/Utils.h"

using namespace url_utils;

TEST(GetDomain, HttpsPrefix) {
  std::string url = "https://cmake.org/cmake/help/latest/command/add_test.html";
  std::string domain = "cmake.org";
  ASSERT_EQ(GetDomain(url), domain);
}

TEST(GetDomain, NoPrefix) {
  std::string url = "cmake.org/cmake/help/latest/command/add_test.html";
  std::string domain = "cmake.org";
  ASSERT_EQ(GetDomain(url), domain);
}

TEST(GetDomain, HttpPrefix) {
  std::string url = "http://google.github.io";
  std::string domain = "google.github.io";
  ASSERT_EQ(GetDomain(url), domain);
}

TEST(GetFilepath, BigPath) {
  std::string url = "https://cmake.org/cmake/help/latest/command/add_test.html";
  std::string filepath = "/cmake/help/latest/command/add_test.html";
  ASSERT_EQ(GetFilepath(url), filepath);
}

TEST(GetFilepath, SmallPath) {
  std::string url = "cmake.org/add_test.html";
  std::string filepath = "/add_test.html";
  ASSERT_EQ(GetFilepath(url), filepath);
}

TEST(GetFilepath, EmptyPath) {
  std::string url = "http://google.github.io";
  std::string filepath = "/";
  ASSERT_EQ(GetFilepath(url), filepath);
}

TEST(GetFilename, BigPath) {
  std::string url = "https://cmake.org/cmake/help/latest/command/add_test.html";
  std::string filename = "add_test.html";
  ASSERT_EQ(GetFilename(url), filename);
}

TEST(GetFilename, SmallPath) {
  std::string url = "cmake.org/add_test.html";
  std::string filename = "add_test.html";
  ASSERT_EQ(GetFilename(url), filename);
}

TEST(GetFilename, EmptyName) {
  std::string url = "http://google.github.io";
  std::string filename = "";
  ASSERT_EQ(GetFilename(url), filename);
}

TEST(CreateGetHttpRequest, BaseCase_1) {
  std::string filepath = "/add_test.html";
  std::string domain = "localhost";
  std::string expected_http = "GET /add_test.html HTTP/1.0\r\n"
                              "Host: localhost\r\n\r\n";
  ASSERT_EQ(CreateGetHttpRequest(domain, filepath), expected_http);
}

TEST(CreateGetHttpRequest, BaseCase_2) {
  std::string filepath = "/hello.txt";
  std::string domain = "www.example.com";
  std::string expected_http = "GET /hello.txt HTTP/1.0\r\n"
                              "Host: www.example.com\r\n\r\n";
  ASSERT_EQ(CreateGetHttpRequest(domain, filepath), expected_http);
}