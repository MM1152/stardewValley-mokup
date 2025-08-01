#pragma once

#include "stdafx.h"

class SoundPlayer
{
protected:
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, sf::Sound> sounds;

public:
    SoundPlayer();
    ~SoundPlayer();

    void Load(const std::string& id, const std::string& filepath);

    void Play(const std::string& id);

    void Stop(const std::string& id);

    void StopAll();
};