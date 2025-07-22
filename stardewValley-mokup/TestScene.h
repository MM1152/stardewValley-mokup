#pragma once
#include "Scene.h"
class TestScene : public Scene
{
	sf::CircleShape shape;
public :
	TestScene();

	void Init() override;
	void Draw(sf::RenderWindow& window) override;
};

