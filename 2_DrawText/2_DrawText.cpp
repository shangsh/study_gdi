// 2_DrawText.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "2_DrawText.h"

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
  LoadStringW(hInstance, IDC_MY2DRAWTEXT, szWindowClass, MAX_LOADSTRING);
  MyRegisterClass(hInstance);

  // Perform application initialization:
  if (!InitInstance(hInstance, nCmdShow))
  {
    return FALSE;
  }

  HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2DRAWTEXT));

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
  wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2DRAWTEXT));
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_BTNHIGHLIGHT);
  wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY2DRAWTEXT);
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_COMMAND:
  {
    int wmId = LOWORD(wParam);
    // Parse the menu selections:
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
  case WM_PAINT:
  {
    RECT rcClient{ 0 };
    ::GetClientRect(hWnd, &rcClient);

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    // 1.输出一个红字，背景透明，靠右对齐的字符串；
    ::SetTextColor(hdc, RGB(255, 0, 0)); // 红字
    int oldBkMode = ::SetBkMode(hdc, TRANSPARENT);
    LPCTSTR str1 = TEXT("1.输出一个红字，背景透明，靠右对齐的字符串~~");
    ::DrawText(hdc, str1, -1, &rcClient, DT_RIGHT);
    ::SetBkMode(hdc, oldBkMode);
    

    // 2.一个黄字，背景红色，垂直居中的字符串--；
    ::SetTextColor(hdc, RGB(255, 255, 0)); // 黄字
    COLORREF oldColor = ::SetBkColor(hdc, RGB(255, 0, 0));
    LPCTSTR str2 = TEXT("2.一个黄字，背景红色，垂直居中的字符串--");
    ::DrawText(hdc, str2, -1, &rcClient, DT_SINGLELINE | DT_VCENTER);
    ::SetBkColor(hdc, oldColor);

    // 3.输出一个有阴影的字符串^_^。
    oldBkMode = ::SetBkMode(hdc, TRANSPARENT);
    LPCTSTR str3 = TEXT("3.输出一个有阴影的字符串^_^。");
    ::SetTextColor(hdc, RGB(128, 128, 128)); // 先写灰色字做为背景字（当阴影）
    ::DrawText(hdc, str3, -1, &rcClient, DT_LEFT);
    RECT tmpRect = rcClient;
    ::OffsetRect(&tmpRect, 1, 1);
    ::SetTextColor(hdc, RGB(255, 0, 0)); // 再写红色字做为前景字
    ::DrawText(hdc, str3, -1, &tmpRect, DT_LEFT);
    ::SetBkMode(hdc, oldBkMode);

    // 4.计算字符串需要的长度和高度，故意减小宽度，让其显示省略号
    LPCTSTR str4 = TEXT("4.计算字符串需要的长度和高度，故意减小宽度，让其显示省略号。123456789");
    SIZE sizeText{ 0 };
    ::GetTextExtentExPoint(hdc, str4, _tcslen(str4), 1000, NULL, NULL, &sizeText);
    RECT rectText{ 0 };
    rectText.left = 200;
    rectText.top = 200;
    rectText.right = rectText.left + sizeText.cx - 50;
    rectText.bottom = rectText.top + sizeText.cy;
    ::SetTextColor(hdc, RGB(0, 255, 0)); // 绿字
    ::DrawText(hdc, str4, -1, &rectText, DT_WORD_ELLIPSIS);

    EndPaint(hWnd, &ps);
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
