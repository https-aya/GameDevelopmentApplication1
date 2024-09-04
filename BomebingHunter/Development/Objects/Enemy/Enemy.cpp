#include "Enemy.h"
#include "EnemyBullet.h"
#include "DxLib.h"

Enemy::Enemy() : animation_count(0), max_animation(0), anime_time(0), shot_count(0),shot_rand(0),alpha(0),blend_flag(FALSE),anim_location(0.0f)
{

}

Enemy::~Enemy()
{
}

//����������
void Enemy::Initialize() 
{

	std::vector<int> tmp;
	switch (type)
	{
	case eBoxEnemy:
		tmp = rm->GetImages("Resource/Images/BoxEnemy/1.png");
		animation.push_back(tmp[0]);
		tmp = rm->GetImages("Resource/Images/BoxEnemy/2.png");
		animation.push_back(tmp[0]);
		tmp = rm->GetSounds("Resource/Sounds/Boss_gahee.wav");
		sound.push_back(tmp[0]);
		box_size = 64.0f;
		score = 10;
		break;
	case eFlyEnemy:
		tmp = rm->GetImages("Resource/Images/WingEnemy/1.png");
		animation.push_back(tmp[0]);
		tmp = rm->GetImages("Resource/Images/WingEnemy/2.png");
		animation.push_back(tmp[0]);
		tmp = rm->GetSounds("Resource/Sounds/teki_gahee.wav");
		sound.push_back(tmp[0]);
		box_size = 64.0f;
		score = 10;
		break;
	case eHarpy:
		tmp = rm->GetImages("Resource/Images/Harpy/1.png");
		animation.push_back(tmp[0]);
		tmp = rm->GetImages("Resource/Images/Harpy/2.png");
		animation.push_back(tmp[0]);
		tmp = rm->GetSounds("Resource/Sounds/pokan.wav");
		sound.push_back(tmp[0]);
		box_size = 64.0f;
		score = -20;
		break;
	case eGoldEnemy:
		tmp = rm->GetImages("Resource/Images/GoldEnemy/1.png");
		animation.push_back(tmp[0]);
		tmp = rm->GetImages("Resource/Images/GoldEnemy/2.png");
		animation.push_back(tmp[0]);
		tmp = rm->GetImages("Resource/Images/GoldEnemy/3.png");
		animation.push_back(tmp[0]);
		tmp = rm->GetImages("Resource/Images/GoldEnemy/4.png");
		animation.push_back(tmp[0]);
		tmp = rm->GetImages("Resource/Images/GoldEnemy/5.png");
		animation.push_back(tmp[0]);
		tmp = rm->GetSounds("Resource/Sounds/arrows_perfect03_short.wav");
		sound.push_back(tmp[0]);
		box_size = 32.0f;
		score = 100;
		break;
	}

	tmp = rm->GetSounds("Resource/Sounds/explosion.wav");
	sound.push_back(tmp[0]);

	for (int i = 0; i < animation.size(); i++)
	{
		max_animation++;
		if (animation[i] == -1)
		{
			throw("�G�l�~�[�̉摜������܂���\n");
		}
	}
	for (int i = 0; i < sound.size(); i++)
	{
		if (sound[i] == -1)
		{
			throw("�G�l�~�[(%c)�̃T�E���h������܂���", type);
		}
	}
	
	float random = (GetRand(10) + 10.0f) / 10.0f;

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
	
	//�����x�̏����l
	alpha = 255;

	fly_text->Initialize();

	//�����i�s�����̐ݒ�
	SetDirection(Vector2D(random, 0.0f));
}

//�X�V����
void Enemy::Update()
{
	if (blend_flag == FALSE)
	{
		shot_count++;

		if (type == eBoxEnemy)
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
	else
	{
		shot_flag = FALSE;
	}

	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimeControl();

	if (alpha <= 0)
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

	if (blend_flag != FALSE)
	{
		fly_text->Draw(anim_location);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawRotaGraphF(anim_location.x, anim_location.y, 0.5, radian, image, TRUE, flip_flag);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		DrawRotaGraphF(location.x, location.y, 0.5, radian, image, TRUE, flip_flag);

	}
}

//�I��������
void Enemy::Finalize()
{
	//�摜�̍폜
	animation.clear();
	anim_location = NULL;
	Delete = TRUE;
}

//�����������̏���
void Enemy::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->GetType() == eBome)
	{
		if (blend_flag != TRUE)
		{
			PlaySoundMem(sound[0], DX_PLAYTYPE_BACK, TRUE);
			PlaySoundMem(sound[1], DX_PLAYTYPE_BACK, TRUE);
			fly_text->SetFlyText(score);
			blend_flag = TRUE;
			box_size = NULL;
			anim_location = location;
			direction = Vector2D(0.0f, 0.1f);
			location = NULL;
			score = 0;
		}
	}
}

void Enemy::Movement()
{
	if (blend_flag != TRUE)
	{
		location += direction;
	}
	else
	{
		anim_location += direction;
	}
	
}

void Enemy::AnimeControl()
{
	if (blend_flag == TRUE)
	{

		alpha-=2;
	}
	else
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
}