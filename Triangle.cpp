
#include <Windows.h>
#include <math.h>
#include <iostream>
void drawTriangle(HDC hdc, int x1, int y1,int x2,int y2, int x3, int y3, COLORREF color);
LRESULT WINAPI MyWndProc(HWND hwnd, UINT mcode, WPARAM wp, LPARAM lp) {
    static int x;
    static int y;
    HDC hdc;
    switch (mcode)
    {

        case WM_LBUTTONDOWN:
            x = LOWORD(lp);
            y = HIWORD(lp);
            break;
        case WM_LBUTTONUP:
            hdc = GetDC(hwnd);
            drawTriangle(hdc, x, y, LOWORD(lp), HIWORD(lp), LOWORD(lp) + 25, HIWORD(lp) + 100, RGB(0, 0, 255));
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default: return DefWindowProc(hwnd, mcode, wp, lp);

    }
    return 0;
}
int APIENTRY WinMain(HINSTANCE hinst, HINSTANCE pinst, LPSTR cmd, int nsh) {
    WNDCLASS wc;
    wc.cbClsExtra = wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = hinst;
    wc.lpfnWndProc = MyWndProc;
    wc.lpszClassName = "MyClass";
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wc);
    HWND hwnd = CreateWindow("MyClass", "Triangle", WS_OVERLAPPEDWINDOW, 0, 0, 1920, 1080, NULL, NULL, hinst, 0);
    ShowWindow(hwnd, nsh);
    UpdateWindow(hwnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;

}

void BresenhamLineDrawing(HDC hdc, int xs, int ys, int xe, int ye, COLORREF color)
{
    int dx = abs(xe - xs);
    int dy = abs(ye - ys);
    int x = xs, y = ys;
    int xCH = xs < xe ? 1 : -1;
    int yCH = ys < ye ? 1 : -1;

    if (dx > dy) {
        int d = dx - 2 * dy;
        int change1 = 2 * (dx - dy);
        int change2 = -2 * dy;
        SetPixel(hdc, x, y, color);
        while (x != xe) {
            if (d < 0) {
                y += yCH;
                d += change1;
            }
            else {
                d += change2;
            }
            x += xCH;
            SetPixel(hdc, x, y, color);
        }
    }
    else {
        int d = 2 * dx - dy;
        int change2 = 2 * dx;
        int change1 = 2 * (dx - dy);
        SetPixel(hdc, x, y, color);
        while (y != ye) {
            if (d > 0) {
                x += xCH;
                d += change1;
            }
            else {
                d += change2;
            }
            y += yCH;
            SetPixel(hdc, x, y, color);
        }
    }
}



void drawTriangle(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3, COLORREF color) {
    BresenhamLineDrawing(hdc, x1, y1, x2, y2, color);
    BresenhamLineDrawing(hdc, x2, y2, x3, y3, color);
    BresenhamLineDrawing(hdc, x3, y3, x1, y1, color);
}