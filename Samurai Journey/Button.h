#pragma once
#include "StateManager.h"

// Código baseado no repositório "JogoPlataforma2D-Jungle" de Giovani Limas Salvi
// Repositório: https://github.com/Giovanenero/JogoPlataforma2D-Jungle
// 
// Este repositório não possui licença explícita. O uso, modificação e distribuição
// deste código podem exigir permissão do autor original.

namespace Menu {

	namespace Buttons {

		enum Button_ID {
			empty,
			newgame,
			loadgame,
			leaderboard,
			exit,
			singleplayer,
			multiplayer,
			archersingle,
			archermulti,
			bosssingle,
			bossmulti,
			resumegame,
			saveprogress,
			pauseexit,
			savescore
		};

		class Button {
		protected:
			static Managers::GraphicManager* pGraphic;
			sf::RectangleShape box;
			Math::CoordF position;
			Math::CoordF size;
			Button_ID id;
		
		public:
			Button(Math::CoordF pos = (0, 0), Math::CoordF size = (0, 0), Button_ID id = empty);
			
			virtual ~Button();

			virtual void render();

			const Math::CoordF getPos() const;

			const Button_ID getButtonID() const;
		};

	}

}