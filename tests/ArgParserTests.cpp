#include <gtest/gtest.h>
#include "../src/ArgParser.h"

TEST(Parse, NoArgs) {
  ArgParser parser;
  ASSERT_EXIT(parser.Parse(0, NULL),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "To few program arguments\n");
}

TEST(Parse, OneArgHasFilename) {
  ArgParser parser;
  char url[] = "http://www.not_existing_url.kek/31231/fsdfsd.kek";
  std::string expected_filename = "fsdfsd.kek";
  int argc = 2;
  char* argv[argc];
  argv[1] = url;
  parser.Parse(argc, argv);
  ASSERT_EQ(parser.GetUrl(), url);
  ASSERT_EQ(parser.GetFilename(), expected_filename);
}

TEST(Parse, OneArgNoFilename) {
  ArgParser parser;
  char url[] = "https://another_strange_url_1231.lol";
  int argc = 2;
  char* argv[argc];
  argv[1] = url;
  parser.Parse(argc, argv);
  ASSERT_EQ(parser.GetUrl(), url);
  ASSERT_TRUE(parser.GetFilename().empty());
}

TEST(Parse, TwoArgs) {
  ArgParser parser;
  char url[] = "https://another_strange_url_1231.lol";
  char filename[] = "very_strange_file.xxx";
  int argc = 3;
  char* argv[argc];
  argv[1] = url;
  argv[2] = filename;
  parser.Parse(argc, argv);
  ASSERT_EQ(parser.GetUrl(), url);
  ASSERT_EQ(parser.GetFilename(), std::string(filename));
}