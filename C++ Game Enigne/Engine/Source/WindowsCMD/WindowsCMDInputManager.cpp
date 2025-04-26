#include "WindowsCMDInputManager.h"

WindowsCMDInputManager::WindowsCMDInputManager(HANDLE* consolInputHandle)
{
    consolInputHandle = consolInputHandle;
}

WindowsCMDInputManager::~WindowsCMDInputManager()
{

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


WindowsCMDInputManager::MouseButtonState WindowsCMDInputManager::GetMouseButtonState(WindowsCMDInputManager::MouseButton mouseButton)
{
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
}

