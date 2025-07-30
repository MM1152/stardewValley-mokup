#pragma once
#include "GameObject.h"

class Inventory;
class Player;
class Crops;

class DropItem :
    public GameObject
{
protected:
	sf::Sprite dropitem;
	std::string dropitemId;
	/*DropItemType di = DropItemType::Crops;*/

	Inventory* inventory = nullptr;
	Player* player = nullptr;
	Crops* crops = nullptr;

	sf::Vector2f curpos = { -1.f, -1.f };


public:
	DropItem(const std::string& name = "",const std::string& Id = "");
	virtual ~DropItem() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetInventory(Inventory* inv) { inventory = inv; };
	void SetPlayer(Player* p) { player = p; };
	void SetCrops(Crops* c) { crops = c; };

	void SetCurrentPosition(sf::Vector2f pos) { curpos = pos; };
	sf::Vector2f GetCurrentPosition() { return curpos; };

};

