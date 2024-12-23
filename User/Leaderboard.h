#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <memory>

#include "User.h"
#include "FontManager.h"
#include "menuitem.h"
#include "Utils.h"

using namespace std;

class Leaderboard
{
private:

    Leaderboard();
    ~Leaderboard();

    string filename = "Storage/LeaderBoard.catfarm";
public:
    static Leaderboard& getInstance();
    // Lấy font từ FontManager
    HFONT customFont;
    HFONT titleFont;
    shared_ptr<TextElement> title;
    vector<shared_ptr<TextElement>> userElements;

    vector<User> users; // Danh sách người dùng trong bảng xếp hạng

    // Đọc file lưu trữ bảng xếp hạng
    bool readFile();

    // Ghi dữ liệu bảng xếp hạng vào file
    void writeFile(User user);

    // Thêm người dùng mới vào bảng xếp hạng
    void addUser(User& user);

    // Cập nhật thông tin người dùng
    void updateUser();

    // Tải bảng xếp hạng (nếu có logic riêng)
    void loadLeaderBoard();

    // Render bảng xếp hạng lên màn hình
    void render(HDC hdc);

    // Sắp xếp người dùng theo điểm số (giảm dần)
    void sortUserByScore();
};
