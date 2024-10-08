#pragma once

#include "../Enum/EnemyType.h"
#include "../EnemyTypeBase.h"

class EnemyTypeFactory
{

private:
	static EnemyTypeFactory* instance;

private:
	EnemyTypeFactory() = default;
	EnemyTypeFactory(const EnemyTypeFactory&) = default;
	EnemyTypeFactory& operator=(const EnemyTypeFactory&) = default;

private:
	class Akabe* akabe;			//アカベェのクラス
	class Pinky* pinky;			//ピンキーのクラス
	class Aosuke* aosuke;		//アオスケのクラス
	class Guzuta* guzuta;		//グズタのクラス

private:
	void Initialize(class EnemyBase& enemy);

public:
	static EnemyTypeBase* Get(class EnemyBase& enemy, eEnemyType type);
	static void Finalize();
};

