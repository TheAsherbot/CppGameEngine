#pragma once
#include <iostream>
#include <Windows.h>

class WindowsCMDRenderer
{
public:

	WindowsCMDRenderer(short rows, short columns, short xFontSize, short yFontSize, void(*Start)(), void(*Update)(float deltaTime));
	~WindowsCMDRenderer();

	void Start();

	void DrawCharacter(const short xPosition, const short yPosition, const char character);
	void DrawString(const int xPosition, const int yPosition, const std::string text);
	std::string GetLastErrorAsString();


	
private:

	short width;
	short height;

	short fontWidth;
	short fontHeight;


	wchar_t* screenBuffer;
	void(*OnStart)();
	void(*OnUpdate)(float deltaTime);

	DWORD charactersWritten = 0;
	HANDLE consoleHandle;

};



