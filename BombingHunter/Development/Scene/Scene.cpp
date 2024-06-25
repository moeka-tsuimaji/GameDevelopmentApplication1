#include"Scene.h"
#include"../Objects/Player/Player.h"
#include"../Objects/Enemy/Enemy.h"
#include"../Objects/Bullet/Bomb.h"
#include"../Objects/Bullet/EnemyBullet.h"
#include"../Utility/InputControl.h"
#include<stdlib.h>
#include"DxLib.h"

#define D_PIVOT_CENTER
#define CREATE_SPAN (120)

//�R���X�g���N�^
Scene::Scene() : objects()
{
	gh = NULL;
	create_count = NULL;
}

//�f�X�g���N�^
Scene::~Scene()
{
	//�Y��h�~
	Finalize();
}

//����������
void Scene::Initialize()
{
	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f, 50.0f));
	gh = LoadGraph("Resource/Images/BackGround.png");
	create_count = 0;
}

//�X�V����
void Scene::Update()
{ 
	this->create_count++;

	int create_count = 0;
	std::vector<Vector2D> enemy_location;

	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
		if (obj->GetType() == ENEMY)
		{
			if (dynamic_cast<Enemy*>(obj)->GetFlag())
			{
				create_count++;
				enemy_location.push_back((obj)->GetLocation());
			}
		}
	}

		for (int i = 0; i < create_count; i++)
		{
			CreateObject<EnemyBullet>(enemy_location[i]);
		}
		enemy_location.clear();

	//�I�u�W�F�N�g���m�̓����蔻��`�F�b�N
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//�����蔻��`�F�b�N����
			HitCheckObject(objects[i], objects[j]);
		}
	}

	//2�b��1��G�𐶐�����
	if (this->create_count >= CREATE_SPAN)
	{
		int RandomEnemy = GetRand(2);
		int randomlocationflag = GetRand(1);
		float x;
		if (randomlocationflag == 1)
		{
			x = 640.0f;
		}
		else
		{
			x = 0.0f;
		}


		switch (RandomEnemy)
		{
		case 0:
			CreateObject<Enemy>(Vector2D(x, 400.0f));
			break;
		case 1:
			CreateObject<Enemy>(Vector2D(x, 300.0f));
			break;
		case 2:
			CreateObject<Enemy>(Vector2D(x, 200.0f));
			break;
		}
		this->create_count = 0;
	}

	//�e�̐���
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		CreateObject<Bomb>(Vector2D(objects[0]->GetLocation().x, objects[0]->GetLocation().y + 50.0f));
	}

}

//�`�揈��
void Scene::Draw() const
{
	DrawExtendGraph(0, 0, 640, 480, gh, FALSE);
	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//�I��������
void Scene::Finalize()
{
	//�I�u�W�F�N�g���X�g������Ȃ�A�������I������
	if (objects.empty())
	{
		return;
	}

	//�I�u�W�F�N�g���X�g���̃I�u�W�F�N�g���������
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//���I�z��̉��
	objects.clear();
}

#ifdef D_PIVOT_CENTER

//�����蔻��`�F�b�N����(��`�̒��S�œ����蔻������j
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//2�̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;
	
	if (a->GetType() != b->GetType())
	{
		//�������傫�����傫���ꍇ�AHit����Ƃ���
		if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
		{
			//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
			a->OnHitCollision(b);
			b->OnHitCollision(a);
		}
	}
	
}

#else

//�����蔻��`�F�b�N�����i���㒸�_�̍��W���瓖���蔻��v�Z���s���j
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//�E�����_���W���擾����
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();
	//���㒸�_���W���擾����
	Vector2D a_upper_left = a->GetLocation() + a->GetBoxSize();
	Vector2D b_upper_left = b->GetLocation() + b->GetBoxSize();

	//��`A�Ƌ�`B�̈ʒu�֌W�𒲂ׂ�
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
		
	{
		//�I�u�W�F�N�g�ɑ΂���Hit�����ʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#endif // D_PIVOT_CENTER