#pragma once
#include "Scene.h"

class Button;
class InputText;
class SceneAnimator : public Scene
{
protected:
	std::string filePath;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::Sprite preview;

	InputText* inputText;

	sf::RectangleShape rightBackGround;

	std::vector<sf::RectangleShape*> rect;
	sf::Vector2f rectStartPos;
	bool startDrawRect = false;

	sf::Vector2f dragStartPos;

	Button* loadBNT;
	Button* saveBNT;

	float timer = 0; 
	float previewFrame = 30;
	int curIndex = 0;
public:
	SceneAnimator();
	~SceneAnimator() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void DrawRectangle();
	void DragToMoveScreen(float dt);
	void UndoRectangle();
	void PreviewAnimation(float dt);
	void DeleteRectangle(const std::string saveData);
};

