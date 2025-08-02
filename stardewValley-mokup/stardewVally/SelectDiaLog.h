#pragma once
#include "GameObject.h"
#include "Button.h"
class SelectDiaLog : public GameObject
{
private:
	sf::Sprite backGround;
	Button* topButton;
	Button* downButton;

	sf::Vector2f buttonPadding = { 10, 7 };
	int idx = -1;
public:
	std::function<void(int)> returnIdxFunc;

	SelectDiaLog();
	~SelectDiaLog() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Show();
};

