#include <gtest/gtest.h>
#include "../src/FileWriter.h"

TEST(Constructor, InvalidFilePath) {
  ASSERT_EXIT(FileWriter("/!@#!#asdfasdf/qwe123/dfasdfs/"),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "Can't open file for writing\n");
}

TEST(Constructor, FileCreation) {
  std::string tmp_filename = "__test_file_with_very_strange_name_0183165462287649";
  {
    FileWriter writer(tmp_filename);
  }

  struct stat file_status;
  int error_status = stat(tmp_filename.c_str(), &file_status);
  ASSERT_EQ(error_status, 0);
  std::remove(tmp_filename.c_str());

  ASSERT_EQ(file_status.st_size, 0);
}

TEST(Write, WritingToFile) {
  std::string tmp_filename = "__test_file_with_very_strange_name_0183165462282341234";
  std::string file_data = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Ut id risus mauris. Aenean luctus turpis enim, ac congue eros blandit sollicitudin. Aenean eu dui nunc. Nulla porttitor mollis tincidunt. Ut vel dui vel purus fermentum congue. Maecenas bibendum dolor a risus bibendum laoreet. Donec scelerisque nibh quam. Quisque sed lobortis magna. Praesent sed massa maximus eros condimentum maximus id in lectus. Interdum et malesuada fames ac ante ipsum primis in faucibus. Vestibulum rhoncus massa at tellus facilisis dapibus. Aenean vehicula, lacus vitae pretium feugiat, dui quam luctus nibh, at aliquam massa leo molestie leo. ";
  {
    FileWriter writer(tmp_filename);
    writer.Write(file_data.c_str(), file_data.size());
  }

  struct stat file_status;
  int error_status = stat(tmp_filename.c_str(), &file_status);
  ASSERT_EQ(error_status, 0);
  ASSERT_EQ(file_status.st_size, file_data.size());

  char written_text[file_data.size()];
  FILE* test_file = fopen(tmp_filename.c_str(), "r");
  int operation_result = fread(written_text, sizeof(written_text), 1, test_file);
  ASSERT_EQ(operation_result, 1);
  ASSERT_EQ(file_data, std::string(written_text, file_data.size()));
  fclose(test_file);

  std::remove(tmp_filename.c_str());
}