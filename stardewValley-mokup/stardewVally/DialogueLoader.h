#pragma once
#include "Singleton.h"
#include "DialogueInfo.h"

class DialogueLoader : public Singleton<DialogueLoader>
{
	friend class Singleton<DialogueLoader>;

protected:
	static std::vector<DialogueEntry> LoadFromFile(const std::string& filename);
public:
};

