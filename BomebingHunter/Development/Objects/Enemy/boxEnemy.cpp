#include "boxEnemy.h"
#include "DxLib.h"

boxEnemy::boxEnemy() : animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

boxEnemy::~boxEnemy()
{
}

//����������
void boxEnemy::Initialize() 
{
	animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");
	float randam = (GetRand(20) + 1.0) / 10;


	for (int i = 0; i < 4; i++)
	{
		if (animation[i] == -1)
		{
			throw("�{�b�N�X�G�l�~�[�̉摜������܂���\n");
		}
	}
	

	if (location.x >= 590.0f)
	{
		randam *= -1;
	}

	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(randam, 0.0f);
}

//�X�V����
void boxEnemy::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimeControl();

	if (location.x < 0)
	{
		Finalize();
	}
}

//�`�揈��
void boxEnemy::Draw() const
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
void boxEnemy::Finalize()
{
	//�摜�̍폜
	for (int i = 0 ; i < 2 ; i++)
	{
		DeleteGraph(animation[i]);
	}
}

//�����������̏���
void boxEnemy::OnHitCollision(GameObject* hit_object)
{
}

void boxEnemy::Movement()
{
	location += direction;
}

void boxEnemy::AnimeControl()
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
		else if(image == animation[1])
		{
			image = animation[0];
		}
	}
}