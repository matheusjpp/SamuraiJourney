#pragma once
#include "MainMenu.h"
#include <fstream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Levels {

	class Level {
	private:
		List::EntitiesList staticEntities;

	public: 
		Level();

		~Level();

		void createMap(const char* filePath);

		List::EntitiesList& getList();
	};

}