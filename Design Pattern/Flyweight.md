- áp dụng vào việc quản lý các tài nguyên dùng chung và dùng riêng của các đối tượng có cùng đặc tính

- Ví dụ: trong khu rừng có nhiều cây, không cần thiết phải tạo lại tất cả cây với cấu trúc như nhau (lá, cành, cấu trúc, đất, tên,...)
- Chỉ cần khởi tạo 1 loại cây và các cây khá chỉ vào vùng nhớ đó và dùng chung các đặc tính khác nhau
- Mỗi cây có số lượng lá, vị trí, độ cao khác nhau, ta chỉ cần thay đổi các đặc tính này

Ưu điểm: tối ưu vùng nhớ, hạn chế việc tạo ra nhiều dữ liệu lặp lại dư thừa, trong khi mình có thể dùng chung
tăng hiệu quả chương trình, các đối tượng khởi tạo nhanh hơn khi chỉ cần trỏ đến vùng nhớ đã được tạo

### áp dụng (từ web)
```cpp
class TreeModel {
private:
    Mesh mesh_;
    Texture bark_;
    Texture leaves_;
};
class Tree {
private:
    TreeModel* model_; // thuộc tính dùng chung, 1 con trỏ trỏ tới vùng nhớ đã có
// các thuộc tính riêng biệt cho từng cây
    Vector position_; //vị trí
    double height_; // cao
    double thickness_;
    Color barkTint_;
    Color leafTint_;
};

```

```cpp
// lớp địa hình
class Terrain {
public:
    Terrain(int movementCost, bool isWater, Texture texture)
        : movementCost_(movementCost), isWater_(isWater), texture_(texture) {}

    int getMovementCost() const { return movementCost_; }
    bool isWater() const { return isWater_; }
    const Texture& getTexture() const { return texture_; }

private:
    int movementCost_;  // chi phí di chuyển
    bool isWater_;      // loại địa hình có phải nước hay không
    Texture texture_;   // cấu trúc
};

// lớp World chia thành các ô đất, mỗi ô đất có một đặc tính
// dùng lại các đặc tính được khởi tạo từ lớp Terrain
// các ô đất cùng loại địa hình có chung đặc tính và dùng chung 1 vùng nhớ
class World {
public:
    World()
        : grassTerrain_(1, false, GRASS_TEXTURE),
          hillTerrain_(3, false, HILL_TEXTURE),
          riverTerrain_(2, true, RIVER_TEXTURE) {}

    const Terrain& getTile(int x, int y) const { return *tiles_[x][y]; }

private:
    Terrain grassTerrain_;
    Terrain hillTerrain_;
    Terrain riverTerrain_;
    Terrain* tiles_[WIDTH][HEIGHT];
};

```