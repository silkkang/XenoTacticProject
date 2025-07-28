#include "stdafx.h"
#include "RoundMgr.h"
#include "SceneRound1.h"


RoundMgr::RoundMgr(const std::vector<RoundConfig>& configs,
	std::function<void(int)> onNew,
	std::function<void()> onClear,
	std::function<void(int)>        onSpawn)
	: rounds(configs), onNewRound(onNew), onRoundClear(onClear), onSpawn(onSpawn)
{
	StartNextRound();
}
void RoundMgr::StartNextRound()
{
	++currentRound;
	if (currentRound >= (int)rounds.size())
	{
		state = RoundState::Finish;
		currentRound = 0;
	}
	state = RoundState::Prepare;
	waveSpawned = 0;
	thisWaveMonsterSpawned = 0;
	spawnedTime = 0.f;
	onNewRound(currentRound + 1);
	state = RoundState::Running;
}

void RoundMgr::StartNextWave()
{
	++waveSpawned;
	thisWaveMonsterSpawned = 0;
	spawnedTime = 0.f;
}



void RoundMgr::Update(float dt)
{
	if (state != RoundState::Running) return;

	auto& cfg = rounds[currentRound];

	spawnedTime += dt;
	while (spawnedTime >= cfg.spawnInterval &&
		thisWaveMonsterSpawned < cfg.perWaveMonster)
	{

		spawnedTime -= cfg.spawnInterval;
		SpawnMonster();
		++thisWaveMonsterSpawned;
	}


	if (thisWaveMonsterSpawned >= cfg.perWaveMonster)
	{
		if (waveSpawned + 1 < cfg.waveLevel)
		{
			StartNextWave();
		}
		else
		{
			StartNextRound();
			state = RoundState::Waiting;

		}
	}


}