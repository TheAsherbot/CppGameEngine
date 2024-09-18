#include <iostream>
#include <string>
#include<sstream>
#include <windows.h>
#include <cmath>

#include "WindowsCMDRenderer/WindowsCMDRenerer.h"


enum Operation
{
	None,
	Division,
	Multiplication,
	Subtraction,
	Addition,
};

WindowsCMDRenderer* windowsCMDRenderer;
float number1;
float number2;
float* currentNumber;
bool isOnDecimalNumber;
int numberOfDecimalPlaces;
float storedNumber;
Operation operation;

void Start();
void Update(float deltaTime);



void DrawSmallCalculator();
void DrawNumbers();
void HandleButtons();


void OnClear();
void OnClearAll();
void OnBackspace();
void OnStore();
void OnDecimal();

void On0();
void On1();
void On2();
void On3();
void On4();
void On5();
void On6();
void On7();
void On8();
void On9();

void OnDivide();
void OnMultiply();
void OnSubtract();
void OnAdd();
void OnEqual();



int main()
{
	std::cout << "HelloWorld\n";

	windowsCMDRenderer = new WindowsCMDRenderer(9, 14, 30, 30, Start, Update);
	// windowsCMDRenderer = new WindowsCMDRenderer(164, 240, 2, 2, Start, Update);

	windowsCMDRenderer->HideCurser();

	windowsCMDRenderer->Start();

	return 0;
}

void Start()
{
	currentNumber = &number1;
}

void Update(float deltaTime)
{
	DrawSmallCalculator();
	HandleButtons();
	DrawNumbers();
}




void DrawSmallCalculator()
{

#pragma region Frame
	// Vertical Dividers
	windowsCMDRenderer->DrawWCharacter(0, 0, 0x2554); // Top Left
	windowsCMDRenderer->DrawRectangleWCharacter(1, 0, 8, 1, 0x2550); // Top
	windowsCMDRenderer->DrawWCharacter(8, 0, 0x2557); // Top Right
	windowsCMDRenderer->DrawRectangleWCharacter(8, 1, 9, 13, 0x2551); // Right
	windowsCMDRenderer->DrawWCharacter(8, 13, 0x255D); // Bottom Right
	windowsCMDRenderer->DrawRectangleWCharacter(1, 13, 8, 14, 0x2550); // Bottom
	windowsCMDRenderer->DrawWCharacter(0, 13, 0x255A); // Bottom Left
	windowsCMDRenderer->DrawRectangleWCharacter(0, 1, 1, 13, 0x2551); // Left


	// Horizontal Dividers
	windowsCMDRenderer->DrawRectangleWCharacter(2, 4, 3, 13, 0x2502); // Left
	windowsCMDRenderer->DrawRectangleWCharacter(4, 4, 5, 13, 0x2502); // Left
	windowsCMDRenderer->DrawRectangleWCharacter(6, 4, 7, 13, 0x2502); // Left
	windowsCMDRenderer->DrawWCharacter(2, 13, 0x2567); // Left
	windowsCMDRenderer->DrawWCharacter(4, 13, 0x2567); // Left
	windowsCMDRenderer->DrawWCharacter(6, 13, 0x2567); // Left


	// Awnser / 1st row Divider
	windowsCMDRenderer->DrawWCharacter(0, 3, 0x255f); // Left Conector
	windowsCMDRenderer->DrawRectangleWCharacter(1, 3, 8, 4, 0x2500); // Bottom
	windowsCMDRenderer->DrawWCharacter(8, 3, 0x2562); // Right Conector
	windowsCMDRenderer->DrawWCharacter(2, 3, 0x252C); // Left Down Conector
	windowsCMDRenderer->DrawWCharacter(4, 3, 0x252C); // Midle Down Conector
	windowsCMDRenderer->DrawWCharacter(6, 3, 0x252C); // Right Down Conector

	// 1st row / 2nd row Divider
	windowsCMDRenderer->DrawWCharacter(0, 5, 0x255f); // Left Conector
	windowsCMDRenderer->DrawRectangleWCharacter(1, 5, 8, 6, 0x2500); // Bottom
	windowsCMDRenderer->DrawWCharacter(8, 5, 0x2562); // Right Conector
	windowsCMDRenderer->DrawWCharacter(2, 5, 0x253C); // Left Down Conector
	windowsCMDRenderer->DrawWCharacter(4, 5, 0x253C); // Midle Down Conector
	windowsCMDRenderer->DrawWCharacter(6, 5, 0x253C); // Right Down Conector

	// 2nd row / 3rd row Divider
	windowsCMDRenderer->DrawWCharacter(0, 7, 0x255f); // Left Conector
	windowsCMDRenderer->DrawRectangleWCharacter(1, 7, 8, 8, 0x2500); // Bottom
	windowsCMDRenderer->DrawWCharacter(8, 7, 0x2562); // Right Conector
	windowsCMDRenderer->DrawWCharacter(2, 7, 0x253C); // Left Down Conector
	windowsCMDRenderer->DrawWCharacter(4, 7, 0x253C); // Midle Down Conector
	windowsCMDRenderer->DrawWCharacter(6, 7, 0x253C); // Right Down Conector

	// 3rd row / 4th row Divider
	windowsCMDRenderer->DrawWCharacter(0, 9, 0x255f); // Left Conector
	windowsCMDRenderer->DrawRectangleWCharacter(1, 9, 8, 10, 0x2500); // Bottom
	windowsCMDRenderer->DrawWCharacter(8, 9, 0x2562); // Right Conector
	windowsCMDRenderer->DrawWCharacter(2, 9, 0x253C); // Left Down Conector
	windowsCMDRenderer->DrawWCharacter(4, 9, 0x253C); // Midle Down Conector
	windowsCMDRenderer->DrawWCharacter(6, 9, 0x253C); // Right Down Conector

	// 4th row / 5th row Divider
	windowsCMDRenderer->DrawWCharacter(0, 11, 0x255f); // Left Conector
	windowsCMDRenderer->DrawRectangleWCharacter(1, 11, 8, 12, 0x2500); // Bottom
	windowsCMDRenderer->DrawWCharacter(8, 11, 0x2562); // Right Conector
	windowsCMDRenderer->DrawWCharacter(2, 11, 0x253C); // Left Down Conector
	windowsCMDRenderer->DrawWCharacter(4, 11, 0x253C); // Midle Down Conector
	windowsCMDRenderer->DrawWCharacter(6, 11, 0x253C); // Right Down Conector
#pragma endregion


#pragma region Inputs
	// Numbers
	windowsCMDRenderer->DrawWCharacter(3, 12, '0');
	windowsCMDRenderer->DrawWCharacter(1, 10, '1');
	windowsCMDRenderer->DrawWCharacter(3, 10, '2');
	windowsCMDRenderer->DrawWCharacter(5, 10, '3');
	windowsCMDRenderer->DrawWCharacter(1, 8, '4');
	windowsCMDRenderer->DrawWCharacter(3, 8, '5');
	windowsCMDRenderer->DrawWCharacter(5, 8, '6');
	windowsCMDRenderer->DrawWCharacter(1, 6, '7');
	windowsCMDRenderer->DrawWCharacter(3, 6, '8');
	windowsCMDRenderer->DrawWCharacter(5, 6, '9');

	// Other
	windowsCMDRenderer->DrawWCharacter(1, 12, 'S'); // Store
	windowsCMDRenderer->DrawWCharacter(5, 12, '.');
	windowsCMDRenderer->DrawWCharacter(1, 4, 'C');
	windowsCMDRenderer->DrawWCharacter(3, 4, 'A'); // Clear All
	windowsCMDRenderer->DrawWCharacter(5, 4, 0x00AB); // Back Space

	// Operations
	windowsCMDRenderer->DrawWCharacter(7, 4, 0xF7); // Clear All
	windowsCMDRenderer->DrawWCharacter(7, 6, 0xD7); // Clear All
	windowsCMDRenderer->DrawWCharacter(7, 8, '-'); // Clear All
	windowsCMDRenderer->DrawWCharacter(7, 10, '+'); // Clear All
	windowsCMDRenderer->DrawWCharacter(7, 12, '='); // Clear All




#pragma endregion


}

void DrawNumbers()
{
	std::stringstream number1StringStream;
	number1StringStream << number1;
	std::stringstream number2StringStream;
	number2StringStream << number2;

	windowsCMDRenderer->DrawRectangleCharacter(1, 1, 8, 3, ' ');

	windowsCMDRenderer->DrawString(1, 1, number1StringStream.str());
	windowsCMDRenderer->DrawString(1, 2, number2StringStream.str());

}

void HandleButtons()
{
	windowsCMDRenderer->IsButtonPressed(22, 106, 73, 162, OnClear);
	windowsCMDRenderer->IsButtonPressed(77, 106, 132, 162, OnClearAll);
	windowsCMDRenderer->IsButtonPressed(137, 106, 192, 162, OnBackspace);
	windowsCMDRenderer->IsButtonPressed(197, 106, 248, 162, OnDivide);

	windowsCMDRenderer->IsButtonPressed(22, 166, 73, 222, On7);
	windowsCMDRenderer->IsButtonPressed(77, 166, 132, 222, On8);
	windowsCMDRenderer->IsButtonPressed(137, 166, 192, 222, On9);
	windowsCMDRenderer->IsButtonPressed(197, 166, 248, 222, OnMultiply);

	windowsCMDRenderer->IsButtonPressed(22, 226, 73, 282, On4);
	windowsCMDRenderer->IsButtonPressed(77, 226, 132, 282, On5);
	windowsCMDRenderer->IsButtonPressed(137, 226, 192, 282, On6);
	windowsCMDRenderer->IsButtonPressed(197, 226, 248, 282, OnSubtract);

	windowsCMDRenderer->IsButtonPressed(22, 286, 73, 342, On1);
	windowsCMDRenderer->IsButtonPressed(77, 286, 132, 342, On2);
	windowsCMDRenderer->IsButtonPressed(137, 286, 192, 342, On3);
	windowsCMDRenderer->IsButtonPressed(197, 286, 248, 342, OnAdd);

	windowsCMDRenderer->IsButtonPressed(22, 346, 73, 400, OnStore);
	windowsCMDRenderer->IsButtonPressed(77, 346, 132, 400, On0);
	windowsCMDRenderer->IsButtonPressed(137, 346, 192, 400, OnDecimal);
	windowsCMDRenderer->IsButtonPressed(197, 346, 248, 400, OnEqual);
}








void OnClear()
{
	*currentNumber = 0;
	isOnDecimalNumber = false;
}
void OnClearAll()
{
	number1 = 0;
	number2 = 0;
	operation = None;
	isOnDecimalNumber = false;
	numberOfDecimalPlaces = 0;
	currentNumber = &number1;
}
void OnBackspace()
{
	//Moving decimal places so they are no longer a decimal place, then moving them back | - 1 to exclude the place we are removing
	*currentNumber = std::floorf((*currentNumber) * std::powf(10, numberOfDecimalPlaces - 1)) / (float)std::powf(10, std::fmaxf(0, numberOfDecimalPlaces - 1));
	if (numberOfDecimalPlaces > 0)
	{
		numberOfDecimalPlaces--;
		isOnDecimalNumber = numberOfDecimalPlaces;
	}
}
void OnStore()
{
	if ((*currentNumber) == 0)
	{
		*currentNumber = storedNumber;
	}
	else
	{
		storedNumber = *currentNumber;
	}
}
void OnDecimal()
{
	if (!isOnDecimalNumber)
	{
		isOnDecimalNumber = true;
		numberOfDecimalPlaces = 0;
	}
}

void AddNumber(int number)
{
	if (isOnDecimalNumber)
	{
		numberOfDecimalPlaces++;
		*currentNumber += (float)number / (float)(std::powf(10.0, numberOfDecimalPlaces));
	}
	else
	{
		*currentNumber = (*currentNumber) * 10 + number;
	}
}
void On0()
{
	AddNumber(0);
}
void On1()
{
	AddNumber(1);
}
void On2()
{
	AddNumber(2);
}
void On3()
{
	AddNumber(3);
}
void On4()
{
	AddNumber(4);
}
void On5()
{
	AddNumber(5);
}
void On6()
{
	AddNumber(6);
}
void On7()
{
	AddNumber(7);
}
void On8()
{
	AddNumber(8);
}
void On9()
{
	AddNumber(9);
}

void HandleCurrentNumbers()
{
	if (currentNumber == &number2)
	{
		OnEqual();
	}
	else
	{
		isOnDecimalNumber = false;
		numberOfDecimalPlaces = 0;
		currentNumber = &number2;
	}
}
void OnDivide()
{
	HandleCurrentNumbers();

	operation = Division;
}
void OnMultiply()
{
	HandleCurrentNumbers();

	operation = Multiplication;
}
void OnSubtract()
{
	HandleCurrentNumbers();

	operation = Subtraction;
}
void OnAdd()
{
	HandleCurrentNumbers();

	operation = Addition;
}
void OnEqual()
{
	switch (operation)
	{
	default:
	case None:

		break;
	case Division:
		number1 = number1 / number2;
		break;
	case Multiplication:
		number1 = number1 * number2;
		break;
	case Subtraction:
		number1 = number1 - number2;
		break;
	case Addition:
		number1 = number1 + number2;
		break;
	}
	number2 = 0;
	numberOfDecimalPlaces = 0;
	isOnDecimalNumber = false;
	currentNumber = &number1;
	operation = None;
}



