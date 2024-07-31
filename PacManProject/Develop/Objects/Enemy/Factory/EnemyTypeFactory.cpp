#include "EnemyTypeFactory.h"

#include "../Akabe.h"
#include "../Pinky.h"
#include "../Aosuke.h"
#include "../Guzuta.h"

EnemyTypeFactory* EnemyTypeFactory::instance = nullptr;

void EnemyTypeFactory::Initialize(class EnemyBase& enemy)
{
	akabe = new Akabe(&enemy);
	pinky = new Pinky(&enemy);
	aosuke = new Aosuke(&enemy);
	guzuta = new Guzuta(&enemy);
}

void EnemyTypeFactory::Finalize()
{
	instance->akabe->Finalize();
	instance->pinky->Finalize();
	instance->aosuke->Finalize();
	instance->guzuta->Finalize();

	delete instance->akabe;
	delete instance->pinky;
	delete instance->aosuke;
	delete instance->guzuta;
}

EnemyBase* EnemyTypeFactory::Get(EnemyBase& enemy, eEnemyType type)
{
	if (instance == nullptr)
	{
		instance = new EnemyTypeFactory();
		instance->Initialize(enemy);
	}

	EnemyBase* ret = nullptr;
	switch (type)
	{
	case eEnemyType::AKABE:
		instance->akabe->Initialize();
		ret = instance->akabe;
		break;
	case eEnemyType::AOSUKE:
		instance->aosuke->Initialize();
		ret = instance->aosuke;
		break;
	case eEnemyType::PINKY:
		instance->pinky->Initialize();
		ret = instance->pinky;
		break;
	case eEnemyType::GUZUTA:
		instance->guzuta->Initialize();
		ret = instance->guzuta;
		break;
	default:
		break;
	}
	return ret;
}