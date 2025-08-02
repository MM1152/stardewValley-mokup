#include "stdafx.h"
#include "Trigger.h"
#include "Player.h"

Trigger::Trigger(const std::string& name)
	:GameObject(name)
	,type(TriggerType::None)
{
}

void Trigger::Init()
{
	rect.setFillColor(sf::Color::Blue);
	rect.getFillColor().a - 127;
	rect.setOutlineThickness(1.f);
}

void Trigger::Release()
{
}

void Trigger::Reset()
{
	inTrigger = false;
}

void Trigger::Update(float dt)
{
	if (player) {
		if (player->GetGlobalBounds().intersects(rect.getGlobalBounds())) {
			if (callback) {
				callback();
				inTrigger = true;
			}
		}
		else {
			inTrigger = false;
		}
	}
}

void Trigger::Draw(sf::RenderWindow& window)
{
	window.draw(rect);
}

void Trigger::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	rect.setPosition(pos);
}

void Trigger::SetSize(const sf::Vector2f size)
{
	rect.setSize(size);
}
