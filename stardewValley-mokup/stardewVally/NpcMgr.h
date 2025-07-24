#pragma once
#include "Collider.h"

class Player;
class Shop;
class NpcMgr : public Collider
{
protected:
	sf::Sprite npcSprite;
	float speed = 20.f;
	sf::Vector2f direction = { 0.f, 0.f };

	sf::RectangleShape playerRect;
	sf::RectangleShape npcUiRect;
	Player* player = nullptr;
	Shop* shop;

	std::function<void()> callback;

	bool isNpcMove = true;
public:
	NpcMgr(const std::string& name = "Npc");
	virtual ~NpcMgr() = default;

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
	void SetPlayer(Player* p) { player = p; }
	bool IsCollidingPlayer(sf::RectangleShape rect);
	void setCallBack(std::function<void()> cb);
	sf::FloatRect GetGlobalBounds();
};

