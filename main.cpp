#include <iostream>
#include <string>

#include "Tape.hpp"

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr << "Usage: ./main [file_name]\n"; 
    return 1;
  }

  std::string file_name = argv[1];

  if (file_name.empty())
  {
    std::cerr << "Error: Incorrect name of file\n";
    return 1;
  }

  std::fstream input_file(file_name);
  if (!input_file.is_open())
  {
    std::cerr << "Error: File " << file_name << " not found\n";
    return 1;
  }

  int latency = 0;

  std::ifstream config_stream("config.txt");
  if (config_stream.is_open())
  {
    config_stream >> latency;

    if (latency < 0)
    {
      std::cerr << "Error: Latency is a positive number\n";
      return 1;
    }
  }
  else
  {
    std::cerr << "Error: Config file (config.txt) not found\n";
    return 1;
  }
  config_stream.close();

  Tape tape(input_file, new Configuration(latency));
  
  auto start = std::chrono::high_resolution_clock::now();

  tape.series_sort();

  auto end = std::chrono::high_resolution_clock::now();

  std::cout << "Result is saved in " << file_name << '\n'
            << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
            << " ms.\n";
  
  return 0;
}
