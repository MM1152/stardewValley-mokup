#pragma once
#include "GameObject.h"
class DialogueBox : public GameObject
{
protected:
	sf::Font font;
	sf::Sprite boxSprite;

	std::vector<std::string> currentLines; 
	int currentLineIndex = 0;

	sf::Text speakerNameText;
	sf::Text dialogueLineText;
	sf::Sprite characterPortrait;

	DialogueInfo loadedDialogue;

	bool isDialogueShow = false; 

	std::function<void()> onCloseCallback;

public:
	DialogueBox(const std::string& name = "");
	virtual ~DialogueBox() = default;

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

	void ShowDialogue();
	void CloseDialogue();
	bool isDialogueShowing();
	void LoadDialogue(const std::string& characterName);

	bool IsLastLine();
	void NextLine();
};

