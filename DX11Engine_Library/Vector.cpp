#include "pch.h"
#include "Vector.h"
Vector4D::Vector4D()
{
	x = y = z = w = 0.0f;
}
Vector4D::Vector4D(float x, float y, float z, float w)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
}
Vector4D::Vector4D(const Vector4D& v)
{
	x = v.x;
	y = v.y;
}
Vector4D Vector4D::operator + (Vector4D& v)
{
	return Vector4D(x + v.x, y + v.y, z + v.z, w + v.w);
}
Vector4D Vector4D::operator - (Vector4D& v)
{
	return Vector4D(x - v.x, y - v.y, z - v.z, w - v.w);
}
Vector4D Vector4D::operator * (float scala)
{
	return Vector4D(x * scala, y * scala, z * scala, w * scala);
}
Vector4D Vector4D::operator / (float scala)
{
	return Vector4D(x / scala, y / scala, z / scala, w / scala);
}
Vector4D Vector4D::operator *= (float scala)
{
	x *= scala;
	y *= scala;
	z *= scala;
	w *= scala;
	return *this;
}
Vector4D Vector4D::operator += (Vector4D& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}
Vector4D Vector4D::operator -= (Vector4D& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}
bool      Vector4D::operator == (Vector4D& v)
{
	if (fabs(x - v.x) < T_Epsilon)
	{
		if (fabs(y - v.y) < T_Epsilon)
		{
			if (fabs(z - v.z) < T_Epsilon)
			{
				if (fabs(w - v.w) < T_Epsilon)
				{
					return true;
				}
			}
			return true;
		}
	}
	return false;
}
bool      Vector4D::operator <= (Vector4D& b)
{
	if (x <= b.x)
	{
		if (y <= b.y)
		{
			if (z <= b.z)
			{
				if (w <= b.w)
				{
					return true;
				}
			}
			return true;
		}
	}
	return false;
}
bool      Vector4D::operator >= (Vector4D& b)
{
	if (x >= b.x)
	{
		if (y >= b.y)
		{
			if (z >= b.z)
			{
				if (w >= b.w)
				{
					return true;
				}
			}
			return true;
		}
	}
	return false;
}
float Vector4D::LengthSquared()
{
	return (x * x + y * y, z * z + w * w);
}

float Vector4D::Length()
{
	return sqrt(LengthSquared());
}
// 정규화 -> 단위벡터(자신을) 계산
void Vector4D::Normalized()
{
	float fInvertLength = 1.0f / Length();
	x = x * fInvertLength;
	y = y * fInvertLength;
	z = z * fInvertLength;
	w = w * fInvertLength;
}
// 단위벡터 반환
Vector4D Vector4D::Identity()
{
	Vector4D ret = *this;
	float fInvertLength = 1.0f / Length();
	ret.x = ret.x * fInvertLength;
	ret.y = ret.y * fInvertLength;
	ret.z = ret.z * fInvertLength;
	ret.w = ret.w * fInvertLength;
	return ret;
}
float     Vector4D::Angle(Vector4D& v)
{
	float fCos = x * v.x + y * v.y + z * v.z + w * v.w;//내적
	fCos = fCos / (Length() * v.Length());
	float fRadian = acos(fCos);
	float fDegree = RadianToDegree(fRadian);
	return fDegree;
}


Vector2D::Vector2D()
{
	x = y = 0.0f;
}
Vector2D::Vector2D(float x, float y)
{
	v[0] = x;
	v[1] = y;
}
Vector2D::Vector2D(const Vector2D& v)
{
	x = v.x;
	y = v.y;
}
Vector2D Vector2D::operator + (Vector2D& v)
{
	return Vector2D(x + v.x, y + v.y);
}
Vector2D Vector2D::operator - (Vector2D& v)
{
	return Vector2D(x - v.x, y - v.y);
}
Vector2D Vector2D::operator * (float scala)
{
	return Vector2D(x * scala, y * scala);
}
Vector2D Vector2D::operator / (float scala)
{
	return Vector2D(x / scala, y / scala);
}
Vector2D Vector2D::operator *= (float scala)
{
	x *= scala;
	y *= scala;
	return *this;
}
Vector2D Vector2D::operator += (Vector2D& v)
{
	x += v.x;
	y += v.y;
	return *this;
}
Vector2D Vector2D::operator -= (Vector2D& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}
bool      Vector2D::operator == (Vector2D& v)
{
	if (fabs(x - v.x) < T_Epsilon)
	{
		if (fabs(y - v.y) < T_Epsilon)
		{
			return true;
		}
	}
	return false;
}
bool      Vector2D::operator <= (Vector2D& b)
{
	if (x <= b.x)
	{
		if (y <= b.y)
		{
			return true;
		}
	}
	return false;
}
bool      Vector2D::operator >= (Vector2D& b)
{
	if (x >= b.x)
	{
		if (y >= b.y)
		{
			return true;
		}
	}
	return false;
}
float Vector2D::LengthSquared()
{
	return (x * x + y * y);
}

float Vector2D::Length()
{
	return sqrt(LengthSquared());
}
// 정규화 -> 단위벡터(자신을) 계산
void Vector2D::Normalized()
{
	float fInvertLength = 1.0f / Length();
	x = x * fInvertLength;
	y = y * fInvertLength;
}
// 단위벡터 반환
Vector2D Vector2D::Identity()
{
	Vector2D ret = *this;
	float fInvertLength = 1.0f / Length();
	ret.x = ret.x * fInvertLength;
	ret.y = ret.y * fInvertLength;
	return ret;
}
float     Vector2D::Angle(Vector2D& v)
{
	float fCos = x * v.x + y * v.y;//내적
	fCos = fCos / (Length() * v.Length());
	float fRadian = acos(fCos);
	float fDegree = RadianToDegree(fRadian);
	return fDegree;
}


///// 3d
Vector::Vector()
{
	x = y = z = 0.0f;
}
Vector::Vector(float x, float y, float z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}
Vector::Vector(const Vector& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}
Vector Vector::operator + (Vector& v)
{
	return Vector(x + v.x, y + v.y, z + v.z);
}
Vector Vector::operator - (Vector& v)
{
	return Vector(x - v.x, y - v.y, z - v.z);
}
Vector Vector::operator * (float scala)
{
	return Vector(x * scala, y * scala, z * scala);
}
Vector Vector::operator / (float scala)
{
	return Vector(x / scala, y / scala, z / scala);
}
Vector Vector::operator *= (float scala)
{
	x *= scala;
	y *= scala;
	z *= scala;
	return *this;
}
Vector Vector::operator += (Vector& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
Vector Vector::operator -= (Vector& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
bool      Vector::operator <= (Vector& b)
{
	if (fabs(x - b.x) <= T_Epsilon)
	{
		if (fabs(y - b.y) <= T_Epsilon)
		{
			if (fabs(z - b.z) <= T_Epsilon)
			{
				return true;
			}
		}
	}
	return false;
}
bool      Vector::operator >= (Vector& b)
{
	if (fabs(x - b.x) >= T_Epsilon)
	{
		if (fabs(y - b.y) >= T_Epsilon)
		{
			if (fabs(z - b.z) >= T_Epsilon)
			{
				return true;
			}
		}
	}
	return false;
}
bool      Vector::operator == (Vector& v)
{
	if (fabs(x - v.x) < T_Epsilon)
	{
		if (fabs(y - v.y) < T_Epsilon)
		{
			if (fabs(z - v.z) < T_Epsilon)
			{
				return true;
			}
		}
	}
	return false;
}

float Vector::LengthSquared()
{
	return (x * x + y * y + z * z);
}

float Vector::Length()
{
	return sqrt(LengthSquared());
}
// 정규화 -> 단위벡터(자신을) 계산
void Vector::Normalized()
{
	float fInvertLength = 1.0f / Length();
	x = x * fInvertLength;
	y = y * fInvertLength;
	z = z * fInvertLength;
}
// 단위벡터 반환
Vector Vector::Identity()
{
	Vector ret = *this;
	float fInvertLength = 1.0f / Length();
	ret.x = ret.x * fInvertLength;
	ret.y = ret.y * fInvertLength;
	ret.z = ret.z * fInvertLength;
	return ret;
}
float     Vector::Angle(Vector& v)
{
	float fCos = x * v.x + y * v.y + z * v.z;//내적
	fCos = fCos / (Length() * v.Length());
	float fRadian = acos(fCos);
	float fDegree = RadianToDegree(fRadian);
	return fDegree;
}