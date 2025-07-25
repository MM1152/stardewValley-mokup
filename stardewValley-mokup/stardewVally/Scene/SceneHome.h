#pragma once
#include "Scene.h"
class SceneHome : public Scene
{
protected:
	sf::Sprite home;
	std::string homeId = "graphics/myhome.bmp";


public:
	SceneHome();
	~SceneHome() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;


	void Draw(sf::RenderWindow& window) override;
};

