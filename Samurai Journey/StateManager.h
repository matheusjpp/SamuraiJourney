#pragma once
#include "State.h"

// C�digo baseado no reposit�rio "NightZ" de Pedro Ribeiro de Almeida e Matheus Jos� Pereira
// Reposit�rio: https://github.com/pedroribe1r0/NightZ
// Licen�a: MIT
// 
// Conforme a licen�a MIT, este c�digo pode ser usado, modificado e distribu�do,
// desde que a atribui��o aos autores originais seja mantida.

namespace Managers {

	namespace States {

		class StateManager {
		private:
			std::stack<State*> stateStack;
			static StateManager* pStateM;
			static GraphicManager* pGraphic;

			StateManager();

		public:
			~StateManager();

			static StateManager* getInstance();

			void pushState(State* state);

			void popState();

			void popState(int quantity);

			void renderState();

			void executeState();

			State* getCurrentState() const;

			State* getPreviousState();
		};

	}

}