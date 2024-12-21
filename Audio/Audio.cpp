#include "Audio.h"


// Play a music file
bool Audio::PlayMusic(const std::string& file_music) {
    if (PlaySoundA(file_music.c_str(), NULL, SND_FILENAME | SND_ASYNC)) {
        return true;
    }
    else {
        return false;
    }
}

// Stop the currently playing music
bool Audio::StopMusic() {
    if (PlaySoundA(NULL, NULL, 0)) {
        return true;
    }
    else {
        return false;
    }
}

// Play a sound effect
bool Audio::PlaySoundEffect(const std::string& file_sound) {
    if (PlaySoundA(file_sound.c_str(), NULL, SND_FILENAME | SND_ASYNC)) {
        return true;
    }
    else {
        return false;
    }
}

// Stop the currently playing sound effect
bool Audio::StopSoundEffect() {
    return StopMusic(); // Uses the same mechanism as stopping music
}