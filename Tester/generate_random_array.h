#pragma once
#include "i_cmd_let.h"

class generate_random_array : public i_cmd_let{
	static void _write_help();
public:
	int operator()(const input_data& args) override;
	void error_call(const int error_code) override;
};
