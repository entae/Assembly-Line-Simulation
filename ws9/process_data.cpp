// Workshop 9 - Multi-Threading, Thread Class
// process_data.cpp
// 2021/1/5 - Jeevan Pant
// 2023/11/17 - Cornel

#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <thread>
#include "process_data.h"

namespace sdds
{
	// The following function receives array (pointer) as the first argument, number of array 
	//   elements (size) as second argument, divisor as the third argument, and avg as fourth argument. 
	//   size and divisor are not necessarily same. When size and divisor hold same value, avg will 
	//   hold average of the array elements. When they are different, avg will hold a value called 
	// 	 as average-factor. For part 1, you will be using same value for size and double. Use of 
	//   different values for size and divisor will be useful for multi-threaded implementation in part-2. 
	void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
		std::this_thread::sleep_for(std::chrono::nanoseconds(10));
		avg = 0;
		for (int i = 0; i < size; i++) {
			avg += arr[i];
		}
		avg /= divisor;
	}

	// The following function receives array (pointer) as the first argument, number of array elements  
	//   (size) as second argument, divisor as the third argument, computed average value of the data items
	//   as fourth argument, and var as fifth argument. Size and divisor are not necessarily same as in the 
	//   case of computeAvgFactor. When size and divisor hold same value, var will get total variance of 
	//   the array elements. When they are different, var will hold a value called as variance factor. 
	//   For part 1, you will be using same value for size and double. Use of different values for size 
	//   and divisor will be useful for multi-threaded implementation in part-2. 
	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
		std::this_thread::sleep_for(std::chrono::nanoseconds(10));
		var = 0;
		for (int i = 0; i < size; i++) {
			var += (arr[i] - avg) * (arr[i] - avg);
		}
		var /= divisor;
	}

	// The following constructor of the functor receives name of the data file, opens it in 
	//   binary mode for reading, reads first int data as total_items, allocate memory space 
	//   to hold the data items, and reads the data items into the allocated memory space. 
	//   It prints first five data items and the last three data items as data samples. 
	//   
	ProcessData::ProcessData(const std::string& filename, int n_threads) {  
		// TODO: Open the file whose name was received as parameter and read the content
		//         into variables "total_items" and "data". Don't forget to allocate
		//         memory for "data".
		//       The file is binary and has the format described in the specs.
		std::ifstream inFile(filename, std::ios::binary);

		bool success = false;

		if (inFile.is_open()) {
			// read num of data items
			inFile.read(reinterpret_cast<char*>(&total_items), sizeof(int));

			if (total_items > 0) {
				// allocate memory based on total_items read
				data = new int[total_items];
				inFile.read(reinterpret_cast<char*>(data), sizeof(int) * total_items);

				success = true;
			}
		}
		inFile.close();

		if (!success) {
			std::cerr << "Error processing file: " << filename << std::endl;
			total_items = 0;
			data = nullptr;
		} else {
			std::cout << "Item's count in file '"<< filename << "': " << total_items << std::endl;
			std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
		          << data[total_items - 3] << ", " << data[total_items - 2] << ", "
		          << data[total_items - 1] << "]" << std::endl;
		}

		// Following statements initialize the variables added for multi-threaded 
		//   computation
		num_threads = n_threads; 
		averages = new double[num_threads] {};
		variances = new double[num_threads] {};
		p_indices = new int[num_threads+1] {};
		for (int i = 0; i < num_threads; i++)
			p_indices[i] = i * (total_items / num_threads);
		p_indices[num_threads] = total_items;
	}

	ProcessData::~ProcessData() {
		delete[] data;
		delete[] averages;
		delete[] variances;
		delete[] p_indices;
	}

	ProcessData::operator bool() const {
		return total_items > 0 && data;
	}

	// TODO Improve operator() function from part-1 for multi-threaded operation. Enhance the  
	//   function logic for the computation of average and variance by running the 
	//   function computeAvgFactor and computeVarFactor in multile threads. 
	// The function divides the data into a number of parts, where the number of parts is 
	//   equal to the number of threads. Use multi-threading to compute average-factor for 
	//   each part of the data by calling the function computeAvgFactor. Add the obtained 
	//   average-factors to compute total average. Use the resulting total average as the 
	//   average value argument for the function computeVarFactor, to compute variance-factors 
	//   for each part of the data. Use multi-threading to compute variance-factor for each 
	//   part of the data. Add computed variance-factors to obtain total variance.
	// Save the data into a file with filename held by the argument fname_target. 
	// Also, read the workshop instruction.
	int ProcessData::operator()(const std::string& target_file, double& avg, double& var) {
		int returnCode = 0;

		// Resource variables to store intermediate results from threads
		std::vector<double> avg_factors(std::thread::hardware_concurrency(), 0.0);
		std::vector<double> var_factors(std::thread::hardware_concurrency(), 0.0);

		// Multi-threaded computation of avg
		std::vector<std::thread> avgThreads;
		const size_t partition_size = total_items / avg_factors.size();

		for (size_t i = 0; i < avg_factors.size(); ++i) {
			avgThreads.emplace_back(
				std::bind(&computeAvgFactor, data + i * partition_size, partition_size, total_items, std::ref(avg_factors[i]))
			);
		}

		// Join threads
		for (auto& thread : avgThreads) {
			thread.join();
		}

		// Compute total avg
		avg = 0.0;
		for (const auto& avg_factor : avg_factors) {
			avg += avg_factor;
		}

		// Multi-threaded computation of var
		std::vector<std::thread> varThreads;

		for (size_t i = 0; i < var_factors.size(); ++i) {
			varThreads.emplace_back(
				std::bind(&computeVarFactor, data + i * partition_size, partition_size, total_items, avg, std::ref(var_factors[i]))
			);
		}

		// Join threads
		for (auto& thread : varThreads) {
			thread.join();
		}

		// Compute total var
		var = 0.0;
		for (const auto& var_factor : var_factors) {
			var += var_factor;
		}

		std::ofstream outFile(target_file, std::ios::binary);
		if (!outFile.is_open()) {
			std::cerr << "Error opening target file: " << target_file << std::endl;
			returnCode = -1; // Return an error code
		} else {
			// Write the total number of data items
			outFile.write(reinterpret_cast<const char*>(&total_items), sizeof(int));

			// Write the data-item values
			outFile.write(reinterpret_cast<const char*>(data), sizeof(int) * total_items);

			outFile.close();
		}

		return returnCode; // Return success code
	}

}
