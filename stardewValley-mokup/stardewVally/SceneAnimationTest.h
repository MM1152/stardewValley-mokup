#pragma once
#include "Scene.h"

class Player;
class SceneAnimationTest : public Scene
{
private:
	Player* player;
public:
	SceneAnimationTest();
	~SceneAnimationTest() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

