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
	class Akabe* akabe;			//�A�J�x�F�̃N���X
	class Pinky* pinky;			//�s���L�[�̃N���X
	class Aosuke* aosuke;		//�A�I�X�P�̃N���X
	class Guzuta* guzuta;		//�O�Y�^�̃N���X

private:
	void Initialize(class EnemyBase& enemy);

public:
	static EnemyTypeBase* Get(class EnemyBase& enemy, eEnemyType type);
	static void Finalize();
};

