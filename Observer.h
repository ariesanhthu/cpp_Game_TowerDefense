#pragma once

#include <vector>
#include <algorithm>
#include <memory>
#include <windows.h>

using namespace std;

namespace towerdefense {
    enum Event {
        MOVESETTOWERSTATE,
    };

    class Observer {
    public:
        virtual ~Observer() {}
        //phương thức quản lý các thông báo sự kiện
        virtual void onNotify(const Event event) = 0;
    };

    // Lớp Subject
    // Dùng để quản lý danh sách các observer
    // thông báo khi có sự kiện xảy ra
    class Subject {
    public:
        void addObserver(shared_ptr<Observer> observer) {
            observers.push_back(observer);
        }

        void removeObserver(shared_ptr<Observer> observer) {
            observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
        }

    protected:
        void notify(const Event event) {
            OutputDebugStringA("FIXING STATE 1\n");
            for (const auto& observer : observers) {
                observer->onNotify(event);
            }
        }

    private:
        // quản lý danh sách các obsevers
        std::vector<shared_ptr<Observer>> observers;
    };
}


