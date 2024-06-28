#include"Enemy.h"
#include"DxLib.h"
#include"stdlib.h"
#include"time.h"

Enemy::Enemy() : animation_count(0), direction(0.0f), flag_count(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
	shotflag = false;
	hitflag = false;
}

Enemy::~Enemy()
{
}

//����������
void Enemy::Initialize()
{
	srand((unsigned int)time(NULL));
	int RandomSpeed =  1 + rand() % 4;

	//�摜�̓ǂݍ���
	if (location.y >= 390.0f)
	{
		animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
		animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");
	}
	else if (location.y >= 290.0f)
	{
		animation[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
		animation[1] = LoadGraph("Resource/Images/WingEnemy/2.png");
	}
	else if (location.y >= 190.0f)
	{
		animation[0] = LoadGraph("Resource/Images/Harpy/1.png");
		animation[1] = LoadGraph("Resource/Images/Harpy/2.png");
	}
	
	if (location.x == 640.0f)
	{
		direction.x = -RandomSpeed;
	}
	else
	{
		direction.x = RandomSpeed;
	}

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�G�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	type = ENEMY;

}

//�X�V����
void Enemy::Update()
{
	flag_count++;
	if (flag_count >= 180)
	{
		if (shotflag == false)
		{
			shotflag = true;
			flag_count = 0;
		}
	}
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void Enemy::Draw() const
{
	//�摜���]�t���O
	int flip_flag = FALSE;

	//�i�s�����ɂ���āA���]��Ԃ����肷��
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//������Ƀn�R�e�L�摜��`�悷��
	DrawRotaGraphF(location.x, location.y, 0.7, radian, image, TRUE, flip_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void Enemy::Finalize()
{
	//�g�p�����摜�����
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
void Enemy::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->GetType() == BOMB)
	{
		//�����������̏���
		direction = 0.0f;
		hitflag = true;
	}
}

bool Enemy::GetFlag()
{
		bool flag = shotflag;
		shotflag = false;
		return flag;
	
}

bool Enemy::GetHitFlag()
{
	return hitflag;
}
//�ړ�����
void Enemy::Movement()
{
	//��ʒ[�ɓ��B������A�i�s�����𔽓]����
	/*if (((location.x + direction.x) < box_size.x) ||
		(640.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}
	if (((location.y + direction.y) < box_size.y) ||
		(480.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}*/

	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
	if (location.x >= 660 || location.x <= -30)
	{
		hitflag = true;
	}
}

//�A�j���[�V��������
void Enemy::AnimationControl()
{
	//�A�j���[�V�����J�E���g�����Z����
	animation_count++;

	//30�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		animation_count = 0;
		{
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
}