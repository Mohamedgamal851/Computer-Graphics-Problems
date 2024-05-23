                #include <Windows.h>
//utility function to swap
void swap(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}
//utility function to round
int round(double x) {
    return (int)(x + 0.5);
}
//drawing a line by the simple DDL algorithm
void drowDDLline(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    SetPixel(hdc, x1, y1, color);
    if (abs(dx) >= abs(dy)) {
        if (x1 > x2) {
            swap(x1, x2);
            swap(y1, y2);
        }
        int x = x1;
        double y = y1;
        double m = (double)dy / dx;
        while (x2 > x) {
            x++;
            y += m;
            SetPixel(hdc, x, round(y), color);
        }
    }
    else {
        if (y1 > y2) {
            swap(x1, x2);
            swap(y1, y2);
        }
        double x = x1;
        int y = y1;
        double mi = (double)dx / dy;
        while (y2 > y) {
            y++;
            x += mi;
            SetPixel(hdc, round(x), y, color);
        }
    }
}
LRESULT WINAPI WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    static int x, y;
    switch (message)
    {
        case WM_LBUTTONDOWN:
        {
            x = LOWORD(lParam);
            y = HIWORD(lParam);
            break;
        }
        case WM_LBUTTONUP:
        {
            COLORREF c = RGB(255, 30, 5);
            hdc = GetDC(hWnd);
            drowDDLline(hdc, x, y, LOWORD(lParam), HIWORD(lParam), c);
            ReleaseDC(hWnd, hdc);
            break;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
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

int APIENTRY WinMain(HINSTANCE hinst, HINSTANCE pinst, LPSTR cmd, int nsh)
{
    WNDCLASS wc;
    wc.cbClsExtra = wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(RGB(255, 255, 255));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = hinst;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = "MyClass";
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wc);
    HWND hwnd = CreateWindow("MyClass", "My First Window", WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL, hinst, 0);
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