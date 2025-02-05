#pragma once
#include "List.h"

namespace List {
    class EntitiesList {
    private:
        List<Entities::Entity*> entList; // Note que a lista armazena ponteiros para entidades
    public:
        EntitiesList();
        ~EntitiesList();
        void addEntity(Entities::Entity* pEntity);
        void removeEntity(Entities::Entity* pEntity);
        //void removeEntity(unsigned int ind);
        int getSize() const;
        void execute(float dt);
        List<Entities::Entity*>::Iterator begin();
        List<Entities::Entity*>::Iterator end();
    };
}
