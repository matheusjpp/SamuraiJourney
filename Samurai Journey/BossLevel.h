#pragma once
#include "Level.h"

// C�digo baseado no reposit�rio "JogoPlataforma2D-Jungle" de Giovani Limas Salvi
// Reposit�rio: https://github.com/Giovanenero/JogoPlataforma2D-Jungle
// 
// Este reposit�rio n�o possui licen�a expl�cita. O uso, modifica��o e distribui��o
// deste c�digo podem exigir permiss�o do autor original.

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