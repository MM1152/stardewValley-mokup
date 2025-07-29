#include "stdafx.h"
#include "Crops.h"
#include "TimeMoneyUi.h"

Crops::Crops(const std::string& name)
	: Gatherable(name)
{
}

void Crops::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;


	SetCropsType(ctype);
	SetScale({ 1.f, 1.f });
}

void Crops::Reset()
{
	GtSp.setTexture(TEXTURE_MGR.Get(cropsId));
}

void Crops::GrowUp(){
	curGrow++;
	sf::IntRect Grow(16 * curGrow, 0, 16, 16);
	GtSp.setTextureRect(Grow);
	if (curGrow > 5 && cropsId == "graphics/parsnip.png")
	{
		curGrow = 5;
		sf::IntRect Grow(16 * curGrow, 0, 16, 16);
		GtSp.setTextureRect(Grow);
		growup = true;
	}
	else if (curGrow > 5 && cropsId == "graphics/garlic.png")
	{
		curGrow = 5;
		sf::IntRect Grow(16 * curGrow, 0, 16, 16);
		GtSp.setTextureRect(Grow);
		growup = true;
	}
	else if (curGrow > 6 && cropsId == "graphics/caluliflower.png")
	{
		curGrow = 6;
		sf::IntRect Grow(16 * curGrow, 0, 16, 16);
		GtSp.setTextureRect(Grow);
		growup = true;
	}
	else if (curGrow > 6 && cropsId == "graphics/potato.png")
	{
		curGrow = 6;
		sf::IntRect Grow(16 * curGrow, 0, 16, 16);
		GtSp.setTextureRect(Grow);
		growup = true;
	}
}

void Crops::SetCropsType(CropsType c)
{
	ctype = c;
	sf::IntRect seed(0, 0, 16, 16);
	switch (ctype)
	{
	case CropsType::Parsnip:
		cropsId = "graphics/parsnip.png";
		GtSp.setTextureRect(seed);
		break;
	case CropsType::Cauliflower:
		cropsId = "graphics/caluliflower.png";
		GtSp.setTextureRect(seed);
		break;
	case CropsType::Potato:
		cropsId = "graphics/potato.png";
		GtSp.setTextureRect(seed);
		break;
	case CropsType::Garlic:
		cropsId = "graphics/garlic.png";
		GtSp.setTextureRect(seed);
		break;
	}
}



void Crops::Setidx(int index)
{
	idx = index;
}

int Crops::Getidx()
{
	return idx;
}
Crops::CropsType Crops::GetCropsType()
{
	return ctype;
}
void Crops::SetTimeMoneyUi(TimeMoneyUi* time)
{
	tm = time;
}

TimeMoneyUi* Crops::GetTimeMoneyUi()
{
	return tm;
}
