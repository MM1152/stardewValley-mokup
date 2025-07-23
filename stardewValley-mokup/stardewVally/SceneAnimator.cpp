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

    Button* includeBNT = new Button(FONT_PATH"DOSGothic.ttf");
    includeBNT->onClickFunc = [this]() {
        filePath = OpenFileDialog();
    };
    AddGameObject(includeBNT);
    includeBNT->SetPosition({ 1920 / 2 , 1080 / 2 });
    Scene::Init();
}

void SceneAnimator::Enter()
{
    Scene::Enter();
}

void SceneAnimator::Update(float dt)
{
    Scene::Update(dt);
}

