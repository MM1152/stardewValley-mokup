#pragma once
#include "InGameItem.h"
#include "Item.h"
#include "Animator.h"
class Hoe : public InGameItem
{
private:
	bool startAnimation = false;
	Animator hoeAni;

	sf::Vector2i prevDir;
public:
	Hoe() = default;
	Hoe(ItemInfo info);
	~Hoe() override = default;

	void Update(float dt) override;
	void Reset() override;
	void UseItem() override;
	void Draw(sf::RenderWindow& window) override;
	void StartAnimation(sf::Vector2i lookDir);
};

