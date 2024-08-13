#include "WindowsCMDRenerer.h"
#include <Windows.h>
#include <string>

WindowsCMDRenderer::WindowsCMDRenderer(short rows, short columns, short xFontSize, short yFontSize, void(*Start)(), void(*Update)(float deltaTime)) :
    width(rows), height(columns), fontWidth(xFontSize), fontHeight(yFontSize), OnStart(Start), OnUpdate(Update), consoleHandle(CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL))
{

    screenBuffer = new wchar_t[width * height];
    SetConsoleActiveScreenBuffer(consoleHandle);

    for (int i = 0; i < width * height; i++)
    {
        screenBuffer[i] = ' ';
    }

    // Setting this to min value to prevent code from braking later.
    SMALL_RECT windowRect = { 0, 0, 1, 1 };
    SetConsoleWindowInfo(consoleHandle, TRUE, &windowRect);

    CONSOLE_FONT_INFOEX consoleFontInfo;
    consoleFontInfo.cbSize = sizeof(consoleFontInfo);
    consoleFontInfo.nFont = 1;
    consoleFontInfo.dwFontSize.X = fontWidth;
    consoleFontInfo.dwFontSize.Y = fontHeight;
    consoleFontInfo.FontFamily = FF_DONTCARE;
    consoleFontInfo.FontWeight = FW_NORMAL;
    wcscpy_s(consoleFontInfo.FaceName, L"Consolas");

    SetCurrentConsoleFontEx(consoleHandle, false, &consoleFontInfo);

    COORD buffer = { (short)width, (short)height };
    SetConsoleScreenBufferSize(consoleHandle, buffer);

    windowRect = { 0, 0, (short)(width - 1), (short)(height - 1) };
    SetConsoleWindowInfo(consoleHandle, TRUE, &windowRect);


}

WindowsCMDRenderer::~WindowsCMDRenderer()
{

}

void WindowsCMDRenderer::Start()
{
    OnStart();

    while (1)
    {

        COORD buffer = { (short)width, (short)height };
        SetConsoleScreenBufferSize(consoleHandle, buffer);

        SMALL_RECT windowRect = { 0, 0, (short)(width - 1), (short)(height - 1) };
        SetConsoleWindowInfo(consoleHandle, TRUE, &windowRect);


        OnUpdate(0);


        WriteConsoleOutputCharacter(consoleHandle, screenBuffer, width * height, { 0, 0 }, &charactersWritten);
    }
}

void WindowsCMDRenderer::DrawCharacter(const short xPosition, const short yPosition, const wchar_t character)
{
    screenBuffer[xPosition + (yPosition * width)] = (wchar_t)character;
}

void WindowsCMDRenderer::DrawString(const short xPosition, const short yPosition, const std::wstring text)
{
    for (int i = 0; i < text.length(); i++)
    {
        DrawCharacter(xPosition + i, yPosition, text[i]);
    }
}

void WindowsCMDRenderer::DrawRectangle(const short startXPosition, const short startYPosition, const short endXPosition, const short endYPosition, const wchar_t character)
{
    if (endXPosition <= startXPosition || endYPosition <= startYPosition)
    {
        return;
    }

    int xDistance = endXPosition - startXPosition;
    int yDistance = endYPosition - startYPosition;


    for (int x = 0; x < xDistance; x++)
    {
        for (int y = 0; y < yDistance; y++)
        {
            DrawCharacter(startXPosition + x, startYPosition + y, character);
        }
    }

}

