#include <windows.h>
#include <string>     // std::string, std::to_string

#include "WindowsCMDRenerer.h"


WindowsCMDRenderer::WindowsCMDRenderer(short rows, short columns, short xFontSize, short yFontSize, void(*Start)(), void(*Update)(float deltaTime)) :
    width(rows), height(columns), fontWidth(xFontSize), fontHeight(yFontSize), OnStart(Start), OnUpdate(Update), consoleHandle(CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL))
{

    screenBuffer = new wchar_t[width * height];
    SetConsoleActiveScreenBuffer(consoleHandle);
    consolInputHandle = GetStdHandle(STD_INPUT_HANDLE);

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

    SetConsoleMode(consolInputHandle, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
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


        
#pragma region Mouse Input
        INPUT_RECORD inputRecord[32];
        // for (int i = 0; i < numberOfInputs; i++)
        // {
        //     inputRecord[i] = *new INPUT_RECORD();
        // }

        GetNumberOfConsoleInputEvents(consolInputHandle, &numberOfInputs);

        if (numberOfInputs > 0)
        {
            ReadConsoleInput(consolInputHandle, inputRecord, numberOfInputs, &numberOfInputs);
        }

        for (int i = 0; i < numberOfInputs; i++)
        {
            switch (inputRecord[i].EventType)
            {
            case MOUSE_EVENT:
                switch (inputRecord[i].Event.MouseEvent.dwEventFlags)
                {
                case MOUSE_MOVED:
                    break;
                case 0:
                    //                                      5 Possible mouse buttons, 0 = Left, 1 = Right, 2 = Middle, 3 = Side Button 1, 4 = Side Button 2
                    for (int mouseButton = 0; mouseButton < 5; mouseButton++)
                    {
                        mouseNewState[mouseButton] = inputRecord[i].Event.MouseEvent.dwButtonState & (1 << mouseButton);
                    }
                    break;
                }
                break;
            }
        }
        if (mouse[0].isHeld)
        {
            std::cout << 10 << std::endl;
        }
        //                                      5 Possible mouse buttons, 0 = Left, 1 = Right, 2 = Middle, 3 = Side Button 1, 4 = Side Button 2
        for (int mouseButton = 0; mouseButton < 5; mouseButton++)
        {
            mouse[mouseButton].isPressed = false;
            mouse[mouseButton].isReleased = false;

            if (mouseNewState[mouseButton] != mouseOldState[mouseButton])
            {
                if (mouseNewState[mouseButton])
                {
                    mouse[mouseButton].isPressed = true;
                    mouse[mouseButton].isHeld = true;
                }
                else
                {
                    mouse[mouseButton].isReleased = true;
                    mouse[mouseButton].isHeld = false;
                }
            }

            mouseOldState[mouseButton] = mouseNewState[mouseButton];
        }
#pragma endregion



        OnUpdate(0);


        WriteConsoleOutputCharacter(consoleHandle, screenBuffer, width * height, { 0, 0 }, &numberOfCharactersWritten);

    }
}


void WindowsCMDRenderer::DrawWCharacter(const short xPosition, const short yPosition, const wchar_t character)
{
    screenBuffer[xPosition + (yPosition * width)] = (wchar_t)character;
}
void WindowsCMDRenderer::DrawCharacter(const short xPosition, const short yPosition, const char character)
{
    screenBuffer[xPosition + (yPosition * width)] = (wchar_t)character;
}


void WindowsCMDRenderer::DrawWString(const short xPosition, const short yPosition, const std::wstring text)
{
    for (int i = 0; i < text.length(); i++)
    {
        DrawWCharacter(xPosition + i, yPosition, text[i]);
    }
}
void WindowsCMDRenderer::DrawString(const short xPosition, const short yPosition, const std::string text)
{
    for (int i = 0; i < text.length(); i++)
    {
        DrawWCharacter(xPosition + i, yPosition, text[i]);
    }
}

void WindowsCMDRenderer::DrawRectangleWCharacter(const short startXPosition, const short startYPosition, const short endXPosition, const short endYPosition, const wchar_t character)
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
            DrawWCharacter(startXPosition + x, startYPosition + y, character);
        }
    }

}
void WindowsCMDRenderer::DrawRectangleCharacter(const short startXPosition, const short startYPosition, const short endXPosition, const short endYPosition, const char character)
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
            DrawWCharacter(startXPosition + x, startYPosition + y, character);
        }
    }

}

void WindowsCMDRenderer::HideCurser()
{
    ShowCursor(FALSE);
}

Vector2 WindowsCMDRenderer::GetMousePosition()
{
    POINT mousePoint;
    GetCursorPos(&mousePoint); // On screen

    GetConsoleWindow();

    if (!ScreenToClient(GetConsoleWindow(), &mousePoint))
    {
        DrawString(0, 3, "Not Work");
        




        //Get the error message ID, if any.
        DWORD errorMessageID = ::GetLastError();
        if (errorMessageID == 0) {
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

        DrawString(0, 4, message);
    }

    Vector2 result;
    result.x = mousePoint.x;
    result.y = mousePoint.y;

    return result;
}

void WindowsCMDRenderer::IsButtonPressed(const short startXPosition, const short startYPosition, const short endXPosition, const short endYPosition, void(*OnButtonPressed)())
{
    if (mouse[0].isReleased)
    {
        Vector2 mousePosition = GetMousePosition();
        if (mousePosition.x > startXPosition && mousePosition.x < endXPosition && mousePosition.y > startYPosition && mousePosition.y < endYPosition)
        {
            OnButtonPressed();
        }
    }
}






std::string Vector2::ToString() const
{
    std::string result = "x: " + std::to_string(x) + ", y: " + std::to_string(y);
    return result;
}


