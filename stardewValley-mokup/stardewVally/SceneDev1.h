#pragma once
#include "Scene.h"

class TextGo;
class Inventory;
class QuickBar;
class SceneDev1 : public Scene
{
protected:
	Inventory* inven;
	QuickBar* quickBar;
	/*Item* item = nullptr;
	Item copyItem;*/
public:
	SceneDev1();
	~SceneDev1() override;

	void Init() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

