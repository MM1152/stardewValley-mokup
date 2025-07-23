#include "stdafx.h"
#include "SceneAnimator.h"
#include "Button.h"
#include <Windows.h>
#include <CommDlg.h>
#include <iostream>
#include <string>
#include <codecvt> // for wstring_convert
#include <locale>  // for codecvt_utf8

std::string OpenFileDialog() {
    OPENFILENAMEA  ofn;
    char szFileName[MAX_PATH] = "";  // char ¹è¿­
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&ofn)) {
        std::cout << "true" << std::endl;
        return szFileName;
    }
    return "FAIL TO LOAD";
}

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

    loadBNT = new Button(FONT_PATH"DOSGothic.ttf");
    loadBNT->sortingLayer = SortingLayers::UI;
    loadBNT->onClickFunc = [this]() {
        filePath = OpenFileDialog();
        texture.loadFromFile(filePath);

        preview.setTexture(texture, true);
        sprite.setTexture(texture, true);
    };

    rightBackGround.setPosition({ FRAMEWORK.GetWindowSizeF().x / 2 , 0 });
    rightBackGround.setSize({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y });
    rightBackGround.setFillColor(sf::Color(187, 187, 187));
    
    preview.setPosition(FRAMEWORK.GetWindowSizeF().x / 1.35f  , 300.f);

    AddGameObject(loadBNT);

    Scene::Init();
}

void SceneAnimator::Enter()
{
    Scene::Enter();

    loadBNT->SetString("Load\nSprite");
    loadBNT->SetTextColor(sf::Color::Black);
    loadBNT->SetPosition({ 1920 / 2 , 1080 / 2 });
}

void SceneAnimator::Update(float dt)
{
    Scene::Update(dt);
    DrawRectangle();
    DragToMoveScreen(dt);
    UndoRectangle();
    PreviewAnimation(dt);
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
}

void SceneAnimator::DrawRectangle()
{
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
        rect[rect.size() - 1]->setSize({ScreenToWorld(InputMgr::GetMousePosition()).x - rectStartPos.x,ScreenToWorld(InputMgr::GetMousePosition()).y - rectStartPos.y });
    }
    if (InputMgr::GetMouseButtonUp(sf::Mouse::Left)) {
        if ((int)rect[rect.size() - 1]->getSize().x == 0 || (int)rect[rect.size() - 1]->getSize().y == 0 ) {
            delete rect[rect.size() - 1];
            rect.pop_back();
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
        worldView.setCenter({ worldView.getCenter() - ((sf::Vector2f)InputMgr::GetMousePosition() - dragStartPos) * dt * 5.f});
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

        sf::IntRect bounds = (sf::IntRect)rect[curIndex++]->getGlobalBounds();
        preview.setTextureRect(bounds);

        if (curIndex >= rect.size()) curIndex = 0;
    }
}

