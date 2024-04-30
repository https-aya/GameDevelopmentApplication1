#include "WingEnemy.h"
#include "DxLib.h"

WingEnemy::WingEnemy() : animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

WingEnemy::~WingEnemy()
{
}

//����������
void WingEnemy::Initialize()
{
	animation[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/WingEnemy/2.png");
	float randam = (GetRand(20) + 1.0) / 10;

	for (int i = 0; i < 4; i++)
	{
		if (animation[i] == -1)
		{
			throw("�{�b�N�X�G�l�~�[�̉摜������܂���\n");
		}
	}

	if (location.x >= 500.0f)
	{
		randam *= -1;
	}
	
	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	scale = 64.0;

	//�����摜�̐ݒ�
	image = animation[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(randam, 0.0f);
}

//�X�V����
void WingEnemy::Update()
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
void WingEnemy::Draw() const
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

	//�f�o�b�O�p
#if _DEBUG
//�����蔻��̉���
	Vector2D box_collision_upper_left = location - (Vector2D(1.0f) *
		(float)scale / 2.0f);
	Vector2D box_collision_upper_right = location + (Vector2D(1.0f) *
		(float)scale / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_upper_right.x, box_collision_upper_right.y,
		GetColor(255, 0, 0), FALSE);
#endif
}

//�I��������
void WingEnemy::Finalize()
{
	//�摜�̍폜
	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(animation[i]);
	}
}

//�����������̏���
void WingEnemy::OnHitCollision(GameObject* hit_object)
{
}

void WingEnemy::Movement()
{
	location += direction;
}

void WingEnemy::AnimeControl()
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
		else if (image == animation[1])
		{
			image = animation[0];
		}

		if (image == animation[2])
		{
			image = animation[3];
		}
		else if (image == animation[3])
		{
			image = animation[2];
		}
	}
}