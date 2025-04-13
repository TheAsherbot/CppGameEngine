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
	enum Key
	{
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		One,
		Two,
		THree,
		Four,
		Five,
		Six,
		Seven,
		Eight,
		Nine,
		Zero,
		Ctrl,
		Shift,
		Alt,
		Esc,
		Tab,
		ExclamationMark,
		QuestionMark,
		AtSign,
		Pound,
		DollerSign,
		PercentSign,
		Carrot,
		AndSybmle,
		Star,
		OpenParinthases,
		CloseParinthases,
		Minus,
		Underscore,
		Plus,
		Exquals,
		Backspace,
		OpenBrace,
		CloseBrace,
		Openbracket,
		CloseBracket,
		Pile,
		BackSlash,
		ForwardSlash,
		Collen,
		SemiCollen,
		Quotations,
		Aposraphy,
		Enter,
		GraterThanSymble,
		LessThanSymble,
		UpArrow,
		DownArrow,
		LeftArrow,
		RightArrow,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		Pause,
		Deleate,
		Insert,
		Home,
		PageUp,
		PageDown,
		End,
	};
	


	WindowsCMDRenderer(short rows, short columns, short xFontSize, short yFontSize, void(*Start)(), void(*Update)(float deltaTime));
	WindowsCMDRenderer(void(*Start)(), void(*Update)(float deltaTime));
	WindowsCMDRenderer();
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
	
	bool IsKeyPressed(Key key);

	
private:

	short width;
	short height;

	short fontWidth;
	short fontHeight;

	wchar_t* screenBuffer;

	DWORD numberOfCharactersWritten = 0;
	HANDLE consoleHandle;



	HANDLE consolInputHandle;
	DWORD numberOfInputs;
	int mouseNewState[5];
	int mouseOldState[5];
	Mouse mouse[5];

	
	
	void(*OnStart)();
	void(*OnUpdate)(float deltaTime);

};



