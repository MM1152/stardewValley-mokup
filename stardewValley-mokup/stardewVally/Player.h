#pragma once
#include "Collider.h"
#include "stdafx.h"

class NpcMgr;
class Inventory;
class TimeMoneyUi;

class Player : public Collider
{
protected:
	//player move
	bool isPlayer = true;
	bool openInven = false;
	bool openShop = false;
	bool fainting = false;

	sf::Sprite sprite;
	float speed = 100.f;

	int money = 500;
	
	NpcMgr* npcMgr = nullptr;
	Inventory* inventory = nullptr;
	TimeMoneyUi* timemoneyui = nullptr;


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

	void SetInventory(Inventory* inven);
	Inventory* GetInventory();

	void SetTimer(TimeMoneyUi* time);
	TimeMoneyUi* GetTimer();
	

	//player move
	void ChangeisPlayer()
	{
		isPlayer = !isPlayer;
	}
	bool GetisPlayer()
	{
		return isPlayer;
	}
	//openinventory
	void ChangeOpenInven()
	{
		openInven = !openInven;
	}
	bool GetOpenInven()
	{
		return openInven;
	}
	//openshop
	void ChangeOpenShop()
	{
		openShop = !openShop;
	}
	bool GetOpenShop()
	{
		return openShop;
	}
	//player fainting
	void ChangeFainting()
	{
		fainting = !fainting;
	}
	bool GetFainting()
	{
		return fainting;
	}


	int GetMoney()
	{
		return money;
	}
};