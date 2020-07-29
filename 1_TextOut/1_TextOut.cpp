// 1_TextOut.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "1_TextOut.h"

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
  LoadStringW(hInstance, IDC_MY1TEXTOUT, szWindowClass, MAX_LOADSTRING);
  MyRegisterClass(hInstance);

  // Perform application initialization:
  if (!InitInstance(hInstance, nCmdShow))
  {
    return FALSE;
  }

  HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1TEXTOUT));

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
  wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1TEXTOUT));
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_GRAYTEXT);
  wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY1TEXTOUT);
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
    GetClientRect(hWnd, &rcClient);
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    // Test 1 在指定的位置输出默认字体
    LPCTSTR str1 = TEXT("在指定的位置输出默认字体~");
    ::TextOut(hdc, rcClient.left + 100, rcClient.top + 100, str1, _tcslen(str1));

    // Test 2 将字体修改成其他颜色（红色）输出
    LPCTSTR str2 = TEXT("将字体修改成其他颜色（红色）输出~");
    ::SetTextColor(hdc, RGB(255, 0, 0));
    ::TextOut(hdc, rcClient.left + 120, rcClient.top + 120, str2, _tcslen(str2));
    ::SetTextColor(hdc, RGB(0, 0, 0));

    // Test 3 设置字体背景是透明的
    LPCTSTR str3 = TEXT("设置字体背景是透明的，看上去更好看！");
    ::SetBkMode(hdc, TRANSPARENT);
    ::TextOut(hdc, rcClient.left + 150, rcClient.top + 150, str3, _tcslen(str3));
    ::SetBkMode(hdc, OPAQUE);

    // Test 4 设置字体背景的颜色
    LPCTSTR str4 = TEXT("改变字体背景颜色（绿色），绿底黑字。");
    COLORREF oldBkColor = ::SetBkColor(hdc, RGB(0, 255, 0));
    ::TextOut(hdc, rcClient.left + 170, rcClient.top + 170, str4, _tcslen(str4));
    ::SetBkColor(hdc, oldBkColor);

    // Test 5 将字体设为36号字体 + 微软雅黑 + 斜体 + 下划线
    LPCTSTR str5 = TEXT("将字体设为36号字体 + 微软雅黑 + 斜体 + 下划线");
    LOGFONT lf{ 0 };
    lf.lfItalic = true; //使用斜体
    lf.lfUnderline = true; //带下划线
    lf.lfCharSet = GB2312_CHARSET; //有中文就选这个
    lf.lfHeight = 48; // 36号字高度就是48像素
    _tcscpy_s(lf.lfFaceName, TEXT("微软雅黑"));
    HFONT hFontNew = ::CreateFontIndirect(&lf);
    HFONT hFontOld = (HFONT)::SelectObject(hdc, hFontNew);
    ::TextOut(hdc, rcClient.left + 200, rcClient.top + 200, str5, _tcslen(str5));
    // 将原字体还原
    ::SelectObject(hdc, hFontOld);
    ::DeleteObject(hFontNew);
    hFontNew = NULL;

    /*
    // Test 2 将字体修改成其他颜色（红色）输出
    LPCTSTR str2 = TEXT("将字体修改成其他颜色（红色）输出~");
    LOGPEN lp{ 0 };
    // 先获取当前DC的画刷
    HGDIOBJ hPen = ::GetCurrentObject(hdc, OBJ_PEN);
    // 再获取画刷的属性信息（即LOGPEN结构体）
    ::GetObject(hPen, sizeof(LOGPEN), &lp);
    // 备份画面原来的颜色并设置新的颜色
    COLORREF oldLopnColor = lp.lopnColor;
    lp.lopnColor = RGB(255, 0, 0);
    HPEN hNewPen = ::CreatePenIndirect(&lp);
    ::SelectObject(hdc, hNewPen);
    ::TextOut(hdc, rcClient.left + 120, rcClient.top + 120, str2, _tcslen(str1));
    // 讲画刷的颜色还原
    ::SelectObject(hdc, hPen);
    ::DeleteObject(hNewPen);
    hNewPen = NULL;
    */

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
