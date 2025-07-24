#pragma once
#include "stdafx.h"
#include "GameObject.h"
class Button : public GameObject
{
private:
	sf::RectangleShape bnt;
	sf::Text text;

	std::string fontId;
	std::string texId;

	Origins textOrigin = Origins::BC;
public:
	Button(const std::string fontId, const std::string texId = "", const std::string name = "");
	~Button() override = default;

	std::function<void()> onClickFunc;

	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void SetString(const std::string word);
	void SetTextColor(sf::Color color);
};

