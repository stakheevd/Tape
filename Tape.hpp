#ifndef TAPE_HPP
#define TAPE_HPP

#include <fstream>
#include <string>
#include <list>
#include <iostream>
#include <memory>
#include <algorithm>

struct Configuration
{
  Configuration(unsigned int mem, unsigned int lat = 0, int len = -1, int low_ind = -1, int up_ind = -1) : 
    MEMORY_SIZE(mem), 
    LATENCY(lat),
    TAPE_LENGTH(len),
    LOWER_LIMIT_INDEX(low_ind),
    UPPER_LIMIT_INDEX(up_ind)
  {} 

  unsigned int MEMORY_SIZE;
  unsigned int LATENCY;
  int TAPE_LENGTH;
  int LOWER_LIMIT_INDEX;
  int UPPER_LIMIT_INDEX;
};

class Tape
{
public:
  Tape(std::ifstream& input_stream, std::ofstream& output_stream, Configuration* conf) noexcept;

  void init_runs();
  void merge_files();

  Tape(const Tape& other_tape) = delete;
  Tape(Tape&& other_tape) = delete;

  ~Tape();

  Tape& operator=(const Tape& other_tape) = delete;
  Tape& operator=(Tape&& other_tape) = delete;

private:
  std::list<int> tape;
  std::unique_ptr<Configuration> configuration_ptr;

  std::ifstream in_stream;
  std::ofstream out_stream;

  unsigned int number_of_element;
  unsigned int current_index;

  void read_block();
};

#endif
