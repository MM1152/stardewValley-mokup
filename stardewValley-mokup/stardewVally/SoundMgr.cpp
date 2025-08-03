#include "stdafx.h"
#include "SoundMgr.h"

SoundMgr::SoundMgr()
{
}
SoundMgr::~SoundMgr()
{
}

void SoundMgr::Load(const std::string& id, const std::string& filepath)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filepath))
    {
        return;
    }

    soundBuffers[id] = buffer;
    sounds[id].setBuffer(soundBuffers[id]);
}

void SoundMgr::Play(const std::string& id)
{
    auto it = sounds.find(id);
    if (it != sounds.end())
    {
        it->second.play();
    }
}

void SoundMgr::Stop(const std::string& id)
{
    auto it = sounds.find(id);
    if (it != sounds.end())
    {
        it->second.stop();
    }
}

void SoundMgr::StopAll()
{
    for (auto& pair : sounds)
    {
        pair.second.stop();
    }
}