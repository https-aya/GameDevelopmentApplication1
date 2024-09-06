#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h" 
#include "Factory/EnemyTypeFactory.h"
#include "DxLib.h"

#define ENEMY_SPEED (45.0f)

EnemyBase::EnemyBase()
	:velocity(0.0f)
	, enemy_type()
	, enemy_state()
	, hold_state()
	, world_time(0.0f)
	, flash_count(0)
	, izike_time(0.0f)
	, player(nullptr)
	, enemy_delta(eEnemyDeltaState::NOMAL)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize()
{

	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE) / 2.0f;
	// �����̐ݒ�
	mobility = eMobilityType::Movable;
	z_layer = 6;
}

void EnemyBase::Update(float delta_second)
{
	if (player->GetPowerUp() == true && enemy_delta == eEnemyDeltaState::NOMAL)
	{
		if (enemy_state!=eEnemyState::eIZIKE && enemy_state != eEnemyState::eESCAPE)
		{
			hold_state = enemy_state;
		}
		if (enemy_state != eEnemyState::eESCAPE)
		{
			enemy_state = eEnemyState::eIZIKE;
		}
	}
	else if(enemy_delta == eEnemyDeltaState::BEGIN || enemy_delta == eEnemyDeltaState::NOMAL && enemy_state != eEnemyState::eIDLE)
	{
		enemy_state = hold_state;
		enemy_delta = eEnemyDeltaState::NOMAL;
	}
	enemy_type->Update(delta_second,(this));
	location += velocity * ENEMY_SPEED * delta_second;
	if (enemy_state != eEnemyState::eIZIKE && enemy_state != eEnemyState::eESCAPE)
	{
		world_time += delta_second;
	}
	if (location.x >= 640)
	{
		location.x = 1;
	}
	else if (location.x <= 0)
	{
		location.x = 639;
	}
	if (enemy_delta == eEnemyDeltaState::RETRUN)
	{
		enemy_state = hold_state;
	}
}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	enemy_type->Draw(screen_offset);
}

void EnemyBase::Finalize()
{
	enemy_type->Finalize();
}

void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
	Vector2D obj_loc = hit_object->GetLocation();

	if (hit_object->GetCollision().object_type == eObjectType::player)
	{
		player->SetEnemy(this);
		if (enemy_state == eEnemyState::eIZIKE)
		{
			enemy_state = eEnemyState::eESCAPE;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
		}
	}	

	// ���������A�I�u�W�F�N�g���ǂ�������

	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// �����蔻������擾���āA�J�v�Z��������ʒu�����߂�
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// �ŋߖT�_�����߂�
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Player����near_point�ւ̕����x�N�g�����擾
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// �߂荞�񂾍���
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diff�̕������߂�
		location += dv.Normalize() * diff;
	}
}

//�G�l�~�[�̏�Ԃ̎擾
eEnemyState EnemyBase::GetEnemyState()
{
	return enemy_state;
}

//�G�l�~�[�̏�Ԃ̕ύX
void EnemyBase::ChangeEnemyState(eEnemyState state)
{
	this->hold_state = state;
}

//�G�l�~�[�̎�ނ�ݒ�
void EnemyBase::SetEnemytype()
{
	int x, y;
	//���݂̍��W���p�l���̒l�ɕύX
	StageData::ConvertToIndex(location, y, x);
	switch (x)
	{
	case 13:
		enemy_type = EnemyTypeFactory::Get((*this), eEnemyType::AKABE);
		enemy_state = eEnemyState::ePATROL;
		hold_state = eEnemyState::ePATROL;
		break;
	case 12:
		enemy_type = EnemyTypeFactory::Get((*this), eEnemyType::AOSUKE);
		enemy_state = eEnemyState::eIDLE;
		hold_state = eEnemyState::ePATROL;
		break;
	case 16:
		enemy_type = EnemyTypeFactory::Get((*this), eEnemyType::GUZUTA);
		enemy_state = eEnemyState::eIDLE;
		hold_state = eEnemyState::ePATROL;
		break;
	case 14:
		enemy_type = EnemyTypeFactory::Get((*this), eEnemyType::PINKY);
		enemy_state = eEnemyState::eIDLE;
		hold_state = eEnemyState::ePATROL;
		break;
	default:
		break;
	}
}

//�v���C���[���̐ݒ�
void EnemyBase::SetPlayer(Player* object)
{
	this->player = object;
}

//�v���C���[���̎擾
Player* EnemyBase::GetPlayer()
{
	return player;
}

//�ړ����̎擾
void EnemyBase::SetVelocity(Vector2D velocity)
{
	this->velocity = velocity;
}

//�����̕ύX
void EnemyBase::SetMobility(eMobilityType mobility)
{
	this->mobility = mobility;
}

//���C�t���̎擾
void EnemyBase::SetEnemyDeltaState(eEnemyDeltaState delta)
{
	enemy_delta = delta;
}

//�J�E���g�̎擾
float EnemyBase::GetWorldTime()
{
	return world_time;
}

//�J�E���g�̏�����
void EnemyBase::ClearWorldTime()
{
	world_time = 0.0f;
}