#pragma once
#include "Enemy.h" 
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
		void execute(float dt);
		List<Entities::Entity>::iterator begin();
		List<Entities::Entity>::iterator end();
	};
}