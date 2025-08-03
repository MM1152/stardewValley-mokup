#pragma once
#include "Singleton.h"
class SoundMgr : public Singleton<SoundMgr>
{
	friend class Singleton<SoundMgr>;

protected:
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, sf::Sound> sounds;

public:
    SoundMgr();
    ~SoundMgr();

    void Load(const std::string& id, const std::string& filepath);

    void Play(const std::string& id);

    void Stop(const std::string& id);

    void StopAll();
};

