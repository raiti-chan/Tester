// SpeedTest.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include "Tester.h"
#include "generate_random_array.h"


int add(int a, int b) {
	return  a + b;
}

int main() {
	test();
	init();
	std::string s;
	std::string a_1;
	while (input(&s)) {
		input_data data(s);
		data.get_argument_string(0, a_1);
		if (a_1 == "exit") break;
		std::unordered_map<std::string, i_cmd_let*>& cmd_lets = data_class::instance().cmd_lets();
		i_cmd_let* call;
		try {
			call = cmd_lets.at(a_1);
		} catch (std::out_of_range&) {

			std::cout << "Unknown Command let.\n";
			continue;
		}
		const int error_code = (*call)(data);
		if (error_code) {
			(*call).error_call(error_code);
		}
	}

	fin();
	
	return 0;
}

bool input(std::string* s) {
	try {
		std::printf("> ");
		std::getline(std::cin, *s);
		
	} catch (const std::istream::failure &e) {
		std::cerr << "Exception happened : " << e.what() << "\n" << std::endl;
		return false;
	}
	return true;
}

void init() {
	random::init_rand();
	data_class::instance().cmd_lets()["GenRandom"] = new generate_random_array;
}

void fin() {
	std::unordered_map<std::string, i_cmd_let*>& cmd_lets = data_class::instance().cmd_lets();
	for (const std::unordered_map<std::string, i_cmd_let*>::value_type& element : cmd_lets) {
		delete element.second;
	}
}


void test() {


}
