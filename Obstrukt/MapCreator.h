#pragma once
#include "Map.h"

class MapCreator
{
private:
	static std::vector<Map*> deletedMaps;
	static void saveMapToDeleted();
	static int levelIndex;

public:
	static Map* CreateMenuMap();
	static Map* CreateGameOverMap();
	static Map* CreateWinMap();
	static Map* createEditorMap();

	static Map* LoadGameMap(int index);
	static Map* LoadNextGameMap();
	static void deleteOldMaps();
};