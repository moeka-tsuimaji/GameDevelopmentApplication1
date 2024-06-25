#pragma once

#include"../GameObject.h"
class Bomb : public GameObject
{
private:
	int animation[4];
	int animation_count;
	float b_speed;

public:
	Bomb();
	virtual ~Bomb();

	virtual void Initialize() override;     //����������
	virtual void Update() override;          //�X�V����
	virtual void Draw() const override;      //�`�揈��
	virtual void Finalize() override;        //�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	void Movement();
	void AnimationControl();
};
