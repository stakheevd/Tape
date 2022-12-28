#ifndef TAPE_HPP
#define TAPE_HPP

#include <fstream>
#include <iostream>
#include <memory>
#include <cmath>
#include <chrono>
#include <thread>

struct Configuration
{
  Configuration(int lat = 0) noexcept : 
    LATENCY(lat)
  {} 

  const unsigned int LATENCY;
};

class Tape
{
public:
  Tape(std::fstream& data_stream, Configuration* conf);

  Tape(const Tape& other_tape) = delete;
  Tape(Tape&& other_tape) = delete;

  ~Tape();

  Tape& operator=(const Tape& other_tape) = delete;
  Tape& operator=(Tape&& other_tape) = delete;
  
  void series_sort(unsigned int pow = 0);
  void simulate_latency(unsigned int msec = 0);
  bool is_sorted(int& temp_value, int& next_temp_value);

private:
  std::unique_ptr<Configuration> configuration_ptr;
  std::fstream stream;

  unsigned int power;
  int temp_value;
  int next_temp_value;
  unsigned int first_tape_index;
  unsigned int second_tape_index;
};

#endif
