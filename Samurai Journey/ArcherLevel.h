#pragma once
#include "BossLevel.h"

namespace Levels {

	class ArcherLevel : public Level {
	private:
		Entities::Obstacles::Portal* pPortal;

	public:
		ArcherLevel(bool isMultiplayer, Managers::States::State_ID id = Managers::States::State_ID::empty, bool isLoaded = false);

		~ArcherLevel();

		void verifyLevelEnd();

		void execute(float dt);

	};

}