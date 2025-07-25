#pragma once
#include "Collider.h"
#include "stdafx.h"

class NpcMgr;


class Player : public Collider
{
protected:

	sf::Sprite sprite;
	float speed = 100.f;

	int money = 500;
	
	NpcMgr* npcMgr = nullptr;

public:
	void SetActive(bool a) { active = a; };
	void SetPosition(const sf::Vector2f& pos);
	void SetRotation(float rot);
	void SetScale(const sf::Vector2f& s);
	void SetOrigin(const sf::Vector2f& o);
	void SetNpcMgr(NpcMgr* n) { this->npcMgr = n; }

	Player(const std::string name = "Player");
	virtual ~Player() = default;

	void Init();
	void Release();
	void Reset();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	int GetMoney()
	{
		return money;
	}

};