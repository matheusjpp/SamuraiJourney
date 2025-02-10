#pragma once
#include "Level.h"

// Código baseado no repositório "JogoPlataforma2D-Jungle" de Giovani Limas Salvi
// Repositório: https://github.com/Giovanenero/JogoPlataforma2D-Jungle
// 
// Este repositório não possui licença explícita. O uso, modificação e distribuição
// deste código podem exigir permissão do autor original.

namespace Levels {

	class BossLevel : public Level {
	private:
		int pastPoints;
	public:
		BossLevel(bool isMultiplayer, Managers::States::State_ID id = Managers::States::State_ID::empty, int playerPoints = 0, bool isLoaded = false);

		~BossLevel();

		void verifyLevelEnd();

		void execute(float dt);
	};
	
}