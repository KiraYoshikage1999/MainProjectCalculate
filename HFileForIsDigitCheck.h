// Function to delete from any type Dinamyc Arr ,element with index 
template<typename T>
void DeleteFromOperatorArray(T*& Arr, int& amount, int index) {
	if (amount <= 0 || index < 0 || index >= amount) {
		return;
	}
	else {
		T* tempArr = new T[amount - 1];
		int tempIndex = 0;

		for (int i = 0; i < amount; i++) { if (i != index) { tempArr[tempIndex++] = Arr[i]; } }

		delete[] Arr;
		amount--;

		Arr = new T[amount];
		for (int i = 0; i < amount; i++) { Arr[i] = tempArr[i]; }

		delete[] tempArr;
	}


}
//--------------------------------------------
