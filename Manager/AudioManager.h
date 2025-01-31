﻿#pragma once

#include <string>
#include <map>
#include <Windows.h>
#include <mmsystem.h> // Thư viện xử lý âm thanh của WinAPI
#pragma comment(lib, "winmm.lib") // Liên kết thư viện WinAPI

//#include "EventManager.h"

#include <mutex>
using namespace std;

namespace towerdefense
{
    class AudioManager
    {
    private:
        std::mutex audioMutex;
        std::map<std::string, std::wstring> soundEffects; // Map lưu trữ đường dẫn của các hiệu ứng âm thanh
        std::wstring backgroundMusic; // Đường dẫn nhạc nền
        float masterVolume; // Âm lượng tổng
        float effectVolume; // Âm lượng hiệu ứng
        float musicVolume; // Âm lượng nhạc nền
        std::thread musicThread;
        AudioManager(); // Constructor riêng tư để đảm bảo Singleton
        ~AudioManager();

    public:
        std::atomic<bool> isBackgroundMusicPlaying{ true };
		//bool isBackgroundMusicPlaying = true; // Trạng thái phát nhạc nền
        // Singleton instance
        static AudioManager& getInstance();

        // Quản lý âm thanh
        void loadSoundEffect(const std::string& name, const std::wstring& path); // Tải hiệu ứng âm thanh

        void playSoundEffect(const std::string& name); // Phát hiệu ứng âm thanh

        void setBackgroundMusic(const std::wstring& path); // Thiết lập nhạc nền
        void playBackgroundMusic(); // Phát nhạc nền
        void stopBackgroundMusic(); // Dừng nhạc nền

        // Quản lý âm lượng
        void setMasterVolume(float volume); // Cài đặt âm lượng tổng
        void setEffectVolume(float volume); // Cài đặt âm lượng hiệu ứng
        void setMusicVolume(float volume); // Cài đặt âm lượng nhạc nền

        // Thêm đường dẫn sound
        void setupAudio();
        // ======================================================
        float getMusicVolume() const;
        void adjustMusicVolume(float delta);
		// ======================================================

        //void setupAudioListeners();

    };
}
// use
//  auto& audio = AudioManager::getInstance();

    // Phát nhạc nền
//audio.playBackgroundMusic();
//
//// Phát hiệu ứng âm thanh
//audio.playSoundEffect("shoot");
//audio.playSoundEffect("explosion");
// 
//
//class Audio {
//	
//public: 
//	bool PlayMusic(const std::string& file_music);
//	bool StopMusic();
//
//	bool PlaySoundEffect(const std::string& file_sound);
//	bool StopSoundEffect();
//
//    int SetVolume(int volumePercentage) {
//        if (volumePercentage < 0) volumePercentage = 0;
//        if (volumePercentage > 99) volumePercentage = 0;
//
//        DWORD volume = (DWORD)(0xFFFF * (volumePercentage / 100.0f));
//        DWORD volumeSetting = (volume & 0xFFFF) | (volume << 16);
//
//        waveOutSetVolume(0, volumeSetting);
//        
//        return volumePercentage;
//    }
//};
//
