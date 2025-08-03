#pragma once
#include "InGameItem.h"

struct CellData;
class DropItemFix : public InGameItem
{
private:
	CellData* cellData;
public:
	DropItemFix(ItemInfo type , CellData* cellData);
	~DropItemFix() override = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
};

