#include "stdafx.h"
#include "Player.h"
#include "NpcMgr.h"


Player::Player(const std::string name)
	:Collider(name)
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

void Player::SetOrigin(const Origins originPreset)
{
	GameObject::SetOrigin(this->originPreset);
	this->originPreset = originPreset;
	Utils::SetOrigin(sprite, originPreset);
}

void Player::Init()
{
	//Player Position값은 각 씬마다 달라져서 각 씬에서 초기 위치값 설정해서 사용해야합니다~ -민성-
	//SetPosition({100.f, 100.f});
	Collider::Init();
}

void Player::Release()
{
}

void Player::Reset()
{
	sprite.setTexture(TEXTURE_MGR.Get("graphics/testC.png"));
	SetOrigin(Origins::BL);

}

void Player::Update(float dt)
{
	sf::Vector2f movement = { 0.f, 0.f };

	float moveX = InputMgr::GetAxis(Axis::Horizontal);
	float moveY = InputMgr::GetAxis(Axis::Vertical);

	movement.x = moveX * speed * dt;
	movement.y = moveY * speed * dt;

	std::vector<sf::RectangleShape> shapes;

	sf::Vector2f moveOffset(movement.x, movement.y);

	Collider::areaBlocked(position, sprite, moveOffset);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}



