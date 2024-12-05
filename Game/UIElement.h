#pragma once

#include <windows.h>
#include <Graphic.h>

class UIElement {
protected:
    POINT position;  // Vị trí của phần tử giao diện
    POINT size;      // Kích thước của phần tử
    HBITMAP image;   // Hình ảnh mặc định cho phần tử

public:
    UIElement(POINT pos, HBITMAP img)
        : position(pos), image(img) {
        size = Graphic::GetBitmapSize(image);
    }

    virtual ~UIElement() {
        if (image) {
            DeleteObject(image); // Giải phóng HBITMAP
            image = nullptr;
        }
    }

    // Vẽ phần tử lên HDC
    virtual void render(HDC hdc) {
        if (image) {
            Graphic::DrawBitmap(image, position, hdc);
        }
    }

    // Kiểm tra xem con trỏ chuột có đang nằm trên phần tử không
    virtual bool isHovered(POINT mousePos) const {
        return mousePos.x >= position.x && mousePos.x <= position.x + size.x &&
            mousePos.y >= position.y && mousePos.y <= position.y + size.y;
    }

    // Xử lý khi phần tử được nhấp chuột
    virtual void handleClick() {}
};
