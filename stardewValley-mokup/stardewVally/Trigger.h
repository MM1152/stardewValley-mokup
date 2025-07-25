#pragma once

#include "GameObject.h"

enum class TriggerType{
	None,
	Door,
};

class Player;
class Trigger : public GameObject
{
private:
	sf::RectangleShape rect;
	TriggerType type;

	Player* player;
public:
	std::function<void()> callback;

	Trigger(const std::string& name = "");
	~Trigger() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetSize(const sf::Vector2f size);
	sf::Vector2f GetSize() { return rect.getSize(); };

	void SetType(const TriggerType type) { this->type = type; };
	void SetPlayer(Player* player) { this->player = player; };
	TriggerType GetType() { return type; };
};

