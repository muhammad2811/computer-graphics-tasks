// graphics.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "graphics.h"

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
int round(double x)
{
    return (int)(x + 0.5);
}
void lineeDDA(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
    int dx = x2 - x1, dy = y2 - y1;
    if (abs(dx) >= abs(dy))
    {
        if (x1 > x2)swap(x1, y1, x2, y2);
        int x = x1;
        double y = y1;
        SetPixel(hdc, x1, y1, c);
        double m = (double)dy / dx;
        while (x < x2)
        {
            x++;
            y += m;
            SetPixel(hdc, x, round(y), c);
        }
    }
    else
    {
        if (y1 > y2)swap(x1, y1, x2, y2);
        int y = y1;
        double x = x1;
        SetPixel(hdc, x1, y1, c);
        double mi = (double)dx / dy;
        while (y < y2)
        {
            y++;
            x += mi;
            SetPixel(hdc, round(x), y, c);
        }
    }
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPWSTR    lpCmdLine,_In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GRAPHICS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GRAPHICS));

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

    return (int) msg.wParam;
}

//  FUNCTION: MyRegisterClass()
//  PURPOSE: Registers the window class.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GRAPHICS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GRAPHICS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//   FUNCTION: InitInstance(HINSTANCE, int)
//   PURPOSE: Saves instance handle and creates main window
//   COMMENTS:
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
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
////  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
////  PURPOSE: Processes messages for the main window.
////  WM_COMMAND  - process the application menu
////  WM_PAINT    - Paint the main window
////  WM_DESTROY  - post a quit message and return
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    HDC hdc;
//    static int x, y;
//    switch (message)
//    {
//    case WM_LBUTTONDOWN:
//        x = LOWORD(lParam);
//        y = HIWORD(lParam);
//        break;
//    case WM_LBUTTONUP:
//        hdc = GetDC(hWnd);
//        lineeDDA(hdc, x, y, LOWORD(lParam), HIWORD(lParam), RGB(255, 0, 0));
//        ReleaseDC(hWnd, hdc);
//        break;
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    HDC hdc;
//    static int x1, y1, x2, y2;
//    static bool isFirstClick = true;
//
//    switch (message)
//    {
//    case WM_LBUTTONDOWN:
//        if (isFirstClick) {
//            x1 = LOWORD(lParam);
//            y1 = HIWORD(lParam);
//            isFirstClick = false;
//        }
//        else {
//            x2 = LOWORD(lParam);
//            y2 = HIWORD(lParam);
//            isFirstClick = true;
//            hdc = GetDC(hWnd);
//            lineeDDA(hdc, x1, y1, x2, y2, RGB(255, 0, 0));
//            ReleaseDC(hWnd, hdc);
//        }
//        break;
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    static int x1, y1, x2, y2;
    static bool isFirstClick = true;

    switch (message)
    {
    case WM_LBUTTONDOWN:
        if (isFirstClick) {
            x1 = LOWORD(lParam);
            y1 = HIWORD(lParam);
            isFirstClick = false;
        }
        else {
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            isFirstClick = true;
            hdc = GetDC(hWnd);

            // Draw four lines to form the rectangle
            lineeDDA(hdc, x1, y1, x2, y1, RGB(255, 0, 0)); // Top line
            lineeDDA(hdc, x2, y1, x2, y2, RGB(255, 0, 0)); // Right line
            lineeDDA(hdc, x2, y2, x1, y2, RGB(255, 0, 0)); // Bottom line
            lineeDDA(hdc, x1, y2, x1, y1, RGB(255, 0, 0)); // Left line

            ReleaseDC(hWnd, hdc);
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
