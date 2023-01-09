#include <windows.h>
#include <iostream>

HWND win;
int widthWin;
int heightWin;

POINT p;
DWORD color;
HDC hdc = GetDC(NULL);
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

int windowCascade();
int mouseCoord();
int ziseAndColorChange();


int main()
{
	windowCascade();
	ziseAndColorChange();
	while (1) {
		windowCascade();
		//mouseCoord();
	}
}

int mouseCoord()
{
	while (1) {
		GetCursorPos(&p);
		//std::cout << "\t[" << p.x << ";" << p.y << "]" << std::endl;
		color = GetPixel(hdc, p.x, p.y);

		int r, g, b;
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);
		//std::cout << r << " " << g << " " << b << " ";

		HDC hdc = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
		RECT rect = { 100, 270, 220, 430 };

		HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
		FillRect(hdc, &rect, brush);
		DeleteObject(brush);
	
		//return(0);
	}
}

int windowCascade()
{
	//std::cout << "Hello" << std::endl;
	win = GetConsoleWindow();
	widthWin = GetSystemMetrics(SM_CXSCREEN);
	heightWin = GetSystemMetrics(SM_CYSCREEN);

	CascadeWindows(

		NULL,    // дескриптор родительского окна
		MDITILE_ZORDER,          // типы окон, которые не упорядочиваются
		NULL, // прямоугольник, в котором упорядочиваются окна
		NULL,         // число окон для упорядочивания
		NULL  // массив дескрипторов окна
	);

	BringWindowToTop
	(
		win			// дескриптор окна
	);

	return(0);
}

int ziseAndColorChange()
{
	HWND hwnd;
	wchar_t Title[1024];
	GetConsoleTitle(Title, 1024); // Узнаем имя окна
	hwnd = FindWindow(NULL, Title);
	HANDLE hin = GetStdHandle(STD_INPUT_HANDLE); // получаем дескриптор
	INPUT_RECORD InputRecord; // используется для возвращения информации о входных сообщениях в консольном входном буфере
	DWORD Events; // unsigned long

	HWND hWnd = GetConsoleWindow();
	RECT rc;
	GetClientRect(hWnd, &rc);
	int w = rc.right; // ширина рабочей области
	int h = rc.bottom;

	/*Запретить выделение консоли*/
	DWORD prev_mode;
	GetConsoleMode(hin, &prev_mode);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));

	SetConsoleMode(hin, ENABLE_MOUSE_INPUT); // разрешаем обработку мыши

	while (true)
	{
		GetCursorPos(&p);
		//std::cout << "\t[" << p.x << ";" << p.y << "]" << std::endl;
		color = GetPixel(hdc, p.x, p.y);

		int r, g, b;
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);
		//std::cout << r << " " << g << " " << b << " ";

		HDC hdc = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
		RECT rect = { 100, 270, 220, 430 };

		HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
		FillRect(hdc, &rect, brush);
		DeleteObject(brush);

		ReadConsoleInput(hin, &InputRecord, 1, &Events); // считывание 

		if (InputRecord.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
		{
			std::cout << "dclick";
			SetWindowPos
			(
				hwnd,			// дескриптор окна
				NULL,		// дескриптор порядка размещения
				NULL,				// позиция по горизонтали
				NULL,				// позиция по вертикали
				w / 4,				// ширина
				h / 4,				// высота
				NULL 			// флажки позиционирования окна
			);
			Sleep(500);
		
		}
		else if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) // левая кнопка
		{
			Sleep(500);
			std::cout << "left";
			SetWindowPos
			(
				hwnd,			// дескриптор окна
				NULL,		// дескриптор порядка размещения
				NULL,				// позиция по горизонтали
				NULL,				// позиция по вертикали
				w/2,				// ширина
				h/2,				// высота
				NULL 			// флажки позиционирования окна
			);

		}
		else if (InputRecord.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			Sleep(500);
			std::cout << "right";
			SetWindowPos
			(
				hwnd,			// дескриптор окна
				NULL,		// дескриптор порядка размещения
				NULL,				// позиция по горизонтали
				NULL,				// позиция по вертикали
				w,				// ширина
				h,				// высота
				NULL 			// флажки позиционирования окна
			);
		}
	}

	return 0;

}