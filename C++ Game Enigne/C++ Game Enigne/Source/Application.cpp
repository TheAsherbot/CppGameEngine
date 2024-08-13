#include <iostream>
#include "WindowsCMDRenderer/WindowsCMDRenerer.h"
#include <windows.h>


WindowsCMDRenderer* windowsCMDRenderer;

void Start();
void Update(float deltaTime);
void DrawBigCalculator();
void DrawSmallCalculator();

int main()
{
	std::cout << "HelloWorld\n";
	
	windowsCMDRenderer = new WindowsCMDRenderer(9, 14, 30, 30, Start, Update);
	// windowsCMDRenderer = new WindowsCMDRenderer(164, 240, 2, 2, Start, Update);
	
	windowsCMDRenderer->Start();

}

void Start()
{

}

void Update(float deltaTime)
{
	DrawSmallCalculator();
}




void DrawSmallCalculator()
{

#pragma region Frame
	// Vertical Dividers
	windowsCMDRenderer->DrawCharacter(0, 0, 0x2554); // Top Left
	windowsCMDRenderer->DrawRectangle(1, 0, 8, 1, 0x2550); // Top
	windowsCMDRenderer->DrawCharacter(8, 0, 0x2557); // Top Right
	windowsCMDRenderer->DrawRectangle(8, 1, 9, 13, 0x2551); // Right
	windowsCMDRenderer->DrawCharacter(8, 13, 0x255D); // Bottom Right
	windowsCMDRenderer->DrawRectangle(1, 13, 8, 14, 0x2550); // Bottom
	windowsCMDRenderer->DrawCharacter(0, 13, 0x255A); // Bottom Left
	windowsCMDRenderer->DrawRectangle(0, 1, 1, 13, 0x2551); // Left


	// Vertical Dividers
	windowsCMDRenderer->DrawRectangle(2, 4, 3, 13, 0x2502); // Left
	windowsCMDRenderer->DrawRectangle(4, 4, 5, 13, 0x2502); // Left
	windowsCMDRenderer->DrawRectangle(6, 4, 7, 13, 0x2502); // Left
	windowsCMDRenderer->DrawCharacter(2, 13, 0x2567); // Left
	windowsCMDRenderer->DrawCharacter(4, 13, 0x2567); // Left
	windowsCMDRenderer->DrawCharacter(6, 13, 0x2567); // Left


	// Awnser / 1st row Divider
	windowsCMDRenderer->DrawCharacter(0, 3, 0x255f); // Left Conector
	windowsCMDRenderer->DrawRectangle(1, 3, 8, 4, 0x2500); // Bottom
	windowsCMDRenderer->DrawCharacter(8, 3, 0x2562); // Right Conector
	windowsCMDRenderer->DrawCharacter(2, 3, 0x252C); // Left Down Conector
	windowsCMDRenderer->DrawCharacter(4, 3, 0x252C); // Midle Down Conector
	windowsCMDRenderer->DrawCharacter(6, 3, 0x252C); // Right Down Conector

	// 1st row / 2nd row Divider
	windowsCMDRenderer->DrawCharacter(0, 5, 0x255f); // Left Conector
	windowsCMDRenderer->DrawRectangle(1, 5, 8, 6, 0x2500); // Bottom
	windowsCMDRenderer->DrawCharacter(8, 5, 0x2562); // Right Conector
	windowsCMDRenderer->DrawCharacter(2, 5, 0x253C); // Left Down Conector
	windowsCMDRenderer->DrawCharacter(4, 5, 0x253C); // Midle Down Conector
	windowsCMDRenderer->DrawCharacter(6, 5, 0x253C); // Right Down Conector

	// 2nd row / 3rd row Divider
	windowsCMDRenderer->DrawCharacter(0, 7, 0x255f); // Left Conector
	windowsCMDRenderer->DrawRectangle(1, 7, 8, 8, 0x2500); // Bottom
	windowsCMDRenderer->DrawCharacter(8, 7, 0x2562); // Right Conector
	windowsCMDRenderer->DrawCharacter(2, 7, 0x253C); // Left Down Conector
	windowsCMDRenderer->DrawCharacter(4, 7, 0x253C); // Midle Down Conector
	windowsCMDRenderer->DrawCharacter(6, 7, 0x253C); // Right Down Conector

	// 3rd row / 4th row Divider
	windowsCMDRenderer->DrawCharacter(0, 9, 0x255f); // Left Conector
	windowsCMDRenderer->DrawRectangle(1, 9, 8, 10, 0x2500); // Bottom
	windowsCMDRenderer->DrawCharacter(8, 9, 0x2562); // Right Conector
	windowsCMDRenderer->DrawCharacter(2, 9, 0x253C); // Left Down Conector
	windowsCMDRenderer->DrawCharacter(4, 9, 0x253C); // Midle Down Conector
	windowsCMDRenderer->DrawCharacter(6, 9, 0x253C); // Right Down Conector

	// 4th row / 5th row Divider
	windowsCMDRenderer->DrawCharacter(0, 11, 0x255f); // Left Conector
	windowsCMDRenderer->DrawRectangle(1, 11, 8, 12, 0x2500); // Bottom
	windowsCMDRenderer->DrawCharacter(8, 11, 0x2562); // Right Conector
	windowsCMDRenderer->DrawCharacter(2, 11, 0x253C); // Left Down Conector
	windowsCMDRenderer->DrawCharacter(4, 11, 0x253C); // Midle Down Conector
	windowsCMDRenderer->DrawCharacter(6, 11, 0x253C); // Right Down Conector
#pragma endregion


#pragma region Inputs
	// Numbers
	windowsCMDRenderer->DrawCharacter(3, 12, '0');
	windowsCMDRenderer->DrawCharacter(1, 10, '1');
	windowsCMDRenderer->DrawCharacter(3, 10, '2');
	windowsCMDRenderer->DrawCharacter(5, 10, '3');
	windowsCMDRenderer->DrawCharacter(1, 8, '4');
	windowsCMDRenderer->DrawCharacter(3, 8, '5');
	windowsCMDRenderer->DrawCharacter(5, 8, '6');
	windowsCMDRenderer->DrawCharacter(1, 6, '7');
	windowsCMDRenderer->DrawCharacter(3, 6, '8');
	windowsCMDRenderer->DrawCharacter(5, 6, '9');

	// Other
	windowsCMDRenderer->DrawCharacter(1, 12, 'S'); // Store
	windowsCMDRenderer->DrawCharacter(5, 12, '.');
	windowsCMDRenderer->DrawCharacter(1, 4, 'C');
	windowsCMDRenderer->DrawCharacter(3, 4, 'A'); // Clear All
	windowsCMDRenderer->DrawCharacter(5, 4, 0x00AB); // Clear All

	// Operations
	windowsCMDRenderer->DrawCharacter(7, 4, 0xF7); // Clear All
	windowsCMDRenderer->DrawCharacter(7, 6, 0xD7); // Clear All
	windowsCMDRenderer->DrawCharacter(7, 8, '-'); // Clear All
	windowsCMDRenderer->DrawCharacter(7, 10, '+'); // Clear All
	windowsCMDRenderer->DrawCharacter(7, 12, '='); // Clear All


#pragma endregion


}








void DrawBoarder()
{
	// Boarder
	windowsCMDRenderer->DrawRectangle(0, 1, 1, 239, 0x2588);
	windowsCMDRenderer->DrawRectangle(163, 1, 164, 239, 0x2588);
	windowsCMDRenderer->DrawRectangle(1, 0, 163, 1, 0x2588);
	windowsCMDRenderer->DrawRectangle(1, 239, 163, 240, 0x2588);
}

void DrawDeviders()
{
	// Horizontal
	windowsCMDRenderer->DrawRectangle(0, 59, 164, 60, 0x2588);
	windowsCMDRenderer->DrawRectangle(0, 95, 164, 96, 0x2588);
	windowsCMDRenderer->DrawRectangle(0, 131, 164, 132, 0x2588);
	windowsCMDRenderer->DrawRectangle(0, 167, 164, 168, 0x2588);
	windowsCMDRenderer->DrawRectangle(0, 203, 164, 204, 0x2588);

	// Vertical
	windowsCMDRenderer->DrawRectangle(41, 59, 42, 240, 0x2588);
	windowsCMDRenderer->DrawRectangle(82, 59, 83, 240, 0x2588);
	windowsCMDRenderer->DrawRectangle(123, 59, 124, 240, 0x2588);
}

void DrawBigCalculator()
{
	DrawBoarder();
	DrawDeviders();
}