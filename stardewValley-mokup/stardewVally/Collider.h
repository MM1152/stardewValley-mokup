#pragma once
#include "GameObject.h"
#include "Map.h"

class Map;
class Player;

class Collider : public GameObject
{
protected:
	sf::RectangleShape shape;
	std::vector<sf::RectangleShape*> shapes;
public:
	Map* map;
	Player* player;

	Collider(const std::string& name = "Collider");
	virtual ~Collider() = default;

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

	bool IsColliding(const GameObject& sprite);
	bool IsColliding(const sf::Sprite &sprite);
	bool IsColliding(const sf::FloatRect rect);
	bool IsColliding(const sf::RectangleShape& rect);

	void areaBlocked(sf::Vector2f& position, GameObject& sprite, const sf::Vector2f& moveOffset);
	void areaBlocked(sf::Vector2f& position, sf::Sprite& sprite, const sf::Vector2f& moveOffset);
	void areaBlocked(sf::Vector2f& position, sf::RectangleShape& shape, const sf::Vector2f& moveOffset);
	void SetMap(Map* map);
	void SetPlayer(Player* player);
	Player* GetPlayer() { return player; };
	Map* GetMap() { return map; };
};

