#pragma once
#include "InGameItem.h"
#include "Animator.h"
class Pick : public InGameItem
{
private:
	bool startAnimation = false;
	Animator hoeAni;

	sf::Vector2i prevDir;

	sf::Vector2f plusPos = { 0,0 };
public:
	Pick() = default;
	Pick(ItemInfo info);
	~Pick() override = default;

	void Update(float dt) override;
	void Reset() override;
	void UseItem() override;
	void Draw(sf::RenderWindow& window) override;
	void StartAnimation(sf::Vector2i lookDir);
};

