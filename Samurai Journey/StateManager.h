#pragma once
#include "State.h"

// Código baseado no repositório "NightZ" de Pedro Ribeiro de Almeida e Matheus José Pereira
// Repositório: https://github.com/pedroribe1r0/NightZ
// Licença: MIT
// 
// Conforme a licença MIT, este código pode ser usado, modificado e distribuído,
// desde que a atribuição aos autores originais seja mantida.

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