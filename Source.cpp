#include <fstream>
#include <string>
#include <Windows.h>
#include "createNewUser.h"
#include <tchar.h>

#define MAX_LOADSTRING 100


// Global Variables:
int width = 360, height = 360;
HINSTANCE hInst;							
HWND xd, login, registerUser, userName, userPassword, logOff, welcomeMessage;

WCHAR szClassName[] = L"CodeBlocksWindowsApp";
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
	HWND hwnd;              
	MSG messages;           
	WNDCLASSEX wincl;       
	 
	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WndProc;     
	wincl.style = CS_DBLCLKS;                
	wincl.cbSize = sizeof(WNDCLASSEX);
	wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;               
	wincl.cbClsExtra = 0;                    
	wincl.cbWndExtra = 0;                     					   
	wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;


	if (!RegisterClassEx(&wincl))
		return 0;

	hwnd = CreateWindowEx(0, szClassName, _T("Code::Blocks Template Windows App"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, HWND_DESKTOP, NULL, hThisInstance, NULL);
	
	if (!hwnd)
		return 0;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	
	while (GetMessage(&messages, NULL, 0, 0))
	{
		TranslateMessage(&messages);
		DispatchMessage(&messages);
	}
	return messages.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	std::fstream file;
	char user[50];
	char password[50];
	bool loginSuccessful = false;
	std::memset(user, 0, sizeof user);
	std::memset(password, 0, sizeof password);

	switch (message)
	{
	case WM_CREATE:
		userName = CreateWindowExA(WS_EX_WINDOWEDGE, "Edit", "name", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 10, 250, 25, hWnd, NULL, hInst, (LPVOID)lParam);
		userPassword = CreateWindowExA(WS_EX_WINDOWEDGE, "Edit", "", WS_VISIBLE | ES_PASSWORD | WS_CHILD | WS_BORDER, 10, 50, 250, 25, hWnd, NULL, hInst, (LPVOID)lParam);
		login = CreateWindowExA(WS_EX_WINDOWEDGE, "Button", "Login", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 100, 75, 25, hWnd, NULL, hInst, (LPVOID)lParam);
		registerUser = CreateWindowExA(WS_EX_WINDOWEDGE, "Button", "Register", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 100, 75, 25, hWnd, NULL, hInst, (LPVOID)lParam);
	case WM_COMMAND:
	{
		if (message == WM_COMMAND && (HWND)lParam == registerUser) {
			int userLength = SendMessage(userName, WM_GETTEXTLENGTH, 0, 0);
			int pwLength = SendMessage(userPassword, WM_GETTEXTLENGTH, 0, 0);
			
			if (userLength == 0) {
				MessageBoxA(NULL, "You must enter a username", "Error", MB_OK | MB_ICONERROR);
				return 0;
			}
			if (pwLength == 0) {
				MessageBoxA(NULL, "You must enter a password", "Error", MB_OK | MB_ICONERROR);
				return 0;
			}
			else {
				GetWindowTextA(userName, (LPSTR)user, _countof(user));
				GetWindowTextA(userPassword, (LPSTR)password, _countof(password));
				createNewUser obj;
				obj.newUser(user, password);
			}
		}
		if (message == WM_COMMAND && (HWND)lParam == login) {
			GetWindowTextA(userName, (LPSTR)user, _countof(user));
			GetWindowTextA(userPassword, (LPSTR)password, _countof(password));
			createNewUser obj;

			obj.readUsers(user);
			if (!obj.userExist) {
				return 0;
			}
			if (password == obj.decrypted) {
				MessageBoxA(NULL, "Login successfull!", "Info", MB_OK);
				loginSuccessful = true;
			}
			else if (password != obj.decrypted.c_str()) {
				MessageBoxA(NULL, "Incorrect, try again.", "Error", MB_OK | MB_ICONERROR);
			}

			if (loginSuccessful) {
				DestroyWindow(userName);
				DestroyWindow(userPassword);
				DestroyWindow(login);
				DestroyWindow(registerUser);

				welcomeMessage = CreateWindowExA(WS_EX_WINDOWEDGE, "Static", "Hello", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 10, 250, 25, hWnd, NULL, hInst, (LPVOID)lParam);
				logOff = CreateWindowExA(WS_EX_WINDOWEDGE, "Button", "log off", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 100, 75, 25, hWnd, NULL, hInst, (LPVOID)lParam);
			}
		}
		if (message == WM_COMMAND && (HWND)lParam == logOff) {
			loginSuccessful = false;
			DestroyWindow(welcomeMessage);
			DestroyWindow(logOff);

			userName = CreateWindowExA(WS_EX_WINDOWEDGE, "Edit", "name", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 10, 250, 25, hWnd, NULL, hInst, (LPVOID)lParam);
			userPassword = CreateWindowExA(WS_EX_WINDOWEDGE, "Edit", "", WS_VISIBLE | ES_PASSWORD | WS_CHILD | WS_BORDER, 10, 50, 250, 25, hWnd, NULL, hInst, (LPVOID)lParam);
			login = CreateWindowExA(WS_EX_WINDOWEDGE, "Button", "Login", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 100, 75, 25, hWnd, NULL, hInst, (LPVOID)lParam);
			registerUser = CreateWindowExA(WS_EX_WINDOWEDGE, "Button", "Register", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 100, 75, 25, hWnd, NULL, hInst, (LPVOID)lParam);
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
}