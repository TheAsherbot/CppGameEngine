#pragma once

#include "WindowsCMDRenerer.h"
#include "WindowsCMDInputManager.h"

class WindowsCMD
{
public:
	WindowsCMD(short rows, short columns, short xFontSize, short yFontSize, void(*Start)(), void(*Update)(float deltaTime));
	~WindowsCMD();


	WindowsCMDInputManager *inputManager;
	WindowsCMDRenderer* renderer;
private:

};

WindowsCMD::WindowsCMD(short rows, short columns, short xFontSize, short yFontSize, void(*Start)(), void(*Update)(float deltaTime))
{
	HANDLE consoleInputHandle = nullptr;

	renderer = new WindowsCMDRenderer(rows, columns, xFontSize, yFontSize, Start, Update, &consoleInputHandle);
	inputManager = new WindowsCMDInputManager(&consoleInputHandle);
}

WindowsCMD::~WindowsCMD()
{
}