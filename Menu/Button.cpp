//#include "Button.h"
//
//Button::Button(HWND parent, int buttonId, POINT pos, POINT sz)
//    : hwndParent(parent), id(buttonId), position(pos), size(sz), state(DEFAULT),
//    hDefault(nullptr), hHover(nullptr), hOnClick(nullptr), hFont(nullptr) {}
//
//Button::~Button() {
//    graphic.ReleaseBitmap(hDefault);
//    graphic.ReleaseBitmap(hHover);
//    graphic.ReleaseBitmap(hOnClick);
//}
//
//void Button::create() {
//    hwndButton = CreateWindowEx(
//        0, L"STATIC", nullptr, WS_VISIBLE | WS_CHILD,
//        position.x, position.y, size.x, size.y,
//        hwndParent, (HMENU)id,
//        (HINSTANCE)GetWindowLongPtr(hwndParent, GWLP_HINSTANCE),
//        nullptr);
//}
//
//void Button::setImages(const wchar_t* def, const wchar_t* hover, const wchar_t* click, double scale) {
//    hDefault = graphic.LoadBitmapImage(def, scale);
//    hHover = graphic.LoadBitmapImage(hover, scale);
//    hOnClick = graphic.LoadBitmapImage(click, scale);
//}
//
//void Button::setText(const std::wstring& text, HFONT font) {
//    label = text;
//    hFont = font ? font : (HFONT)GetStockObject(DEFAULT_GUI_FONT);
//}
//
//void Button::setCallback(std::function<void()> callback) {
//    onClickCallback = callback;
//}
//
//void Button::handleEvent(UINT message, WPARAM wParam, LPARAM lParam) {
//    POINT cursor;
//    GetCursorPos(&cursor);
//    ScreenToClient(hwndParent, &cursor);
//
//    bool isInside = (cursor.x >= position.x && cursor.x <= position.x + size.x &&
//        cursor.y >= position.y && cursor.y <= position.y + size.y);
//
//    switch (message) {
//    case WM_MOUSEMOVE:
//        if (isInside && state != HOVER) {
//            state = HOVER;
//            InvalidateRect(hwndButton, nullptr, TRUE);
//            TRACKMOUSEEVENT tme = { sizeof(TRACKMOUSEEVENT), TME_LEAVE, hwndParent, HOVER_DEFAULT };
//            TrackMouseEvent(&tme);
//        }
//        break;
//    case WM_MOUSELEAVE:
//        if (!isInside) {
//            state = DEFAULT;
//            InvalidateRect(hwndButton, nullptr, TRUE);
//        }
//        break;
//    case WM_LBUTTONDOWN:
//        if (isInside) {
//            state = ON_CLICK;
//            InvalidateRect(hwndButton, nullptr, TRUE);
//        }
//        break;
//    case WM_LBUTTONUP:
//        if (isInside && state == ON_CLICK) {
//            state = HOVER;
//            InvalidateRect(hwndButton, nullptr, TRUE);
//            if (onClickCallback) onClickCallback();
//        }
//        break;
//    default:
//        break;
//    }
//}
//
//void Button::render(HDC hdc) {
//    HBITMAP currentBitmap = nullptr;
//
//    switch (state) {
//    case DEFAULT:
//        currentBitmap = hDefault;
//        break;
//    case HOVER:
//        currentBitmap = hHover;
//        break;
//    case ON_CLICK:
//        currentBitmap = hOnClick;
//        break;
//    }
//
//    if (currentBitmap) {
//        graphic.DrawBitmap(currentBitmap, position, hdc);
//    }
//
//    if (!label.empty()) {
//        SelectObject(hdc, hFont);
//        SetBkMode(hdc, TRANSPARENT);
//        RECT rect = { position.x, position.y, position.x + size.x, position.y + size.y };
//        DrawText(hdc, label.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
//    }
//}
