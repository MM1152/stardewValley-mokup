#pragma once
#include "Collider.h"
#include "stdafx.h"
#include "Animator.h"
#include "InGameItem.h"

class NpcMgr;
class Inventory;
class TimeMoneyUi;
class TileMap;
class Map;
class Crops;

class Player : public Collider
{
protected:
	Animator body;
	Animator hand;
	Animator hat;
	//player move
	sf::RectangleShape bound;
	bool isPlayer = true;
	bool openInven = false;
	bool openShop = false;
	bool fainting = false;
	bool useItem = false;
	bool growup = false;

	sf::Vector2f prevDir = { 0,0 };

	sf::Sprite bodySprite;
	sf::Sprite handSprite;
	sf::Sprite hatSprite;

	float speed = 100.f;
	int money = 500;
	
	NpcMgr* npcMgr = nullptr;
	Inventory* inventory = nullptr;
	TimeMoneyUi* timemoneyui = nullptr;
	TileMap* tileMap;

	sf::RectangleShape seedGuideRect;
	
	InGameItem* copyItem;
	Item* item;
	
	sf::Vector2i lookDir = { 0,0 };

	int quickBarIdx = -1;
public:
	sf::Vector2i GetLookDir() { return lookDir; };

	void SetActive(bool a) { active = a; };
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s);
	void SetOrigin(const sf::Vector2f& o);
	void SetOrigin(Origins preset);
	void SetNpcMgr(NpcMgr* n) { this->npcMgr = n; }
	void SetItem(Item* item);

	Player(const std::string name = "Player");
	virtual ~Player() = default;

	void Init();
	void Release();
	void Reset();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	void PlayMoveAnimation(sf::Vector2f dir);
	void PlayUseItemAnimation(sf::Vector2i dir);

	bool CanUseItemOnTile(int tileIdx);

	void SetInventory(Inventory* inven);
	Inventory* GetInventory();

	void SetTimer(TimeMoneyUi* time);
	TimeMoneyUi* GetTimer();
	
	virtual sf::FloatRect GetLocalBounds() const
	{
		return bodySprite.getLocalBounds();
	}

	virtual sf::FloatRect GetGlobalBounds() const
	{
		return bound.getGlobalBounds();
	}

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
	//crops growup
	void SetGrowup(bool grow)
	{
		growup = grow;
	}
	bool GetGrowup()
	{
		return growup;
	}

	int GetMoney()
	{
		return money;
	}

	void SetMoney(int m)
	{
		money = m;
	}
};