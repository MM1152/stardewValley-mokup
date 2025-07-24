#pragma once

#define DEF_DEV
#define INVEN_IMG_PATH "InventoryImg/"
#define ITEM_IMG_PATH "ItemImg/"
#define FONT_PATH "Font/"

enum class SortingLayers
{
	Background,
	Foreground,
	Default,
	UI,
};

enum class Origins
{
	TL, TC, TR,	// 0 1 2
	ML, MC, MR,	// 3 4 5
	BL, BC, BR, // 6 7 8
	Custom
};

enum class SceneIds
{
	None = -1,
	Game,
	Dev1,
	Dev2,
	Animator,
	Count,
};

enum class Sides
{
	Left,
	Right,
	None,
};