#pragma once
#include "Collider.h"
#include "stdafx.h"

class NpcMgr;
class Inventory;
class Player : public Collider
{
protected:

	sf::Sprite sprite;
	float speed = 100.f;

	int money = 500;
	
	NpcMgr* npcMgr = nullptr;
	Inventory* inventory = nullptr;

public:
	void SetActive(bool a) { active = a; };
	void SetPosition(const sf::Vector2f& pos);
	void SetRotation(float rot);
	void SetScale(const sf::Vector2f& s);
	void SetOrigin(const sf::Vector2f& o);
	void SetOrigin(const Origins originPreset) override;
	void SetNpcMgr(NpcMgr* n) { this->npcMgr = n; }

	Player(const std::string name = "Player");
	virtual ~Player() = default;

	void Init();
	void Release();
	void Reset();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	virtual sf::FloatRect GetLocalBounds() const
	{
		return sprite.getLocalBounds();
	}

	virtual sf::FloatRect GetGlobalBounds() const
	{
		return sprite.getGlobalBounds();
	}
	void SetInventory(Inventory* inven);
	Inventory* GetInventory();

	int GetMoney()
	{
		return money;
	}

	void SetMoney(int m)
	{
		money = m;
	}

};