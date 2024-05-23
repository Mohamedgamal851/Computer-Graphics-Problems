#include <Windows.h>
#include <math.h>
#include <algorithm>
#include<cmath>
using namespace std;
void Draw8Points(HDC hdc, int xc, int yc, int x, int y, COLORREF c) {
	SetPixel(hdc, xc + x, yc + y, c);
	SetPixel(hdc, xc - x, yc + y, c);
	SetPixel(hdc, xc - x, yc - y, c);
	SetPixel(hdc, xc + x, yc - y, c);
	SetPixel(hdc, xc + y, yc + x, c);
	SetPixel(hdc, xc - y, yc + x, c);
	SetPixel(hdc, xc - y, yc - x, c);
	SetPixel(hdc, xc + y, yc - x, c);
}
void CircleFasterBresenham(HDC hdc, int xc, int yc, int R, COLORREF color)
{
	int x = 0, y = R;
	int d = 1 - R;
	int c1 = 3, c2 = 5 - 2 * R;
	Draw8Points(hdc, xc, yc, x, y, color);
	while (x < y)
	{
		if (d < 0)
		{
			d += c1;
			c2 += 2;
		}
		else
		{

			d += c2;
			c2 += 4;
			y--;
		}
		c1 += 2;
		x++;
		Draw8Points(hdc, xc, yc, x, y, color);
	}
}
void Face(HDC hdc, int xc, int yc, int R, COLORREF c) {
	// big circle for face
	CircleFasterBresenham(hdc, xc, yc, R, c);
	// 2 small circle for eyes
	CircleFasterBresenham(hdc, xc + R / 3, yc - R / 3, R / 6, c);
	CircleFasterBresenham(hdc, xc - R / 3, yc - R / 3, R / 6, c);
	// medium circle for mouth
	CircleFasterBresenham(hdc, xc, yc + R / 2, R / 4, c);
}
LRESULT WINAPI Window(HWND hwnd, UINT m, WPARAM wp, LPARAM lp) {
	HDC hdc;
	static int x1, y1, x2, y2, radius;
	switch (m)
	{
	case WM_LBUTTONDOWN:
		x1 = LOWORD(lp);
		y1 = HIWORD(lp);
		break;
	case WM_LBUTTONUP:
		hdc = GetDC(hwnd);
		x2 = LOWORD(lp);
		y2 = HIWORD(lp);
		radius = max(x1 - x2, x2 - x1);
		Face(hdc, x1, y1, radius, 0XF00);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hwnd, m, wp, lp); // default window procedure to interact with any message not in your switch
	}
	return 0;
}
int APIENTRY WinMain(HINSTANCE h, HINSTANCE p, LPSTR cmd, int csh) {
	WNDCLASS wc;
	// why you need to define your own window class??
	// beacuse you don't need a standard window class
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH); // window background color
	// GetStockObject Returns Handle Graphic Object then cast it into Brush (HBRUSH)
	wc.hCursor = LoadCursor(NULL, IDC_HAND); // Óåã ÇáãÇæÓ NULL stands for default windows cursor (IDC_ARROW)
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Program Icon
	wc.hInstance = h;
	wc.lpfnWndProc = Window; // name of the function get called by the dispatch of the message(event caused) part
	wc.lpszClassName = "MyClass"; // give a name for your window class
	// why lpsz ? (long pointer to string zero terminated (terminated by zero))
	// 'L' stands for Unicode String not ASCI
	wc.lpszMenuName = NULL; // if i have menu defined in the resource part
	wc.style = CS_HREDRAW | CS_VREDRAW; // if window resized redraw it horizontaly or verticaly
	RegisterClass(&wc);
	HWND hwnd = CreateWindow("MyClass", "WOWWOW", WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL, h, 0);
	ShowWindow(hwnd, csh);
	UpdateWindow(hwnd);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}