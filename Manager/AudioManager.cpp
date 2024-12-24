#include "AudioManager.h"

namespace towerdefense
{
    AudioManager::AudioManager()
        : masterVolume(1.0f), effectVolume(1.0f), musicVolume(1.0f)
    {
        // Constructor rỗng
		setBackgroundMusic(L"Assets/Audio/background/background-gameplay.wav");
    }

    AudioManager::~AudioManager()
    {
        stopBackgroundMusic(); // Đảm bảo nhạc nền dừng khi hủy đối tượng
    }

    AudioManager& AudioManager::getInstance()
    {
        static AudioManager instance;
        return instance;
    }

    void AudioManager::loadSoundEffect(const std::string& name, const std::wstring& path)
    {
        std::lock_guard<std::mutex> lock(audioMutex);
        soundEffects[name] = path;
    }

    void AudioManager::playSoundEffect(const std::string& name)
    {
        std::lock_guard<std::mutex> lock(audioMutex);

        auto it = soundEffects.find(name);
        if (it != soundEffects.end())
        {
           /* PlaySound(it->second.c_str(), NULL, SND_FILENAME | SND_ASYNC);*/
            std::thread([path = it->second]() {
                PlaySound(path.c_str(), NULL, SND_FILENAME | SND_ASYNC);
                }).detach();
        }
    }
	// ------------ BACKGROUND MUSIC ------------
    
    void AudioManager::setBackgroundMusic(const std::wstring& path)
    {
        backgroundMusic = path;
    }

    void AudioManager::playBackgroundMusic()
    {
        if (!backgroundMusic.empty())
        {
            PlaySound(backgroundMusic.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        }
    }
    //void AudioManager::playBackgroundMusic()
    //{
    //    if (isBackgroundMusicPlaying)
    //    {
    //        return;
    //    }

    //    isBackgroundMusicPlaying = true;
    //    musicThread = std::thread([this]()
    //        {
    //            if (isBackgroundMusicPlaying)
    //            /*while (isBackgroundMusicPlaying)
    //            */
    //            {
    //                PlaySound(backgroundMusic.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    //                std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //            }

    //            PlaySound(NULL, NULL, SND_ASYNC);
    //        });
    //    musicThread.detach();
    //}

    void AudioManager::stopBackgroundMusic()
    {
        PlaySound(NULL, NULL, SND_PURGE);
    }
	// ----------------------------------------------------------------------------------

	// SETTING VOLUME

    void AudioManager::setMasterVolume(float volume)
    {
        masterVolume = volume;
        // Bạn có thể sử dụng thêm các thư viện hoặc API khác để áp dụng âm lượng tổng
    }

    void AudioManager::setMusicVolume(float volume)
    {
        musicVolume = volume;
        // Tương tự như effectVolume
    }
    void AudioManager::setEffectVolume(float volume)
    {
        effectVolume = volume;
        // Nếu cần, bạn có thể áp dụng thông qua các thư viện nâng cao hơn
    }
	// ----------------------------------------------------------------------------------
    //void AudioManager::setupAudioListeners()
    //{
    //    EventManager::getInstance().registerListener(GameEvent::Shoot, []()
    //        {
    //            playSoundEffect("gunfire");
    //        });

    //    EventManager::getInstance().registerListener(GameEvent::Hit, []()
    //        {
    //            playSoundEffect("explosion");
    //        });
    //}
    void AudioManager::setupAudio()
    {
        auto& audio = AudioManager::getInstance();

            // Tải các hiệu ứng âm thanh
        //audio.loadSoundEffect("shoot", L"sounds/shoot.wav");
        audio.loadSoundEffect("explosion", L"Assets/audio/explosion.wav");

        // Đặt nhạc nền
        //audio.setBackgroundMusic(L"sounds/background.wav");
      
    }

    float AudioManager::getMusicVolume() const { return musicVolume; } // Lấy âm lượng nhạc nền
    void AudioManager::adjustMusicVolume(float delta)
    {
        musicVolume += delta;
        if (musicVolume > 1.0f)
        {
            musicVolume = 1.0f; // Giới hạn tối đa
        }
        else if (musicVolume < 0.0f)
        {
            musicVolume = 0.0f; // Giới hạn tối thiểu
        }
    }

}//