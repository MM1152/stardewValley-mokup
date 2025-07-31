#include "stdafx.h"
#include "TitleUi.h"
#include "Button.h"
#include "SceneTitle.h"

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
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
	title.setScale({ 1.08f, 1.2f });
	title.setPosition({ 0.f, 0.f });

	yes_or_no.setScale({ 1.3f, 1.3f });
	yes_or_no.setPosition({ 375.f, 200.f });

	tool.setScale({ 1.3f, 1.3f });
	tool.setPosition({ 375.f, 200.f });

	startbnt = new Button("fonts/Stardew_Valley.ttf", "title/mainchoice.png", "start");
	startbnt->SetOrigin(Origins::MC);
	startbnt->SetScale({ 1.05f, 4.8f });
	startbnt->SetPosition({ 243.f, 555.f });
	startbnt->SetTextureRect({ 0, 121, 174, 121 });
	startbnt->onClickFunc = [this]() {
		if (!exitview && !toolview)
		SCENE_MGR.ChangeScene(SceneIds::Test);
		};

	loadbnt = new Button("fonts/Stardew_Valley.ttf", "title/mainchoice.png", "load");
	loadbnt->SetOrigin(Origins::MC);
	loadbnt->SetScale({ 1.05f, 4.8f });
	loadbnt->SetPosition({ 449.f, 555.f });
	loadbnt->SetTextureRect({ 174, 121, 174, 121 });
	loadbnt->onClickFunc = [this]() {
		if (!exitview && !toolview)
		std::cout << "저장된 파일이 없습니다." << std::endl;
		};

	toolbnt = new Button("fonts/Stardew_Valley.ttf", "title/mainchoice.png", "toolbnt");
	toolbnt->SetOrigin(Origins::MC);
	toolbnt->SetScale({ 1.05f, 4.8f });
	toolbnt->SetPosition({ 655.f, 555.f });
	toolbnt->SetTextureRect({ 348, 121, 174, 121 });
	toolbnt->onClickFunc = [this]() {
		if (!exitview && !toolview)
			toolview = true;
		};

	exitbnt = new Button("fonts/Stardew_Valley.ttf", "title/mainchoice.png", "exit");
	exitbnt->SetOrigin(Origins::MC);
	exitbnt->SetScale({ 1.05f, 4.8f });
	exitbnt->SetPosition({ 863.f, 555.f });
	exitbnt->SetTextureRect({ 522, 121, 174, 121 });
	exitbnt->onClickFunc = [this]() {
		if (!exitview && !toolview)
		exitview = true;
		};


	yesbnt = new Button("fonts/Stardew_Valley.ttf", "title/yes.png", "yes");
	yesbnt->SetOrigin(Origins::MC);
	yesbnt->SetScale({ 1.1f, 2.33f });
	yesbnt->SetPosition({ 462.f, 415.f });
	yesbnt->onClickFunc = [this]() {
		if (exitview)
		{
			FRAMEWORK.GetWindow().close();
		}
		};

	nobnt = new Button("fonts/Stardew_Valley.ttf", "title/no.png", "no");
	nobnt->SetOrigin(Origins::MC);
	nobnt->SetScale({ 1.1f, 2.33f });
	nobnt->SetPosition({ 679.f, 415.f });
	nobnt->onClickFunc = [this]() {
		if (exitview)
		{
			exitview = false;
		}
		};

	maptoolbnt = new Button("fonts/Stardew_Valley.ttf", "title/maptool.png", "maptoolbnt");
	maptoolbnt->SetOrigin(Origins::MC);
	maptoolbnt->SetScale({ 1.1f, 2.33f });
	maptoolbnt->SetPosition({ 462.f, 415.f });
	maptoolbnt->onClickFunc = [this]() {
		if (toolview)
		{
			SCENE_MGR.ChangeScene(SceneIds::Maptool);
		}
		};
	animatorbnt = new Button("fonts/Stardew_Valley.ttf", "title/animator.png", "animatorbnt");
	animatorbnt->SetOrigin(Origins::MC);
	animatorbnt->SetScale({ 1.1f, 2.33f });
	animatorbnt->SetPosition({ 679.f, 415.f });
	animatorbnt->onClickFunc = [this]() {
		if (toolview)
		{
			SCENE_MGR.ChangeScene(SceneIds::Animator);
		}
		};
}

void TitleUi::Release()
{
}

void TitleUi::Reset()
{
	title.setTexture(TEXTURE_MGR.Get("title/main.bmp"));
	yes_or_no.setTexture(TEXTURE_MGR.Get("title/yes_or_no.png"));
	tool.setTexture(TEXTURE_MGR.Get("title/choicetool.png"));
	startbnt->Reset();
	startbnt->SetString("            ");
	loadbnt->Reset();
	loadbnt->SetString("            ");
	toolbnt->Reset();
	toolbnt->SetString("            ");
	exitbnt->Reset();
	exitbnt->SetString("            ");

	yesbnt->Reset();
	yesbnt->SetString("         ");
	nobnt->Reset();
	nobnt->SetString("         ");

	maptoolbnt->Reset();
	maptoolbnt->SetString("         ");
	animatorbnt->Reset();
	animatorbnt->SetString("         ");
}

void TitleUi::Update(float dt)
{
	startbnt->Update(dt);
	loadbnt->Update(dt);
	toolbnt->Update(dt);
	exitbnt->Update(dt);

	yesbnt->Update(dt);
	nobnt->Update(dt);

	maptoolbnt->Update(dt);
	animatorbnt->Update(dt);

	if (exitview)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			exitview = false;
		}
	}
	if (toolview)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			toolview = false;
		}
	}
}

void TitleUi::Draw(sf::RenderWindow& window)
{
	window.draw(title);
	startbnt->Draw(window);
	loadbnt->Draw(window);
	toolbnt->Draw(window);
	exitbnt->Draw(window);

	if (exitview)
	{
		window.draw(yes_or_no);
		yesbnt->Draw(window);
		nobnt->Draw(window);
	}

	if (toolview)
	{
		window.draw(tool);
		maptoolbnt->Draw(window);
		animatorbnt->Draw(window);
	}
}
