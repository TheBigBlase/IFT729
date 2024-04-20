#ifndef WORD_LIST_HPP
#define WORD_LIST_HPP

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <iostream>
#include "value_types.hpp"

// singleton
class Word_list {
	private:
		inline static std::string file_name = "./word_list.txt";
		std::vector<std::string> word_list;
		value_t number_lines;

		Word_list() : word_list{} {
			std::srand(std::time(nullptr));
			std::ifstream file;
			file.open(file_name);
			// last line doesnt have \n necessarly
			number_lines = std::count(std::istreambuf_iterator<char>(file),
									  std::istreambuf_iterator<char>(), '\n') +
						   1;

			file.clear();
			file.seekg(0);
			word_list.resize(number_lines);
			// fill the vector
			std::string word;
			for (int k = 0 ; k < number_lines - 1; ++k) {
				std::getline(file, word);
				word_list[k] = word;
			}
			file.close();
		}

	  public:
		Word_list(Word_list const &) = delete;
		void operator=(Word_list const &) = delete;

		static Word_list &get() {
			static Word_list wl;
			return wl; 
		}

		std::string get_random_word() {
			value_t index = std::rand() % number_lines;

			return word_list[index];
		}

		std::string get_random_word_different_from(std::string last) {
			std::string res;

			do {
				res = get_random_word();
			} while(res == last);

			return res;
		}
};

#endif
