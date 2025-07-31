#pragma once
#include "GameObject.h"

class Button;

class TitleUi : public GameObject
{
protected:
	bool exitview = false;
	bool toolview = false;

	sf::Sprite title;
	sf::Sprite yes_or_no;
	sf::Sprite tool;
	Button* startbnt;
	Button* loadbnt;
	Button* toolbnt;
	Button* exitbnt;

	Button* yesbnt;
	Button* nobnt;

	Button* maptoolbnt;
	Button* animatorbnt;

public:
	TitleUi(const std::string& name = "");
	virtual ~TitleUi() = default;

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
};

