#include "stdafx.h"
#include "QuickBar.h"
#include "Item.h"
QuickBar::QuickBar(const std::string& texId, const std::string& name)
	:GameObject(name)
	,texId(texId)
{
}

void QuickBar::Init()
{
	quickBar.setSize({560 , 80});
	
	outLine.setFillColor(sf::Color::Transparent);
	outLine.setOutlineColor(sf::Color::Red);
	outLine.setOutlineThickness(4.f);
	

	for (int i = 0; i < 12; i++) {
		quickBar_Slots.push_back(new QuickBar_Slot(INVEN_IMG_PATH"ItemSlot.png"));
		quickBar_Slots[i]->Init();
	}

	outLine.setSize({40 , 70});
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
	quickBar.setTexture(&TEXTURE_MGR.Get(texId));
	quickBar.setPosition({ FRAMEWORK.GetWindowSizeF().x * 0.125f , FRAMEWORK.GetWindowSizeF().y - 170.f });
	
	for (int i = 0; i < quickBar_Slots.size(); i++) {
		quickBar_Slots[i]->Reset();
		quickBar_Slots[i]->SetPosition({ quickBar.getPosition().x + (i * 45) + 10.f, quickBar.getPosition().y + 7.f});
	}
	
	outLine.setPosition(quickBar_Slots[0]->GetPosition());
}

void QuickBar::Update(float dt)
{
	if ((int)InputMgr::GetInputKey() >= 27 && (int)InputMgr::GetInputKey() <= 35) {
		outLine.setPosition(quickBar_Slots[(int)InputMgr::GetInputKey() - 27]->GetPosition());
	}

	if (InputMgr::GetInputKey() == sf::Keyboard::Key::Num0) {
		outLine.setPosition(quickBar_Slots[9]->GetPosition());
	}
	if ((int)InputMgr::GetInputKey() == 56) {
		outLine.setPosition(quickBar_Slots[10]->GetPosition());
	}
	if ((int)InputMgr::GetInputKey() == 55) {
		outLine.setPosition(quickBar_Slots[11]->GetPosition());
	}
}

void QuickBar::Draw(sf::RenderWindow& window)
{
	window.draw(quickBar);
	for (auto slot : quickBar_Slots) {
		slot->Draw(window);
	}
	window.draw(outLine);
	
}

void QuickBar::SetItem(Item* item, int idx)
{
	quickBar_Slots[idx]->SetItem(item);
}


