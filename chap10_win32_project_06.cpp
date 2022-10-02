// chap10_win32_project_06.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "chap10_win32_project_06.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Custom Global Variables
HWND hwndList = NULL;
HWND hwndStatic = NULL;
HWND hwndDlg = NULL;

WCHAR pszCurDir[MAX_PATH];

BOOL CALLBACK FileDlgProc(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_CHAP10_WIN32_PROJECT_06, szWindowClass, MAX_LOADSTRING);
	GetCurrentDirectoryW(MAX_PATH, pszCurDir);

    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHAP10_WIN32_PROJECT_06));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
       
		if (NULL == hwndDlg || !IsDialogMessage(hwndDlg, &msg)) {
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

    }

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CHAP10_WIN32_PROJECT_06));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CHAP10_WIN32_PROJECT_06);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 400, 430, nullptr, nullptr, hInstance, nullptr);

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
//  PURPOSE:  Processes messages for the main window.
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
            // Parse the menu selections:
            switch ( LOWORD(wParam) )
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;

			case ID_OPEN_FILE:
			{	
					hwndDlg = CreateDialog(::hInst, MAKEINTRESOURCEW(IDD_FILELIST_DLG), hWnd, FileDlgProc);
					
					ShowWindow(hwndDlg, SW_SHOW); UpdateWindow(hwndDlg);

					DlgDirListW(hwndDlg, pszCurDir, (int)IDL_LIST_BOX, (int)IDC_STATIC_CTL, DDL_DRIVES | DDL_DIRECTORY | DDL_READWRITE | DDL_POSTMSGS);
					/*
					SendDlgItemMessageW(hwndDlg, (int)IDL_LIST_BOX, LB_RESETCONTENT, NULL, NULL);
					SendDlgItemMessageW(hwndDlg, (int)IDL_LIST_BOX, LB_DIR, DDL_DIRECTORY | DDL_READWRITE, (LPARAM)lstrcatW(pszCurDir,L"\\*.*")); */
			}
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
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
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
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hDlg, (INT_PTR)TRUE);
			break;

		case IDCANCEL:
			EndDialog(hDlg, (INT_PTR)FALSE);
			break;

		}
		break;

	case WM_CLOSE:
		EndDialog(hDlg, (INT_PTR)FALSE);
		break;

	default: break;
    }
    return (INT_PTR)FALSE;
}


// Message handler for IDD_FILELIST_DLG
BOOL CALLBACK FileDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (uMsg)
	{
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;
		
		case WM_COMMAND:
			if (LOWORD(wParam) == IDL_LIST_BOX) {
				switch (HIWORD(wParam)) {
					case LBN_SELCHANGE:
					{
						WCHAR szItem[MAX_PATH];
						DlgDirSelectExW(hDlg, szItem, MAX_PATH, (int)IDL_LIST_BOX);
						lstrcpynW(pszCurDir, szItem, MAX_PATH);
					}
					break;

					case LBN_DBLCLK:
						DlgDirListW(hDlg, pszCurDir, (int)IDL_LIST_BOX, (int)IDC_STATIC_CTL, DDL_DRIVES | DDL_DIRECTORY | DDL_READWRITE);
						break;

					default: break;

				 } // closing inner if --> switch
			} // closing if
			break;

		case WM_SYSCOMMAND:
			if (wParam == SC_CLOSE) DestroyWindow(hDlg); hwndDlg = NULL; break;

		default: break;
	}
	return (INT_PTR)FALSE;
}
