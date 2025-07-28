#pragma once
#include <vector>
#include <functional>

struct RoundConfig
{
	int waveLevel;
	int perWaveMonster;
	float spawnInterval;
};

enum class RoundState
{
	Prepare,
	Running,
	Waiting,
	Finish
};;

class RoundMgr
{
private:
	std::vector<RoundConfig> rounds;
	std::function<void(int)>  onNewRound;
	std::function<void()>     onRoundClear;
	std::function<void(int)> onSpawn;

	int currentRound = -1;
	RoundState state = RoundState::Prepare;
	int waveSpawned = 0;
	int thisWaveMonsterSpawned = 0;
	float spawnedTime = 0.0f;

	
	void StartNextWave();

public:
	RoundMgr() = default;
	RoundMgr(const std::vector<RoundConfig>& configs,
		std::function<void(int)> onNew,
		std::function<void()> onClear,
		std::function<void(int)> onSpawn);

	void StartNextRound();

	void SpawnMonster() {if (onSpawn) onSpawn(1);}
	void Update(float dt);
	RoundState GetState() const { return state; }
	int GetCurrentRound() const { return currentRound+1; }

};

