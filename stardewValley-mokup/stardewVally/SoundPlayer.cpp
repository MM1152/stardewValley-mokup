#include "stdafx.h"
#include "SoundPlayer.h"

SoundPlayer::SoundPlayer()
{
}
SoundPlayer::~SoundPlayer()
{
}

void SoundPlayer::Load(const std::string& id, const std::string& filepath)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filepath))
    {
        return;
    }

    soundBuffers[id] = buffer;
    sounds[id].setBuffer(soundBuffers[id]);
}

void SoundPlayer::Play(const std::string& id)
{
    auto it = sounds.find(id);
    if (it != sounds.end())
    {
        it->second.play();
    }
}

void SoundPlayer::Stop(const std::string& id)
{
    auto it = sounds.find(id);
    if (it != sounds.end())
    {
        it->second.stop();
    }
}

void SoundPlayer::StopAll()
{
    for (auto& pair : sounds)
    {
        pair.second.stop();
    }
}