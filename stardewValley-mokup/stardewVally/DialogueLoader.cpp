#include "stdafx.h"
#include "DialogueLoader.h"

std::vector<DialogueEntry> DialogueLoader::LoadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open " << filename << std::endl;
        return {};
    }

    nlohmann::json j;
    file >> j;

    std::vector<DialogueEntry> dialogues;

    for (const auto& item : j["dialogues"])
    {
        DialogueEntry entry;
        entry.character = item.value("character", "");
        entry.id = item.value("id", "");
        entry.lines = item.value("lines", std::vector<std::string>());

        dialogues.push_back(entry);
    }

    return dialogues;
}
