#pragma once
#include <iostream>
#include <Windows.h>

struct Vector2
{
public:
	short x;
	short y;

	std::string ToString() const;
};

struct Mouse
{
public:
	bool isPressed;
	bool isReleased;
	bool isHeld;
};

class WindowsCMDRenderer
{
public:

	


	WindowsCMDRenderer(short rows, short columns, short xFontSize, short yFontSize, void(*Start)(), void(*Update)(float deltaTime));
	~WindowsCMDRenderer();

	void Start();

	void DrawWCharacter(const short xPosition, const short yPosition, const wchar_t character);
	void DrawCharacter(const short xPosition, const short yPosition, const char character);
	
	void DrawWString(const short xPosition, const short yPosition, const std::wstring text);
	void DrawString(const short xPosition, const short yPosition, const std::string text);
	
	void DrawRectangleWCharacter(const short startXPosition, const short startYPosition, const short endXPosition, const short endYPosition, const wchar_t character);
	void DrawRectangleCharacter(const short startXPosition, const short startYPosition, const short endXPosition, const short endYPosition, const char character);

	void HideCurser();
	Vector2 GetMousePosition();

	void IsButtonPressed(const short startXPosition, const short startYPosition, const short endXPosition, const short endYPosition, void(*OnButtonPressed)());
	

	
private:

	short width;
	short height;

	short fontWidth;
	short fontHeight;

	wchar_t* screenBuffer;

	DWORD numberOfCharactersWritten = 0;
	HANDLE consoleHandle;



	HANDLE consolInputHandle;
	INPUT_RECORD inputRecord[32];
	DWORD numberOfInputs;
	int mouseNewState[5];
	int mouseOldState[5];
	Mouse mouse[5];

	
	
	void(*OnStart)();
	void(*OnUpdate)(float deltaTime);

};



