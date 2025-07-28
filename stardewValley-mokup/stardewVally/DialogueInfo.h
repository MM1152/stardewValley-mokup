#pragma once
#include "stdafx.h"

struct DialogueEntry
{
	std::string character;
	std::string id;
	std::string portrait_textureId;
	std::vector<std::string> lines;

};