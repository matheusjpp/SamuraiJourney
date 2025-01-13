#pragma once
#include "Entity.h" 
#include "List.h" 

namespace List {
	class EntitiesList {
	private:
		List <Entities::Entity> entList;
	public:
		EntitiesList();
		~EntitiesList();
	};
}