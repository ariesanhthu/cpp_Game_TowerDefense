#pragma once
#include <vector>

using namespace std;

class UIManager {
private:
    std::vector<UIElement*> elements;

public:
    void addElement(UIElement* element) {
        elements.push_back(element);
    }

    void render() {
        for (UIElement* element : elements) {
            element->render();
        }
    }

    void update(float delta) {
        for (UIElement* element : elements) {
            element->update(delta);
        }
    }

    void handleInput(InputEvent input) {
        for (UIElement* element : elements) {
            element->handleInput(input);
        }
    }
};


