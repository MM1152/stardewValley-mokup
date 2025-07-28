#pragma once
#include "Singleton.h"
#include "DialogueInfo.h"

class DialogueLoader : public Singleton<DialogueLoader>
{
	friend class Singleton<DialogueLoader>;

protected:
	std::unordered_map<std::string, std::vector<DialogueInfo>> charactersDialogue;
public:

	void LoadFromJson(const std::string& filename);

	const std::vector<DialogueInfo>& GetDialogue(const std::string& characterName);
	const std::unordered_map<std::string, std::vector<DialogueInfo>>& GetAllDialogues() const;
};

