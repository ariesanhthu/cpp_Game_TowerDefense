- Dùng cho việc khởi tạo các đối tượng từ đối tượng mẫu
- Các đối tượng khác được khởi tạo bằng cách clone lại đối tượng mẫu, thêm khác thuộc tính khác

```cpp
#include <iostream>
#include <memory>
#include <string>
using namespace std;

// Prototype Interface
class Prototype {
public:
    virtual ~Prototype() {}
    virtual Prototype* clone() const = 0; // Phương thức clone
    virtual void show() const = 0;
};

// Concrete Prototype
class ConcretePrototype : public Prototype {
private:
    string name;
    int value;

public:
    ConcretePrototype(string name, int value) : name(name), value(value) {}

    /*
		Phương thức đặc trưng: clone
		// override từ lớp interface
	    // tạo một vùng nhớ mới và copy giá trị vào
    */
    Prototype* clone() const override {
        return new ConcretePrototype(*this); // Tạo bản sao
    }

    void show() const override {
        cout << "Name: " << name << ", Value: " << value << endl;
    }
};

int main() {
    // Tạo prototype ban đầu
    ConcretePrototype prototype1("Prototype1", 100);

    // Clone từ prototype ban đầu
    Prototype* clone1 = prototype1.clone();

    clone1->show(); // In ra thông tin của bản sao

    delete clone1; // Dọn bộ nhớ
    return 0;
}

```

```cpp
#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
using namespace std;

// Base Class (Abstract Prototype)
class BaseEnemy {
public:
    virtual unique_ptr<BaseEnemy> clone() const = 0;
    virtual void display() const = 0;
    virtual ~BaseEnemy() = default;
};

// Concrete Class: Zombie
class Zombie : public BaseEnemy {
    int health;
public:
    Zombie(int h) : health(h) {}
    unique_ptr<BaseEnemy> clone() const override {
        return make_unique<Zombie>(*this); // Clone itself 
    }
    void display() const override {
        cout << "Zombie with health: " << health << endl;
    }
};

// Concrete Class: Vampire
class Vampire : public BaseEnemy {
    int damage;
public:
    Vampire(int d) : damage(d) {}
    unique_ptr<BaseEnemy> clone() const override {
        return make_unique<Vampire>(*this);
    }
    void display() const override {
        cout << "Vampire with damage: " << damage << endl;
    }
};

// Concrete Class: Ghost
class Ghost : public BaseEnemy {
    int speed;
public:
    Ghost(int s) : speed(s) {}
    unique_ptr<BaseEnemy> clone() const override {
        return make_unique<Ghost>(*this);
    }
    void display() const override {
        cout << "Ghost with speed: " << speed << endl;
    }
};

// Prototype Registry
class EnemyFactory {
    unordered_map<string, unique_ptr<BaseEnemy>> prototypes;
public:
    void addPrototype(const string& type, unique_ptr<BaseEnemy> prototype) {
        prototypes[type] = move(prototype);
    }

    unique_ptr<BaseEnemy> createEnemy(const string& type) const {
        return prototypes.at(type)->clone();
    }
};

int main() {
    // Create Prototype Registry
    EnemyFactory factory;
    factory.addPrototype("Zombie", make_unique<Zombie>(100));
    factory.addPrototype("Vampire", make_unique<Vampire>(50));
    factory.addPrototype("Ghost", make_unique<Ghost>(20));

    // Create clones
    auto enemy1 = factory.createEnemy("Zombie");
    auto enemy2 = factory.createEnemy("Vampire");
    auto enemy3 = factory.createEnemy("Ghost");

    // Display details
    enemy1->display(); // Output: Zombie with health: 100
    enemy2->display(); // Output: Vampire with damage: 50
    enemy3->display(); // Output: Ghost with speed: 20

    return 0;
}

```
Giả sử bạn có 3 lớp con: `Zombie`, `Vampire`, và `Ghost`, tất cả đều kế thừa từ `BaseEnemy`.

#### **Mô tả chương trình**

- Lớp `BaseEnemy`: Đóng vai trò lớp cha, định nghĩa phương thức `clone()` như một interface.
- Lớp con (`Zombie`, `Vampire`, `Ghost`): Cài đặt phương thức `clone()` để tạo bản sao của chính nó.
- Một "factory" lưu các Prototype ban đầu (Registry) để tạo bản sao nhanh.