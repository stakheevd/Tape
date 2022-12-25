#include "Tape.hpp"

Tape::Tape(std::ifstream& input_stream, std::ofstream& output_stream, Configuration* conf) noexcept :
  tape(),
  configuration_ptr(conf),
  in_stream(std::move(input_stream)),
  out_stream(std::move(output_stream)),
  number_of_element(0),
  current_index(0)
{
}

void Tape::init_runs()
{
  int file_number = 0;

  while (!in_stream.eof() && in_stream.good())
  {
    read_block();
    tape.sort();

    std::ofstream temp_out;
    temp_out.open("/tmp/" + std::to_string(file_number++));

    for (auto iter = tape.begin(); iter != tape.end(); iter++)
    {
      temp_out << *iter << " ";
    }

    tape.clear();
  }

  if (!in_stream.good())
  {

  }
}

void Tape::merge_files()
{
}

void Tape::read_block()
{
  int temp_value = 0;

  while ((configuration_ptr->TAPE_LENGTH != current_index) 
    && (configuration_ptr->MEMORY_SIZE != tape.size()) && (in_stream >> temp_value))
  {
    if (current_index >= configuration_ptr->LOWER_LIMIT_INDEX 
      && current_index  <= configuration_ptr->UPPER_LIMIT_INDEX)
    {
      current_index++;
      continue;
    }

    tape.push_back(temp_value);

    //number_of_element++;
    current_index++;
  }

  if (configuration_ptr->TAPE_LENGTH == current_index)
  {
    return;
  }

  //if ((!in_stream.eof()) && (configuration_ptr->TAPE_LENGTH!= number_of_element) || in_stream.good())
  //{
  //  std::cerr << "Incorrect data\n";

  //  if (number_of_element == 0)
  //  {

  //  }
  //}

}

Tape::~Tape()
{
  in_stream.close();
  out_stream.close();
}
