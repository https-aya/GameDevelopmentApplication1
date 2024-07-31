#pragma once

#include "../Enum/EnemyType.h"

class EnemyTypeFactory
{

private:
	static EnemyTypeFactory* instance;

private:
	EnemyTypeFactory() = default;
	EnemyTypeFactory(const EnemyTypeFactory&) = default;
	EnemyTypeFactory& operator=(const EnemyTypeFactory&) = default;

private:
	class Akabe* akabe;
	class Pinky* pinky;
	class Aosuke* aosuke;
	class Guzuta* guzuta;

private:
	void Initialize(class EnemyBase& enemy);

public:
	static EnemyBase* Get(class EnemyBase& enemy, eEnemyType type);
	static void Finalize();
};

