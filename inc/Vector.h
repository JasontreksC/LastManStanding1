#pragma once
#define T_PI 3.141592f
#define DegreeToRadian(x)  (x *(T_PI / 180.0f))
#define RadianToDegree(x) (x *(180.0f / T_PI))
#define T_Epsilon 0.001f

struct Float2
{
	union
	{
		struct {
			float x;
			float y;
		};
		float v[2];
	};
};

struct Float3
{
	union
	{
		struct {
			float x;
			float y;
			float z;
		};
		float v[3];
	};
};

struct Float4
{
	union
	{
		struct {
			float x;
			float y;
			float z;
			float w;
		};
		float v[4];
	};
};

class Vector2D : public Float2
{
public:
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(const Vector2D& v);

public:
	Vector2D operator + (Vector2D& v);
	Vector2D operator - (Vector2D& v);
	Vector2D operator * (float scala);
	Vector2D operator / (float scala);
	Vector2D operator *= (float scala);
	Vector2D operator += (Vector2D& v);
	Vector2D operator -= (Vector2D& v);
	bool      operator == (Vector2D& v);
	bool      operator <= (Vector2D& v);
	bool      operator >= (Vector2D& v);
public:
	float     LengthSquared();
	float     Length();
	void      Normalized();
	Vector2D Identity();
	float     Angle(Vector2D& v);
};

class Vector4D : public Float4
{
public:
	Vector4D();
	Vector4D(float x, float y, float z, float w);
	Vector4D(const Vector4D& v);
public:
	Vector4D operator + (Vector4D& v);
	Vector4D operator - (Vector4D& v);
	Vector4D operator * (float scala);
	Vector4D operator / (float scala);
	Vector4D operator *= (float scala);
	Vector4D operator += (Vector4D& v);
	Vector4D operator -= (Vector4D& v);
	bool      operator == (Vector4D& v);
	bool      operator <= (Vector4D& v);
	bool      operator >= (Vector4D& v);
public:
	float     LengthSquared();
	float     Length();
	void      Normalized();
	Vector4D Identity();
	float     Angle(Vector4D& v);
};

class Vector : public Float3
{
public:
	Vector();
	Vector(float x, float y, float z);
	Vector(const Vector& v);
public:
	Vector operator + (Vector& v);
	Vector operator - (Vector& v);
	Vector operator * (float scala);
	Vector operator / (float scala);
	Vector operator *= (float scala);
	Vector operator += (Vector& v);
	Vector operator -= (Vector& v);
	bool      operator == (Vector& v);
	bool      operator <= (Vector& v);
	bool      operator >= (Vector& v);
public:
	float     LengthSquared();
	float     Length();
	void      Normalized();
	Vector Identity();
	float     Angle(Vector& v);
};

