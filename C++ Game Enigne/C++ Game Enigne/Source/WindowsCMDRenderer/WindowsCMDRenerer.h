#pragma once
#include <iostream>
#include <Windows.h>

class WindowsCMDRenderer
{
public:

	WindowsCMDRenderer(short rows, short columns, short xFontSize, short yFontSize, void(*Start)(), void(*Update)(float deltaTime));
	~WindowsCMDRenderer();

	void Start();

	void DrawCharacter(const short xPosition, const short yPosition, const wchar_t character);
	void DrawString(const short xPosition, const short yPosition, const std::wstring text);
	void DrawRectangle(const short startXPosition, const short startYPosition, const short endXPosition, const short endYPosition, const wchar_t character);


	
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



