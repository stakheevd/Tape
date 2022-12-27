#include "Tape.hpp"

Tape::Tape(std::fstream& input_stream, std::ofstream& output_stream, Configuration* conf) noexcept :
  tape(),
  configuration_ptr(conf),
  in_stream(std::move(input_stream)),
  out_stream(std::move(output_stream)),
  power(0),
  number_of_element(0),
  current_index(0),
  chunk_counter(0)
{
}

void Tape::init_runs()
{
  while (!in_stream.eof() && in_stream.good())
  {
    read_block();
    tape.sort();

    std::ofstream temp_out;
    temp_out.open("/tmp/" + std::to_string(chunk_counter++));

    for (auto iter = tape.begin(); iter != tape.end(); iter++)
    {
      temp_out << *iter << " ";
    }

    tape.clear();
    temp_out.close();
  }

  if (!in_stream.good())
  {

  }

  in_stream.close();
}

void Tape::merge_files()
{
  int chunk = 0;
  for (int i = 0; i < chunk_counter; i+= configuration_ptr->MEMORY_SIZE - 1)
  while (chunk != chunk_counter)
  {
    for (int j = chunk; j < configuration_ptr->MEMORY_SIZE - 1 + chunk && chunk != chunk_counter; j++)
    {
      std::priority_queue<Node, std::list<Node>, Compare> min_heap;

      std::unique_ptr<std::ifstream[]> input_stream_arr = std::make_unique<std::ifstream[]>(chunk_counter);
    
    }

    if (configuration_ptr->MEMORY_SIZE - 1 > chunk_counter - chunk)
      chunk = 8;
    else
      chunk = 5 - 5;

  }
  
}

void Tape::read_data(unsigned int pow)
{
  int next_temp_value = 0;
  int temp_value = 0;
  bool is_sorted = true;

  in_stream.clear();
  in_stream.seekg(in_stream.beg);
  in_stream.seekp(in_stream.beg);

  in_stream >> temp_value;

  while (in_stream >> next_temp_value)
  {
    if (next_temp_value < temp_value)
    {
      is_sorted = false;
      break;
    }

    temp_value = next_temp_value;
  }

  if (is_sorted)
    return;
  
  in_stream.clear();
  in_stream.seekg(in_stream.beg);
  in_stream.seekp(in_stream.beg);

  std::fstream temp_out_ev("/tmp/even", std::ios::out | std::ios::in | std::ios::trunc);
  std::fstream temp_out_nev("/tmp/noteven", std::ios::out | std::ios::in | std::ios::trunc);

  //in_stream.(std::ios::trunc);

  if (!temp_out_ev.is_open())
    std::cout << "123" << std::endl;

  unsigned int div = 0;
  unsigned int i = 0;

  while (in_stream.good())
  {
    i = 0;
    if (div % (static_cast<unsigned int>(std::pow(2 , (pow))) * 2) == 0)
    {
      for (i = 0; i < std::pow(2, pow) && in_stream.good(); i++)
      {
        if (in_stream >> temp_value)
        {
          temp_out_ev << temp_value << " ";
          div++;
        }
      }
    }
    else
    {
      for (i = 0; i < std::pow(2, pow) && in_stream.good(); i++)
      {
        if (in_stream >> temp_value)
        {
          temp_out_nev << temp_value << " ";
          div++;
        }
      }
    }
  }

  std::flush(temp_out_ev);
  std::flush(temp_out_nev);

  temp_out_ev.clear();
  temp_out_ev.seekg(temp_out_ev.beg);
  temp_out_ev.seekp(temp_out_ev.beg);
  
  temp_out_nev.clear();
  temp_out_nev.seekg(temp_out_nev.beg);
  temp_out_nev.seekp(temp_out_nev.beg);

  in_stream.clear();
  in_stream.seekg(in_stream.beg);
  in_stream.seekp(in_stream.beg);

  temp_out_ev >> temp_value;
  temp_out_nev >> next_temp_value;

  while (temp_out_ev.good() || temp_out_nev.good())
  {
    if (temp_out_ev.good())
      i = 0;
    
    if (temp_out_nev.good())
      div = 0;

    while ((div < std::pow(2, pow) && temp_out_nev.good()) || (i < std::pow(2, pow) && temp_out_ev.good()))
    {
      if (temp_value <= next_temp_value || div == std::pow(2, pow))
      {
        if (i == (std::pow(2, pow)))// - 1))
        {
          //out_stream << next_temp_value << " ";
          in_stream << next_temp_value << " ";
          if (temp_out_nev.good() && temp_out_nev >> next_temp_value){}
          div++;
        }
        else
        {
          //out_stream << temp_value << " ";
          in_stream << temp_value << " ";
          if (temp_out_ev.good() && temp_out_ev >> temp_value){}
          i++;
        }
      }
      else if (next_temp_value < temp_value || i == std::pow(2, pow))
      {
        //if (std::pow(2, div) == std::pow(2, pow))
        if (!temp_out_nev.good() && div != (std::pow(2, pow)))
        {
          div++;
          continue;
        }

        if (div == (std::pow(2, pow)))// - 1))
        {
          //out_stream << temp_value << " ";
          in_stream << temp_value << " ";
          if (temp_out_ev.good() && temp_out_ev >> temp_value){}
          i++;
        }
        else
        {
          //out_stream << next_temp_value << " ";
          in_stream << next_temp_value << " ";
          if (temp_out_nev.good() && temp_out_nev >> next_temp_value){}
          div++;
        }
      }
    }
  }

  std::flush(in_stream);

  temp_out_ev.clear();
  temp_out_ev.seekg(temp_out_ev.beg);
  temp_out_ev.seekp(temp_out_ev.beg);

  temp_out_nev.clear();
  temp_out_nev.seekg(temp_out_nev.beg);
  temp_out_nev.seekp(temp_out_nev.beg);

  in_stream.clear();
  in_stream.seekg(in_stream.beg);
  in_stream.seekp(in_stream.beg);

  temp_out_ev.close();
  temp_out_nev.close();
  //in_stream.close();

  read_data(++power);
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
