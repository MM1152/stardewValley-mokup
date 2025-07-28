#include "stdafx.h"
#include "SceneAnimationTest.h"
#include "Player.h"
SceneAnimationTest::SceneAnimationTest()
	:Scene(SceneIds::AnimationTest)
{
}
void SceneAnimationTest::Init()
{
	texIds.push_back(GRAPHICS_PATH"farmer_base.png");
	texIds.push_back(GRAPHICS_PATH"hats.png");
	/*aniIds.push_back(ANIMATION_PATH"playerleft.csv");
	aniIds.push_back(ANIMATION_PATH"playerforward.csv");
	aniIds.push_back(ANIMATION_PATH"playerbackward.csv");
	aniIds.push_back(ANIMATION_PATH"playerlefthand.csv");
	aniIds.push_back(ANIMATION_PATH"playerforwardhand.csv");
	aniIds.push_back(ANIMATION_PATH"playerbackwardhand.csv");*/

	player = new Player();

	AddGameObject(player);
	Scene::Init();
}

void SceneAnimationTest::Enter()
{
	worldView.setSize({ FRAMEWORK.GetWindowSizeF().x / 4 , FRAMEWORK.GetWindowSizeF().y /4});
	worldView.setCenter({ 0,0 });
	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter({ 0,0 });
	Scene::Enter();
}

void SceneAnimationTest::Exit()
{
	Scene::Exit();
}

void SceneAnimationTest::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter)) {
		SCENE_MGR.ChangeScene(SceneIds::Animator);
	}

	Scene::Update(dt);
}

void SceneAnimationTest::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
