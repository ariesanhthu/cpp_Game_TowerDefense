[[make_unique]]: quản lý con trỏ an toàn, tự động hủy, tránh bị memory leak


Với yêu cầu của bạn:

1. **Các lớp `Enemy` có animation, thuộc tính khác nhau nhưng có chung state**: Điều này cho thấy các lớp `Enemy` chia sẻ một số logic, nhưng cũng có các chi tiết cụ thể riêng biệt.
2. **Chỉ cần khởi tạo các đối tượng mới**: Bạn không yêu cầu sao chép đối tượng trong runtime mà chỉ cần khởi tạo các đối tượng `Enemy` mới.
3. **Tối đa 20 `Enemy`**: Số lượng không lớn, không cần tối ưu hóa quá mức về bộ nhớ.

---

### **Lựa chọn tốt nhất: Factory Pattern**

- Với yêu cầu **khởi tạo đối tượng mới** và quản lý các lớp `Enemy` một cách thống nhất, **Factory Pattern** là giải pháp tốt nhất.
- Bạn có thể sử dụng **Factory** để tạo các `Enemy` từ một điểm tập trung mà không cần xử lý logic tạo đối tượng trong phần chính của chương trình.
- Factory Pattern giúp:
    - Tăng tính mở rộng: Nếu thêm loại `Enemy` mới, chỉ cần chỉnh sửa Factory mà không cần thay đổi phần còn lại của chương trình.
    - Đơn giản hóa logic khởi tạo: Tạo `Enemy` mà không cần biết lớp cụ thể.

---

### **Tại sao không dùng Copy Constructor hoặc Prototype?**

- **Copy Constructor**:
    - Không cần thiết vì bạn chỉ cần tạo mới đối tượng, không cần sao chép từ đối tượng có sẵn.
    - Mỗi lớp con của `Enemy` có thể có logic khởi tạo riêng, Copy Constructor không giúp ích nhiều.
- **Prototype Pattern**:
    - Không cần thiết nếu bạn không cần sao chép đối tượng trong runtime.
    - Dùng Prototype khi bạn cần clone các đối tượng từ một đối tượng mẫu (`prototype`), nhưng ở đây bạn chỉ cần khởi tạo từ đầu.

---

### **Ví dụ sử dụng Factory Pattern**

#### **BaseEnemy và các lớp con**

```cpp
#include <iostream>
#include <memory>
using namespace std;

// Base class for all enemies
class BaseEnemy {
public:
    virtual void display() const = 0; // Pure virtual function
    virtual ~BaseEnemy() = default;
};

// Derived classes
class Zombie : public BaseEnemy {
public:
    void display() const override {
        cout << "I am a Zombie with slow movement and high health!" << endl;
    }
};

class Vampire : public BaseEnemy {
public:
    void display() const override {
        cout << "I am a Vampire with fast movement and medium health!" << endl;
    }
};

class Ghost : public BaseEnemy {
public:
    void display() const override {
        cout << "I am a Ghost with stealth ability and low health!" << endl;
    }
};
```

#### **Factory Class**

```cpp
#include <string>

// Factory class to create enemies
class EnemyFactory {
public:
    static unique_ptr<BaseEnemy> createEnemy(const string& type) {
        if (type == "Zombie") {
            return make_unique<Zombie>();
        } else if (type == "Vampire") {
            return make_unique<Vampire>();
        } else if (type == "Ghost") {
            return make_unique<Ghost>();
        } else {
            throw invalid_argument("Unknown enemy type");
        }
    }
};
```

#### **Main Program**

```cpp
int main() {
    unique_ptr<BaseEnemy> zombie = EnemyFactory::createEnemy("Zombie");
    unique_ptr<BaseEnemy> vampire = EnemyFactory::createEnemy("Vampire");
    unique_ptr<BaseEnemy> ghost = EnemyFactory::createEnemy("Ghost");

    zombie->display();
    vampire->display();
    ghost->display();

    return 0;
}
```

**Kết quả chạy chương trình:**

```
I am a Zombie with slow movement and high health!
I am a Vampire with fast movement and medium health!
I am a Ghost with stealth ability and low health!
```

---

### **Ưu điểm của Factory Pattern trong trường hợp này**

1. **Đơn giản**: Không cần thêm cơ chế clone phức tạp như Prototype.
2. **Mở rộng dễ dàng**: Thêm loại `Enemy` mới chỉ cần chỉnh sửa `EnemyFactory`.
3. **Tối ưu hóa quản lý logic khởi tạo**: Tập trung logic tại một nơi (Factory), giảm sự phụ thuộc giữa các lớp.
4. **Không lãng phí tài nguyên**: Vì số lượng đối tượng nhỏ (tối đa 20), việc tạo mới từng đối tượng là đủ hiệu quả.