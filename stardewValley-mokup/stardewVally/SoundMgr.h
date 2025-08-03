#pragma once
#include "Singleton.h"


enum class SoundType {
    BGM,
    TITLE,
    FARM,
    VILLIGE,
    SFX,
    MENUOPEN,
    MENUCLOSE,
    DOOROPEN,

};
class SoundMgr : public Singleton<SoundMgr>
{
	friend class Singleton<SoundMgr>;

protected:
    std::map<SoundType, sf::SoundBuffer> soundBuffers;
    std::map<SoundType, sf::Sound> sounds;

public:
    SoundMgr();
    ~SoundMgr();

    void Load(SoundType id, const std::string& filepath);
    void Play(SoundType id);
    void Stop(SoundType id);

    void StopAll();
};

#define SOUND_MGR SoundMgr::Instance()