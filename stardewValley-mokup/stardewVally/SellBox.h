#pragma once
#include "GameObject.h"

class Inventory;
class Player;
class SellBox : public GameObject
{
protected:
	sf::Sprite sellBoxSprite;

	//std::function<void()> callback;

	bool isShippingShow =  false; 

	Inventory* inventory;
	Player* player;

	sf::RectangleShape boxRect;
	sf::RectangleShape playerRect;


public:
	SellBox(const std::string& name = "");
	virtual ~SellBox() = default;

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
	//void setCallBack(std::function<void()> cb);
	bool IsCollidingBox(sf::RectangleShape rect);
	void SetInventory(Inventory* inven);
	Inventory* GetInventory();
	void SetPlayer(Player* p);
	Player* GetPlayer();
};

