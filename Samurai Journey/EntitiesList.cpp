#include "EntitiesList.h"

namespace List {
	EntitiesList::EntitiesList():entList(){}

	EntitiesList::~EntitiesList() {
		entList.clear();
	}
    void EntitiesList::addEntity(Entities::Entity* pEntity) {
        if (pEntity) {
            entList.push_back(pEntity);
        }
        else {
            std::cerr << "Erro: Entidade nula passada para addEntity." << std::endl;
        }
    }

    void EntitiesList::removeEntity(Entities::Entity* pEntity) {
        if (!pEntity) {
            std::cerr << "Erro: Entidade nula passada para removeEntity." << std::endl;
            return;
        }

        List<Entities::Entity>::iterator it = entList.begin();
        while (it != entList.end()) {
            if (*it == pEntity) {
                delete* it; // Deleta o objeto apontado pela entidade
                entList.remove(pEntity); // Remove o nó correspondente
                return;
            }
            ++it;
        }

        std::cerr << "Erro: Entidade não encontrada na lista." << std::endl;
    }

    void EntitiesList::removeEntity(unsigned int ind) {
        if (ind >= entList.getSize() || ind<0) {
            std::cerr << "Erro: Índice inválido passado para removeEntity." << std::endl;
            return;
        }

        unsigned int currentInd = 0;
        List<Entities::Entity>::iterator it = entList.begin();
        while (it != entList.end()) {
            if (currentInd == ind) {
                delete* it; // Deleta o objeto apontado pela entidade
                entList.remove(*it); // Remove o nó correspondente
                return;
            }
            ++it;
            ++currentInd;
        }
    }

     int  EntitiesList :: getSize() {
        return entList.getSize();
     }
     void EntitiesList::execute(float dt) {

         List<Entities::Entity>::iterator it = entList.begin();
         while (it != entList.end()) {
             Entities::Entity* entity = *it; // Obtém o ponteiro para a entidade atual
             if (entity) {
                 entity->update(dt); // Atualiza a entidade passando o tempo delta
             }
             ++it; // Move para o próximo elemento
         }
     }

     List<Entities::Entity>::iterator EntitiesList::begin() {
         return entList.begin();
     }
     List<Entities::Entity>::iterator EntitiesList::end() {
         return entList.end();
     }
}