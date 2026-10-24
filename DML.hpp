////////////////////////////////////////////////////////////////
//
// DML | Digla Math Library
// 
////////////////////////////////////////////////////////////////

#ifndef DML_HPP
#define DML_HPP

#include <cmath>

namespace dml {
	template<typename T>
	struct Vector2 {
		T x, y;

		void operator=(const Vector2& other) { x = other.x; y = other.y; }
		bool operator==(const Vector2& other)   { return x == other.x && y == other.y; }
		bool operator>(const Vector2& other)    { return x > other.x && y > other.y; }
		bool operator<(const Vector2& other)    { return x < other.x && y < other.y; }
		bool operator>=(const Vector2& other)   { return x >= other.x && y >= other.y; }
		bool operator<=(const Vector2& other)   { return x <= other.x && y <= other.y; }
		Vector2 operator+(const Vector2& other) { return { x + other.x, y + other.y }; };
		Vector2 operator-(const Vector2& other) { return { x - other.x, y - other.y }; };
		Vector2 operator*(const Vector2& other) { return { x * other.x, y * other.y }; };
		Vector2 operator/(const Vector2& other) { return { x / other.x, y / other.y }; };

		Vector2 operator*(const float& other) { return { x * other, y * other }; }
	};
	
	using Vector2i = Vector2<int>;
	using Vector2ui = Vector2<unsigned int>;
	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;

	template<typename T>
	struct Vector3 {
		T x, y, z;

		void operator=(const Vector3& other)    { x = other.x; y = other.y; z = other.z; }
		bool operator==(const Vector3& other)   { return x == other.x && y == other.y && z == other.z; }
		bool operator>(const Vector3& other)    { return x > other.x && y > other.y && z > other.z; }
		bool operator<(const Vector3& other)    { return x < other.x && y < other.y && z < other.z; }
		bool operator>=(const Vector3& other)   { return x >= other.x && y >= other.y && z >= other.z; }
		bool operator<=(const Vector3& other)   { return x <= other.x && y <= other.y && z <= other.z; }
		Vector3 operator+(const Vector3& other) { return { x + other.x, y + other.y, z + other.z }; }
		Vector3 operator-(const Vector3& other) { return { x - other.x, y - other.y, z - other.z }; }
		Vector3 operator*(const Vector3& other) { return { x * other.x, y * other.y, z * other.z }; }
		Vector3 operator/(const Vector3& other) { return { x / other.x, y / other.y, z / other.z }; }

		Vector3 operator*(const float& other) { return { x * other, y * other, z * other }; }
	};

	using Vector3i = Vector3<int>;
	using Vector3ui = Vector3<unsigned int>;
	using Vector3f = Vector3<float>;
	using Vector3d = Vector3<double>;

	template<typename T>
	struct Vector4 {
		T x, y, z, w;

		void operator=(const Vector4& other) { x = other.x; y = other.y; z = other.z; w = other.w; }
		bool operator==(const Vector4& other) { return x == other.x && y == other.y && z == other.z && w == other.w; }
		bool operator>(const Vector4& other) { return x > other.x && y > other.y && z > other.z && w > other.w; }
		bool operator<(const Vector4& other) { return x < other.x && y < other.y && z < other.z && w < other.w; }
		bool operator>=(const Vector4& other) { return x >= other.x && y >= other.y && z >= other.z && w >= other.w; }
		bool operator<=(const Vector4& other) { return x <= other.x && y <= other.y && z <= other.z && w <= other.w; }
		Vector4 operator+(const Vector4& other) { return { x + other.x, y + other.y, z + other.z, w + other.w }; }
		Vector4 operator-(const Vector4& other) { return { x - other.x, y - other.y, z - other.z, w - other.w }; }
		Vector4 operator*(const Vector4& other) { return { x * other.x, y * other.y, z * other.z, w * other.w }; }
		Vector4 operator/(const Vector4& other) { return { x / other.x, y / other.y, z / other.z, w / other.w }; }
	};

	using Vector4i = Vector3<int>;
	using Vector4ui = Vector3<unsigned int>;
	using Vector4f = Vector3<float>;
	using Vector4d = Vector3<double>;
}

#endif /* DML_HPP */