#include "stdafx.h"
#include "DialogueBox.h"
#include "DialogueLoader.h"

DialogueBox::DialogueBox(const std::string& name)
	: GameObject(name)
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 3;
}

void DialogueBox::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	boxSprite.setPosition(pos);
}

void DialogueBox::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	boxSprite.setRotation(rot);
}

void DialogueBox::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	boxSprite.setScale(s);
}

void DialogueBox::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	boxSprite.setOrigin(o);
}

void DialogueBox::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(boxSprite, preset);
	}
}

void DialogueBox::Init()
{
}

void DialogueBox::Release()
{
}

void DialogueBox::Reset()
{
	boxSprite.setTexture(TEXTURE_MGR.Get("graphics/uiBox.png"));
	boxSprite.setPosition({ 80.f, 480.f });
	boxSprite.setPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f - 350 , FRAMEWORK.GetWindowSizeF().y * 0.5f + 100.f});
	boxSprite.setScale({1.f , 1.f});

}

void DialogueBox::Update(float dt)
{
	if (isDialogueShow)
	{
		return;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Z))
	{
		currentLineIndex++;
		if (currentLineIndex >= currentLines.size())
		{
			CloseDialogue();
		}
		else
		{
			dialogueLineText.setString(currentLines[currentLineIndex]);
		}
	}
}

void DialogueBox::Draw(sf::RenderWindow& window)
{
	if (isDialogueShow)
	{
		window.draw(boxSprite);
		window.draw(speakerNameText);
		window.draw(dialogueLineText);
		window.draw(characterPortrait);
	}
}

void DialogueBox::ShowDialogue()
{
	isDialogueShow = true;
	currentLineIndex = 0;
	dialogueLineText.setString(currentLines[currentLineIndex]);
}

void DialogueBox::CloseDialogue()
{
	isDialogueShow = false;
	currentLines.clear();
	currentLineIndex = 0;

	if (onCloseCallback)
	{
		onCloseCallback(); 
	}
}

bool DialogueBox::isDialogueShowing()
{
	return isDialogueShow;
}

void DialogueBox::LoadDialogue(const std::string& characterName)
{
	const auto& dialogues = DialogueLoader::Instance().GetDialogue(characterName);

	if (dialogues.empty()) {
		std::cerr << "No dialogues found for character: " << characterName << "\n";
		return;
	}

	loadedDialogue = dialogues[0];
	currentLines = loadedDialogue.lines;
	currentLineIndex = 0;

	sf::Vector2f boxPos = boxSprite.getPosition();

	font = FONT_MGR.Get("fonts/Stardew_Valley.ttf");

	speakerNameText.setFont(font);
	speakerNameText.setCharacterSize(30);
	speakerNameText.setFillColor(sf::Color::Black);
	speakerNameText.setPosition({ boxPos.x + 530.f, boxPos.y + 200 });

	dialogueLineText.setFont(font);
	dialogueLineText.setCharacterSize(30);
	dialogueLineText.setFillColor(sf::Color::Black);
	dialogueLineText.setPosition({ boxPos.x + 30, boxPos.y + 30 });

	characterPortrait.setTexture(TEXTURE_MGR.Get(loadedDialogue.portrait_textureId));
	characterPortrait.setPosition({ boxPos.x + 500.f, boxPos.y + 40 });
	characterPortrait.setScale({ 2.3f, 2.3f });

	speakerNameText.setString(loadedDialogue.character);
	dialogueLineText.setString(currentLines[currentLineIndex]);
	 
	isDialogueShow = true;
}

bool DialogueBox::IsLastLine()
{
	return currentLineIndex >= currentLines.size() - 1;
}

void DialogueBox::NextLine()
{
	if (currentLineIndex < currentLines.size() - 1) {
		currentLineIndex++;
		dialogueLineText.setString(currentLines[currentLineIndex]);
	}
}
