#include "stdafx.h"
#include "SceneAnimator.h"
#include "Button.h"
#include "InputText.h"
#include <Windows.h>
#include <CommDlg.h>
#include <string>
#include <codecvt> // for wstring_convert
#include <locale>  // for codecvt_utf8
#include <iostream>
#include <filesystem>
#include <string>

std::string OpenFileDialog() {
    OPENFILENAMEA  ofn;
    char szFileName[MAX_PATH] = "";  // char 배열
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

std::string SaveFileDialog(const std::string saveData) {
    OPENFILENAMEA ofn;       // common dialog box structure
    char szFile[260];        // buffer for file name
    HANDLE hFile = NULL;     // file handle

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;  // If NULL, the dialog has no owner
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0'; // Make sure it's empty
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "*.csv";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

    if (GetSaveFileNameA(&ofn) == TRUE) {
        hFile = CreateFileA(ofn.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        if (hFile != INVALID_HANDLE_VALUE) {
            // Write example text
            std::string data = saveData; // ANSI 텍스트. 한글은 깨질 수 있음.
            DWORD bytesWritten;
            WriteFile(hFile, data.c_str(), data.length(), &bytesWritten, NULL);
            CloseHandle(hFile);
        }
        else {
            std::cerr << "파일 생성 실패" << std::endl;
        }
    }
    else {
        std::cout << "파일 선택 취소" << std::endl;
    }
    return "";
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

    inputText = new InputText(FONT_PATH"DOSGothic.ttf");
    inputText->SetTextColor(sf::Color::Black);
    inputText->SetPosition({20 , 20});

    loadBNT = new Button(FONT_PATH"DOSGothic.ttf");
    loadBNT->sortingLayer = SortingLayers::UI;
    loadBNT->onClickFunc = [this]() {
        filePath = OpenFileDialog();
        texture.loadFromFile(filePath);
        TCHAR filePath[MAX_PATH];
        GetModuleFileName(NULL, filePath, MAX_PATH);
        std::wcout << L"실행 파일 경로: " << filePath << std::endl;
      

        preview.setTexture(texture, true);
        sprite.setTexture(texture, true);
    };

    saveBNT = new Button(FONT_PATH"DOSGothic.ttf");
    saveBNT->sortingLayer = SortingLayers::UI;
    saveBNT->onClickFunc = [this]() {
        std::vector<std::string> newPath = Utils::Split(filePath, (char)92);
        int idx = Utils::FindStringIdx(newPath, "graphics");

        if (sprite.getTexture() != nullptr && rect.size() > 0 && !inputText->GetString().empty() && idx != -1) {
            std::string saveData;
            saveData = "ID,FPS,LoopType (0: Single. 1: Loop)\n"
                "" + inputText->GetString() + ",10,1\n\n"
                "TEXTURE ID,LEFT,TOP,WIDTH,HEIGHT,FLIPX(0:Fale. 1:True)\n";
          
            for (int i = 0; i < rect.size(); i++) {
                sf::FloatRect rectSize = rect[i]->getGlobalBounds();
                saveData += newPath[idx] + "/" + newPath[idx + 1] + "," + std::to_string(rectSize.left) + "," + std::to_string(rectSize.top) + "," + std::to_string(rectSize.width) + "," + std::to_string(rectSize.height)+"," + "0" + "\n";
            }
            SaveFileDialog(saveData);
        }
    };

    rightBackGround.setPosition({ FRAMEWORK.GetWindowSizeF().x / 2 , 0 });
    rightBackGround.setSize({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y });
    rightBackGround.setFillColor(sf::Color(187, 187, 187));
    
    preview.setPosition(FRAMEWORK.GetWindowSizeF().x / 1.35f  , 300.f);

    AddGameObject(loadBNT);
    AddGameObject(saveBNT);
    AddGameObject(inputText);

    Scene::Init();
}

void SceneAnimator::Enter()
{
    Scene::Enter();

    loadBNT->SetString("Load Sprite");
    loadBNT->SetTextColor(sf::Color::Black);
    loadBNT->SetPosition({ 1920 / 2 , 1080 / 2 });

    saveBNT->SetString("Save csv");
    saveBNT->SetTextColor(sf::Color::Black);
    saveBNT->SetPosition({ 1920 / 2 - 150.f, 1080 / 2 });
}

void SceneAnimator::Update(float dt)
{
    Scene::Update(dt);
    DrawRectangle();
    DragToMoveScreen(dt);
    UndoRectangle();
    PreviewAnimation(dt);

    if (InputMgr::GetKeyDown(sf::Keyboard::Enter)) {
        SCENE_MGR.ChangeScene(SceneIds::AnimationTest);
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

        if (curIndex >= rect.size()) curIndex = 0;

        sf::IntRect bounds = (sf::IntRect)rect[curIndex++]->getGlobalBounds();
        preview.setTextureRect(bounds);
    }
}

