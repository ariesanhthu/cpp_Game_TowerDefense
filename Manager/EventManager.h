#pragma once
#include <functional>
#include <map>
#include <vector>
#include "AudioManager.h"

namespace towerdefense
{ 

    enum class GameEvent
    {
        Shoot,
        Hit,
        Missed,
        EnemyMove,
        PlayerMove
    };


    class EventManager
    {
    private:
        // Singleton instance
        static EventManager* instance;

        // Map chứa các sự kiện và danh sách callback tương ứng
        std::map<GameEvent, std::vector<std::function<void()>>> eventListeners;

        EventManager() = default;

    public:

        // Xóa tất cả listener (nếu cần)
        void clearListeners()
        {
            eventListeners.clear();
        }

        // Lấy instance của EventManager
        static EventManager& getInstance()
        {
            if (instance == nullptr)
            {
                instance = new EventManager();
            }
            return *instance;
        }

        // Đăng ký callback cho một sự kiện
        void registerListener(GameEvent event, std::function<void()> callback)
        {
            eventListeners[event].push_back(callback);
        }

        // ==========================================================================
        // Kích hoạt sự kiện (gọi tất cả callback)
        void triggerEvent(GameEvent event)
        {
            if (eventListeners.find(event) != eventListeners.end())
            {
                for (const auto& callback : eventListeners[event])
                {
                    callback(); // Gọi từng callback đã đăng ký
                }
            }
        }
        // ==========================================================================

        // Đăng ký sự kiện trong hàm khởi tạo
        // ==========================================================================
        void setupEventListeners()
        {
            // Đăng ký sự kiện Shoot
            EventManager::getInstance().registerListener(GameEvent::Shoot, []()
                {
                    AudioManager::getInstance().playSoundEffect("gunfire");
                });

            // Đăng ký sự kiện Hit
            EventManager::getInstance().registerListener(GameEvent::Hit, []()
                {
                    AudioManager::getInstance().playSoundEffect("explosion");
                });

            // Đăng ký sự kiện Missed
            EventManager::getInstance().registerListener(GameEvent::Missed, []()
                {
                    AudioManager::getInstance().playSoundEffect("missed");
                });
        }

    };
} // namespace towerdefense