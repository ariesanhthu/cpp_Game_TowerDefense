#pragma once

#include <string> 
#include <windows.h>


class Audio {
	
public: 
	bool PlayMusic(const std::string& file_music);
	bool StopMusic();

	bool PlaySoundEffect(const std::string& file_sound);
	bool StopSoundEffect();

    int SetVolume(int volumePercentage) {
        if (volumePercentage < 0) volumePercentage = 0;
        if (volumePercentage > 99) volumePercentage = 0;

        DWORD volume = (DWORD)(0xFFFF * (volumePercentage / 100.0f));
        DWORD volumeSetting = (volume & 0xFFFF) | (volume << 16);

        waveOutSetVolume(0, volumeSetting);
        
        return volumePercentage;
    }
};

