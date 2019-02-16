#pragma once

/// <summary>
/// 入力データを解析します
/// </summary>
class input_data final {
	/// <summary>
	/// 入力された文字列サイズ
	/// </summary>
	unsigned int _text_size = 0;
	/// <summary>
	/// 文字列へのポインタ
	/// </summary>
	char* _text = nullptr;
	/// <summary>
	/// 引数の数
	/// </summary>
	unsigned int _argument_size = 0;
	/// <summary>
	/// 引数個々の文字列サイズ
	/// </summary>
	unsigned int* _argument_text_sizes = nullptr;
	/// <summary>
	/// 引数文字列へのポインターへのポインタ
	/// </summary>
	const char** _arguments = nullptr;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="text">入力文字列</param>
	explicit input_data(const std::string& text) noexcept;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~input_data() noexcept;

	/// <summary>
	/// 入力された文字列サイズを取得します。
	/// </summary>
	/// <returns>入力された文字列サイズ</returns>
	unsigned int text_size() const noexcept {
		return  this->_text_size;
	}
	/// <summary>
	/// 入力された文字列の先頭のポインタを取得します。
	/// </summary>
	/// <returns>文字列へのポインタ</returns>
	const char* text() const noexcept {
		return this->_text;
	}

	/// <summary>
	/// 引数の数を取得します。
	/// </summary>
	/// <returns>引数の数</returns>
	unsigned int argument_size() const noexcept {
		return this->_argument_size;
	}
	/// <summary>
	/// 引数個々の文字列サイズを取得します。
	/// </summary>
	/// <param name="index">引数のインデックス</param>
	/// <returns>指定されたインデックスの文字列サイズ</returns>
	unsigned int get_argument_text_size(const unsigned int index) const noexcept {
		return this->_argument_text_sizes[index];
	}
	/// <summary>
	/// 引数個々の文字列の先頭のポインタを取得します。
	/// </summary>
	/// <param name="index">引数のインデックス</param>
	/// <returns>指定されたインデックスの文字列へのポインタ</returns>
	const char* get_argument(const unsigned int index) const noexcept {
		return this->_arguments[index];
	}
	/// <summary>
	/// 引数個々の文字列をstringにコピーして取得します。
	///  string::clearの後にappendします
	/// </summary>
	/// <param name="index">引数のインデックス</param>
	/// <param name="str">格納先string</param>
	/// <returns>無し</returns>
	void get_argument_string(const unsigned int index, std::string& str) const noexcept;
};

