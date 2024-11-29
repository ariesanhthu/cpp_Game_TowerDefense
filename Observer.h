#pragma once

#include <vector>

using namespace std;

enum Event {
    MOVELOGINPAGE,
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
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

protected:
    void notify(const Event event) {
        for (Observer* observer : observers) {
            observer->onNotify(event);
        }
    }

private:
    // quản lý danh sách các obsevers
    std::vector<Observer*> observers;
};

