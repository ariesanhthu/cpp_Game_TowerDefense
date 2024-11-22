- quản lý các trạng thái của đối tượng trong game
- Các đối tượng thay đổi phụ thuộc và trạng thái một cách độc lập, không ảnh hưởng hoặc bị kiểm soát bởi cấu trúc code (if else...)

```cpp
/*
lớp cơ sở cho tất cả các trạng thái của nhân vật. Nó định nghĩa các phương thức ảo `handleInput` và `update` mà các trạng thái cụ thể sẽ triển khai.
*/
class HeroineState {
public:
    virtual ~HeroineState() {}
    virtual void handleInput(Heroine& heroine, Input input) {}
    virtual void update(Heroine& heroine) {}
};
/*
Lớp trạng thái cụ thể
triển khai các phương thức và xử lý logic khi ở state cuối
*/
class DuckingState : public HeroineState {
public:
    DuckingState() : chargeTime_(0) {}

    virtual void handleInput(Heroine& heroine, Input input) {
        if (input == RELEASE_DOWN) {
            heroine.setGraphics(IMAGE_STAND);
            heroine.changeState(new StandingState());
        }
    }

    virtual void update(Heroine& heroine) {
        chargeTime_++;
        if (chargeTime_ > MAX_CHARGE) {
            heroine.superBomb();
        }
    }

private:
    int chargeTime_;
};

/*
Lớp chính của nhân vật
Giữ một con trỏ trạng thái hiện tại và ủy quyền xử lý đầu vào, cập nhật trạng thái đó.
*/
class Heroine {
public:
    Heroine() : state_(new StandingState()) {}

    void handleInput(Input input) {
        HeroineState* state = state_->handleInput(*this, input);
        if (state != nullptr) {
            delete state_;
            state_ = state;
            state_->enter(*this);
        }
    }

    void update() {
        state_->update(*this);
    }
// thay đổi trạng thái nhân vật
    void changeState(HeroineState* state) {
        delete state_;
        state_ = state;
        state_->enter(*this);
    }

    void setGraphics(int image) {
        // Cập nhật hình ảnh của nhân vật
    }

    void superBomb() {
        // Kích hoạt siêu bom
    }

private:
    HeroineState* state_;
};



```