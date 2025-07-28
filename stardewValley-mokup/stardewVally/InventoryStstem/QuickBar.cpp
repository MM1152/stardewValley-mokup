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
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	quickBar.setSize({825 , 90});
	
	outLine.setFillColor(sf::Color::Transparent);
	outLine.setOutlineColor(sf::Color::Red);
	outLine.setOutlineThickness(4.f);
	

	for (int i = 0; i < 12; i++) {
		quickBar_Slots.push_back(new QuickBar_Slot(INVEN_IMG_PATH"ItemSlot.png"));
		quickBar_Slots[i]->Init();
	}

	outLine.setSize({53 , 53});
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
	quickBar.setPosition({ FRAMEWORK.GetWindowSizeF().x / 2 - 400.f , FRAMEWORK.GetWindowSizeF().y - 100.f });
	
	for (int i = 0; i < quickBar_Slots.size(); i++) {
		quickBar_Slots[i]->Reset();
		quickBar_Slots[i]->SetPosition({ quickBar.getPosition().x + (i * 65) + 20.f, quickBar.getPosition().y + 13.f});
	}
	
	outLine.setPosition(quickBar_Slots[0]->GetPosition().x + 9.f, 
						quickBar_Slots[0]->GetPosition().y + 6.f);
}

void QuickBar::Update(float dt)
{
	if ((int)InputMgr::GetInputKey() >= 27 && (int)InputMgr::GetInputKey() <= 35) {
		outLine.setPosition(quickBar_Slots[(int)InputMgr::GetInputKey() - 27]->GetPosition().x + 9.f,
							quickBar_Slots[(int)InputMgr::GetInputKey() - 27]->GetPosition().y + 6.f);
		idx = (int)InputMgr::GetInputKey() - 27;
	}
	if (InputMgr::GetInputKey() == sf::Keyboard::Key::Num0) {
		outLine.setPosition(quickBar_Slots[9]->GetPosition().x + 9.f,
			quickBar_Slots[9]->GetPosition().y + 6.f);
		idx = 9;
	}
	if ((int)InputMgr::GetInputKey() == 56) {
		outLine.setPosition(quickBar_Slots[10]->GetPosition().x + 9.f, 
			quickBar_Slots[10]->GetPosition().y + 6.f);
		idx = 10;
	}
	if ((int)InputMgr::GetInputKey() == 55) {
		outLine.setPosition(quickBar_Slots[11]->GetPosition().x + 9.f, 
			quickBar_Slots[11]->GetPosition().y + 6.f);
		idx = 11;
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

Item* QuickBar::GetItem()
{
	return quickBar_Slots[idx]->GetItem();
}


