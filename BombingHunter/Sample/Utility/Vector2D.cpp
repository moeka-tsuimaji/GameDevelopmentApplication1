#include"Vector2D.h"
#include<math.h>

//�R���X�g���N�^
Vector2D::Vector2D() : x(0.0f), y(0.0f)    //���������X�g
{
}

Vector2D::Vector2D(float scalar) : x(scalar), y(scalar)
{
}

Vector2D::Vector2D(float mx, float my) : x(mx), y(my)
{
}

//�f�X�g���N�^
Vector2D::~Vector2D()
{
}

//������������Z�q�I�[�o�[���[�h���Ă���
Vector2D& Vector2D::operator=(const Vector2D& location)
{
	//���g�̃����o�ϐ����Ɉ����̒l��������
	this->x = location.x;
	//���g�̃����o�ϐ����Ɉ����̒l��������
	this->y = location.y;

	//�������g��Ԃ�
	return *this;
}

//���Z����
const Vector2D Vector2D::operator+(const Vector2D& location) const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x + location.x;
	result.y = this->y + location.y;
	
	return result;
}

//���ȑ���i���Z)
Vector2D& Vector2D::operator+=(const Vector2D& location)
{
	//���Z���
	this->x += location.x;
	this->y += location.y;

	//�������g��Ԃ�
	return *this;
}

const Vector2D Vector2D::operator-(const Vector2D& location) const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x - location.x;
	result.y = this->y - location.y;

	return result;
}

Vector2D& Vector2D::operator-=(const Vector2D& location)
{
	//���Z�������
	this->x -= location.x;
	this->y -= location.y;

	//�������g��Ԃ�
	return *this;
}

const Vector2D Vector2D::operator*(const float& scalar) const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x * scalar;
	result.y = this->y * scalar;

	return result;
}

const Vector2D Vector2D::operator*(const Vector2D& location) const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x * location.x;
	result.y = this->y * location.y;

	return result;
}

Vector2D& Vector2D::operator*=(const float& scalar)
{
	//��Z�������
	this->x *= scalar;
	this->y *= scalar;

	//�������g��Ԃ�
	return *this;
}

Vector2D& Vector2D::operator*=(const Vector2D& location)
{
	//��Z���
	this->x *= location.x;
	this->y *= location.y;

	//�������g��Ԃ�
	return *this;
}

const Vector2D Vector2D::operator/(const float& scalar) const
{
	//�O���Z���Ă��邩�H�m�F
	if (fabsf(scalar) < 1e-6f)
	{
		return Vector2D(0.0f);
	}

	return Vector2D(this->x / scalar, this->y / scalar);
}

const Vector2D Vector2D::operator/(const Vector2D& location) const
{
	//�O���Z���Ă��邩�H�m�F
	if ((fabsf(location.x) < 1e-6f) || (fabsf(location.y) < 1e-6f))
	{
		return Vector2D(0.0f);
	}
	return Vector2D(this->x / location.x, this->y / location.y);
}

Vector2D& Vector2D::operator/=(const float& scalar)
{
	//�O���Z���Ă��邩�H�m�F
	if (fabsf(scalar) < 1e-6f)
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	else
	{
		this->x /= scalar;
		this->y /= scalar;
	}

	return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D& location)
{
	//�O���Z���Ă��邩�H�m�F
	if ((fabsf(location.x) < 1e-6f) || (fabsf(location.y) < 1e-6f))
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	else
	{
		this->x /= location.x;
		this->y /= location.y;
	}

	return *this;
}

//�����l�ɃL���X�g����
void Vector2D::ToInt(int* x, int* y) const
{
	*x = static_cast<int>(this->x);
	*y = static_cast<int>(this->y);
}