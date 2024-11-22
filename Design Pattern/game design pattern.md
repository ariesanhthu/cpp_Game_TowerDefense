ref
[Singleton](https://gameprogrammingpatterns.com/singleton.html)),  ([Flyweight](https://gameprogrammingpatterns.com/flyweight.html) and [Observer](https://gameprogrammingpatterns.com/observer.html)) ([Prototype](https://gameprogrammingpatterns.com/prototype.html) and [State](https://gameprogrammingpatterns.com/state.html)).
# [[Observer]]
- quản lý sự kiện enemy bị tiêu diệt 
- -> cập nhật điểm số, số lượng, hiệu ứng nổ
- audio

- **Lớp Observer**: Định nghĩa giao diện cho các observer với phương thức `onNotify`.
    
- **Lớp Subject**: Quản lý danh sách các observer và thông báo cho họ khi có sự kiện xảy ra.
    
- **Lớp Enemy**: Kẻ địch trong game, kế thừa từ Subject và thông báo sự kiện khi bị tấn công hoặc tiêu diệt.
    
- **Lớp ScoreSystem**: Hệ thống điểm số, kế thừa từ Observer và cập nhật điểm số khi kẻ địch bị tiêu diệt.
    
- **Lớp EffectSystem**: Hệ thống hiệu ứng, kế thừa từ Observer và hiển thị hiệu ứng khi kẻ địch bị tấn công hoặc tiêu diệt.

```cpp
#include <vector>
#include <iostream>

// Định nghĩa các sự kiện
enum Event {
    EVENT_ENEMY_ATTACKED,
    EVENT_ENEMY_DESTROYED
};

// Lớp Observer
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

// Lớp Enemy (Kẻ địch)
class Enemy : public Subject {
public:
    void attack() {
        // Logic tấn công
        std::cout << "Enemy attacked!" << std::endl;
        notify(EVENT_ENEMY_ATTACKED);
    }

    void destroy() {
        // Logic tiêu diệt
        std::cout << "Enemy destroyed!" << std::endl;
        notify(EVENT_ENEMY_DESTROYED);
    }
};

// Lớp ScoreSystem (Hệ thống điểm số)
class ScoreSystem : public Observer {
public:
    void onNotify(const Event event) override {
        if (event == EVENT_ENEMY_DESTROYED) {
            score += 10;
            std::cout << "Score: " << score << std::endl;
        }
    }

private:
    int score = 0;
};

// Lớp EffectSystem (Hệ thống hiệu ứng)
class EffectSystem : public Observer {
public:
    void onNotify(const Event event) override {
        if (event == EVENT_ENEMY_ATTACKED) {
            std::cout << "Show attack effect!" << std::endl;
        } else if (event == EVENT_ENEMY_DESTROYED) {
            std::cout << "Show destroy effect!" << std::endl;
        }
    }
};

int main() {
    Enemy enemy;
    ScoreSystem scoreSystem;
    EffectSystem effectSystem;

    enemy.addObserver(&scoreSystem);
    enemy.addObserver(&effectSystem);

    enemy.attack();
    enemy.destroy();

    return 0;
}


```




# [[[Flyweight]]]
	áp dụng
	các kẻ địch, tháp có chung các đặc tính như hình vẽ, thông số máu, cấp độ
	các nhau về vị trí, cập nhật máu hiện tại,...
```cpp
#include <vector>
#include <iostream>

// Lớp Flyweight cho kẻ địch
class EnemyModel {
public:
    EnemyModel(const std::string& model, const std::string& texture)
        : model_(model), texture_(texture) {}

    const std::string& getModel() const { return model_; }
    const std::string& getTexture() const { return texture_; }

private:
    std::string model_;
    std::string texture_;
};

// Lớp kẻ địch
class Enemy {
public:
    Enemy(EnemyModel* model, int x, int y, int health)
        : model_(model), x_(x), y_(y), health_(health) {}

    void render() {
        std::cout << "Rendering enemy at (" << x_ << ", " << y_ << ") with model " << model_->getModel() << " and texture " << model_->getTexture() << std::endl;
    }

private:
    EnemyModel* model_;
    int x_;
    int y_;
    int health_;
};

// Lớp quản lý kẻ địch
class EnemyManager {
public:
    void addEnemy(EnemyModel* model, int x, int y, int health) {
        enemies_.emplace_back(model, x, y, health);
    }

    void renderEnemies() {
        for (auto& enemy : enemies_) {
            enemy.render();
        }
    }

private:
    std::vector<Enemy> enemies_;
};

int main() {
    // Tạo các mô hình kẻ địch
    EnemyModel goblinModel("GoblinModel", "GoblinTexture");
    EnemyModel orcModel("OrcModel", "OrcTexture");

    // Tạo quản lý kẻ địch
    EnemyManager enemyManager;

    // Thêm kẻ địch vào game
    enemyManager.addEnemy(&goblinModel, 10, 20, 100);
    enemyManager.addEnemy(&goblinModel, 15, 25, 100);
    enemyManager.addEnemy(&orcModel, 30, 40, 200);

    // Hiển thị kẻ địch
    enemyManager.renderEnemies();

    return 0;
}

```




# [[State]]
- GameState: startGame, endGame, pauseGame
- EnemyState: stop, attacked (bắn trúng), isDead, running
- TowerSate: IdleState (chờ), attackingState (tấn công)
- BulletState: running, stop, attacked(bắn trúng)
```cpp
class TowerState {
public:
    virtual ~TowerState() {}
    virtual void handleInput(Tower& tower, Input input) {}
    virtual void update(Tower& tower) {}
};
class IdleState : public TowerState {
public:
    virtual void handleInput(Tower& tower, Input input) {
        if (input == ENEMY_DETECTED) {
            tower.changeState(new AttackingState());
        }
    }

    virtual void update(Tower& tower) {
        // Logic cập nhật khi tháp ở trạng thái chờ
    }
};

class AttackingState : public TowerState {
public:
    virtual void handleInput(Tower& tower, Input input) {
        if (input == NO_ENEMY) {
            tower.changeState(new IdleState());
        }
    }

    virtual void update(Tower& tower) {
        // Logic cập nhật khi tháp ở trạng thái tấn công
        tower.attack();
    }
};
class Tower {
public:
    Tower() : state_(new IdleState()) {}

    void handleInput(Input input) {
        TowerState* state = state_->handleInput(*this, input);
        if (state != nullptr) {
            delete state_;
            state_ = state;
            state_->enter(*this);
        }
    }

    void update() {
        state_->update(*this);
    }

    void changeState(TowerState* state) {
        delete state_;
        state_ = state;
        state_->enter(*this);
    }

    void attack() {
        // Logic tấn công kẻ địch
    }

    void setGraphics(int image) {
        // Cập nhật hình ảnh của tháp
    }

private:
    TowerState* state_;
};

```
___

### ví dụ về gameState
```cpp
class GameState {
public:
    virtual ~GameState() {}
    virtual void handleInput(Game& game, Input input) {}
    virtual void update(Game& game) {}
    virtual void enter(Game& game) {}
    virtual void exit(Game& game) {}
};
// -------------------------------------------------------------------
// các trạng thái
class RunningState : public GameState {
public:
    virtual void handleInput(Game& game, Input input) {
        if (input == PAUSE) {
            game.changeState(new PauseState());
        }
    }

    virtual void update(Game& game) {
        // Logic cập nhật khi game đang chạy
    }

    virtual void enter(Game& game) {
        // Logic khi vào trạng thái chạy
    }

    virtual void exit(Game& game) {
        // Logic khi rời khỏi trạng thái chạy
    }
};

class PauseState : public GameState {
public:
    virtual void handleInput(Game& game, Input input) {
        if (input == RESUME) {
            game.changeState(new RunningState());
        }
    }

    virtual void update(Game& game) {
        // Logic cập nhật khi game đang tạm dừng
    }

    virtual void enter(Game& game) {
        // Logic khi vào trạng thái tạm dừng
    }

    virtual void exit(Game& game) {
        // Logic khi rời khỏi trạng thái tạm dừng
    }
};

class EndState : public GameState {
public:
    virtual void handleInput(Game& game, Input input) {
        if (input == RESTART) {
            game.changeState(new RunningState());
        }
    }

    virtual void update(Game& game) {
        // Logic cập nhật khi game kết thúc
    }

    virtual void enter(Game& game) {
        // Logic khi vào trạng thái kết thúc
    }

    virtual void exit(Game& game) {
        // Logic khi rời khỏi trạng thái kết thúc
    }
};
//---------------------------------------------------------------------------
class Game {
public:
    Game() : state_(new RunningState()) {}

    void handleInput(Input input) {
        GameState* state = state_->handleInput(*this, input);
        if (state != nullptr) {
            state_->exit(*this);
            delete state_;
            state_ = state;
            state_->enter(*this);
        }
    }

    void update() {
        state_->update(*this);
    }

    void changeState(GameState* state) {
        state_->exit(*this);
        delete state_;
        state_ = state;
        state_->enter(*this);
    }

private:
    GameState* state_;
};


```
# so sánh

- Prototype: clone, copy tạo ra một bản sao từ bản gốc, bản sao là một đối tượng riêng biệt, có thể tùy biến, không bị tác động bởi bản gốc (đúng nghĩa copy). Dùng khi cần sao chép một đối tượng có nhiều đặc tính phức tạp, tạo nhanh nhiều đối tượng giống nhau (nhưng mỗi đối tượng sau này không ảnh hưởng và liên quan đến nhau)
- Flyweight: các đối tượng được tạo ra có các đặc tính giống nhau, các đối tượng sử dụng chung 1 tài nguyên, khi tài nguyên thay đổi các đối tượng cũng sẽ bị ảnh hướng, không dùng khi các đối tượng hoạt động độc lập nhau, ưu tiên khi sử dụng nhằm tiết kiệm bộ nhớ (cần tạo ra số lượng lớn đối tượng giống nhau), các đối tượng dùng chung một giao diện,...
- Factory: liên quan đến việc khởi tạo và quản lý khởi tạo các lớp (CLASS), khởi tạo đối tượng mới từ đầu, thiết kế đến việc tập trung quản lý các lớp cùng nhóm vào một FACTORY giúp tiện cho việc khởi tạo.

### **So sánh Prototype và Flyweight**

| **Tiêu chí**           | **Prototype Pattern**                                      | **Flyweight Pattern**                                     |
| ---------------------- | ---------------------------------------------------------- | --------------------------------------------------------- |
| **Mục đích**           | Tạo bản sao đối tượng gốc bằng cách clone.                 | Tái sử dụng dữ liệu dùng chung để giảm bộ nhớ.            |
| **Khi nào dùng**       | Khi cần sao chép đối tượng có trạng thái hiện tại.         | Khi có nhiều đối tượng giống nhau với dữ liệu dùng chung. |
| **Tài nguyên sử dụng** | Tốn tài nguyên hơn vì mỗi đối tượng là bản sao riêng biệt. | Tối ưu bộ nhớ do dữ liệu chung chỉ lưu một lần.           |
| **Phù hợp với**        | Đối tượng phức tạp có trạng thái khác biệt.                | Đối tượng giống nhau về giao diện (bitmap).               |
| **Ví dụ**              | Sao chép enemy với trạng thái cụ thể (HP, tốc độ).         | Chia sẻ ảnh bitmap của enemy để tiết kiệm tài nguyên.     |
### **So sánh giữa Prototype và Factory Pattern**

| **Tiêu chí**              | **Prototype Pattern**                                                                                                                 | **Factory Pattern**                                                                                                |
| ------------------------- | ------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------ |
| **Mục đích**              | Tạo đối tượng bằng cách **sao chép (clone)** một đối tượng đã tồn tại.                                                                | Tạo đối tượng mới bằng cách sử dụng một **nhà máy (factory)**.                                                     |
| **Cách hoạt động**        | Dùng phương thức `clone()` để tạo bản sao từ đối tượng gốc.                                                                           | Dùng một phương thức (thường là `create`) để trả về đối tượng mới.                                                 |
| **Khi nào dùng**          | - Khi việc khởi tạo đối tượng tốn kém (về thời gian hoặc tài nguyên).  <br>- Khi cần sao chép trạng thái hiện tại của đối tượng.      | - Khi cần tạo nhiều đối tượng thuộc các lớp con khác nhau.  <br>- Khi không muốn tiết lộ lớp cụ thể của đối tượng. |
| **Tính mở rộng**          | Phù hợp với các đối tượng phức tạp có trạng thái cần được sao chép.                                                                   | Phù hợp với việc thay đổi cách khởi tạo đối tượng (thêm lớp con mới).                                              |
| **Sao chép hay khởi tạo** | Sao chép (copy) đối tượng gốc, giữ nguyên cấu trúc và trạng thái.                                                                     | Khởi tạo đối tượng mới từ đầu.                                                                                     |
| **Phức tạp**              | Yêu cầu mỗi lớp hỗ trợ phương thức `clone()`.                                                                                         | Tập trung việc tạo đối tượng vào một nơi duy nhất (Factory).                                                       |
| **Ưu điểm**               | - Giảm chi phí khởi tạo.  <br>- Lưu giữ trạng thái đối tượng.                                                                         | - Linh hoạt khi thêm loại đối tượng mới.  <br>- Giảm phụ thuộc vào lớp cụ thể.                                     |
| **Nhược điểm**            | - Sao chép nông (**shallow copy**) dễ gặp lỗi với các đối tượng phức tạp.  <br>- Mọi đối tượng phải triển khai phương thức `clone()`. | - Tăng phức tạp khi thêm nhiều lớp Factory.  <br>- Phải dự đoán các lớp cần hỗ trợ ngay từ đầu.                    |
| **Ví dụ thực tế**         | - Sao chép tài liệu gốc để làm bản nháp.  <br>- Nhân bản game nhân vật với thông số giống nhau.                                       | - Tạo xe theo loại (xe máy, ô tô).  <br>- Tạo hình học (hình tròn, hình vuông).                                    |

---
