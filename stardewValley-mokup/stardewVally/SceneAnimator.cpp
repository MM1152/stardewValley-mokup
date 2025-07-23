#include "stdafx.h"
#include "SceneAnimator.h"

SceneAnimator::SceneAnimator()
	:Scene(SceneIds::Animator)
{
}

void SceneAnimator::Init()
{
	Scene::Init();
}

void SceneAnimator::Release()
{
	Scene::Release();
}

void SceneAnimator::Enter()
{
	Scene::Enter();
}

void SceneAnimator::Exit()
{
	Scene::Exit();
}

void SceneAnimator::Update(float dt)
{
	Scene::Update(dt);
}

void SceneAnimator::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
