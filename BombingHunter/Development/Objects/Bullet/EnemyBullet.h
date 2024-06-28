#pragma once

#include"../GameObject.h"
class EnemyBullet : public GameObject
{
private:
	int animation[4];
	int animation_count;
	Vector2D direction;
	float speed;
	bool hitflag;          //�����������ǂ���
	bool animflag;

public:
	EnemyBullet();
	virtual ~EnemyBullet();

	virtual void Initialize() override;     //����������
	virtual void Update() override;          //�X�V����
	virtual void Draw() const override;      //�`�揈��
	virtual void Finalize() override;        //�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;
	bool GetHitFlag();

private:
	void Movement();
	void AnimationControl();
};

