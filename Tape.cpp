#include "Tape.hpp"

Tape::Tape(std::fstream& data_stream, Configuration* conf) noexcept :
  configuration_ptr(conf),
  stream(std::move(data_stream)),
  power(0)
{
}

void Tape::series_sort(unsigned int pow)
{
  int next_temp_value = 0;
  int temp_value = 0;
  bool is_sorted = true;

  stream.clear();
  stream.seekp(stream.beg);

  stream >> temp_value;
  simulate_latency(configuration_ptr->LATENCY);

  if ((pow == 0) && (!stream.eof()) && (!stream.good()))
    std::cerr << "Error: Invalid input data\n";

  while (stream >> next_temp_value)
  {
    simulate_latency(configuration_ptr->LATENCY);

    if (next_temp_value < temp_value)
    {
      is_sorted = false;
      break;
    }

    temp_value = next_temp_value;
  }

  if (is_sorted)
    return;
  
  stream.clear();
  stream.seekp(stream.beg);

  std::fstream first_tape_stream("/tmp/first_tape", std::ios::out | std::ios::in | std::ios::trunc);
  std::fstream second_tape_stream("/tmp/second_tape", std::ios::out | std::ios::in | std::ios::trunc);

  unsigned int first_tape_index = 0;
  unsigned int second_tape_index = 0;

  while (stream.good())
  {
    second_tape_index = 0;
    if (first_tape_index % (static_cast<unsigned int>(std::pow(2 , (pow))) * 2) == 0)
    {
      for (second_tape_index = 0; second_tape_index < std::pow(2, pow) && stream.good(); second_tape_index++)
      {
        if (stream >> temp_value)
        {
          simulate_latency(configuration_ptr->LATENCY);

          first_tape_stream << temp_value << " ";
          simulate_latency(configuration_ptr->LATENCY);

          first_tape_index++;
        }
      }
    }
    else
    {
      for (second_tape_index = 0; second_tape_index < std::pow(2, pow) && stream.good(); second_tape_index++)
      {
        if (stream >> temp_value)
        {
          simulate_latency(configuration_ptr->LATENCY);

          second_tape_stream << temp_value << " ";
          simulate_latency(configuration_ptr->LATENCY);

          first_tape_index++;
        }
      }
    }
  }

  if ((pow == 0) && (!stream.eof()) && (!stream.good()))
    std::cerr << "Error: Invalid input data\n";

  std::flush(first_tape_stream);
  std::flush(second_tape_stream);

  first_tape_stream.clear();
  first_tape_stream.seekg(first_tape_stream.beg);
  
  second_tape_stream.clear();
  second_tape_stream.seekg(second_tape_stream.beg);

  stream.clear();
  stream.seekp(stream.beg);

  first_tape_stream >> temp_value;
  simulate_latency(configuration_ptr->LATENCY);

  second_tape_stream >> next_temp_value;
  simulate_latency(configuration_ptr->LATENCY);

  while (first_tape_stream.good() || second_tape_stream.good())
  {
    if (first_tape_stream.good())
      second_tape_index = 0;
    
    if (second_tape_stream.good())
      first_tape_index = 0;

    while ((first_tape_index < std::pow(2, pow) && second_tape_stream.good()) 
        || (second_tape_index < std::pow(2, pow) && first_tape_stream.good()))
    {
      if (temp_value <= next_temp_value || first_tape_index == std::pow(2, pow))
      {
        if (second_tape_index == (std::pow(2, pow)))
        {
          stream << next_temp_value << " ";
          simulate_latency(configuration_ptr->LATENCY);

          if (second_tape_stream.good() && second_tape_stream >> next_temp_value)
            simulate_latency(configuration_ptr->LATENCY);

          first_tape_index++;
        }
        else
        {
          stream << temp_value << " ";
          simulate_latency(configuration_ptr->LATENCY);

          if (first_tape_stream.good() && first_tape_stream >> temp_value)
            simulate_latency(configuration_ptr->LATENCY);
          
          second_tape_index++;
        }
      }
      else if (next_temp_value < temp_value || second_tape_index == std::pow(2, pow))
      {
        if (!second_tape_stream.good() && first_tape_index != (std::pow(2, pow)))
        {
          first_tape_index++;
          continue;
        }

        if (first_tape_index == (std::pow(2, pow)))
        {
          stream << temp_value << " ";
          simulate_latency(configuration_ptr->LATENCY);

          if (first_tape_stream.good() && first_tape_stream >> temp_value)
            simulate_latency(configuration_ptr->LATENCY);
          
          second_tape_index++;
        }
        else
        {
          stream << next_temp_value << " ";
          simulate_latency(configuration_ptr->LATENCY);

          if (second_tape_stream.good() && second_tape_stream >> next_temp_value)
            simulate_latency(configuration_ptr->LATENCY);
          
          first_tape_index++;
        }
      }
    }
  }

  std::flush(stream);

  first_tape_stream.clear();
  first_tape_stream.seekp(first_tape_stream.beg);

  second_tape_stream.clear();
  second_tape_stream.seekp(second_tape_stream.beg);

  stream.clear();
  stream.seekg(stream.beg);

  first_tape_stream.close();
  second_tape_stream.close();

  series_sort(++power);
}

void Tape::simulate_latency(unsigned int ms)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

Tape::~Tape()
{
  stream.close();
}
