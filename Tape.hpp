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
  Configuration(unsigned int lat = 0) : 
    LATENCY(lat)
  {} 

  unsigned int LATENCY;
};

class Tape
{
public:
  Tape(std::fstream& data_stream, Configuration* conf) noexcept;

  Tape(const Tape& other_tape) = delete;
  Tape(Tape&& other_tape) = delete;

  ~Tape();

  Tape& operator=(const Tape& other_tape) = delete;
  Tape& operator=(Tape&& other_tape) = delete;
  
  void series_sort(unsigned int pow = 0);
  void simulate_latency(unsigned int msec = 0);

private:
  std::unique_ptr<Configuration> configuration_ptr;
  std::fstream stream;
  unsigned int power;
};

#endif
