#pragma once
#include <unordered_map>
#include "i_cmd_let.h"

/// <summary>
/// T型の配列を保持するクラス
/// </summary>
template<class T>
class array_data final {
	/// <summary>
	/// 配列サイズ
	/// </summary>
	unsigned int _size = 0;
	/// <summary>
	/// 配列へのポインタ
	/// </summary>
	T* _array_ptr = nullptr;

public:
	/// <summary>
	/// コンストラクタ。配列はnullptrになります。
	/// </summary>
	array_data() : _array_ptr(nullptr) {}
	/// <summary>
	/// 指定されたサイズの配列を生成します。
	/// </summary>
	/// <param name="size">配列の要素数</param>
	explicit array_data(const unsigned int size) : _size(size), _array_ptr(new T[size]) {}
	/// <summary>
	/// is_copyがtrueの場合新規に配列を確保し、渡された配列ポインタからデータをコピーします。
	/// is_copyがfalseの場合渡されたポインタを保持します。この場合ポインタの指す領域を手動で解放しないでください。
	/// またポインタから値を変えるとこちらの値も変更されます。
	/// また別のインスタンスがコピー/ムーブされた時、またはデストラクタが呼ばれた時自動的に開放されます。
	/// </summary>
	/// <param name="ptr">コピーまたはアドレス参照する配列ポインタ</param>
	/// <param name="size">配列の要素数</param>
	/// <param name="is_copy">配列をコピーするか否か</param>
	array_data(T* ptr, const unsigned int size, const bool is_copy) : _size(size) {
		if (!is_copy) {
			this->_array_ptr = ptr;
			return;
		}
		this->_array_ptr = new T[size];
		std::memcpy(this->_array_ptr, ptr, sizeof(T) * size);
	}
	/// <summary>
	/// インスタンスを複製します。配列も複製されます。
	/// </summary>
	/// <param name="d">複製元インスタンス</param>
	array_data(const array_data<T>& d) : _size(d._size), _array_ptr(new T[d._size]) {
		std::memcpy(this->_array_ptr, d._array_ptr, sizeof(T) * d._size);
	}
	/// <summary>
	/// インスタンスをムーブします。移動元のインスタンスは使用以降しないでください。
	/// </summary>
	/// <param name="d">移動元インスタンス</param>
	array_data(array_data<T>&& d) noexcept : _size(d._size), _array_ptr(d._array_ptr) {
		d._size = 0;
		d._array_ptr = nullptr;
	}

	~array_data() {
		if (this->_array_ptr == nullptr) return;
		delete[] _array_ptr;
	}

	/// <summary>
	/// インスタンスを複製して代入します。元の配列は解放され新しい要素になります。
	/// </summary>
	/// <param name="d">複製元インスタンス</param>
	/// <returns>このインスタンスへの参照</returns>
	array_data<T>& operator=(const array_data<T>& d) {
		if (this->_array_ptr != nullptr) {
			delete[] this->_array_ptr;
		}
		this->_size = d._size;
		this->_array_ptr = new T[d._size];
		std::memcpy(this->_array_ptr, d._array_ptr, sizeof(T) * d._size);
		return *this;
	}

	/// <summary>
	/// インスタンスをムーブして代入します。元の配列は解放され新しい配列ポインタを参照します。移動元のインスタンスは以降使用しないでください。
	/// </summary>
	/// <param name="d">移動元インスタンス</param>
	/// <returns>このインスタンスへの参照</returns>
	array_data<T>& operator=(array_data<T>&& d) noexcept {
		if (this->_array_ptr != nullptr) {
			delete[] this->_array_ptr;
		}
		this->_size = d._size;
		this->_array_ptr = d._array_ptr;
		d._size = 0;
		d._array_ptr = nullptr;
		return *this;
	}

	/// <summary>
	/// 配列の要素数を取得します。
	/// </summary>
	/// <returns>要素数</returns>
	unsigned int get_array_size() const {
		return this->_size;
	}

	/// <summary>
	/// 配列へのポインタを取得します。
	/// ここで取得したポインタはこのインスタンスが別のインスタンスで上書きされた場合やデストラクタが呼ばれた場合使用できなくなります。
	/// </summary>
	/// <returns>ポインタ</returns>
	const T* get_array_ptr() {
		return this->_array_ptr;
	}
};

class data_class final {
	data_class() = default;
	~data_class() = default;

	std::unordered_map<std::string, i_cmd_let*> _cmd_lets;

	array_data<int> _int_array[2];

public:

	const array_data<int>& get_int_array(const unsigned int index) const {
		return this->_int_array[index];
	}

	array_data<int> set_int_array(const unsigned int index, array_data<int>&& array) {
		array_data<int> ret = std::move(this->_int_array[index]);
		this->_int_array[index] = array;
		return ret;
	}

	std::unordered_map<std::string, i_cmd_let*>& cmd_lets() {
		return this->_cmd_lets;
	}




	static data_class& instance() {
		static data_class instance;
		return instance;
	}
};
