#include "stdafx.h"
#include "SoundMgr.h"

SoundMgr::SoundMgr()
{
}
SoundMgr::~SoundMgr()
{
}

void SoundMgr::Load(SoundType id, const std::string& filepath)
{
    sf::SoundBuffer buffer;

    if (soundBuffers.find(id) != soundBuffers.end()) {
        return;
    }

    if (!buffer.loadFromFile(filepath))
    {
        return;
    }

    soundBuffers[id] = buffer;
    sounds[id].setBuffer(soundBuffers[id]);
}

void SoundMgr::Play(SoundType id)
{
   
    auto it = sounds.find(id);
    if (it != sounds.end())
    {
        it->second.play();

        if ((int)id < (int)SoundType::BGM) {
            it->second.setLoop(true);
        }
        else {
            it->second.setLoop(false);
        }
    }
}

void SoundMgr::Stop(SoundType id)
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