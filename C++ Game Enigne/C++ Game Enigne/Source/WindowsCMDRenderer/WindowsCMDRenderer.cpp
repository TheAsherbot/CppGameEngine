#include "WindowsCMDRenerer.h"
#include <Windows.h>
#include <string>

WindowsCMDRenderer::WindowsCMDRenderer(short rows, short columns, short xFontSize, short yFontSize, void(*Start)(), void(*Update)(float deltaTime)) :
    width(rows), height(columns), fontWidth(xFontSize), fontHeight(yFontSize), OnStart(Start), OnUpdate(Update), consoleHandle(CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL))
{

    screenBuffer = new wchar_t[width * height];
    if (!SetConsoleActiveScreenBuffer(consoleHandle))
    {
        std::cout << "ERROR!\n";
        std::cout << GetLastErrorAsString() << std::endl;
    }

    for (int i = 0; i < width * height; i++)
    {
        screenBuffer[i] = 1;
    }

    // Setting this to min value to prevent code from braking later.
    SMALL_RECT windowRect = { 0, 0, 1, 1 };
    SetConsoleWindowInfo(consoleHandle, TRUE, &windowRect);


    CONSOLE_FONT_INFOEX consoleFontInfo;
    consoleFontInfo.cbSize = sizeof(consoleFontInfo);
    consoleFontInfo.nFont = 0;
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

//Returns the last Win32 error, in string format. Returns an empty string if there is no error.
std::string WindowsCMDRenderer::GetLastErrorAsString()
{
    //Get the error message ID, if any.
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0) {
        return std::string(); //No error message has been recorded
    }

    LPSTR messageBuffer = nullptr;

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    //Copy the error message into a std::string.
    std::string message(messageBuffer, size);

    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);

    return message;
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

void WindowsCMDRenderer::DrawString(const int xPosition, const int yPosition, const std::string text)
{
    for (int i = 0; i < text.length(); i++)
    {
        DrawCharacter(xPosition + i, yPosition, text[i]);
    }
}

void WindowsCMDRenderer::DrawCharacter(const short xPosition, const short yPosition, const char character)
{
    screenBuffer[xPosition + (yPosition * width)] = character;
}
