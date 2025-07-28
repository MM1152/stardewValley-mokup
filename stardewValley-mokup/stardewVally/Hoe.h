#pragma once
#include "Item.h"
#include "Animator.h"

class Player;
class Hoe : public Item
{
private:
	bool playAnimation = false;
	Animator hoeAni;
	
public:
	Hoe(ItemInfo iteminfo);
	Hoe() = default;
	~Hoe() override = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	const std::string UseItem() override;
};

