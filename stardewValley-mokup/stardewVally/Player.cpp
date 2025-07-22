#include "stdafx.h"
#include "Player.h"


Player::Player(const std::string name)
	:GameObject(name)
{
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void Player::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void Player::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void Player::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void Player::Init()
{
	SetPosition({0.f, 0.f});
	shape.setPosition(100.f, 100.f);
	shape.setSize({ 20.f,20.f });
	shape.setFillColor(sf::Color::Red);

	shape2.setPosition(70.f, 70.f);
	shape2.setSize({ 100.f,20.f });
	shape2.setFillColor(sf::Color::Red);

	shapes.push_back(shape);
	shapes.push_back(shape2);
}

void Player::Release()
{
}

void Player::Reset()
{
	sprite.setTexture(TEXTURE_MGR.Get("graphics/testC.png"));
}

void Player::Update(float dt)
{
	sf::Vector2f movement = { 0.f, 0.f };

	float moveX = InputMgr::GetAxis(Axis::Horizontal);
	float moveY = InputMgr::GetAxis(Axis::Vertical);

	movement.x = moveX * speed * dt;
	movement.y = moveY * speed * dt;

	std::vector<sf::RectangleShape> shapes;

	/*SetPosition(movement + position);*/

	areaBlocked(movement);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	for (auto shape : shapes)
	{
		window.draw(shape);
	}
	

}

bool Player::IsColliding(sf::RectangleShape rect)
{
	sf::Vector2f playerPos = sprite.getPosition();
	sf::Vector2f playerSize = sprite.getGlobalBounds().getSize();

	sf::Vector2f rectPos = rect.getPosition();
	sf::Vector2f rectSize = rect.getGlobalBounds().getSize(); // ask 민성오빠

	return playerPos.x < rectPos.x + rectSize.x &&
		   rectPos.x < playerPos.x + playerSize.x &&
		   playerPos.y < rectPos.y + rectSize.y &&
		   rectPos.y < playerPos.y + playerSize.y;
}

void Player::areaBlocked(sf::Vector2f moveOffset)
{
	position.x += moveOffset.x;
	sprite.setPosition(position);
	for (auto shape : shapes)
	{
		if (IsColliding(shape))
		{
			position.x -= moveOffset.x;
			sprite.setPosition(position);
			std::cout << "side 충돌" << std::endl;
		}
	}

	position.y += moveOffset.y;
	sprite.setPosition(position);
	for (auto shape : shapes)
	{
		if (IsColliding(shape))
		{
			position.y -= moveOffset.y;
			sprite.setPosition(position);
			std::cout << "up&down 충돌" << std::endl;
		}
	}
}




