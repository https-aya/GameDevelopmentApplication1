#pragma once
#include "Enum/EnemyType.h"
#include "Enum/EnemyState.h"
#include "../../Utility/Vector2D.h"
#include "../Player/Player.h"
#include "EnemyBase.h"

class EnemyTypeBase
{
protected:
	enum eEnemyDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
	};

protected:
	std::vector<int> animation;			//�A�j���[�V����
	std::vector<int> eyeanimation;		//�ڂ̃A�j���[�V����

	eEnemyType type;					//�G�l�~�[�̎��
	eEnemyState enemy_state;			//�G�l�~�[�̏��
	eEnemyDirectionState now_direction; //�����Ă����
	Vector2D velocity;					//�ړ�����
	class EnemyBase* enemy;				//�G�l�~�[�̏��
	class Player* player;				//�v���C���[���
	eEnemyDeltaState enemy_delta;		//�G�l�~�[�̐��̏��

	std::map<eAdjacentDirection, ePanelID> ret; //�㉺���E�̃p�l�����
	ePanelID panel;								//���ݒn�p�l�����
	float move_count;							//�ړ��̃J�E���g
	int target_panel_x;							//�ڕW�p�l����
	int target_panel_y;							//�ڕW�p�l����
	int x;										//���݃p�l����
	int	y;										//���݃p�l����

private:

	int flash_count;							//�G�l�~�[������������߂�Ƃ��̓_��
	float izike_time;							//���������̃J�E���g
	float animation_time;						//
	int animation_count;
	bool fast;
	int eye_image;
	int image;

public:
	EnemyTypeBase(class EnemyBase* e);


	virtual ~EnemyTypeBase() = default;

public:
	//�����������֐�
	virtual void Initialize();

	//�X�V����
	void Update(float delta_second ,class EnemyBase* e);

	//�`�揈��
	void Draw(const Vector2D& screen_offset) const;

	//�I�������֐�
	void Finalize();



protected:
	virtual void AnimationControl(float delta_second);
	void Movement(float delta_second);
	virtual void IdolMove(float delta_second);
	virtual void PatorolMove(float delta_second);
	void IzikeMove(float delta_second);
	void EscapeMove(float delta_second);
	void EscMonsterRoom(float delta_second);

protected:
	virtual void AttackMove(float delta_second, Player* playerdate);
};

 