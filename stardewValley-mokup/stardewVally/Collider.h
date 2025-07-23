#pragma once
#include "GameObject.h"
class Collider :
    public GameObject
{
protected:
	sf::RectangleShape shape;
	sf::RectangleShape shape2;
	std::vector<sf::RectangleShape> shapes;
public:
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

	bool IsColliding(const sf::Sprite sprite);
	bool IsColliding(const sf::FloatRect rect);

	void areaBlocked(sf::Vector2f& position, sf::Sprite& sprite, const sf::Vector2f& moveOffset);
};

