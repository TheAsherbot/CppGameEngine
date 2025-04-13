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


class WindowsCMDInputManager
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
		Equals,
		Backspace,
		OpenBrace,
		CloseBrace,
		Openbracket,
		CloseBracket,
		Pipe,
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

	WindowsCMDInputManager();
	~WindowsCMDInputManager();

private:

	void HideCurser(bool hidden);
	Vector2 GetMousePosition();

	void IsButtonPressed(const short startXPosition, const short startYPosition, const short endXPosition, const short endYPosition, void(*OnButtonPressed)());

	bool IsKeyPressed(Key key);

	HANDLE consolInputHandle;
	DWORD numberOfInputs;
	int mouseNewState[5];
	int mouseOldState[5];
	Mouse mouse[5];

	std::string keyCodes[94] 
	{
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"0",
		"Ctrl",
		"Shift",
		"Alt",
		"Esc",
		"Tab",
		"!",
		"?",
		"@",
		"#",
		"$",
		"%",
		"^",
		"&",
		"*",
		"(",
		")",
		"-",
		"_",
		"+",
		"=",
		"BackSpace",
		"{",
		"}",
		"[",
		"]",
		"|",
		"\\",
		"/",
		":",
		";",
		"\"",
		"'",
		"Enter",
		">",
		"<",
		"UpArrow",
		"DownArrow",
		"LeftArrow",
		"RightArrow",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"F11",
		"F12",
		"Pause",
		"Deleate",
		"Insert",
		"Home",
		"PageUp",
		"PageDowb",
		"End",
	};

};