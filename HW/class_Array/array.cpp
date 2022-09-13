#include <iostream>
#include <fstream>


class Array {
public:
	Array() {
		arr = new int[1];
		*arr = 0;
	}
	Array(const int size) {
		iSize = size;
		arr = new int[size];
		memset(arr, 0, size * sizeof(int));
	}
	Array(const Array& array) {
		iCurrentCount = array.iCurrentCount;
		iSize = array.iSize;
		arr = new int[iSize * sizeof(int)];
		memcpy(arr, array.arr, iSize * sizeof(int));
	}
	Array(const int size, int* memblock) {
		iCurrentCount = size;
		iSize = size;
		arr = new int[iSize * sizeof(int)];
		memcpy(arr, memblock, iSize * sizeof(int));
	}
	~Array() {
		delete[] arr;
	}

	void PushBack(int x) {
		CheckSize();
		arr[iCurrentCount] = x;
		iCurrentCount++;
		return;
	}

	int PopBack() {
		int tmp = arr[iCurrentCount];
		arr[iCurrentCount] = 0;
		iCurrentCount--;
		return tmp;
	}

	void PushFront(int x) {
		CheckSize();
		memmove(&arr[1], arr, iCurrentCount * sizeof(int));
		arr[0] = x;
		iCurrentCount++;
		return;
	}

	int PopFront() {
		int temp = arr[0];
		memmove(arr, &arr[1], (iCurrentCount - 1) * sizeof(int));
		iCurrentCount--;
		return temp;
	}

	void Push(int x, size_t position) { // pos == index 
		if (position < 0) {
			return;
		}
		if (position >= iCurrentCount) {
			PushBack(x);
			return;
		}
		CheckSize();
		memmove(&arr[position+1], &arr[position],
				(iCurrentCount - position) * sizeof(int));
		iCurrentCount++;
		arr[position] = x;
		return;
	}

	int Pop(int position) {
		int temp = arr[position];
		memmove(&arr[position], &arr[position+1],
			(iCurrentCount - position) * sizeof(int));
		//memmove(arr + position * sizeof(int), arr + (position + 1) * sizeof(int), 
			//	iCurrentCount - position);
		arr[iCurrentCount] = 0;
		iCurrentCount--;
		return temp;
	}

	void ReSize(size_t newSize) {
		if (newSize == iSize) {
			return;
		}
		int* arrTemp = new int[newSize];
		if (newSize >= iCurrentCount) {
			memcpy(arrTemp, arr, iCurrentCount * sizeof(int));
			memset(arrTemp, 0, (newSize - iCurrentCount) * sizeof(int));
		}
		else {
			memcpy(arrTemp, arr, newSize * sizeof(int));
			iCurrentCount = newSize;
		}
		delete[] arr;
		arr = arrTemp;
		iSize = newSize;
		return;
	}

	int GetSize() {
		return iSize;
	}

	int GetCount() {
		return iCurrentCount;
	}

	void Print(int position, std::ofstream out) {
		out << arr[position] << std::endl;;
		return;
	}

	void Print(int position) {
		std::cout << arr[position] << std::endl;
		return;
	}

	void PrintAll(std::ofstream out) {
		for (size_t i = 0; i < iCurrentCount; ++i) {
			out << arr[i];
		}
		out << std::endl;
		return;
	}

	void PrintAll() {
		for (size_t i = 0; i < iCurrentCount; ++i) {
			std::cout << arr[i] << ' ';
		}
		std::cout << std::endl;
		return;
	}

	Array& operator =(const Array& second) {
		if (&second == this) { 
			return *this; 
		}
		delete[] arr;
		arr = new int[second.iSize];
		memcpy(arr, second.arr, second.iSize * sizeof(int));
		iCurrentCount = second.iCurrentCount;
		iSize = second.iSize;
		return *this;
	}

	Array operator +(const Array& second) const {
		Array temp(this->iCurrentCount + second.iCurrentCount); 
		
		memcpy(temp.arr, this->arr, this->iCurrentCount * sizeof(int));

		memcpy(&(temp.arr[this->iCurrentCount]), second.arr,
			second.iCurrentCount * sizeof(int));
		temp.iCurrentCount = iCurrentCount + second.iCurrentCount;

		/*memcpy(temp->arr + this->iCurrentCount * sizeof(int), second.arr,
				second.iCurrentCount * sizeof(int));*/
		//temp.iCurrentCount = second.iCurrentCount + this->iCurrentCount;


		return Array(temp); // не знаю на сколько рационально вызывать конструктор, другого способа не нашел 
	}

	Array operator +(const int& x) const{
		Array temp(*this);
		temp.PushBack(x);
		return Array(temp);
	}

	//const int operator +( Array& second) {
	//	second.PushFront();
	//}

	Array operator *(const int x) const {
		Array temp(iCurrentCount * x);
		for (int i = 0; i < x; ++i) {
			memcpy(&temp.arr[0 + i * iCurrentCount], arr, iCurrentCount * sizeof(int));
		}
		temp.iCurrentCount = iCurrentCount * x;
		return Array(temp);
	}
	
	int at(size_t x) {
		try {
			if (x >= iCurrentCount) {
				throw "Check index. \n Exit... ";
			}
			return arr[x];
		}
		catch(const char* err){
			std::cout << err;
			exit(-1);
		}
	}

	Array operator [](size_t x) {
		return this->at(x);
	}


private:
	int* arr = nullptr;
	size_t iSize = 1;
	size_t iCurrentCount = 0;

	void ReAllocation(int newSize) {
		int* arrTemp = new int[newSize];
		memcpy(arrTemp, arr, iCurrentCount * sizeof(int));
		memset(&arrTemp[iCurrentCount], 0, (newSize - iCurrentCount) * sizeof(int));
		//memset(arrTemp + iCurrentCount * sizeof(int), 0, (newSize - iCurrentCount) * sizeof(int));
		delete[] arr;
		arr = arrTemp;
		iSize = newSize;
		return;
	}

	void CheckSize() {
		if (iCurrentCount == iSize) {
			ReAllocation(iSize <= 10000 ? iSize * 2ull : iSize * 1.6);
		}
	}
};

int main() {

}
