#include "stdafx.h"
#include "SceneAnimator.h"
#include "Button.h"
#include "InputText.h"
#include <Windows.h>

SceneAnimator::SceneAnimator()
	:Scene(SceneIds::Animator)
{
}

void SceneAnimator::Init()
{
	worldView.setSize(FRAMEWORK.GetWindowSizeF());
	worldView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });
	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });

	fontIds.push_back(FONT_PATH"DOSGothic.ttf");
	texIds.push_back("title/save_csv.png");
	texIds.push_back("title/load_sprite.png");
	texIds.push_back("title/gotitle.png");
	texIds.push_back("title/yes.png");
	texIds.push_back("title/no.png");
	texIds.push_back("title/gotitleyes_or_no.png");

	gtyes_or_no.setScale({ 1.3f, 1.3f });
	gtyes_or_no.setPosition({ 375.f, 200.f });

	inputText = new InputText(FONT_PATH"DOSGothic.ttf");
	inputText->SetTextColor(sf::Color::Black);
	inputText->SetPosition({ 20 , 20 });

	loadBNT = new Button(FONT_PATH"DOSGothic.ttf", "title/load_sprite.png");
	loadBNT->sortingLayer = SortingLayers::UI;
	loadBNT->onClickFunc = [this]() {
		if (!gotitleView)
		{
			filePath = Utils::OpenFileDialog();
			texture.loadFromFile(filePath);
			TCHAR filePath[MAX_PATH];
			GetModuleFileName(NULL, filePath, MAX_PATH);
			preview.setTexture(texture, true);
			sprite.setTexture(texture, true);
		}
		};

	saveBNT = new Button(FONT_PATH"DOSGothic.ttf", "title/save_csv.png");
	saveBNT->sortingLayer = SortingLayers::UI;
	saveBNT->onClickFunc = [this]() {
		if (!gotitleView)
		{
			std::vector<std::string> newPath = Utils::Split(filePath, (char)92);
			int idx = Utils::FindStringIdx(newPath, "graphics");

			if (sprite.getTexture() != nullptr && rect.size() > 0 && !inputText->GetString().empty() && idx != -1) {
				std::string saveData;
				saveData = "ID,FPS,LoopType (0: Single. 1: Loop)\n"
					"" + inputText->GetString() + ",10,1\n\n"
					"TEXTURE ID,LEFT,TOP,WIDTH,HEIGHT,FLIPX(0:Fale. 1:True)\n";

				for (int i = 0; i < rect.size(); i++) {
					sf::FloatRect rectSize = rect[i]->getGlobalBounds();
					saveData += newPath[idx] + "/" + newPath[idx + 1] + "," + std::to_string(rectSize.left) + "," + std::to_string(rectSize.top) + "," + std::to_string(rectSize.width) + "," + std::to_string(rectSize.height) + "," + "0" + "\n";
				}
				Utils::SaveFileDialog(saveData);
			}
		}
		};

	gttitlebnt = new Button(FONT_PATH"DOSGothic.ttf", "title/gotitle.png");

	gttitlebnt->onClickFunc = [this]() {
		if (!gotitleView)
		{
			gotitleView = true;
		}
		};
	gttitlebnt->sortingLayer = SortingLayers::UI;

	gtyesbnt = new Button("fonts/DOSGothic.ttf", "title/yes.png", "yes");
	gtyesbnt->SetString("         ");
	gtyesbnt->SetScale({ 1.1f, 2.33f });
	gtyesbnt->SetPosition({ 462.f, 415.f });
	gtyesbnt->onClickFunc = [this]() {
		if (gotitleView)
		{
			gotitleView = false;
			SCENE_MGR.ChangeScene(SceneIds::Title);
		}
		};
	gtyesbnt->sortingLayer = SortingLayers::UI;

	gtnobnt = new Button("fonts/DOSGothic.ttf", "title/no.png", "no");
	gtnobnt->SetString("         ");
	gtnobnt->SetScale({ 1.1f, 2.33f });
	gtnobnt->SetPosition({ 679.f, 415.f });
	gtnobnt->onClickFunc = [this]() {
		if (gotitleView)
		{
			gotitleView = false;
		}
		};
	gtnobnt->sortingLayer = SortingLayers::UI;

	rightBackGround.setPosition({ FRAMEWORK.GetWindowSizeF().x / 2 , 0 });
	rightBackGround.setSize({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y });
	rightBackGround.setFillColor(sf::Color(187, 187, 187));

	preview.setPosition(FRAMEWORK.GetWindowSizeF().x / 1.35f, 300.f);

	AddGameObject(loadBNT);
	AddGameObject(saveBNT);
	AddGameObject(inputText);

	AddGameObject(gttitlebnt);
	AddGameObject(gtyesbnt);
	AddGameObject(gtnobnt);


	Scene::Init();
}

void SceneAnimator::Enter()
{
	Scene::Enter();

	loadBNT->SetString("        ");
	loadBNT->SetScale({ 1.f, 1.4f });
	loadBNT->SetPosition({ 1280 / 2 + 100, 1080 / 2 });

	saveBNT->SetString("        ");
	saveBNT->SetScale({ 1.f, 1.4f });
	saveBNT->SetPosition({ 1280 / 2 + 250.f, 1080 / 2 });

	gttitlebnt->SetString("        ");
	gttitlebnt->SetScale({ 1.f, 1.4f });
	gttitlebnt->SetPosition({ 1280 / 2 + 400.f, 1080 / 2 });

	gtyes_or_no.setTexture(TEXTURE_MGR.Get("title/gotitleyes_or_no.png"));
}

void SceneAnimator::Update(float dt)
{
	if (!gotitleView)
	{
		gtyesbnt->SetActive(false);
		gtnobnt->SetActive(false);
	}
	else
	{
		gtyesbnt->SetActive(true);
		gtnobnt->SetActive(true);
	}
	Scene::Update(dt);
	DrawRectangle();
	DragToMoveScreen(dt);
	UndoRectangle();
	PreviewAnimation(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		gotitleView = false;
	}
}

void SceneAnimator::Draw(sf::RenderWindow& window)
{
	window.setView(worldView);
	for (auto rec : rect) {
		window.draw(*rec);
	}
	if (sprite.getTexture()) {
		window.draw(sprite);
	}
	window.setView(uiView);
	window.draw(rightBackGround);
	window.draw(preview);
	Scene::Draw(window);

	if (gotitleView)
	{
		window.draw(gtyes_or_no);
		gtyesbnt->Draw(window);
		gtnobnt->Draw(window);
	}
}

void SceneAnimator::DrawRectangle()
{
	if (filePath.empty()) return;
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left)) {
		startDrawRect = true;
		rectStartPos = ScreenToWorld(InputMgr::GetMousePosition());
		rect.push_back(new sf::RectangleShape());
		rect[rect.size() - 1]->setPosition(rectStartPos);
		rect[rect.size() - 1]->setFillColor(sf::Color::Transparent);
		rect[rect.size() - 1]->setOutlineColor(sf::Color::Green);
		rect[rect.size() - 1]->setOutlineThickness(2.f);
	}
	if (InputMgr::GetMouseButton(sf::Mouse::Left) && startDrawRect) {
		rect[rect.size() - 1]->setSize({ ScreenToWorld(InputMgr::GetMousePosition()).x - rectStartPos.x,ScreenToWorld(InputMgr::GetMousePosition()).y - rectStartPos.y });
	}
	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left) && startDrawRect) {
		if ((int)rect[rect.size() - 1]->getSize().x == 0 || (int)rect[rect.size() - 1]->getSize().y == 0) {
			delete rect[rect.size() - 1];
			rect.pop_back();
		}
		else {
			std::cout << rect[rect.size() - 1]->getGlobalBounds().left << ", " << rect[rect.size() - 1]->getGlobalBounds().top << ", " << rect[rect.size() - 1]->getGlobalBounds().width << ", " << rect[rect.size() - 1]->getGlobalBounds().height << std::endl;
		}
		startDrawRect = false;


	}

}

void SceneAnimator::DragToMoveScreen(float dt)
{
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right)) {
		dragStartPos = (sf::Vector2f)InputMgr::GetMousePosition();
	}
	if (InputMgr::GetMouseButton(sf::Mouse::Right)) {
		worldView.setCenter({ worldView.getCenter() - ((sf::Vector2f)InputMgr::GetMousePosition() - dragStartPos) * dt * 5.f });
	}
	if (InputMgr::GetMouseWheel() != 0) {
		float heightPer = worldView.getSize().y / worldView.getSize().x;
		worldView.setSize({ worldView.getSize().x - 50.f * InputMgr::GetMouseWheel(),worldView.getSize().y - (50.f * InputMgr::GetMouseWheel() * heightPer) });
	}
}

void SceneAnimator::UndoRectangle()
{
	if (InputMgr::GetKey(sf::Keyboard::LControl) && InputMgr::GetKeyDown(sf::Keyboard::Z)) {
		if (rect.size() > 0) {
			delete rect[rect.size() - 1];
			rect.pop_back();
		}
	}
}

void SceneAnimator::PreviewAnimation(float dt)
{
	timer -= dt;
	if (timer < 0 && rect.size() > 0) {
		timer = rect.size() / previewFrame;

		if (curIndex >= rect.size()) curIndex = 0;

		sf::IntRect bounds = (sf::IntRect)rect[curIndex++]->getGlobalBounds();
		preview.setTextureRect(bounds);
	}
}

