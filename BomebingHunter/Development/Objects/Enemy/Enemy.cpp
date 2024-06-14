#include "Enemy.h"
#include "EnemyBullet.h"
#include "DxLib.h"

Enemy::Enemy() : animation_count(0), max_animation(0), anime_time(0), shot_count(0),shot_rand(0)
{
	for (int i = 0; i < 5; i++)
	{
		animation[i] = NULL;
	}
}

Enemy::~Enemy()
{
}

//����������
void Enemy::Initialize() 
{
	switch (type)
	{
	case 3:
		animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
		animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");
		animation[2] = NULL;
		animation[3] = NULL;
		animation[4] = NULL;
		box_size = 64.0f;
		sca = 10;
		break;
	case 4:
		animation[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
		animation[1] = LoadGraph("Resource/Images/WingEnemy/2.png");
		animation[2] = NULL;
		animation[3] = NULL;
		animation[4] = NULL;
		box_size = 64.0f;
		sca = 10;
		break;
	case 5:
		animation[0] = LoadGraph("Resource/Images/Harpy/1.png");
		animation[1] = LoadGraph("Resource/Images/Harpy/2.png");
		animation[2] = NULL;
		animation[3] = NULL;
		animation[4] = NULL;
		box_size = 64.0f;
		sca = -20;
		break;
	case 6:
		animation[0] = LoadGraph("Resource/Images/GoldEnemy/1.png");
		animation[1] = LoadGraph("Resource/Images/GoldEnemy/2.png");
		animation[2] = LoadGraph("Resource/Images/GoldEnemy/3.png");
		animation[3] = LoadGraph("Resource/Images/GoldEnemy/4.png");
		animation[4] = LoadGraph("Resource/Images/GoldEnemy/5.png");
		box_size = 32.0f;
		sca = 100;
		break;
	}

	for (int i = 0; i < 5; i++)
	{
		if (animation[i] != NULL)
		{
			max_animation++;
		}
		else if (animation[i] == -1)
		{
			throw("�G�l�~�[�̉摜������܂���\n");
		}
	}
	
	float random = (GetRand(10) + 10.0) / 10;

	if (location.x >= 50.0f)
	{
		random *= -1;
	}

	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	shot_rand = 100;

	//�����摜�̐ݒ�
	image = animation[0];

	//�����i�s�����̐ݒ�
	SetDirection(Vector2D(random, 0.0f));
}

//�X�V����
void Enemy::Update()
{
	shot_count++;

	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimeControl();

	if (type != 5)
	{
		if (shot_count >= shot_rand)
		{
			shot_flag = TRUE;
			shot_count = 0;
			shot_rand = (GetRand(2) + 1) * 100;
		}
		else
		{
			shot_flag = FALSE;
		}
	}
	
	if (location.x < 0 || location.x > 630)
	{
		Finalize();
	}
}

//�`�揈��
void Enemy::Draw() const
{
	int flip_flag = FALSE;

	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	DrawRotaGraphF(location.x, location.y, 0.5, radian, image, TRUE, flip_flag);
	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void Enemy::Finalize()
{
	//�摜�̍폜
	for (int i = 0 ; i < 5 ; i++)
	{
		DeleteGraph(animation[i]);
	}
	box_size = NULL;
	direction = 0.0f;
	location = NULL;
	Delete = TRUE;
}

//�����������̏���
void Enemy::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->GetType() == 2)
	{
		Finalize();
	}
}

void Enemy::Movement()
{
	location += direction;
}

void Enemy::AnimeControl()
{
	//�A�j���[�V�����J�E���g�����Z����
	animation_count++;

	//60�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		//�J�E���g���Z�b�g
		animation_count = 0;
		anime_time++;

		//�摜�̐؂�ւ�
		if (image == animation[max_animation - 1])
		{
			anime_time = 0;
			image = animation[0];
		}
		else
		{
			image = animation[anime_time];
		}

	}
}