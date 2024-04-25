#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy() : animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

Enemy::~Enemy()
{
}

//����������
void Enemy::Initialize() 
{
	animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");

	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�{�b�N�X�G�l�~�[�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	scale = 64.0;

	//�����摜�̐ݒ�
	image = animation[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(-1.0f, 0.0f);
}

//�X�V����
void Enemy::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimeControl();

	if (location.x < 60)
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

	__super::Draw();
}

//�I��������
void Enemy::Finalize()
{
	//�摜�̍폜
	for (int i = 0 ; i < 2 ; i++)
	{
		DeleteGraph(animation[i]);
	}
}

//�����������̏���
void Enemy::OnHitCollision(GameObject* hit_object)
{
	direction = 0.0f;
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
	if (animation_count >= 60)
	{
		//�J�E���g���Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}