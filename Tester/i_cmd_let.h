#pragma once
#include "input_data.h"

class i_cmd_let {
public:
	virtual ~i_cmd_let() = default;
	virtual int operator()(const input_data&) = 0;
	virtual void error_call(const int error_code) = 0;
};
