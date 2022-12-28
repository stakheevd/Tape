#include <gtest/gtest.h>

#include "Tape.hpp"

class TapeTest : public ::testing::Test
{
protected:
  void SetUp(const std::string& fname, int latency)
  {
    std::fstream input_stream(fname);
    tape_ptr = new Tape(input_stream, new Configuration(latency));
  }

  virtual void TearDown()
  {
    delete tape_ptr;
  }

  Tape* tape_ptr;
};

TEST_F(TapeTest, Sorting_0Elements_IsSorted) {
  SetUp("numbers_0.txt", 0);
  int temp_value = 0;
  int next_temp_value = 0;

  ASSERT_TRUE(tape_ptr->is_sorted(temp_value, next_temp_value));
}

TEST_F(TapeTest, Sorting_1Elements_IsSorted) {
  SetUp("numbers_1.txt", 0);
  int temp_value = 0;
  int next_temp_value = 0;

  ASSERT_TRUE(tape_ptr->is_sorted(temp_value, next_temp_value));
}

TEST_F(TapeTest, Sorting_100Elements_IsSorted) {
  SetUp("numbers_100.txt", 0);
  int temp_value = 0;
  int next_temp_value = 0;

  EXPECT_FALSE(tape_ptr->is_sorted(temp_value, next_temp_value));

  tape_ptr->series_sort();

  ASSERT_TRUE(tape_ptr->is_sorted(temp_value, next_temp_value));
}

TEST_F(TapeTest, Sorting_1000Elements_IsSorted) {
  SetUp("numbers_1000.txt", 0);
  int temp_value = 0;
  int next_temp_value = 0;

  EXPECT_FALSE(tape_ptr->is_sorted(temp_value, next_temp_value));

  tape_ptr->series_sort();

  ASSERT_TRUE(tape_ptr->is_sorted(temp_value, next_temp_value));
}

TEST_F(TapeTest, Sorting_10000Elements_IsSorted) {
  SetUp("numbers_10000.txt", 0);
  int temp_value = 0;
  int next_temp_value = 0;

  EXPECT_FALSE(tape_ptr->is_sorted(temp_value, next_temp_value));

  tape_ptr->series_sort();

  ASSERT_TRUE(tape_ptr->is_sorted(temp_value, next_temp_value));
}

TEST_F(TapeTest, Sorting_100000Elements_IsSorted) {
  SetUp("numbers_100000.txt", 0);
  int temp_value = 0;
  int next_temp_value = 0;

  EXPECT_FALSE(tape_ptr->is_sorted(temp_value, next_temp_value));

  tape_ptr->series_sort();

  ASSERT_TRUE(tape_ptr->is_sorted(temp_value, next_temp_value));
}

TEST_F(TapeTest, Sorting_1000000Elements_IsSorted) {
  SetUp("numbers_1000000.txt", 0);
  int temp_value = 0;
  int next_temp_value = 0;

  EXPECT_FALSE(tape_ptr->is_sorted(temp_value, next_temp_value));

  tape_ptr->series_sort();

  ASSERT_TRUE(tape_ptr->is_sorted(temp_value, next_temp_value));
}

TEST_F(TapeTest, Sorting_10000000Elements_IsSorted) {
  SetUp("numbers_10000000.txt", 0);
  int temp_value = 0;
  int next_temp_value = 0;

  EXPECT_FALSE(tape_ptr->is_sorted(temp_value, next_temp_value));

  tape_ptr->series_sort();

  ASSERT_TRUE(tape_ptr->is_sorted(temp_value, next_temp_value));
}

TEST_F(TapeTest, Sorting_InvalidData_PartiallySorted) {
  SetUp("invalid_data.txt", 0);
  int temp_value = 0;
  int next_temp_value = 0;

  testing::internal::CaptureStderr();

  ASSERT_FALSE(tape_ptr->is_sorted(temp_value, next_temp_value));

  tape_ptr->series_sort();

  std::string mes = testing::internal::GetCapturedStderr();
  ASSERT_STREQ("Error: Invalid input data\n", mes.c_str());
  ASSERT_TRUE(tape_ptr->is_sorted(temp_value, next_temp_value));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
