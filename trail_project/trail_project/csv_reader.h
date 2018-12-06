#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "hash_map.h"
#include "linked_list.h"

namespace storage {
  template <typename U>
  class csv_reader_t {
  public:
    typedef void(*csv_reader_process_fn)(containers::linked_list_t<std::string> *, U);
  private:
    std::ifstream input_file;

  public:
    csv_reader_t(const char *filename);
    void process(typename csv_reader_t::csv_reader_process_fn process_fn, U user_data);
  };

  template <typename U>
  void __write_row(U data, std::ofstream &file) {
    file << data->to_csv() << std::endl;
  }

  template <typename T, typename U>
  class csv_writer_t {
  public:
    static void write_to_file(const char *filename, containers::hash_map_t<T, U> *hash_map);
  };

  template<typename T, typename U>
  void csv_writer_t<T, U>::write_to_file(const char * filename, containers::hash_map_t<T, U>* hash_map) {
    std::ofstream ofile(filename);
    hash_map->foreach_data<std::ofstream&>(__write_row, ofile);
  }

  template<typename U>
  csv_reader_t<U>::csv_reader_t(const char * filename) {
    input_file.open(filename, std::ifstream::in);
  }

  template<typename U>
  void csv_reader_t<U>::process(typename csv_reader_t::csv_reader_process_fn process_fn, U user_data) {
    std::string line;

    while (std::getline(input_file, line)) {
      containers::linked_list_t<std::string> tokens;
      std::stringstream line_stream(line);
      std::string cell;
      while (std::getline(line_stream, cell, ',')) {
        tokens.append(cell);
      }

      if (!line_stream && cell.empty()) {
        tokens.append("");
      }

      process_fn(&tokens, user_data);
    }
  }
}