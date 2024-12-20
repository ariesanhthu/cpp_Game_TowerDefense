#pragma once
#include <vector>
#include <unordered_map>
#include <string>

class ResourceManager {
private:
    std::unordered_map<std::string, std::vector<std::wstring>> resources;
    // Private constructor để ngăn việc tạo nhiều đối tượng
    ResourceManager() {}
public:
    void loadResources() {
        resources["enemy5"] = {
            L"Assets/game/enemy5/enemy5-0.png",
            L"Assets/game/enemy5/enemy5-1.png",
            L"Assets/game/enemy5/enemy5-2.png",
            L"Assets/game/enemy5/enemy5-3.png"
        };
        
        resources["enemy2"] = {
            L"Assets/game/enemy2/enemy1-1.png",
            L"Assets/game/enemy2/enemy1-2.png",
            L"Assets/game/enemy2/enemy1-3.png"
        };
        
        resources["enemy3"] = {
            L"Assets/game/enemy3/enemy3-1.png",
            L"Assets/game/enemy3/enemy3-2.png",
            L"Assets/game/enemy3/enemy3-3.png",
            L"Assets/game/enemy3/enemy3-4.png"
        };
        // goblin nước
        resources["enemy4"] = {
            L"Assets/game/enemy4/enemy4-0.png",
            L"Assets/game/enemy4/enemy4-1.png",
            L"Assets/game/enemy4/enemy4-2.png",
            L"Assets/game/enemy4/enemy4-3.png"
        };

    }

    const std::vector<std::wstring>& getResource(const std::string& key) {
        return resources[key];
    }

    static ResourceManager& getInstance() {
        static ResourceManager instance;
        return instance;
    }


    // Ngăn việc sao chép đối tượng singleton
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

};