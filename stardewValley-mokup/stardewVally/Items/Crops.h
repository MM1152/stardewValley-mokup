#pragma once
#include "GameObject.h"
#include "Seeds.h"

class TimeMoneyUi;

class Crops : public GameObject
{
public:
	enum class CropsType
	{
		Parsnip,
		Cauliflower,
		Potato,
		Garlic,
		None,
	};

protected:
	sf::Sprite crops;
	std::string cropsId;

	CropsType ctype = CropsType::None;

	TimeMoneyUi* tm = nullptr;

	int idx = 0;

	int curGrow = 0;
	int growup = 0;
public:
	Crops(const std::string& name = "");
	virtual ~Crops() = default;

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

	void GrowUp();

	void Setidx(int index);
	int Getidx();

	void SetCropsType(CropsType c);
	Crops::CropsType GetCropsType();

	void SetTimeMoneyUi(TimeMoneyUi* time);
	TimeMoneyUi* GetTimeMoneyUi();
};

