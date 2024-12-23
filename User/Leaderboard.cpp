#include "Leaderboard.h"

Leaderboard::Leaderboard()
{

}

Leaderboard::~Leaderboard()
{
    OutputDebugStringA("~LeaderBoard");
}

Leaderboard& Leaderboard::getInstance() {
    static Leaderboard instance;
    return instance;
}

// Đọc dữ liệu bảng xếp hạng từ file
bool Leaderboard::readFile()
{
    ifstream inFile(filename.c_str(), ios::binary);
    if (!inFile)
    {
        return false;
    }

    users.clear();

    while (!inFile.eof())
    {
        int nameLength;
        inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength)); // Đọc độ dài của tên
        if (inFile.eof()) break;

        string username(nameLength, '\0');
        inFile.read(&username[0], nameLength); // Đọc tên người dùng

        int lenscore;
        inFile.read(reinterpret_cast<char*>(&lenscore), sizeof(lenscore)); // Đọc điểm số
       
        string score(lenscore, '\0');
        inFile.read(&score[0], lenscore);

        // Tạo đối tượng User và thêm vào danh sách
        User tempUser(username, stoi(score));
        users.push_back(tempUser);
    }

    inFile.close();

    return true;
}

// Ghi dữ liệu bảng xếp hạng vào file
void Leaderboard::writeFile(User user)
{
    ofstream outFile(filename.c_str(), ios::binary | ios::app);
    if (!outFile)
    {
        cout << "Khong the mo file: " << filename << "\n";
        return;
    }

    //for (auto& user : users)
    //{
        // Ghi độ dài của tên người dùng
        int nameLength = user.getName().size();
        outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(int));

        // Ghi tên người dùng
        outFile.write(user.getName().c_str(), nameLength);

        // Ghi điểm số
        string score = to_string(user.getScore());

        int lenScore = score.size();
        
        outFile.write(reinterpret_cast<const char*>(&lenScore), sizeof(int));

        outFile.write(score.c_str(), lenScore);
    //}

    outFile.close();
}

// Thêm người dùng mới vào bảng xếp hạng
void Leaderboard::addUser(User& user)
{
    users.push_back(user);
    sortUserByScore(); // Sắp xếp sau khi thêm người dùng
}

// Sắp xếp danh sách người dùng theo điểm số (giảm dần)
void Leaderboard::sortUserByScore()
{
    sort(users.begin(), users.end(), []( User& a,  User& b)
        {
            return a.getScore() > b.getScore();
        });
}

// Tải dữ liệu và chuẩn bị các thành phần để render
void Leaderboard::loadLeaderBoard()
{
    customFont = FontManager::getInstance().getFont("normal");
    titleFont = FontManager::getInstance().getFont("title");

    // Tạo TextElement cho tiêu đề
    title = make_shared<TextElement>(L"LEADERBOARD", titleFont, RGB(255, 255, 255), POINT{ 300, 130 });
    // ---------------------------------------------------------------

    // Xóa danh sách hiển thị cũ (nếu có)
    userElements.clear();

    // Tạo các TextElement cho từng người dùng
    POINT startPos = { 500, 250 };
    int yOffset = 50; // Khoảng cách giữa các dòng

    // ---------------------------------------------------------------
    // đọc file
    if (!readFile())
    {
        userElements.push_back(make_shared<TextElement>(L"There are no user", customFont, RGB(255, 255, 255), startPos));
        return;
    }
    sortUserByScore(); // sort
    int numberUser = min(users.size() - 1, 5);
    // ---------------------------------------------------------------

    for (size_t i = 0; i <= numberUser; ++i)
    {
        string str = to_string(i + 1) + ". " + users[i].getName() + " " + to_string(users[i].getScore());

        wstring userInfo = Utils::stringToWstring(str);

        POINT pos = { startPos.x, startPos.y + static_cast<LONG>(i * yOffset) };
        userElements.push_back(make_shared<TextElement>(userInfo, customFont, RGB(255, 255, 255), pos));
    }
}

// Render bảng xếp hạng lên màn hình
void Leaderboard::render(HDC hdc)
{
    if (title)
    {
        title->render(hdc); // Render tiêu đề
    }

    // Render từng người dùng trong danh sách
    for (const auto& userElement : userElements)
    {
        userElement->render(hdc);
    }
}