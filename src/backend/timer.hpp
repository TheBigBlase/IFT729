#ifndef TIMER_HPP
#define TIMER_HPP

#include <fstream>
#include <ratio>
#include <chrono>
#include <iostream>

class Timer {
	private:
		inline static std::string file_name = "./output_time.txt";
		std::ofstream file;
		bool started;
		std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
		std::chrono::time_point<std::chrono::high_resolution_clock> end_time;

		Timer(): file {file_name}, started{false} {}

		~Timer() { file.close(); }

	  public:
		Timer(Timer const &) = delete;
		void operator=(Timer const &) = delete;

		static Timer &get() {
			static Timer t;
			return t; 
		}

		// i didnt find func traits, so for void funcs, lamda passed has to
		// return a value.
		template <class F, class... Args> auto tester(F f, Args &&...args, std::string name = "tester") {
			auto pre = std::chrono::high_resolution_clock::now();
			auto res = f(std::forward<Args>(args)...);
			auto post = std::chrono::high_resolution_clock::now();
			const std::chrono::duration<double, std::nano> time = post - pre;
			if (!file.is_open())
				std::cerr << "file not opened" << std::endl;
			file << name << ":" << time.count() << "ns" << std::endl;
			file.flush();
			return res;
		}
};

#endif
