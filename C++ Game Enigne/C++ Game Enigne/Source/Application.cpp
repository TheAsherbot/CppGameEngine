#include <iostream>
#include "WindowsCMDRenderer/WindowsCMDRenerer.h"
#include <windows.h>


WindowsCMDRenderer* windowsCMDRenderer;

void Start();
void Update(float deltaTime);


int main()
{
	std::cout << "HelloWorld\n";
	
	windowsCMDRenderer = new WindowsCMDRenderer(20, 20, 20, 20, Start, Update);

	windowsCMDRenderer->Start();

	//windowsCMDRenderer = *new WindowsCMDRenderer(170, 250, 2, 2, Start, Update);
}

void Start()
{

}

void Update(float deltaTime)
{
	(*windowsCMDRenderer).DrawCharacter(0, 0, '8');
	(*windowsCMDRenderer).DrawCharacter(1, 0, '7');
	(*windowsCMDRenderer).DrawString(0, 1, "Hello World!");
}