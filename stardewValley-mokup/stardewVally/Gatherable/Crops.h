#pragma once
#include "Gatherable.h"
#include "DropItem.h"

class TimeMoneyUi;
class DropItem;
class inventory;

class Crops : public Gatherable
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
	std::string cropsId;

	CropsType ctype = CropsType::None;
	TimeMoneyUi* tm = nullptr;
	DropItem* dropitem = nullptr;
	Inventory* inventory = nullptr;

	int idx = 0;
	int curGrow = 0;

	bool growup_interaction = false;

	sf::Vector2f curcropspos = {-1.f, -1.f};

public:
	Crops(const std::string& name = "");
	virtual ~Crops() = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void DropItems() override;

	void GrowUp();

	void Setidx(int index);
	int Getidx();

	void SetCropsType(CropsType c);
	Crops::CropsType GetCropsType();
	
	void SetCurrentCropsPosition(sf::Vector2f pos) { curcropspos = pos; };
	sf::Vector2f GetCurrentCropsPosition() { return curcropspos; };
	void SetTimeMoneyUi(TimeMoneyUi* time);
	TimeMoneyUi* GetTimeMoneyUi();
	void SetInventory(Inventory* inv) { inventory = inv; };
	void SetDropItem(DropItem* drop) { dropitem = drop; };
};

