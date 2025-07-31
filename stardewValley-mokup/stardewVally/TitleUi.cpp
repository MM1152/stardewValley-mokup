#include "stdafx.h"
#include "TitleUi.h"
#include "Button.h"

TitleUi::TitleUi(const std::string& name)
	: GameObject(name)
{
}

void TitleUi::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	title.setPosition(pos);
}

void TitleUi::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	title.setRotation(rot);
}

void TitleUi::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	title.setScale(s);
}

void TitleUi::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	title.setOrigin(o);
}

void TitleUi::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(title, preset);
	}
}

void TitleUi::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = 0;
	title.setOrigin({ 600.f, 300.f });
	title.setScale({ 1.08f, 1.2f });
	title.setPosition({ 0.f, 0.f });
	

	Button* startbnt = new Button("fonts/Stardew_Valley.ttf", "graphics/mainchoice.png", "start");
	startbnt->SetOrigin({ 600.f,300.f });
	startbnt->SetScale({ 1.08f, 1.2f });
	startbnt->SetPosition({ 0.f, 0.f });
	//startbnt->SetTextureRect({ 0, 0, 348, 121 });
	startbnt->Reset();
	startbnt->onClickFunc = [this]() {
		SCENE_MGR.ChangeScene(SceneIds::Test);
		};
	startbnt->sortingLayer = SortingLayers::UI;
}

void TitleUi::Release()
{
}

void TitleUi::Reset()
{
	title.setTexture(TEXTURE_MGR.Get("graphics/main.bmp"));	
}

void TitleUi::Update(float dt)
{
}

void TitleUi::Draw(sf::RenderWindow& window)
{
	window.draw(title);
	
}
