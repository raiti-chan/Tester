#include "pch.h"
#include "generate_random_array.h"
#include <algorithm>


void generate_random_array::_write_help() {
	std::cout << "Generate Random Array.\n"
		<< "GenRandom help : output this message.\n"
		<< "GenRandom [id] [size] : Generate Random Array at size is \"size\" in \"id\".\n"
		<< "GenRandom [id] [size] -o : Generate Random Array at size is \"size\" in \"id\" and output to console.\n";
}


int generate_random_array::operator()(const input_data& args) {
	if (args.argument_size() == 1) {
		generate_random_array::_write_help();
		return 0;
	}

	std::string a_1;
	args.get_argument_string(1, a_1);
	if (a_1 == "help") {
		generate_random_array::_write_help();
		return 0;
	}

	if (!(a_1 == "0" || a_1 == "1")) return 1; //第一引数エラー
	if (args.argument_size() <3) return 2; //引数が少ない
	
	unsigned int size;
	try {
		std::string a_2;
		args.get_argument_string(2, a_2);
		size = std::stoul(a_2, nullptr, 0);
	} catch (std::invalid_argument&) {
		return 3;
	} catch (std::out_of_range&) {
		return 4;
	}

	int* values_ptr = new int[size];
	int* ptr = values_ptr;
	for (unsigned int i = 0; i < size; i++, ptr++) {
		*ptr = random::rand_int();
	}
	data_class::instance().set_int_array(a_1[0] == '0' ? 0 : 1, array_data<int>(values_ptr , size, false));

	return 0;
}

void generate_random_array::error_call(const int error_code) {
	switch (error_code) {
	case 1:
		std::cout << "id is 0 or 1.\n";
		return;
	case 2:
		std::cout << "Insufficient of Argument. \"id \" and \"size\" is must required.\n";
		return;
	case 3:
		std::cout << "size is unsigned integer.\n";
		return;
	case 4:
		std::cout << "Out of range to \"size\". That is range of 0 to " << UINT_MAX << ".\n";
		return;
	default :
		std::cout << "Unknown found error.\n";
	}
}
