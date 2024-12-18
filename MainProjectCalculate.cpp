
//Block of code for including and connecting all of the Libs.
#include <iostream>
#include <ctime>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <cmath>
#include <fstream>
//---------- My own Libs ----------
#include <HFileForIsDigitCheck.h>



int main()
{
	while (true) {
		cout << "<------------{Menu}------------->" << endl
			<< "Choose option: " << endl
			<< "1 - Enter your exspression;" << endl
			<< "2 - show your mathematical expression;" << endl
			<< "3 - Show all Array Information;" << endl
			<< "4 - Clear exspresion;" << endl
			<< "5 - Calculate;" << endl
			<< "<-------------------------------->" << endl;

		cin >> userChooseOption;
		if (userChooseOption == '1') { // User enters his exspression with space after each operand or operator.

			string tempVaruable = "";

			cout << "<------------{Menu}------------->" << endl << "Enter your exspression with operands (0-9) , operators(+,-,*,/,^,| <-sqrt() , ( , ) )" << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			getline(cin, userCinValue);
			for (int i = 0; i < userCinValue.length(); i++) {
				if (userCinValue[i] == ' ') {
					objMathFunc.AddOperandOrOperatorInMemory(tempVaruable);
					tempVaruable = "";
				}
				else {
					tempVaruable += userCinValue[i];
				}

			}
			if (!tempVaruable.empty()) {
				objMathFunc.AddOperandOrOperatorInMemory(tempVaruable);
				tempVaruable.clear();
			}

		}
		else if (userChooseOption == '2') {
			cout << userCinValue << endl;
		}
		else if (userChooseOption == '3') {
			cout << "------First Array-----" << endl;
			objMathFunc.PrintInfoMemoryArr();
			cout << "------Next Array-----" << endl;
			objMathFunc.PrintInfoNumberArr();
			cout << "------Next Array-----" << endl;
			objMathFunc.PrintInfoOperatorArr();
			cout << "------Next Array-----" << endl;
			objMathFunc.PrintInfoPriorityArr();
		}
		else if (userChooseOption == '4') {
			userCinValue.clear();
			tempVaruable.clear();

			objMathFunc.Clear();
		}
		else if (userChooseOption == '5') {
			objMathFunc.RecreatingOperandsOperators();
			objMathFunc.MathOperations();
		}

	}
}


