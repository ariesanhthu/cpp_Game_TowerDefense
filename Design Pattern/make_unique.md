### **`make_unique` trong C++ là gì?**

`make_unique` là một hàm tiện ích trong C++ (có từ C++14) thuộc thư viện `<memory>`. Nó được sử dụng để tạo một đối tượng `std::unique_ptr`, giúp quản lý vùng nhớ động một cách an toàn và hiệu quả.

---

### **Tại sao cần `make_unique`?**

1. **Quản lý vùng nhớ an toàn**:
    
    - Thay vì dùng `new` để cấp phát vùng nhớ và tự quản lý, `make_unique` đảm bảo việc hủy vùng nhớ sẽ tự động xảy ra khi con trỏ không còn được sử dụng.
    - Tránh các lỗi như **memory leak** (rò rỉ bộ nhớ).
2. **Viết mã ngắn gọn và rõ ràng hơn**:
    
    - Không cần viết `std::unique_ptr<T>(new T(...))`.
3. **An toàn trong các trường hợp ngoại lệ**:
    
    - Tránh các lỗi khi viết `std::unique_ptr<T>(new T(...))` mà `new` có thể ném ngoại lệ trước khi `unique_ptr` được khởi tạo.

---

### **Cách sử dụng `make_unique`**

#### **Cú pháp:**

```cpp
std::make_unique<T>(constructor_args...);
```

- **T**: Kiểu dữ liệu của đối tượng được quản lý.
- **constructor_args...**: Các tham số để gọi constructor của đối tượng.

#### **Ví dụ:**

##### **Tạo một đối tượng duy nhất:**

```cpp
#include <iostream>
#include <memory>
using namespace std;

class Enemy {
    int health;
public:
    Enemy(int h) : health(h) {
        cout << "Enemy created with health: " << health << endl;
    }
    ~Enemy() {
        cout << "Enemy destroyed!" << endl;
    }
    void attack() {
        cout << "Enemy attacks with " << health << " health!" << endl;
    }
};

int main() {
    // Sử dụng make_unique để tạo unique_ptr
    auto enemy = make_unique<Enemy>(100);

    // Gọi phương thức thông qua unique_ptr
    enemy->attack();

    return 0;
}
```

**Kết quả:**

```
Enemy created with health: 100
Enemy attacks with 100 health!
Enemy destroyed!
```

---

#### **Tạo mảng với `make_unique`:**

```cpp
#include <memory>
#include <iostream>
using namespace std;

int main() {
    auto arr = make_unique<int[]>(5); // Mảng 5 phần tử

    for (int i = 0; i < 5; ++i) {
        arr[i] = i * 10;
        cout << arr[i] << " ";
    }

    return 0;
}
```

**Kết quả:**

```
0 10 20 30 40
```

---

### **So sánh với cách dùng `unique_ptr` thông thường**

#### **Cách không dùng `make_unique`:**

```cpp
#include <memory>
#include <iostream>
using namespace std;

int main() {
    unique_ptr<int> ptr(new int(10)); // Cần tự tạo con trỏ bằng new
    cout << *ptr << endl;
    return 0;
}
```

#### **Cách dùng `make_unique`:**

```cpp
#include <memory>
#include <iostream>
using namespace std;

int main() {
    auto ptr = make_unique<int>(10); // Ngắn gọn hơn
    cout << *ptr << endl;
    return 0;
}
```

---

### **Ưu điểm của `make_unique`:**

1. **Ngắn gọn, dễ đọc hơn**.
2. **An toàn hơn khi xử lý ngoại lệ**:
    - Với `new`, nếu constructor ném ngoại lệ, vùng nhớ không được giải phóng. `make_unique` đảm bảo điều này không xảy ra.
3. **Khuyến khích dùng chuẩn**: `make_unique` là cách chuẩn mực trong C++ để tạo `unique_ptr`.

---

### **Khi nào nên dùng `make_unique`?**

- **Luôn dùng `make_unique` thay vì `new`** khi tạo `unique_ptr`.
- Trừ khi bạn làm việc với **trình biên dịch cũ không hỗ trợ C++14**, trong trường hợp đó, bạn vẫn phải tự dùng `new`.