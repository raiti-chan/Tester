#include "pch.h"
#include "input_data.h"

input_data::input_data(const std::string& text) noexcept {
	//入力文字を格納する領域確保
	this->_text_size = static_cast<unsigned int>(text.size());
	this->_text = new char[this->_text_size];
	
	//文字列コピー
	std::memcpy(this->_text, text.c_str(), this->text_size());

	//文字列の解析
	const char* t_ptr = this->_text;
	unsigned int arg_c = 0, text_c = 0; //引数カウンタ, 文字数カウンタ
	bool is_enclose = false; //ダブルクオーテーションのフラグ
	for (unsigned int i = 0; i < this->_text_size; i++, t_ptr++) {
		const char target_c = *t_ptr;
		if(text_c == 0) {
			if (target_c == ' ' && !is_enclose) continue;
			if (target_c == '"') { is_enclose = true; continue; }
			text_c++;
		} else {
			if (is_enclose) {
				if (target_c != '"') {
					text_c++;
					continue;
				}
				arg_c++;
				text_c = 0;
				is_enclose = false;
			} else {
				if (target_c != ' ') { text_c++; continue; }
				arg_c++;
				text_c = 0;
			}
		}

	}

	if(text_c != 0) {
		arg_c++;
	}

	//引数ポインタの格納領域の確保
	this->_argument_size = arg_c;
	this->_argument_text_sizes = new unsigned int [arg_c];
	this->_arguments = new const char* [arg_c];

	//文字列の分解
	t_ptr = this->_text;
	arg_c = 0; text_c = 0;
	is_enclose = false;
	for (unsigned int i = 0; i < this->_text_size; i++, t_ptr++) {
		const char target_c = *t_ptr;
		if (text_c == 0) {
			if (target_c == ' ' && !is_enclose) continue;
			if (target_c == '"') {
				is_enclose = true;
				continue;
			}
			this->_arguments[arg_c] = t_ptr;
			text_c++;
		} else {
			if (is_enclose) {
				if (target_c != '"') {
					text_c++;
					continue;
				}
				this->_argument_text_sizes[arg_c] = text_c;
				arg_c++;
				text_c = 0;
				is_enclose = false;
			} else {
				if (target_c != ' ') { text_c++; continue; }
				this->_argument_text_sizes[arg_c] = text_c;
				arg_c++;
				text_c = 0;
			}
		}
	}

	if (text_c != 0) {
		this->_argument_text_sizes[arg_c] = text_c;
	}
}

input_data::~input_data() noexcept {
	delete[] this->_text;
	delete[] this->_arguments;
	delete[] this->_argument_text_sizes;
}


unsigned int input_data::text_size() const noexcept {
	return this->_text_size;
}

const char* input_data::text() const noexcept {
	return this->_text;
}

unsigned int input_data::argument_size() const noexcept {
	return this->_argument_size;
}

unsigned int input_data::get_argument_text_size(const unsigned int index) const noexcept {
	return this->_argument_text_sizes[index];
}

const char* input_data::get_argument(const unsigned int index) const noexcept {
	return this->_arguments[index];
}

std::string input_data::get_argument_string(const unsigned index) const noexcept {
	std::string s(this->get_argument(index), this->get_argument_text_size(index));
	return s;
}


