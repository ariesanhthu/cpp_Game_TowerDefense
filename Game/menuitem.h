#pragma once

#include <UIElement.h>

class Background : public UIElement {
public: 
	Background(POINT pos, HBITMAP background) : UIElement(pos, background) {}
};