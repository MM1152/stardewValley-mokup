#include "stdafx.h"
#include "Hoe.h"
#include "Player.h"
Hoe::Hoe(ItemInfo iteminfo)
	:Item(iteminfo)
{
}

void Hoe::Init()
{
	hoeAni.SetTarget(&itemSp);

	hoeAni.AddEvent("hoefront", 4 ,[this]() {
		playAnimation = false;
	});
	hoeAni.AddEvent("hoeback", 4, [this]() {
		playAnimation = false;
	});
}

void Hoe::Reset()
{
	Item::Reset();
	playAnimation = false;
}


void Hoe::Update(float dt)
{
	if (playAnimation) {
		
	}
}

void Hoe::Draw(sf::RenderWindow& window)
{
	window.draw(itemSp);
}

const std::string Hoe::UseItem()
{
	playAnimation = true;
	return "";
}
