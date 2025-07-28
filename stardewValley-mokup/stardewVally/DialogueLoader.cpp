#include "stdafx.h"
#include "DialogueLoader.h"


void DialogueLoader::LoadFromJson(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "Failed to open dialogue JSON file: " << filename << std::endl;
		return;
	}

	charactersDialogue.clear(); 

	nlohmann::json data;
	file >> data;

	if (!data.contains("dialogues") || !data["dialogues"].is_array())
	{
		std::cerr << "'dialogues' key is missing or is not an array\n";
		return;
	}

	for (const auto& entry : data["dialogues"])
	{
		if (!entry.contains("character") || !entry.contains("id") ||
			!entry.contains("portrait_textureId") || !entry.contains("lines"))
		{
			std::cerr << "Missing required fields in entry: " << entry.dump(2) << "\n";
			continue;
		}

		DialogueInfo info;
		info.character = entry["character"];
		info.id = entry["id"];
		info.portrait_textureId = entry["portrait_textureId"];
		for (const auto& line : entry["lines"])
		{
			info.lines.push_back(line);
		}

		charactersDialogue[info.character].push_back(info);
	}
}

const std::vector<DialogueInfo>& DialogueLoader::GetDialogue(const std::string& characterName)
{
	static std::vector<DialogueInfo> emptyDialogue;
	auto it = charactersDialogue.find(characterName);
	if (it != charactersDialogue.end())
	{
		return it->second;
	}
	return emptyDialogue;
}

const std::unordered_map<std::string, std::vector<DialogueInfo>>& DialogueLoader::GetAllDialogues() const
{
	return charactersDialogue;
}

