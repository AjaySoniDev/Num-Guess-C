// guess_game.c
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>

#define IDC_EDIT_NUM        1
#define IDC_BUTTON_GUESS    2
#define IDC_STATIC_STATUS   3
#define IDC_BUTTON_HINT     4
#define IDC_BUTTON_RESTART  5
#define IDC_STATIC_POINTS   6

wchar_t numberStr[16];
int number = 0, tries = 0, maxTries = 5;
int points = 0, totalPoints = 0;

typedef struct {
    int num;
    const wchar_t* message;
} Hint;

Hint hints[] = {
    {1, L"The Topper"},
    {2, L"An Even Number"},
    {3, L"Unlucky Number"},
    {4, L"An Even Number"},
    {5, L"Odd Number"},
    {6, L"Hardly Comes in Dice"},
    {7, L"Related to MSD"},
    {8, L"Big Bro of 4"},
    {9, L"The Larger"},
    {10, L"I have no Hint"}
};

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);
void resetGame(HWND);
void updatePointsDisplay(HWND);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR args, int nCmdShow) {
    WNDCLASSW wc = {0};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInstance;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassW(&wc)) return -1;

    HWND hwnd = CreateWindowW(
        L"myWindowClass", L"Guess the Number Game",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100, 500, 400, NULL, NULL, hInstance, NULL);

    srand((unsigned)time(NULL));
    // CreateWindowW sends WM_CREATE before returning, so controls exist now.
    resetGame(hwnd);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

void resetGame(HWND hwnd) {
    number = rand() % 10 + 1;
    tries = 0;
    points = 0;

    if (hwnd) {
        HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_NUM);
        HWND hGuess = GetDlgItem(hwnd, IDC_BUTTON_GUESS);
        HWND hHint = GetDlgItem(hwnd, IDC_BUTTON_HINT);
        HWND hRestart = GetDlgItem(hwnd, IDC_BUTTON_RESTART);
        HWND hStatus = GetDlgItem(hwnd, IDC_STATIC_STATUS);

        if (hEdit) SetWindowTextW(hEdit, L"");
        if (hGuess) EnableWindow(hGuess, TRUE);
        if (hHint) ShowWindow(hHint, SW_HIDE);
        if (hRestart) ShowWindow(hRestart, SW_HIDE);
        if (hStatus) SetWindowTextW(hStatus, L"");

        updatePointsDisplay(hwnd);
    }
}

void updatePointsDisplay(HWND hwnd) {
    wchar_t buffer[64];
    swprintf_s(buffer, sizeof(buffer) / sizeof(buffer[0]), L"Total Points: %d", totalPoints);
    SetWindowTextW(GetDlgItem(hwnd, IDC_STATIC_POINTS), buffer);
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE:
        AddControls(hwnd);
        break;

    case WM_COMMAND:
    {
        int id = LOWORD(wp);
        if (id == IDC_BUTTON_GUESS) {
            GetWindowTextW(GetDlgItem(hwnd, IDC_EDIT_NUM), numberStr, (int)(sizeof(numberStr) / sizeof(numberStr[0])));
            int guess = _wtoi(numberStr);

            // Validate input first (do not consume a try for invalid input)
            if (guess < 1 || guess > 10) {
                SetWindowTextW(GetDlgItem(hwnd, IDC_STATIC_STATUS), L"Please enter a number between 1 and 10.");
                return 0;
            }

            tries++;
            wchar_t buffer[512];

            if (guess > number) {
                swprintf_s(buffer, sizeof(buffer) / sizeof(buffer[0]), L"Too high! Try again.");
            } else if (guess < number) {
                swprintf_s(buffer, sizeof(buffer) / sizeof(buffer[0]), L"Too low! Try again.");
            } else {
                points = (maxTries - tries + 1) * 2;
                totalPoints += points;
                swprintf_s(buffer, sizeof(buffer) / sizeof(buffer[0]),
                           L"Congratulations! You guessed it in %d %s.\nYou earned %d points.",
                           tries, (tries == 1 ? L"try" : L"tries"), points);
                EnableWindow(GetDlgItem(hwnd, IDC_BUTTON_GUESS), FALSE);
                ShowWindow(GetDlgItem(hwnd, IDC_BUTTON_RESTART), SW_SHOW);
                ShowWindow(GetDlgItem(hwnd, IDC_BUTTON_HINT), SW_HIDE);
            }

            if (tries >= maxTries && guess != number) {
                points = -2;
                totalPoints += points;
                swprintf_s(buffer, sizeof(buffer) / sizeof(buffer[0]),
                           L"Game Over! The number was %d.\nYou lost 2 points.", number);
                EnableWindow(GetDlgItem(hwnd, IDC_BUTTON_GUESS), FALSE);
                ShowWindow(GetDlgItem(hwnd, IDC_BUTTON_RESTART), SW_SHOW);
                ShowWindow(GetDlgItem(hwnd, IDC_BUTTON_HINT), SW_HIDE);
            }

            SetWindowTextW(GetDlgItem(hwnd, IDC_STATIC_STATUS), buffer);
            updatePointsDisplay(hwnd);

            if (tries >= 2 && GetDlgItem(hwnd, IDC_BUTTON_HINT)) {
                ShowWindow(GetDlgItem(hwnd, IDC_BUTTON_HINT), SW_SHOW);
            }
        }
        else if (id == IDC_BUTTON_HINT) {
            const wchar_t* hintMsg = L"No hint available.";
            for (size_t i = 0; i < sizeof(hints) / sizeof(hints[0]); ++i) {
                if (hints[i].num == number) {
                    hintMsg = hints[i].message;
                    break;
                }
            }
            wchar_t hintBuffer[256];
            swprintf_s(hintBuffer, sizeof(hintBuffer) / sizeof(hintBuffer[0]), L"Hint: %s", hintMsg);
            SetWindowTextW(GetDlgItem(hwnd, IDC_STATIC_STATUS), hintBuffer);
        }
        else if (id == IDC_BUTTON_RESTART) {
            resetGame(hwnd);
        }
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, msg, wp, lp);
}

void AddControls(HWND hwnd) {
    HINSTANCE hInst = (HINSTANCE)GetModuleHandle(NULL);

    CreateWindowW(L"Static", L"I have chosen a number between 1 and 10. Can you guess it?",
                  WS_VISIBLE | WS_CHILD | SS_CENTER, 50, 20, 400, 25, hwnd, NULL, hInst, NULL);

    CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
                  150, 60, 200, 25, hwnd, (HMENU)IDC_EDIT_NUM, hInst, NULL);

    CreateWindowW(L"Button", L"Guess", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                  200, 100, 100, 30, hwnd, (HMENU)IDC_BUTTON_GUESS, hInst, NULL);

    CreateWindowW(L"Button", L"Hint", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                  200, 140, 100, 30, hwnd, (HMENU)IDC_BUTTON_HINT, hInst, NULL);
    ShowWindow(GetDlgItem(hwnd, IDC_BUTTON_HINT), SW_HIDE);

    CreateWindowW(L"Button", L"Restart", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                  200, 180, 100, 30, hwnd, (HMENU)IDC_BUTTON_RESTART, hInst, NULL);
    ShowWindow(GetDlgItem(hwnd, IDC_BUTTON_RESTART), SW_HIDE);

    CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | SS_CENTER,
                  50, 220, 400, 50, hwnd, (HMENU)IDC_STATIC_STATUS, hInst, NULL);

    CreateWindowW(L"Static", L"Total Points: 0", WS_VISIBLE | WS_CHILD | SS_CENTER,
                  150, 300, 200, 25, hwnd, (HMENU)IDC_STATIC_POINTS, hInst, NULL);
}
