#pragma once
#include "GameObject.h"
class DialogBox : public GameObject
{
protected:
	sf::Font font;
	sf::Sprite boxSprite;

	std::vector<std::string> currentLines; 
	int currentLineIndex = 0;

	sf::Text speakerNameText;
	sf::Text dialogueLineText;
	sf::Text characterId;
	sf::Sprite characterPortrait_textureId; 

public:
	DialogBox(const std::string& name = "");
	virtual ~DialogBox() = default;

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

