#include "stdafx.h"
#include "QuickBar.h"

QuickBar::QuickBar(const std::string& texId, const std::string& name)
	:GameObject(name)
	,texId(texId)
{
}

void QuickBar::Init()
{
	quickBar.setSize({570 , 100});
	
	outLine.setFillColor(sf::Color::Transparent);
	outLine.setOutlineColor(sf::Color::Red);
	outLine.setOutlineThickness(2.f);

	for (int i = 0; i < 12; i++) {
		quickBar_Slots.push_back(new ItemSlot(INVEN_IMG_PATH"ItemSlot.png"));
		quickBar_Slots[i]->Init();
	}
}

void QuickBar::Release()
{
	for (auto slot : quickBar_Slots) {
		delete slot;
	}

	quickBar_Slots.clear();
}

void QuickBar::Reset()
{
	for (auto slot : quickBar_Slots) {
		slot->Reset();
	}
	quickBar.setTexture(&TEXTURE_MGR.Get(texId));
	Utils::SetOrigin(quickBar, Origins::MC);
	quickBar.setPosition({ 1920 * 0.25f , 1080 - 300.f });
}

void QuickBar::Update(float dt)
{
	
}

void QuickBar::Draw(sf::RenderWindow& window)
{
	window.draw(quickBar);
	for (auto slot : quickBar_Slots) {
		slot->Draw(window);
	}
}
