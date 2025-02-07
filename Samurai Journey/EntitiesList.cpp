#include "EntitiesList.h"
#include <iostream> // Para exibir mensagens de erro

namespace List {
    EntitiesList::EntitiesList() : entList() {
    
    }

    EntitiesList::~EntitiesList() {
        
    }

    void EntitiesList::addEntity(Entities::Entity* pEntity) {
        if (pEntity) {
            entList.push_back(pEntity);
        }
        else {
            std::cerr << "Erro: Entidade nula passada para addEntity." << std::endl;
        }
    }
    /*
    void EntitiesList::removeEntity(Entities::Entity* pEntity) {
        if (!pEntity) {
            std::cerr << "Erro: Entidade nula passada para removeEntity." << std::endl;
            return;
        }

        for (auto it = entList.begin(); it != entList.end(); ++it) {
            if (*it == pEntity) {
                delete* it;         // Libera a memória da entidade
                entList.remove(*it); // Remove o nó da lista
                return;
            }
        }

        std::cerr << "Erro: Entidade não encontrada na lista." << std::endl;
    }*/

    void EntitiesList::removeEntity(Entities::Entity* pEntity) {
        if (!pEntity) {
            std::cerr << "Erro: Entidade nula passada para removeEntity." << std::endl;
            return;
        }

        entList.remove(pEntity);
    }


    int EntitiesList::getSize() const {
        return static_cast<int>(entList.getSize());
    }

    void EntitiesList::execute(float dt) {
        for (auto it = entList.begin(); it != entList.end(); ++it) {
            Entities::Entity* entity = *it;

            if (!entity) {
                std::cerr << "nullptr found" << std::endl;
                continue; 
            }

            if (entity && entity->getIsActive() && entity->getID() != ID::portal) {
                entity->execute();
            }
        }
    }

    List<Entities::Entity*>::Iterator EntitiesList::begin() {
        return entList.begin();
    }

    List<Entities::Entity*>::Iterator EntitiesList::end() {
        return entList.end();
    }
}