//

#include "framework.h"
#include "ass2.h"
#include<cmath>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ASS2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASS2));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASS2));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ASS2);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

void swap(int& x1, int& y1, int& x2, int& y2)
{
    int temp;
    temp = x1;
    x1 = x2;
    x2 = temp;
    temp = y1;
    y1 = y2;
    y2 = temp;
}

int rounde (double x)
{
    return (int)(x + 0.5);
}

void lineeDDA(HDC hdc, int x1, int y1, double slope, COLORREF c)
{
    double pers = -1.0 / slope;
    int x2, y2;
    x2 = x1 + 100;
    y2 = y1 + rounde(pers * (x2 - x1));
    int dx = x2 - x1, dy = y2 - y1;
    if (abs(dx) >= abs(dy))
    {
        if (x1 > x2) {
            swap(x1, y1, x2, y2);
        }
        int x = x1;
        double y = y1;
        SetPixel(hdc, x1, y1, c);
        double m = (double)dy / dx;
        while (x < x2)
        {
            x++;
            y += m;
            SetPixel(hdc, x, rounde(y), c);
        }
    }
    else
    {
        if (y1 > y2) {
            swap(x1, y1, x2, y2);
        }
        int y = y1;
        double x = x1;
        SetPixel(hdc, x1, y1, c);
        double mi = (double)dx / dy;
        while (y < y2)
        {
            y++;
            x += mi;
            SetPixel(hdc, rounde(x), y, c);
        }
    }
}

void draw8points(HDC hdc, int xc, int yc, int x, int y) {
    SetPixel(hdc, xc + x, yc + y, RGB(0, 0, 0)); // Octant 1
    SetPixel(hdc, xc + y, yc + x, RGB(0, 0, 0)); // Octant 2
    SetPixel(hdc, xc - y, yc + x, RGB(0, 0, 0)); // Octant 3
    SetPixel(hdc, xc - x, yc + y, RGB(0, 0, 0)); // Octant 4
    SetPixel(hdc, xc - x, yc - y, RGB(0, 0, 0)); // Octant 5
    SetPixel(hdc, xc - y, yc - x, RGB(0, 0, 0)); // Octant 6
    SetPixel(hdc, xc + y, yc - x, RGB(0, 0, 0)); // Octant 7
    SetPixel(hdc, xc + x, yc - y, RGB(0, 0, 0)); // Octant 8
}

void DrawCircle(HDC hdc, int xc, int yc, int r) {
    int x = r, y = 0;
    int radiusError = 1 - x;

    while (x >= y) {
        draw8points(hdc, xc, yc, x, y);
        y++;
        if (radiusError < 0)
            radiusError += 2 * y + 1;
        else {
            x--;
            radiusError += 2 * (y - x + 1);
        }
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int xc, yc, r,xPos,yPos;
    static bool isFirstClickC = true;
    HDC hdc;
    //static int x1, y1, x2, y2;

    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_LBUTTONDOWN:
    {
        int xk = LOWORD(lParam);
        int yk = HIWORD(lParam);
        hdc = GetDC(hWnd);
        lineeDDA(hdc, xk, yk, double((yk-yc)/(xk-xc)), RGB(255, 0, 0));
        ReleaseDC(hWnd, hdc);
    }
    break;
    case WM_RBUTTONDOWN:
    {
        xPos = LOWORD(lParam);
        yPos = HIWORD(lParam);
        if (isFirstClickC) {
            xc = xPos;
            yc = yPos;
            isFirstClickC = false;
        }
        else{
            r = sqrt((xPos - xc) * (xPos - xc) + (yPos - yc) * (yPos - yc));
            isFirstClickC = true;
            hdc = GetDC(hWnd);
            DrawCircle(hdc, xc, yc, r);
            ReleaseDC(hWnd, hdc);
        }
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}