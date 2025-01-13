#pragma once
#include "Player.h" 
#include "List.h" 

namespace List {
	class EntitiesList {
	private:
		List <Entities::Entity> entList;
	public:
		EntitiesList();
		~EntitiesList();
		void addEntity(Entities::Entity* pEntity);
		void removeEntity(Entities::Entity* pEntity);
		void removeEntity(unsigned int ind);
		int getSize();
		List<Entities::Entity>::iterator begin();
		List<Entities::Entity>::iterator end();
	};
}