#ifndef TAPE_HPP
#define TAPE_HPP

#include <fstream>
#include <string>
#include <list>
#include <queue>
#include <iostream>
#include <memory>
#include <algorithm>
#include <cmath>

using Node = std::pair<int, int>;

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

struct Compare
{
  bool operator() (Node& first_node, Node& second_node)
  {
    return first_node.first >= second_node.first;
  }
};

class Tape
{
public:
  Tape(std::fstream& input_stream, std::ofstream& output_stream, Configuration* conf) noexcept;

  void init_runs();
  void merge_files();

  void read_data(unsigned int pow);

  Tape(const Tape& other_tape) = delete;
  Tape(Tape&& other_tape) = delete;

  ~Tape();

  Tape& operator=(const Tape& other_tape) = delete;
  Tape& operator=(Tape&& other_tape) = delete;

  unsigned int power;

private:
  std::list<int> tape;
  std::unique_ptr<Configuration> configuration_ptr;

  std::fstream in_stream;
  std::ofstream out_stream;


  unsigned int number_of_element;
  unsigned int current_index;
  unsigned int chunk_counter;

  void read_block();
};

#endif
