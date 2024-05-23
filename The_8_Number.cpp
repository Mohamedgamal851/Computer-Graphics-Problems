
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

#define IDC_CLOSE_BUTTON 1001

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

void BresenhansCircle(HDC hdc, int xc, int yc, int R, COLORREF c) {
    int x=0,y=R;
    int d=1-R;
    int c1=3, c2=5-2*R;
    Draw8Points(hdc,xc,yc,x,y,c);
    while(x<y)
    {
        if(d<0)
        {
            d+=c1;
            c2+=2;
        }
        else
        {

            d+=c2;
            c2+=4;
            y--;
        }
        c1+=2;
        x++;
        Draw8Points(hdc,xc,yc,x,y,c);
    }
}

void NRFloodFill(HDC hdc, int x, int y, COLORREF Cb, COLORREF Cf) {
    COLORREF C = GetPixel(hdc, x, y);
    if (C == Cb || C == Cf) return;
    SetPixel(hdc, x, y, Cf);
    NRFloodFill(hdc, x + 1, y, Cb, Cf);
    NRFloodFill(hdc, x - 1, y, Cb, Cf);
    NRFloodFill(hdc, x, y + 1, Cb, Cf);
    NRFloodFill(hdc, x, y - 1, Cb, Cf);
}

void DrawNumberEight(HDC hdc, int xc, int yc, int radius, COLORREF fillColor) {
    // Draw the upper circle of 8
    BresenhansCircle(hdc, xc, yc, radius, fillColor);
    // Draw the lower circle of 8
    BresenhansCircle(hdc, xc, yc + 2 * radius, radius, fillColor);

    // Fill the upper circle of 8
    NRFloodFill(hdc, xc, yc, RGB(250, 250, 250), fillColor);
    // Fill the lower circle of 8
    NRFloodFill(hdc, xc, yc + 2 * radius, RGB(250, 250, 250), fillColor);




}

LRESULT WINAPI WndProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp) {
    HDC hdc;
    static int x = -1, y = -1;
        const int radius = 50; // Predefined radius

    switch (m) {
        case WM_CREATE: {
            CreateWindow("BUTTON", "Close", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                         10, 10, 100, 30, hwnd, (HMENU)IDC_CLOSE_BUTTON, NULL, NULL);
            break;
        }
        case WM_LBUTTONDOWN: {
            COLORREF c = RGB(0, 0, 0);
            hdc = GetDC(hwnd);
            x = LOWORD(lp);
            y = HIWORD(lp);
            DrawNumberEight(hdc, x, y, radius, RGB(255, 255, 255)); // Draw number 8
            ReleaseDC(hwnd, hdc);
            break;
        }
        case WM_COMMAND: {
            switch (LOWORD(wp)) {
                case IDCANCEL:
                case IDC_CLOSE_BUTTON:
                    DestroyWindow(hwnd);
                    break;
            }
            break;
        }
        case WM_CLOSE: {
            DestroyWindow(hwnd);
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(hwnd, m, wp, lp);
    }
    return 0;
}

int APIENTRY WinMain(HINSTANCE hi, HINSTANCE pi, LPSTR c, int ns) {
    WNDCLASS wc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0)); // Black background
    wc.hCursor = LoadCursor(NULL, IDC_HAND);
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hInstance = hi;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = "MyClass"; // the class which I create my window on it
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wc);
    HWND hwnd = CreateWindow("MyClass", "Circle", WS_OVERLAPPEDWINDOW, 15, 15, 1200, 1200, NULL, NULL, hi, 0);
    ShowWindow(hwnd, ns);
    UpdateWindow(hwnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}






