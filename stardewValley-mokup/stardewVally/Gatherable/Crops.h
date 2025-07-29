#pragma once
#include "Gatherable.h"
#include "Seeds.h"

class TimeMoneyUi;

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
	int idx = 0;
	int curGrow = 0;

	bool growup = false;

public:
	Crops(const std::string& name = "");
	virtual ~Crops() = default;

	void Init() override;
	void Reset() override;

	void GrowUp();

	void Setidx(int index);
	int Getidx();

	void SetCropsType(CropsType c);
	Crops::CropsType GetCropsType();

	void SetTimeMoneyUi(TimeMoneyUi* time);
	TimeMoneyUi* GetTimeMoneyUi();
};

