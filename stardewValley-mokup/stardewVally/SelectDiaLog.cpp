#include "stdafx.h"
#include "SelectDiaLog.h"

SelectDiaLog::SelectDiaLog()
{
	sortingLayer = SortingLayers::UI;
}

void SelectDiaLog::Init()
{
	topButton = new Button(FONT_PATH"SDMiSaeng.ttf" , GRAPHICS_PATH"shop_bg.png");
	downButton = new Button(FONT_PATH"SDMiSaeng.ttf" , GRAPHICS_PATH"shop_bg.png");

	topButton->SetTextColor(sf::Color::Black);
	downButton->SetTextColor(sf::Color::Black);
}

void SelectDiaLog::Release()
{
	topButton->Init();
	downButton->Init();
}

void SelectDiaLog::Reset()
{
	TEXTURE_MGR.Load(GRAPHICS_PATH"shop_bg.png");
	FONT_MGR.Load(FONT_PATH"SDMiSaeng.ttf");

	backGround.setTexture(TEXTURE_MGR.Get(GRAPHICS_PATH"shop_bg.png"));
	backGround.setScale({1 , 0.3f});

	topButton->Reset();
	downButton->Reset();

	topButton->SetString("                                           Sleep");
	downButton->SetString("                                       Not Sleep");

	topButton->SetPosition(backGround.getPosition() + buttonPadding);
	downButton->SetPosition({ backGround.getPosition().x + buttonPadding.x , backGround.getPosition().y + buttonPadding.y + 40.f});
}

void SelectDiaLog::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Up)) {
		idx = 1;
		topButton->SetButtonColor(sf::Color(210, 180, 140));
		downButton->SetButtonColor(sf::Color::White);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Down)) {
		idx = 0;
		downButton->SetButtonColor(sf::Color(210, 180, 140));
		topButton->SetButtonColor(sf::Color::White);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter) && idx != -1) {
		if (returnIdxFunc) {
			returnIdxFunc(idx);
			topButton->SetButtonColor(sf::Color::White);
			downButton->SetButtonColor(sf::Color::White);
			SetActive(false);
		}
	}
}

void SelectDiaLog::Draw(sf::RenderWindow& window)
{
	window.draw(backGround);
	topButton->Draw(window);
	downButton->Draw(window);
}

void SelectDiaLog::Show()
{
	SetActive(true);
	idx = -1;
}
