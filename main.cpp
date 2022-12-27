#include "Tape.hpp"

int main()
{
  // From argv
  std::string input_file_name = "inpf.txt";
  std::string output_file_name = "ou.txt";

  if (input_file_name.empty())
  {
    std::cerr << "Incorrect name of input file\n";
    return -1;
  }

  if (output_file_name.empty())
  {
    std::cerr << "Incorrect name of output file\n";
    return -1;
  }

  std::fstream input_file;
  input_file.open(input_file_name);

  if (!input_file.is_open())
  {
    std::cerr << "Input file not found\n";
    return -1;
  }

  std::ofstream output_file;
  output_file.open(output_file_name);

  std::ifstream config_file;
  config_file.open("config.txt");

  if (config_file.is_open())
  {
    // Read config here
  }

  unsigned int memory_limit = 5;

  Tape tape(input_file, output_file, new Configuration(memory_limit, 3, 100, -1, -1));

  //tape.init_runs();
  tape.read_data(tape.power);

  return 0;
}