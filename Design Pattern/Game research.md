# Abstract
   Bài viết tổng hợp lại các kiến thức về:
- Quản lý Game loop
- Xử lý các luồng thread
- Xử lý đồ họa, animation
- Thiết kế lại các class theo Pattern Design, phù hợp với việc scale và maintain
# Cấu trúc game

## LỚP WINDOW:
- Game sử dụng Win32 API, khởi tạo một cửa sổ và thao tác trên cửa sổ ứng dụng
- Cửa số có các hàm có thể sử dụng:
	- LoadIcon: tải lên các icon sử dụng bởi chương trình 
	- LoadCursor: mouse cursor (con trỏ chuột) 
	- RegisterClass: đăng ký lớp window cho chương trình 
	- MessageBox: hiển thị một Box tin nhắn
	- CreateWindow: khởi tạo cửa sổ từ window class. 
	- ShowWindow: hiện cửa số lên màn hình
	- UpdateWindow Directs the window to paint itself. 
	- GetMessage: lấy tin nhắn từ hàng đợi (Obtains a message from the message queue.)
	- TranslateMessage: chuyển đổi tin nhắn keyboard
	- DispatchMessage: gửi tin nhắn đến hàm window
	- **PlaySound: Plays a sound file.** 
	- BeginPaint Initiates the beginning of window painting. 
	- GetStockObject Obtains a graphic object, in this case a brush used for painting the window's background. 
	- GetClientRect Obtains the dimensions of the window's client area. 
	- DrawText Displays a text string. 
	- EndPaint Ends window painting. 
	- PostQuitMessage Inserts a "quit" message into the message queue.
	- DefWindowProc Performs default processing of messages. 


## Tương tác với cửa sổ với callback


## GAME LOOP
```cpp
const double MS_PER_FRAME = 16.67; // 60 FPS
while (true) {
    double start = getCurrentTime();
    processInput();
    update();
    render();
    sleep(start + MS_PER_FRAME - getCurrentTime());
}
```

## Quản lý luồng của game

   Quản lý phân chia trách nhiệm rõ ràng
- Input Handling: Đặt toàn bộ xử lý phím và chuột vào lớp Input.
- Renderer: Xử lý toàn bộ liên quan đến vẽ khung hình và kết xuất buffer.
- UIManager: Chỉ quản lý giao diện và xử lý sự kiện liên quan đến giao diện.
- Game: Chịu trách nhiệm quản lý logic game tổng thể (vòng lặp, cập nhật
	`Game::run()`:
	`Input::process()`.
	`update()` (cập nhật logic).
	`render()` (kết xuất màn hình và giao diện).
### CODE:

```cpp
void Game::run()
{
 LARGE_INTEGER cpu_frequency;
 QueryPerformanceFrequency(&cpu_frequency);
 LARGE_INTEGER last_counter;
 QueryPerformanceCounter(&last_counter);

 while (running)
 {
	  // Tính delta time
	  LARGE_INTEGER current_counter;
	  QueryPerformanceCounter(&current_counter);
	  int64_t counter_elapsed = current_counter.QuadPart - last_counter.QuadPart;
	  float delta = (float)counter_elapsed / (float)cpu_frequency.QuadPart;
	  last_counter = current_counter;

	  // Xử lý sự kiện
	  Input::process();

	  // Cập nhật game
	  update(delta);

	  // Vẽ màn hình
	  render();
 }
}

void Game::render()
{
 Renderer::clear();
 updateGameObjects();  // Cập nhật vị trí và trạng thái vật thể
 uiManager.renderUI(); // Vẽ giao diện
 Renderer::present();  // Kết xuất buffer ra màn hình
}

```

## **Phân tích và giải thích cấu trúc GAME.H**

#### **1. Singleton Pattern**

- `inline static Game& getInstance()`
    - Sử dụng pattern Singleton để đảm bảo chỉ có một instance của class `Game` tồn tại trong suốt vòng đời ứng dụng.
    - Lý do: `Game` là lớp quản lý toàn bộ vòng đời của game. Việc có nhiều hơn một instance sẽ làm rối loạn việc quản lý cửa sổ và logic game.

#### **2. Bổ sung `std::function` cho callback**

- `updateCallback` và `renderCallback`
    - Dùng `std::function` để cung cấp cơ chế callback mềm dẻo. Bạn có thể set bất kỳ logic cập nhật hoặc render nào khi cần.
    - Lý do: Thay vì cứng nhắc định nghĩa phương thức `update` và `render`, dùng callback giúp bạn dễ dàng thay đổi logic game mà không cần sửa trực tiếp `Game`.

#### **3. Tách quản lý UI**

- `std::unique_ptr<class UIManager> uiManager`
    - Thêm một đối tượng `UIManager` để quản lý giao diện người dùng.
    - Lý do: Giao diện (UI) và logic game thường hoạt động song song nhưng độc lập. Tách `UIManager` ra một thành phần riêng biệt giúp tăng khả năng bảo trì và tái sử dụng.

#### **4. Smart Pointer (`std::unique_ptr`)**

- Quản lý `UIManager` thông qua `std::unique_ptr`.
    - Lý do: Tránh việc phải tự giải phóng bộ nhớ và đảm bảo quản lý tài nguyên đúng cách.

#### **5. Bảo vệ bộ nhớ và logic**

- Xóa `Game(const Game&)` và `Game& operator=(const Game&)`
    - Lý do: Đảm bảo không thể tạo bản sao hoặc gán lại `Game`, giữ nguyên ý nghĩa của Singleton.

#### **6. Đảm bảo dễ truy cập**

- `getWindowTitle`, `getWindowWidth`, `getWindowHeight`
    - Lý do: Đưa ra các hàm getter để dễ dàng truy cập thông tin cửa sổ mà không cần truy cập trực tiếp đến thuộc tính private.

#### **7. Thiết kế hàm `startWindow`**

- Hàm này sẽ chịu trách nhiệm:
    - Khởi tạo cửa sổ (`CreateWindowEx`).
    - Thiết lập vòng lặp game (`Game Loop`).
    - Gọi các callback đã định nghĩa (update và render).

---

### **Ưu điểm của cấu trúc này**

1. **Tính module**: Tách biệt trách nhiệm rõ ràng giữa quản lý cửa sổ, UI, và logic game.
2. **Tái sử dụng và mở rộng**:
    - Bạn có thể dễ dàng thay thế logic cập nhật hoặc render mà không cần sửa đổi `Game`.
    - Thêm thành phần mới như âm thanh, vật lý cũng đơn giản hơn.
3. **Quản lý tài nguyên tốt hơn**:
    - Sử dụng `std::unique_ptr` giúp tránh rò rỉ bộ nhớ.
    - Singleton đảm bảo có đúng một instance quản lý game.
4. **Tăng tính linh hoạt**:
    - Callback (`std::function`) cho phép lập trình hướng sự kiện (event-driven programming).

---

# # tổ chức code

```
UIManager
 ├─- Menu
 ├── TowerUI
 ├── EnemyUI
 ├── DecorUI
 ├── MapUI

```
### **UIManager**

- **Chức năng:** Quản lý toàn bộ UI, xử lý input người dùng và phối hợp giữa các thành phần UI khác.
- **Thuộc tính:**
    - Danh sách các UI thành phần (`std::vector<UIElement*> elements`).
    - Trạng thái giao diện (như menu đang mở, map đang hiển thị).
- **Phương thức:**
    - `addElement(UIElement* element)` → Thêm UI vào danh sách.
    - `render()` → Vẽ tất cả UI.
    - `update(float delta)` → Cập nhật logic của UI.
    - `handleInput()` → Xử lý input từ người dùng.
```cpp
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

```

### **UIElement (Abstract Class)**

- **Chức năng:** Lớp cơ sở cho tất cả thành phần UI (menu, button, map...).
- **Thuộc tính:**
    - Vị trí (`x, y`) và kích thước (`width, height`).
- **Phương thức:**
    - `virtual void render()` → Vẽ UI.
    - `virtual void update(float delta)` → Cập nhật logic UI.
    - `virtual void handleInput(InputEvent input)` → Xử lý input.
```cpp
class UIElement {
protected:
    int x, y, width, height;

public:
    virtual void render() = 0;
    virtual void update(float delta) = 0;
    virtual void handleInput(InputEvent input) = 0;
    virtual ~UIElement() {}
};

```

### **Menu**

- **Chức năng:** Quản lý các nút bấm và các lựa chọn trong menu.
- **Thuộc tính:**
    - Danh sách các nút (`std::vector<Button*> buttons`).
- **Phương thức:**
    - `addButton(Button* button)` → Thêm nút vào menu.
    - Override `render()`, `update()`, `handleInput()`.
```cpp
class Menu : public UIElement {
private:
    std::vector<Button*> buttons;

public:
    void addButton(Button* button) {
        buttons.push_back(button);
    }

    void render() override {
        for (Button* button : buttons) {
            button->render();
        }
    }

    void update(float delta) override {
        for (Button* button : buttons) {
            button->update(delta);
        }
    }

    void handleInput(InputEvent input) override {
        for (Button* button : buttons) {
            button->handleInput(input);
        }
    }
};

```

### **Button**

- **Chức năng:** Thành phần tương tác đơn giản trong giao diện.
- **Thuộc tính:**
    - Văn bản (`std::string label`).
    - Trạng thái (`bool isPressed`).
    - Callback (`std::function<void()> onClick`).
- **Phương thức:**
    - `render()`, `update()`, `handleInput()`.
```cpp
class Button : public UIElement {
private:
    std::string label;
    bool isPressed = false;
    std::function<void()> onClick;

public:
    Button(const std::string& label, std::function<void()> onClick)
        : label(label), onClick(onClick) {}

    void render() override {
        // Vẽ nút bấm
    }

    void update(float delta) override {
        // Logic animation hoặc trạng thái
    }

    void handleInput(InputEvent input) override {
        if (/* Kiểm tra input nhấn vào nút */) {
            isPressed = true;
            onClick();
        }
    }
};

```

# LUỒNG WIN32 API

```cpp
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <iostream>

namespace towerdefense {

class Game {
private:
    std::atomic<bool> running{false};  // Kiểm soát trạng thái game.
    std::thread logicThread;           // Luồng xử lý logic.
    std::thread physicsThread;         // Luồng xử lý vật lý.
    std::thread renderThread;          // Luồng xử lý render.

    std::mutex mtx;                    // Bảo vệ dữ liệu chia sẻ.
    std::condition_variable cv;        // Đồng bộ giữa các luồng.

    void logicLoop();
    void physicsLoop();
    void renderLoop();

public:
    void start();
    void stop();
};

} // namespace towerdefense

```


```cpp
void towerdefense::Game::logicLoop() {
    while (running) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            // Cập nhật trạng thái game
            std::cout << "Updating game logic...\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Giả lập 60 FPS
    }
}
```

```cpp
void towerdefense::Game::renderLoop() {
    while (running) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            // Render hình ảnh
            std::cout << "Rendering frame...\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Giả lập 60 FPS
    }
}
```

```cpp
void towerdefense::Game::start() {
    running = true;

    // Khởi chạy các luồng
    logicThread = std::thread(&Game::logicLoop, this);
    physicsThread = std::thread(&Game::physicsLoop, this);
    renderThread = std::thread(&Game::renderLoop, this);

    std::cout << "Game started!\n";

    // Chạy vòng lặp chính (chờ kết thúc game)
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
void towerdefense::Game::stop() {
    running = false;

    if (logicThread.joinable()) logicThread.join();
    if (physicsThread.joinable()) physicsThread.join();
    if (renderThread.joinable()) renderThread.join();

    std::cout << "Game stopped!\n";
}

```



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
**State Pattern** và **Observer Pattern** là hai mẫu thiết kế phổ biến trong lập trình hướng đối tượng, nhưng chúng có mục đích và cách sử dụng khác nhau. Dưới đây là sự phân biệt giữa chúng và cách áp dụng vào class `Enemy` trong game **Tower Defense**.

---

### **1. So sánh giữa State và Observer Pattern**

|**Đặc điểm**|**State Pattern**|**Observer Pattern**|
|---|---|---|
|**Mục đích**|Quản lý trạng thái nội tại của một đối tượng.|Thông báo sự thay đổi trạng thái đến các đối tượng khác.|
|**Khi nào dùng**|Khi đối tượng cần hành vi khác nhau tùy thuộc vào trạng thái.|Khi một đối tượng thay đổi, và nhiều đối tượng khác cần phản ứng lại.|
|**Mô hình thiết kế**|- Thay đổi trạng thái của đối tượng trong runtime. - Chỉ đối tượng hiện tại biết trạng thái của nó.|- Một đối tượng (Subject) thông báo các thay đổi đến các đối tượng khác (Observers).|
|**Thành phần chính**|- Các trạng thái (State) được tách thành các lớp cụ thể. - Một lớp Context chứa trạng thái hiện tại và logic chuyển trạng thái.|- Lớp Subject chứa danh sách các Observers. - Các Observers sẽ đăng ký (subscribe) và nhận thông báo khi có thay đổi.|
|**Ví dụ thực tế**|- Một enemy chuyển giữa trạng thái `Idle`, `Moving`, `Attacking`.|- Khi một enemy bị tiêu diệt, các hệ thống khác (UI, Sound) được thông báo để cập nhật.|

---

### **2. Áp dụng vào class `Enemy`**

#### **a. State Pattern**

**Khi nào dùng?**  
Khi bạn cần quản lý **hành vi** của `Enemy` dựa trên trạng thái của nó, như:

- `Idle`: Đứng yên.
- `Moving`: Di chuyển.
- `Attacking`: Tấn công.

**Cách dùng:**

- Tách mỗi trạng thái (`Idle`, `Moving`, `Attacking`) thành một lớp riêng.
- Lớp `Enemy` đóng vai trò là Context, chứa trạng thái hiện tại và logic để chuyển trạng thái.

**Ưu điểm:**

- Dễ mở rộng: Thêm trạng thái mới mà không ảnh hưởng đến các trạng thái khác.
- Code sạch, giảm việc sử dụng câu lệnh `if-else` hoặc `switch-case`.

#### **b. Observer Pattern**

**Khi nào dùng?**  
Khi bạn cần thông báo cho các hệ thống khác khi `Enemy` thay đổi, như:

- Khi một `Enemy` bị tiêu diệt, các hệ thống khác cần:
    - UI cập nhật số lượng enemy còn lại.
    - Hệ thống âm thanh phát hiệu ứng nổ.
    - Gửi tín hiệu đến lớp `Game` để kiểm tra thắng/thua.

**Cách dùng:**

- Lớp `Enemy` đóng vai trò là **Subject**.
- Các hệ thống khác (UI, Sound, Game Logic) là **Observers** và đăng ký với `Enemy`.

**Ưu điểm:**

- Kết nối lỏng lẻo giữa `Enemy` và các hệ thống khác.
- Dễ dàng thêm hoặc gỡ bỏ các hệ thống phản ứng với `Enemy`.

---

### **3. Kết hợp cả hai trong game Tower Defense**

Bạn có thể sử dụng cả **State Pattern** và **Observer Pattern** cho class `Enemy`:

1. **State Pattern**: Quản lý hành vi của từng enemy:
    
    - Enemy chuyển từ trạng thái `Idle` sang `Moving` khi bắt đầu đi đến mục tiêu.
    - Enemy chuyển sang `Attacking` khi đến gần tháp phòng thủ.
2. **Observer Pattern**: Thông báo các thay đổi quan trọng của enemy:
    
    - Khi `Enemy` chết, thông báo cho UI, âm thanh và logic game.

---

### **4. Sơ đồ UML**

Sơ đồ dưới đây minh họa cách kết hợp cả **State Pattern** và **Observer Pattern** trong class `Enemy`:

```
                         +-------------------+
                         |    IState         |
                         +-------------------+
                         | + handle()        |
                         +-------------------+
                                  ^
                                  |
       +-------------+------------+------------+
       |             |                         |
+-------------+ +-------------+         +-------------+
| IdleState   | | MovingState |         | AttackingState|
+-------------+ +-------------+         +-------------+
| + handle()  | | + handle()  |         | + handle()   |
+-------------+ +-------------+         +-------------+

                         +-------------------+
                         |      Enemy        |
                         +-------------------+
                         | - currentState    |
                         | + setState(state) |
                         | + update()        |
                         +-------------------+
                         |     <<Subject>>   |
                         +-------------------+
                          |   attach()       |
                          |   detach()       |
                          |   notify()       |
                          +-------------------+
                                  ^
                                  |
               +------------------------------------+
               |                                    |
       +-------------------+             +-------------------+
       |      UIObserver   |             | SoundObserver     |
       +-------------------+             +-------------------+
       | + update()        |             | + update()        |
       +-------------------+             +-------------------+
```

---

### **5. Kết luận**

- **State Pattern**: Quản lý hành vi của `Enemy` trong game.
- **Observer Pattern**: Kết nối `Enemy` với các hệ thống khác để cập nhật khi có sự thay đổi.

Sự kết hợp này giúp game dễ mở rộng và bảo trì hơn, đồng thời tối ưu hóa logic xử lý đối tượng `Enemy`.