#pragma once
#include "GameObject.h"
#include "stdafx.h"

class Player : public GameObject
{
protected:

	sf::Sprite sprite;
	float speed = 100.f;
	sf::RectangleShape shape;
	sf::RectangleShape shape2;
	std::vector<sf::RectangleShape> shapes;

public:
	void SetActive(bool a) { active = a; };
	void SetPosition(const sf::Vector2f& pos);
	void SetRotation(float rot);
	void SetScale(const sf::Vector2f& s);
	void SetOrigin(const sf::Vector2f& o);


	Player(const std::string name = "Player");
	virtual ~Player() = default;

	void Init();
	void Release();
	void Reset();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	bool IsColliding(sf::RectangleShape rect);
	void areaBlocked(sf::Vector2f moveOffset);
};

