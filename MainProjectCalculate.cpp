// Project Calculator.



//Block of code for including and connecting all of the Libs.
#include <iostream>
#include <ctime>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <cmath>
#include <fstream>
//Namespaces:
using namespace std;
//---------- My own Libs ----------
#include "HFileForIsDigitCheck.h"
//---------------------------------
float MakingOperation(float firstOperand, float secondOperand, char operation);
void ExpressionBracketsLogicalFunc(int FirstIndex, int SecondIndex, int CounterForArr, string*& ArrMemory, int& amountOfValues);

//Function for checking "Is part of expression Digit or is it float"
bool IsDigit(const string& other) {
	bool hasDecimalPoint = false;

	for (size_t i = 0; i < other.size(); i++) {
		char ch = other[i];
		if (ch == '.') {
			if (hasDecimalPoint == true) return false;
			hasDecimalPoint = true;
		}
		else if (ch < '0' || ch > '9') { // Informatin about char from ASCII.
			return false;
		}
	}
	return true;
}

//class for my own String , but i don't know where i can it use for really. 
class MyString {
	char* arr;
	int Capacity;
public:
	MyString() { // Constructor by default
		this->arr = new char[0];
		this->Capacity = 0;
	}
};

// Function to add to any type of Dinamyc ARR , his amount Of Elements and his new Element
template<typename T, typename T1>
void AddInArray(T*& Arr, int& amount, T1 userValue) {
	T* tempArr = new T[amount];
	for (int i = 0; i < amount; i++) { tempArr[i] = Arr[i]; }

	delete[] Arr;
	amount++;

	Arr = new T[amount];
	for (int i = 0; i < amount - 1; i++) { Arr[i] = tempArr[i]; }

	delete[] tempArr;

	Arr[amount - 1] = userValue;
}
//------------------------------------------

//A function that converts array elements into operands and operators.
void RecreatingArrToExpression(string* ArrMemory, int amountOfValues, string*& OperArr, int*& PriorityArr,
	float*& numberArr, int& amountOfOper, int& amountOfPriorityValues, int& amountOfOperands) {
	float userNumber;
	string userOperator;

	for (int i = 0; i < amountOfValues; i++) {
		if ((ArrMemory[i] == "+") || (ArrMemory[i] == "-") || (ArrMemory[i] == "*") || (ArrMemory[i] == "/") || (ArrMemory[i] == "^") || (ArrMemory[i] == "|") || (ArrMemory[i] == "(") || (ArrMemory[i] == ")")) {
			userOperator = ArrMemory[i];
			// sort operators by priority , information take from https://ru.wikipedia.org/wiki/%D0%9F%D1%80%D0%B8%D0%BE%D1%80%D0%B8%D1%82%D0%B5%D1%82_%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%86%D0%B8%D0%B8
			// Adding operators with prioritate of him to Arrays.
			if ((ArrMemory[i] == "+") || (ArrMemory[i] == "-")) {
				AddInArray(PriorityArr, amountOfPriorityValues, 5);
				AddInArray(OperArr, amountOfOper, userOperator);
			}
			else if ((ArrMemory[i] == "*") || (ArrMemory[i] == "/")) {
				AddInArray(PriorityArr, amountOfPriorityValues, 4);
				AddInArray(OperArr, amountOfOper, userOperator);
			}
			else if ((ArrMemory[i] == "^") || (ArrMemory[i] == "|")) {
				AddInArray(PriorityArr, amountOfPriorityValues, 3);
				AddInArray(OperArr, amountOfOper, userOperator);
			}
			else if ((ArrMemory[i] == "(") || (ArrMemory[i] == ")")) {
				AddInArray(PriorityArr, amountOfPriorityValues, 2);
				AddInArray(OperArr, amountOfOper, userOperator);
			}
		}
		else if (IsDigit(ArrMemory[i])) {
			userNumber = stof(ArrMemory[i]);
			AddInArray(numberArr, amountOfOperands, userNumber);
		}
		else {
			cout << "<--------{Message}------------->\n You entered something wrong. \n <------------------->" << endl;


		}

	}

}

void MathOperations(string* ArrMemory, int amountOfValues, string* OperArr, int* PriorityArr,
	float* numberArr, int amountOfOper, int& amountOfPriorityValues, int& amountOfOperands) { // Math operations
	//------Creating Varuables for MathOperations
	float result = 0.0;
	//int FirstIndexBracket = -1;
	//int SecondIndexBracket = -1;
	int maxPriorityIndex = 0;
	/*int counterForSubExpression = 0;*/
	//------------------------------------------


	while (amountOfPriorityValues > 0) {
		//checking and identifying the most important priority
		for (int i = 0; i < amountOfPriorityValues; i++) {
			if (PriorityArr[i] < PriorityArr[maxPriorityIndex]) {
				maxPriorityIndex = i;
			}
		}

		//for (int i = 0; i < amountOfValues; i++) {
		//	if (ArrMemory[i][0] == '(') {
		//		FirstIndexBracket = i;
		//		if (ArrMemory[i][0] == ')') {
		//			SecondIndexBracket = i;
		//			break;
		//		}
		//		counterForSubExpression++;

		//	}
		//}

		// Using the index, we determine the operator with the highest priority and the required operands on the left and right (first and second)
		//if (FirstIndexBracket != -1 && SecondIndexBracket != -1) {
		//	/*cout << "Here" << endl;*/
		//	ExpressionBracketsLogicalFunc(FirstIndexBracket, SecondIndexBracket, counterForSubExpression, ArrMemory, amountOfValues);




		//}
		if ( //If operator is '|' , It is solve for one operand
			OperArr[maxPriorityIndex][0] == '|') {
			string OperationSymbol = OperArr[maxPriorityIndex];
			float FirstOperand = numberArr[maxPriorityIndex];
			result = MakingOperation(FirstOperand, 0, OperationSymbol[0]);
		}
		else { //The usual solution if everything is ok
			string OperationSymbol = OperArr[maxPriorityIndex];
			float FirstOperand = numberArr[maxPriorityIndex];
			float SecondOperand = numberArr[maxPriorityIndex + 1];
			result = MakingOperation(FirstOperand, SecondOperand, OperationSymbol[0]);
		}

		//Decreasing the array with each iteration of solutions
		numberArr[maxPriorityIndex] = result; // Writing result in array
		for (int i = maxPriorityIndex + 1; i < amountOfOperands - 1; i++) {
			numberArr[i] = numberArr[i + 1];
		}
		amountOfOperands--;

		for (int i = maxPriorityIndex; i < amountOfPriorityValues - 1; i++) {
			PriorityArr[i] = PriorityArr[i + 1];
		}
		amountOfPriorityValues--;

		for (int i = amountOfOper; i < amountOfOper - 1; i++) {
			OperArr[i] = OperArr[i + 1];
		}
		amountOfOper--;
	}

	cout << "<--------{Message}------------->\n Result:  \n" << result << endl << "<---------------------->" << endl;

}

float MakingOperation(float firstOperand, float secondOperand, char operation) {
	switch (operation) {
	case '+':
		return firstOperand + secondOperand;
	case '-':
		return firstOperand - secondOperand;
	case '*':
		return firstOperand * secondOperand;
	case '/':
		if (firstOperand == 0 || secondOperand == 0) {
			cout << "<--------{Message}------------->\n Some of operands become zero, you can't divide on zero! \n <------------------->" << endl;
			return 0;
		}
		else {
			return firstOperand / secondOperand;
		}

	case '^':
		return pow(firstOperand, secondOperand);
	case '|':
		if (firstOperand == 0) {
			cout << "<--------{Message}------------->\n The operand that you want sqrt is zero, you can't do that! \n <------------------->" << endl;
			return 0;
		}
		else {
			return sqrt(firstOperand);
		}

	default:
		cout << "<--------{Message}------------->\n Unsupported operation \n <------------------->" << endl;
		return 0;

	}
}

void ExpressionBracketsLogicalFunc(int FirstIndex, int SecondIndex, int CounterForArr, string*& ArrMemory, int& amountOfValues) {
	//Place for creating varuables and arrays
	int amountOfSValues = SecondIndex - FirstIndex - 1;
	int amountOfSOperators = 0;
	int amountOfSOperands = 0;
	int amountOfSPriority = 0;

	string* subMemoryArr = new string[amountOfSValues]; //Sub expression memory Array
	string* subOperatorsArr = nullptr; //Sub operators Arr
	float* subNumberArr = nullptr; //Sub NumberArr
	int* subPriorityArr = nullptr; // priority of operators in sub operators Arr
	//----------------------------
	int subIndex = 0;
	for (int i = FirstIndex + 1; i < SecondIndex; i++) {
		subMemoryArr[subIndex++] = ArrMemory[i];
		//cout << ArrMemory[i] << "J" << endl;
		//cout << subMemoryArr[subIndex - 1] << "I" << endl;

	}


	DeleteFromOperatorArray(subMemoryArr, amountOfSValues, FirstIndex);
	DeleteFromOperatorArray(subMemoryArr, amountOfSValues, SecondIndex);
	for (int i = 0; i < amountOfValues; i++) {
		if (i > FirstIndex || i < SecondIndex) {
			DeleteFromOperatorArray(subMemoryArr, amountOfSValues, i);
		}
	}

	RecreatingArrToExpression(subMemoryArr, amountOfSValues, subOperatorsArr, subPriorityArr, subNumberArr, amountOfSOperators, amountOfSPriority, amountOfSOperands);
	MathOperations(subMemoryArr, amountOfSValues, subOperatorsArr, subPriorityArr, subNumberArr, amountOfSOperators, amountOfSPriority, amountOfSOperands);
}
template <typename T>
void PrintInfoMemoryArr(T*& Arr, int amount) {
	for (int i = 0; i < amount; i++) {
		cout << "[" << i << "] -- " << Arr[i] << endl;
	}
}

//Function to clear dinamyc arr and recreate him.
template <typename T>
void Clear(T*& Arr, int& amountOfValues) {
	delete[] Arr;
	Arr = nullptr;
	Arr = new T[amountOfValues];
	amountOfValues = 0;
}

int main()
{
	//Block for declaration of variables

	char userOperation;
	string userCinValue;
	string tempVaruable;
	char userChooseOption = '0';
	int amountOfValues = 0;
	int amountOfNumbers = 0;
	int amountOfOpsPriority = 0;
	int amountOfOperators = 0;
	//Creating Dinamyc Arrays
	//string* memoryArr = nullptr;
	//float* numberArrey = nullptr;
	//string* charOperatorArrey = nullptr;
	//int* strOpsPriorityArr = nullptr;

	string* memoryArr = new string[amountOfValues]; //General Array for User's String
	float* numberArrey = new float[amountOfNumbers]; // Array for user operands from strings in memoryArray
	string* charOperatorArrey = new string[amountOfOperators]; // Array for all operators from memoryArray
	int* strOpsPriorityArr = new int[amountOfOpsPriority]; // Array for prioritiers for operators
	//----------------


	//Block of Code where User choosing the option he wants.
	while (true) {
		cout << "<------------{Menu}------------->" << endl
			<< "Choose option: " << endl
			<< "1 - Enter your exspression;" << endl
			<< "2 - show your mathematical expression;" << endl
			<< "3 - Show all Array Information;" << endl
			<< "4 - Clear exspresion;" << endl
			<< "5 - Calculate;" << endl
			<< "6 - Tutorial;" << endl
			<< "7 - Calculator Memory;" << endl
			<< "<-------------------------------->" << endl;

		cin >> userChooseOption; //User Choose
		if (userChooseOption == '1') { // User enters his expression with space after each operand or operator.

			string tempVaruable = "";

			cout << "<------------{Menu}------------->" << endl << "Enter your exspression with operands (0-9) , operators(+,-,*,/,^,| <-sqrt() , ( , ) )" << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			getline(cin, userCinValue);
			for (int i = 0; i < userCinValue.length(); i++) {
				if (userCinValue[i] == ' ') {
					AddInArray(memoryArr, amountOfValues, tempVaruable);
					tempVaruable = "";
				}
				// Check for more operators inline.
				else if ((userCinValue[i] == '+' && userCinValue[i + 1] == '+') || (userCinValue[i] == '-' && userCinValue[i + 1] == '+') || (userCinValue[i] == '-' && userCinValue[i + 1] == '-') || (userCinValue[i] == '*' && userCinValue[i + 1] == '*') || (userCinValue[i] == '/' && userCinValue[i + 1] == '/') || (userCinValue[i] == '+' && userCinValue[i + 1] == '*') || (userCinValue[i] == '+' && userCinValue[i + 1] == '/') || (userCinValue[i] == '-' && userCinValue[i + 1] == '*') || (userCinValue[i] == '-' && userCinValue[i + 1] == '/')) {
					cout << "<--------{Message}------------->\n In expression two operators inline! Clearing expression! \n <---------------------------->" << endl;
					userCinValue.clear();
					tempVaruable.clear();
				}
				else { tempVaruable += userCinValue[i]; }
			}
			if (!tempVaruable.empty()) {
				AddInArray(memoryArr, amountOfValues, tempVaruable);
				tempVaruable.clear();
			}


		}
		else if (userChooseOption == '2') { // just showing user's expression.
			cout << userCinValue << endl;
		}
		else if (userChooseOption == '3') { // Debug option to see what the hell is happening in arrays.
			cout << "------Debug Info [expression Array] -----" << endl;
			PrintInfoMemoryArr(memoryArr, amountOfValues);
			cout << "<----------------------->" << endl;
		}
		else if (userChooseOption == '4') { //Option to clear all arrays of expression and expressions
			if (userCinValue == "" || tempVaruable == "") { cout << "<--------{Message}------------->\n There's no expression to clear. \n <----------------------->" << endl; }
			else {
				userCinValue.clear();
				tempVaruable.clear();
				Clear(memoryArr, amountOfValues);
				Clear(numberArrey, amountOfNumbers);
				Clear(charOperatorArrey, amountOfOperators);
				Clear(strOpsPriorityArr, amountOfOpsPriority);
			}
		}
		else if (userChooseOption == '5') { // Calculate
			RecreatingArrToExpression(memoryArr, amountOfValues, charOperatorArrey, strOpsPriorityArr, numberArrey, amountOfOperators, amountOfOpsPriority, amountOfNumbers);
			MathOperations(memoryArr, amountOfValues, charOperatorArrey, strOpsPriorityArr, numberArrey, amountOfOperators, amountOfOpsPriority, amountOfNumbers);
		}
		else if (userChooseOption == '6') { //tutorial
			cout << "User must enter his expression with spacebar after EACH operand and operator and than click enter" << endl;
		}
		else if (userChooseOption == '7') {
			cout << "<------------{Menu}------------->" << endl
				<< "Choose option: " << endl
				<< "1 - Enter your epression to memory File;" << endl
				<< "2 - show your expressions in memory File;" << endl
				<< "3 - take from memory File expression;" << endl
				<< "<-------------------------------->" << endl;
			cin >> userChooseOption;
			if (userChooseOption == '1') {
				if (userCinValue.empty()) {
					cout << "<--------{Message}------------->\n There's no expression to send in memory File 1. \n <---------------------------->" << endl;
				}
				else {
					ofstream MemoryFile("MemoryFile.bin", ios::binary);
					size_t length = userCinValue.size();
					MemoryFile.write(reinterpret_cast<char*>(&length), sizeof(length));
					MemoryFile.write(userCinValue.c_str(), length);
					cout << "<--------{Message}------------->\n Expression successfully recorded to memory. \n <----------------------->" << endl;
					MemoryFile.close();
				}
			}
			//Just showing last expression , in future I modernize that and it will send all expressions like list.
			else if (userChooseOption == '2') {
				ifstream MemoryFile("MemoryFile.bin", ios::binary);
				size_t length;
				cout << "<--------{saved expressions}------------->" << endl;
				while (MemoryFile.read(reinterpret_cast<char*>(&length), sizeof(length))) {
					char* expression = new char[length + 1];
					MemoryFile.read(expression, length);
					expression[length] = '\0';
					cout << expression << endl;
					delete[] expression;
				}
				cout << "<------------------------------------------->" << endl;
				MemoryFile.close();
			}
			else if (userChooseOption == '3') {
				ifstream MemoryFile("MemoryFile.bin", ios::binary);
				int index;
				cout << "<--------{Message}------------->\n Enter your index from 0 \n <----------------------->" << endl;
				MemoryFile.close();
				cin >> index;

				size_t length;
				size_t currentIndex = 0; //in this moment i just don't know how do the system that will find expression corretly,so i make a close system that could work
				bool found = false;
				while (MemoryFile.read(reinterpret_cast<char*>(&length), sizeof(length))) {
					char* expression = new char[length + 1];
					MemoryFile.read(expression, length);
					expression[length] = '\0';
					if (currentIndex == index) { //but it's still don't work even for first expression in memory... idk wat's wrong...
						cout << "Expression is found " << expression << endl;
						userCinValue = expression;
						found = true;
						delete[] expression;
						break;
					}
					delete[] expression;
					currentIndex++;
				}
				if (!found) {
					cout << "Expression by " << index << " is not found" << endl;
				}
				MemoryFile.close();
			}
			else {
				cout << "<--------{Message}------------->\n You entered some other option that we don't have \n <----------------------------->" << endl;
			}
		}
		else {
			cout << "<--------{Message}------------->\n You entered some other option that we don't have \n <----------------------------->" << endl;
		}

	}
}

