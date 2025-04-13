#include "WindowsCMDInputManager.h"

void WindowsCMDInputManager::HideCurser(bool hidden)
{
    ShowCursor(hidden);
}

Vector2 WindowsCMDInputManager::GetMousePosition()
{
    POINT mousePoint;
    GetCursorPos(&mousePoint); // On screen

    GetConsoleWindow();

    if (!ScreenToClient(GetConsoleWindow(), &mousePoint))
    {
        // Debug, Error "Not Work" Because this fialed





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

        // Debug, Error *message Because this failed
    }

    Vector2 result;
    result.x = mousePoint.x;
    result.y = mousePoint.y;

    return result;
}

void WindowsCMDInputManager::IsButtonPressed(const short startXPosition, const short startYPosition, const short endXPosition, const short endYPosition, void(*OnButtonPressed)())
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

bool WindowsCMDInputManager::IsKeyPressed(Key key)
{
}