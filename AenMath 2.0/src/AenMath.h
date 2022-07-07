#pragma once
#include<cmath>
#include<array>
#include<limits>
#include<iostream>
#include<stdexcept>
#include<algorithm>
#include<DirectXMath.h>
#include<DirectXCollision.h>


// 3D Intersection needs HitNormal intergration and intersection tests.


namespace Aen {

	#ifdef _WINDOWS_
	#undef near
	#undef far
	#undef max
	#endif

	// ----------------------------------------------------------------- //
	//                          Pre definition                           //
	// ----------------------------------------------------------------- //

	namespace Concealed {
		
		template<class T, uint32_t N>
		struct VecT {
			T arr[N];
		};

		template<> struct VecT<float, 2u>;
		template<> struct VecT<int, 2u>;

		template<> struct VecT<float, 3u>;
		template<> struct VecT<int, 3u>;

		template<> struct VecT<float, 4u>;
		template<> struct VecT<int, 4u>;


		template<class T, uint32_t R, uint32_t C>
		struct MatT {
			T arr[R][C];
		};

		template<> struct MatT<float, 3u, 3u>;
		template<> struct MatT<float, 3u, 4u>;
		template<> struct MatT<float, 4u, 3u>;
		template<> struct MatT<float, 4u, 4u>;
	};

	struct Color;
	struct Quat;
	

	// ----------------------------------------------------------------- //
	//                        Load/Store Functions                       //
	// ----------------------------------------------------------------- //

	namespace Concealed {

		using XMVEC = DirectX::XMVECTOR;
		using XMMAT = DirectX::XMMATRIX;

		// Load

		template<class T0, class T1> inline const T0 XMLoad(const T1* t) noexcept {}

		template<> inline const XMVEC XMLoad(const float* t) noexcept {
			return DirectX::XMLoadFloat(t);
		}
		template<> inline const XMVEC XMLoad(const VecT<float, 2u>* t) noexcept {
			return DirectX::XMLoadFloat2((DirectX::XMFLOAT2*)t);
		}
		template<> inline const XMVEC XMLoad(const VecT<float, 3u>* t) noexcept {
			return DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)t);
		}
		template<> inline const XMVEC XMLoad(const VecT<float, 4u>* t) noexcept {
			return DirectX::XMLoadFloat4((DirectX::XMFLOAT4*)t);
		}
		template<> inline const XMVEC XMLoad(const Quat* t) noexcept {
			return DirectX::XMLoadFloat4((DirectX::XMFLOAT4*)t);
		}
		template<> inline const XMVEC XMLoad(const VecT<int, 2u>* t) noexcept {
			return DirectX::XMLoadSInt2((DirectX::XMINT2*)t);
		}
		template<> inline const XMVEC XMLoad(const VecT<int, 3u>* t) noexcept {
			return DirectX::XMLoadSInt3((DirectX::XMINT3*)t);
		}
		template<> inline const XMVEC XMLoad(const VecT<int, 4u>* t) noexcept {
			return DirectX::XMLoadSInt4((DirectX::XMINT4*)t);
		}
		template<> inline const XMMAT XMLoad(const DirectX::XMFLOAT3X3* t) noexcept {
			return DirectX::XMLoadFloat3x3(t);
		}
		template<> inline const XMMAT XMLoad(const DirectX::XMFLOAT3X4* t) noexcept {
			return DirectX::XMLoadFloat3x4(t);
		}
		template<> inline const XMMAT XMLoad(const DirectX::XMFLOAT4X3* t) noexcept {
			return DirectX::XMLoadFloat4x3(t);
		}
		template<> inline const XMMAT XMLoad(const DirectX::XMFLOAT4X4* t) noexcept {
			return DirectX::XMLoadFloat4x4(t);
		}


		// Store

		template<class T0, class T1> inline void XMStore(T0* d, const T1& t) noexcept {}

		template<> inline void XMStore(float* d, const DirectX::XMVECTOR& t) noexcept {
			DirectX::XMStoreFloat(d, t);
		}
		template<> inline void XMStore(VecT<float, 2u>* d, const XMVEC& t) noexcept {
			DirectX::XMStoreFloat2((DirectX::XMFLOAT2*)d, t);
		}
		template<> inline void XMStore(VecT<float, 3u>* d, const XMVEC& t) noexcept {
			DirectX::XMStoreFloat3((DirectX::XMFLOAT3*)d, t);
		}
		template<> inline void XMStore(VecT<float, 4u>* d, const XMVEC& t) noexcept {
			DirectX::XMStoreFloat4((DirectX::XMFLOAT4*)d, t);
		}
		template<> inline void XMStore(Quat* d, const XMVEC& t) noexcept {
			DirectX::XMStoreFloat4((DirectX::XMFLOAT4*)d, t);
		}
		template<> inline void XMStore(VecT<int, 2u>* d, const XMVEC& t) noexcept {
			DirectX::XMStoreSInt2((DirectX::XMINT2*)d, t);
		}
		template<> inline void XMStore(VecT<int, 3u>* d, const XMVEC& t) noexcept {
			DirectX::XMStoreSInt3((DirectX::XMINT3*)d, t);
		}
		template<> inline void XMStore(VecT<int, 4u>* d, const XMVEC& t) noexcept {
			DirectX::XMStoreSInt4((DirectX::XMINT4*)d, t);
		}
		template<> inline void XMStore(DirectX::XMFLOAT3X3* d, const XMMAT& t) noexcept {
			DirectX::XMStoreFloat3x3(d, t);
		}
		template<> inline void XMStore(DirectX::XMFLOAT3X4* d, const XMMAT& t) noexcept {
			DirectX::XMStoreFloat3x4(d, t);
		}
		template<> inline void XMStore(DirectX::XMFLOAT4X3* d, const XMMAT& t) noexcept {
			DirectX::XMStoreFloat4x3(d, t);
		}
		template<> inline void XMStore(DirectX::XMFLOAT4X4* d, const XMMAT& t) noexcept {
			DirectX::XMStoreFloat4x4(d, t);
		}

	}
	

	namespace Concealed {
		
		// ----------------------------------------------------------------- //
		//				  __     __        _								 //
		//				  \ \   / /__  ___| |_ ___  _ __ ___				 //
		//				   \ \ / / _ \/ __| __/ _ \| '__/ __|				 //
		//				    \ V /  __/ (__| || (_) | |  \__ \				 //
		//				 	 \_/ \___|\___|\__\___/|_|  |___/				 //
		// ----------------------------------------------------------------- //


		// ----------------------------------------------------------------- //
		//                          Vector2 Float                            //
		// ----------------------------------------------------------------- //
		template<>
		struct VecT<float, 2u> : public DirectX::XMFLOAT2 {

			constexpr VecT<float, 2u>() noexcept: XMFLOAT2(0.f, 0.f) {};
			constexpr VecT<float, 2u>(const float& n) noexcept: XMFLOAT2(n, n) {};
			constexpr VecT<float, 2u>(const float& x, const float& y) noexcept: XMFLOAT2(x, y) {};
			constexpr VecT<float, 2u>(const VecT<float, 2u>& rhs) noexcept: XMFLOAT2(rhs.x, rhs.y) {};
			explicit VecT<float, 2u>(const float rhs[2]) noexcept: XMFLOAT2(rhs[0], rhs[1]) {};

			// Unary Operators

			VecT<float, 2u> operator+ () const noexcept {
				return *this;
			}
			VecT<float, 2u> operator- () const noexcept {
				VecT<float, 2u> out;
				out.x = -x;
				out.y = -y;
				return out;
			}
			const VecT<float, 2u>& operator++ () noexcept {
				Increment(1.f, 1.f);
				return *this;
			}
			const VecT<float, 2u>& operator++ (int) noexcept {
				Increment(1.f, 1.f);
				return *this;
			}
			const VecT<float, 2u>& operator-- () noexcept {
				Decrement(1.f, 1.f);
				return *this;
			}
			const VecT<float, 2u>& operator-- (int) noexcept {
				Decrement(1.f, 1.f);
				return *this;
			}

			// Assignment Operators

			const VecT<float, 2u>& operator= (const VecT<float, 2u>& rhs) noexcept {
				x = rhs.x;
				y = rhs.y;
				return *this;
			}
			const VecT<float, 2u>& operator= (const float rhs[2]) noexcept {
				x = rhs[0];
				y = rhs[1];
				return *this;
			}
			const VecT<float, 2u>& operator+= (const VecT<float, 2u>& rhs) noexcept {
				Increment(rhs.x, rhs.y);
				return *this;
			}
			const VecT<float, 2u>& operator+= (const float rhs[2]) noexcept {
				Increment(rhs[0], rhs[1]);
				return *this;
			}
			const VecT<float, 2u>& operator-= (const VecT<float, 2u>& rhs) noexcept {
				Decrement(rhs.x, rhs.y);
				return *this;
			}
			const VecT<float, 2u>& operator-= (const float rhs[2]) noexcept {
				Decrement(rhs[0], rhs[1]);
				return *this;
			}

			// Binary Operator

			const VecT<float, 2u> operator+ (const VecT<float, 2u>& rhs) const noexcept {
				return Add(rhs.x, rhs.y);
			}
			const VecT<float, 2u> operator+ (const float rhs[2]) const noexcept {
				return Add(rhs[0], rhs[1]);
			}
			const VecT<float, 2u> operator- (const VecT<float, 2u>& rhs) const noexcept {
				return Subtract(rhs.x, rhs.y);
			}
			const VecT<float, 2u> operator- (const float rhs[2]) const noexcept {
				return Subtract(rhs[0], rhs[1]);
			}
			const VecT<float, 2u> operator* (const float rhs) const noexcept {
				VecT<float, 2u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorScale(temp, rhs);
				XMStore(&out, temp);
				return out;
			}
			const float operator* (const VecT<float, 2u>& rhs) const noexcept {
				return Dot(rhs.x, rhs.y);
			}
			const float operator* (const float rhs[2]) const noexcept {
				return Dot(rhs[0], rhs[1]);
			}

			// Bitwise Operator

			friend std::ostream& operator<<	(std::ostream& out, const VecT<float, 2u>& rhs) noexcept {
				out << "[" << rhs.x << ", " << rhs.y << "]";
				return out;
			}

			// Member Access Operator

			float& operator[] (const uint32_t& i) {
				#if _DEBUG
					if(i > 1u) throw std::invalid_argument("Access Violation!");
				#endif
				return reinterpret_cast<float*>(this)[i];
			}
			const float& operator[] (const uint32_t& i) const {
				#if _DEBUG
					if(i > 1u) throw std::invalid_argument("Access Violation!");
				#endif
				return reinterpret_cast<const float*>(this)[i];
			}

			// Cast Operator

			operator const VecT<int, 2u>() const;
			
			explicit operator const VecT<float, 3u>() const;
			explicit operator const VecT<int, 3u>() const;

			explicit operator const VecT<float, 4u>() const;
			explicit operator const VecT<int, 4u>() const;

			// Functions

			const float Magnitude() const noexcept {
				float out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVector2Length(temp);
				XMStore(&out, temp);
				return out;
			};
			const VecT<float, 2u> Normalized() const noexcept {
				VecT<float, 2u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVector2Normalize(temp);
				XMStore(&out, temp);
				return out;
			}
			const VecT<float, 2u> Sign() const noexcept {
				VecT<float, 2u> out;
				out.x = static_cast<float>(x > 0.f) - static_cast<float>(x < 0.f);
				out.y = static_cast<float>(y > 0.f) - static_cast<float>(y < 0.f);
				return out;
			}
			const VecT<float, 2u> Abs() const noexcept {
				VecT<float, 2u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorAbs(temp);
				XMStore(&out, temp);
				return out;
			}

			// Static Variables

			
			static const VecT<float, 2u> zero;
			static const VecT<float, 2u> one;

			// Private Functions

			private:

			inline void Increment(const float& x, const float& y) {
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorAdd(temp, DirectX::XMVectorSet(x, y, 0.f, 0.f));
				XMStore(this, temp);
			}
			inline void Decrement(const float& x, const float& y) {
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorSubtract(temp, DirectX::XMVectorSet(x, y, 0.f, 0.f));
				XMStore(this, temp);
			}
			inline const VecT<float, 2u> Add(const float& x, const float& y) const noexcept {
				VecT<float, 2u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorAdd(temp, DirectX::XMVectorSet(x, y, 0.f, 0.f));
				XMStore(&out, temp);
				return out;
			}
			inline const VecT<float, 2u> Subtract(const float& x, const float& y) const noexcept {
				VecT<float, 2u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorSubtract(temp, DirectX::XMVectorSet(x, y, 0.f, 0.f));
				XMStore(&out, temp);
				return out;
			}
			inline const float Dot(const float& x, const float& y) const noexcept {
				float out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVector2Dot(temp, DirectX::XMVectorSet(x, y, 0.f, 0.f));
				XMStore(&out, temp);
				return out;
			}
		};
		

		// ----------------------------------------------------------------- //
		//                           Vector2 Int                             //
		// ----------------------------------------------------------------- //
		template<>
		struct VecT<int, 2u> : public DirectX::XMINT2 {

			constexpr VecT<int, 2u>() noexcept : XMINT2(0, 0) {};
			constexpr VecT<int, 2u>(const int& n) noexcept: XMINT2(n, n) {};
			constexpr VecT<int, 2u>(const int& x, const int& y) noexcept: XMINT2(x, y) {};
			constexpr VecT<int, 2u>(const VecT<int, 2u>& rhs) noexcept: XMINT2(rhs.x, rhs.y) {};
			explicit VecT<int, 2u>(const int rhs[2]) noexcept: XMINT2(rhs[0], rhs[1]) {};

			// Unary Operators

			VecT<int, 2u> operator+ () const noexcept {
				return *this;
			}
			VecT<int, 2u> operator- () const noexcept {
				VecT<int, 2u> out;
				out.x = -x;
				out.y = -y;
				return out;
			}
			const VecT<int, 2u>& operator++ () noexcept {
				Increment(1, 1);
				return *this;
			}
			const VecT<int, 2u>& operator++ (int) noexcept {
				Increment(1, 1);
				return *this;
			}
			const VecT<int, 2u>& operator-- () noexcept {
				Decrement(1, 1);
				return *this;
			}
			const VecT<int, 2u>& operator-- (int) noexcept {
				Decrement(1, 1);
				return *this;
			}

			// Assignment Operators

			const VecT<int, 2u>& operator= (const VecT<int, 2u>& rhs) noexcept {
				x = rhs.x;
				y = rhs.y;
				return *this;
			}
			const VecT<int, 2u>& operator= (const int rhs[2]) noexcept {
				x = rhs[0];
				y = rhs[1];
				return *this;
			}
			const VecT<int, 2u>& operator+= (const VecT<int, 2u>& rhs) noexcept {
				Increment(rhs.x, rhs.y);
				return *this;
			}
			const VecT<int, 2u>& operator+= (const int rhs[2]) noexcept {
				Increment(rhs[0], rhs[1]);
				return *this;
			}
			const VecT<int, 2u>& operator-= (const VecT<int, 2u>& rhs) noexcept {
				Decrement(rhs.x, rhs.y);
				return *this;
			}
			const VecT<int, 2u>& operator-= (const int rhs[2]) noexcept {
				Decrement(rhs[0], rhs[1]);
				return *this;
			}

			// Binary Operator

			const VecT<int, 2u> operator+ (const VecT<int, 2u>& rhs) const noexcept {
				return Add(rhs.x, rhs.y);
			}
			const VecT<int, 2u> operator+ (const int rhs[2]) const noexcept {
				return Add(rhs[0], rhs[1]);
			}
			const VecT<int, 2u> operator- (const VecT<int, 2u>& rhs) const noexcept {
				return Subtract(rhs.x, rhs.y);
			}
			const VecT<int, 2u> operator- (const int rhs[2]) const noexcept {
				return Subtract(rhs[0], rhs[1]);
			}
			const VecT<int, 2u> operator* (const int& rhs) const {
				VecT<int, 2u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorScale(temp, static_cast<float>(rhs));
				XMStore(&out, temp);
				return out;
			}
			const int operator* (const VecT<int, 2u>& rhs) const noexcept {
				return Dot(rhs.x, rhs.y);
			}
			const int operator* (const int rhs[2]) const noexcept {
				return Dot(rhs[0], rhs[1]);
			}

			// Bitwise Operator

			friend std::ostream& operator<<	(std::ostream& out, const VecT<int, 2u>& rhs) noexcept {
				out << "[" << rhs.x << ", " << rhs.y << "]";
				return out;
			}

			// Member Access Operator

			int& operator[] (const uint32_t& i) {
				#if _DEBUG
					if(i > 1u) throw std::invalid_argument("Access Violation!");
				#endif
				return reinterpret_cast<int*>(this)[i];
			}
			const int& operator[] (const uint32_t& i) const {
				#if _DEBUG
					if(i > 1u) throw std::invalid_argument("Access Violation!");
				#endif
				return reinterpret_cast<const int*>(this)[i];
			}

			// Cast Operator

			operator const VecT<float, 2u>() const;

			explicit operator const VecT<float, 3u>() const;
			explicit operator const VecT<int, 3u>() const;

			explicit operator const VecT<float, 4u>() const;
			explicit operator const VecT<int, 4u>() const;

			// Functions

			const float Magnitude() const noexcept {
				float out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVector2Length(temp);
				XMStore(&out, temp);
				return out;
			};
			const VecT<float, 2u> Normalized() const noexcept {
				VecT<float, 2u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVector2Normalize(temp);
				XMStore(&out, temp);
				return out;
			}
			const VecT<int, 2u> Sign() const noexcept {
				VecT<int, 2u> out;
				out.x = static_cast<int>(x > 0) - static_cast<int>(x < 0);
				out.y = static_cast<int>(y > 0) - static_cast<int>(y < 0);
				return out;
			}
			const VecT<int, 2u> Abs() const noexcept {
				VecT<int, 2u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorAbs(temp);
				XMStore(&out, temp);
				return out;
			}

			// Static Variables

			static const VecT<int, 2u> zero;
			static const VecT<int, 2u> one;

			// Private Functions

			private:

			inline void Increment(const int& x, const int& y) noexcept {
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorAdd(temp, DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), 0.f, 0.f));
				XMStore(this, temp);
			}
			inline void Decrement(const int& x, const int& y) noexcept {
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorSubtract(temp, DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), 0.f, 0.f));
				XMStore(this, temp);
			}
			inline const VecT<int, 2u> Add(const int& x, const int& y) const noexcept {
				VecT<int, 2u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorAdd(temp, DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), 0.f, 0.f));
				XMStore(&out, temp);
				return out;
			}
			inline const VecT<int, 2u> Subtract(const int& x, const int& y) const noexcept {
				VecT<int, 2u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorSubtract(temp, DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), 0.f, 0.f));
				XMStore(&out, temp);
				return out;
			}
			inline const int Dot(const int& x, const int& y) const noexcept {
				float out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVector2Dot(temp, DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), 0.f, 0.f));
				XMStore(&out, temp);
				return static_cast<int>(out);
			}
		};


		// ----------------------------------------------------------------- //
		//                          Vector3 Float                            //
		// ----------------------------------------------------------------- //
		template<>
		struct VecT<float, 3u> : public DirectX::XMFLOAT3 {

			constexpr VecT<float, 3u>() noexcept: XMFLOAT3(0.f, 0.f, 0.f) {};
			constexpr VecT<float, 3u>(const float& n) noexcept: XMFLOAT3(n, n, n) {};
			constexpr VecT<float, 3u>(const float& x, const float& y, const float& z) noexcept: XMFLOAT3(x, y, z) {};
			constexpr VecT<float, 3u>(const VecT<float, 2u>& vec2, const float& z) noexcept: XMFLOAT3(vec2.x, vec2.y, z) {};
			constexpr VecT<float, 3u>(const float& x, const VecT<float, 2u>& vec2) noexcept: XMFLOAT3(x, vec2.x, vec2.y) {};
			constexpr VecT<float, 3u>(const VecT<float, 3u>& rhs) noexcept: XMFLOAT3(rhs.x, rhs.y, rhs.z) {};
			explicit VecT<float, 3u>(const float rhs[3]) noexcept: XMFLOAT3(rhs[0], rhs[1], rhs[2]) {};

			// Unary Operators

			VecT<float, 3u> operator+ () const noexcept {
				return *this;
			}
			VecT<float, 3u> operator- () const noexcept {
				VecT<float, 3u> out;
				out.x = -x;
				out.y = -y;
				out.z = -z;
				return out;
			}
			const VecT<float, 3u>& operator++ () noexcept {
				Increment(1.f, 1.f, 1.f);
				return *this;
			}
			const VecT<float, 3u>& operator++ (int) noexcept {
				Increment(1.f, 1.f, 1.f);
				return *this;
			}
			const VecT<float, 3u>& operator-- () noexcept {
				Decrement(1.f, 1.f, 1.f);
				return *this;
			}
			const VecT<float, 3u>& operator-- (int) noexcept {
				Decrement(1.f, 1.f, 1.f);
				return *this;
			}

			// Assignment Operators

			const VecT<float, 3u>& operator= (const VecT<float, 3u>& rhs) noexcept {
				x = rhs.x;
				y = rhs.y;
				z = rhs.z;
				return *this;
			}
			const VecT<float, 3u>& operator= (const float rhs[3]) noexcept {
				x = rhs[0];
				y = rhs[1];
				z = rhs[2];
				return *this;
			}
			const VecT<float, 3u>& operator+= (const VecT<float, 3u>& rhs) noexcept {
				Increment(rhs.x, rhs.y, rhs.z);
				return *this;
			}
			const VecT<float, 3u>& operator+= (const float rhs[3]) noexcept {
				Increment(rhs[0], rhs[1], rhs[2]);
				return *this;
			}
			const VecT<float, 3u>& operator-= (const VecT<float, 3u>& rhs) noexcept {
				Decrement(rhs.x, rhs.y, rhs.z);
				return *this;
			}
			const VecT<float, 3u>& operator-= (const float rhs[3]) noexcept {
				Decrement(rhs[0], rhs[1], rhs[2]);
				return *this;
			}

			// Binary Operator

			const VecT<float, 3u> operator+ (const VecT<float, 3u>& rhs) const noexcept {
				return Add(rhs.x, rhs.y, rhs.z);
			}
			const VecT<float, 3u> operator+ (const float rhs[3]) const noexcept {
				return Add(rhs[0], rhs[1], rhs[2]);
			}
			const VecT<float, 3u> operator- (const VecT<float, 3u>& rhs) const noexcept {
				return Subtract(rhs.x, rhs.y, rhs.z);
			}
			const VecT<float, 3u> operator- (const float rhs[3]) const noexcept {
				return Subtract(rhs[0], rhs[1], rhs[2]);
			}
			const VecT<float, 3u> operator* (const float rhs) const noexcept {
				VecT<float, 3u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorScale(temp, rhs);
				XMStore(&out, temp);
				return out;
			}
			const VecT<float, 3u> operator% (const VecT<float, 3u>& rhs) const {
				return Cross(rhs.x, rhs.y, rhs.z);
			}
			const VecT<float, 3u> operator% (const float rhs[3]) const {
				return Cross(rhs[0], rhs[1], rhs[2]);
			}
			const float operator* (const VecT<float, 3u>& rhs) const noexcept {
				return Dot(rhs.x, rhs.y, rhs.z);
			}
			const float operator* (const float rhs[3]) const noexcept {
				return Dot(rhs[0], rhs[1], rhs[2]);
			}

			// Bitwise Operator

			friend std::ostream& operator<<	(std::ostream& out, const VecT<float, 3u>& rhs) noexcept {
				out << "[" << rhs.x << ", " << rhs.y << ", " << rhs.z << "]";
				return out;
			}

			// Member Access Operator

			float& operator[] (const uint32_t& i) {
				#if _DEBUG
					if(i > 2u) throw std::invalid_argument("Access Violation!");
				#endif
				return reinterpret_cast<float*>(this)[i];
			}
			const float& operator[] (const uint32_t& i) const {
				#if _DEBUG
					if(i > 2u) throw std::invalid_argument("Access Violation!");
				#endif
				return reinterpret_cast<const float*>(this)[i];
			}

			// Cast Operator

			explicit operator const VecT<float, 2u>() const;
			explicit operator const VecT<int, 2u>() const;

			operator const VecT<int, 3u>() const;

			explicit operator const VecT<float, 4u>() const;
			explicit operator const VecT<int, 4u>() const;

			// Functions

			const float Magnitude() const noexcept {
				float out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVector3Length(temp);
				XMStore(&out, temp);
				return out;
			};
			const VecT<float, 3u> Normalized() const noexcept {
				VecT<float, 3u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVector3Normalize(temp);
				XMStore(&out, temp);
				return out;
			}
			const VecT<float, 3u> Sign() const noexcept {
				VecT<float, 3u> out;
				out.x = static_cast<float>(x > 0.f) - static_cast<float>(x < 0.f);
				out.y = static_cast<float>(y > 0.f) - static_cast<float>(y < 0.f);
				out.z = static_cast<float>(z > 0.f) - static_cast<float>(z < 0.f);
				return out;
			}
			const VecT<float, 3u> Abs() const noexcept {
				VecT<float, 3u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorAbs(temp);
				XMStore(&out, temp);
				return out;
			}

			// Static Variables

			static const VecT<float, 3u> zero;
			static const VecT<float, 3u> one;

			// Private Functions

			private:

			inline void Increment(const float& x, const float& y, const float& z) {
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorAdd(temp, DirectX::XMVectorSet(x, y, z, 0.f));
				XMStore(this, temp);
			}
			inline void Decrement(const float& x, const float& y, const float& z) {
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorSubtract(temp, DirectX::XMVectorSet(x, y, z, 0.f));
				XMStore(this, temp);
			}
			inline const VecT<float, 3u> Add(const float& x, const float& y, const float& z) const noexcept {
				VecT<float, 3u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorAdd(temp, DirectX::XMVectorSet(x, y, z, 0.f));
				XMStore(&out, temp);
				return out;
			}
			inline const VecT<float, 3u> Subtract(const float& x, const float& y, const float& z) const noexcept {
				VecT<float, 3u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorSubtract(temp, DirectX::XMVectorSet(x, y, z, 0.f));
				XMStore(&out, temp);
				return out;
			}
			inline const float Dot(const float& x, const float& y, const float& z) const noexcept {
				float out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVector3Dot(temp, DirectX::XMVectorSet(x, y, z, 0.f));
				XMStore(&out, temp);
				return out;
			}
			inline const VecT<float, 3u> Cross(const float& x, const float& y, const float& z) const noexcept {
				VecT<float, 3u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVector3Cross(temp, DirectX::XMVectorSet(x, y, z, 0.f));
				XMStore(&out, temp);
				return out;
			}
		};


		// ----------------------------------------------------------------- //
		//                           Vector3 Int                             //
		// ----------------------------------------------------------------- //
		template<>
		struct VecT<int, 3u> : public DirectX::XMINT3 {

			constexpr VecT<int, 3u>() noexcept: XMINT3(0, 0, 0) {};
			constexpr VecT<int, 3u>(const int& n) noexcept: XMINT3(n, n, n) {};
			constexpr VecT<int, 3u>(const int& x, const int& y, const int& z) noexcept: XMINT3(x, y, z) {};
			constexpr VecT<int, 3u>(const VecT<int, 2u>& vec2, const int& z) noexcept: XMINT3(vec2.x, vec2.y, z) {};
			constexpr VecT<int, 3u>(const int& x, const VecT<int, 2u>& vec2) noexcept: XMINT3(x, vec2.x, vec2.y) {};
			constexpr VecT<int, 3u>(const VecT<int, 3u>& rhs) noexcept: XMINT3(rhs.x, rhs.y, rhs.z) {};
			explicit VecT<int, 3u>(const int rhs[3]) noexcept: XMINT3(rhs[0], rhs[1], rhs[2]) {};

			// Unary Operators

			VecT<int, 3u> operator+ () const noexcept {
				return *this;
			}
			VecT<int, 3u> operator- () const noexcept {
				VecT<int, 3u> out;
				out.x = -x;
				out.y = -y;
				out.z = -z;
				return out;
			}
			const VecT<int, 3u>& operator++ () noexcept {
				Increment(1, 1, 1);
				return *this;
			}
			const VecT<int, 3u>& operator++ (int) noexcept {
				Increment(1, 1, 1);
				return *this;
			}
			const VecT<int, 3u>& operator-- () noexcept {
				Decrement(1, 1, 1);
				return *this;
			}
			const VecT<int, 3u>& operator-- (int) noexcept {
				Decrement(1, 1, 1);
				return *this;
			}

			// Assignment Operators

			const VecT<int, 3u>& operator= (const VecT<int, 3u>& rhs) noexcept {
				x = rhs.x;
				y = rhs.y;
				z = rhs.z;
				return *this;
			}
			const VecT<int, 3u>& operator= (const int rhs[3]) noexcept {
				x = rhs[0];
				y = rhs[1];
				z = rhs[2];
				return *this;
			}
			const VecT<int, 3u>& operator+= (const VecT<int, 3u>& rhs) noexcept {
				Increment(rhs.x, rhs.y, rhs.z);
				return *this;
			}
			const VecT<int, 3u>& operator+= (const int rhs[3]) noexcept {
				Increment(rhs[0], rhs[1], rhs[2]);
				return *this;
			}
			const VecT<int, 3u>& operator-= (const VecT<int, 3u>& rhs) noexcept {
				Decrement(rhs.x, rhs.y, rhs.z);
				return *this;
			}
			const VecT<int, 3u>& operator-= (const int rhs[3]) noexcept {
				Decrement(rhs[0], rhs[1], rhs[2]);
				return *this;
			}

			// Binary Operator

			const VecT<int, 3u> operator+ (const VecT<int, 3u>& rhs) const noexcept {
				return Add(rhs.x, rhs.y, rhs.z);
			}
			const VecT<int, 3u> operator+ (const int rhs[3]) const noexcept {
				return Add(rhs[0], rhs[1], rhs[2]);
			}
			const VecT<int, 3u> operator- (const VecT<int, 3u>& rhs) const noexcept {
				return Subtract(rhs.x, rhs.y, rhs.z);
			}
			const VecT<int, 3u> operator- (const int rhs[3]) const noexcept {
				return Subtract(rhs[0], rhs[1], rhs[2]);
			}
			const VecT<int, 3u> operator* (const int rhs) const noexcept {
				VecT<int, 3u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorScale(temp, static_cast<float>(rhs));
				XMStore(&out, temp);
				return out;
			}
			const VecT<int, 3u> operator% (const VecT<int, 3u>& rhs) const {
				return Cross(rhs.x, rhs.y, rhs.z);
			}
			const VecT<int, 3u> operator% (const int rhs[3]) const {
				return Cross(rhs[0], rhs[1], rhs[2]);
			}
			const int operator* (const VecT<int, 3u>& rhs) const noexcept {
				return Dot(rhs.x, rhs.y, rhs.z);
			}
			const int operator* (const int rhs[3]) const noexcept {
				return Dot(rhs[0], rhs[1], rhs[2]);
			}

			// Bitwise Operator

			friend std::ostream& operator<<	(std::ostream& out, const VecT<int, 3u>& rhs) noexcept {
				out << "[" << rhs.x << ", " << rhs.y << ", " << rhs.z << "]";
				return out;
			}

			// Member Access Operator

			int& operator[] (const uint32_t& i) {
				#if _DEBUG
					if(i > 2u) throw std::invalid_argument("Access Violation!");
				#endif
				return reinterpret_cast<int*>(this)[i];
			}
			const int& operator[] (const uint32_t& i) const {
				#if _DEBUG
					if(i > 2u) throw std::invalid_argument("Access Violation!");
				#endif
				return reinterpret_cast<const int*>(this)[i];
			}

			// Cast Operator
			
			explicit operator const VecT<float, 2u>() const;
			explicit operator const VecT<int, 2u>() const;

			operator const VecT<float, 3u>() const;

			explicit operator const VecT<float, 4u>() const;
			explicit operator const VecT<int, 4u>() const;

			// Functions

			const float Magnitude() const noexcept {
				float out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVector3Length(temp);
				XMStore(&out, temp);
				return out;
			};
			const VecT<int, 3u> Normalized() const noexcept {
				VecT<int, 3u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVector3Normalize(temp);
				XMStore(&out, temp);
				return out;
			}
			const VecT<int, 3u> Sign() const noexcept {
				VecT<int, 3u> out;
				out.x = static_cast<int>(x > 0) - static_cast<int>(x < 0);
				out.y = static_cast<int>(y > 0) - static_cast<int>(y < 0);
				out.z = static_cast<int>(z > 0) - static_cast<int>(z < 0);
				return out;
			}
			const VecT<int, 3u> Abs() const noexcept {
				VecT<int, 3u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorAbs(temp);
				XMStore(&out, temp);
				return out;
			}

			// Static Variables

			static const VecT<int, 3u> zero;
			static const VecT<int, 3u> one;

			// Private Functions

			private:

			inline void Increment(const int& x, const int& y, const int& z) {
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorAdd(temp, DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), 0.f));
				XMStore(this, temp);
			}
			inline void Decrement(const int& x, const int& y, const int& z) {
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorSubtract(temp, DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), 0.f));
				XMStore(this, temp);
			}
			inline const VecT<int, 3u> Add(const int& x, const int& y, const int& z) const noexcept {
				VecT<int, 3u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorAdd(temp, DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), 0.f));
				XMStore(&out, temp);
				return out;
			}
			inline const VecT<int, 3u> Subtract(const int& x, const int& y, const int& z) const noexcept {
				VecT<int, 3u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorSubtract(temp, DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), 0.f));
				XMStore(&out, temp);
				return out;
			}
			inline const int Dot(const int& x, const int& y, const int& z) const noexcept {
				float out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVector3Dot(temp, DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), 0.f));
				XMStore(&out, temp);
				return static_cast<int>(out);
			}
			inline const VecT<int, 3u> Cross(const int& x, const int& y, const int& z) const noexcept {
				VecT<int, 3u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVector3Cross(temp, DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), 0.f));
				XMStore(&out, temp);
				return out;
			}
		};


		// ----------------------------------------------------------------- //
		//                          Vector4 Float                            //
		// ----------------------------------------------------------------- //
		template<>
		struct VecT<float, 4u> : public DirectX::XMFLOAT4 {

			constexpr VecT<float, 4u>() noexcept: XMFLOAT4(0.f, 0.f, 0.f, 0.f) {};
			constexpr VecT<float, 4u>(const float& n) noexcept: XMFLOAT4(n, n, n, n) {};
			constexpr VecT<float, 4u>(const float& x, const float& y, const float& z, const float& w) noexcept: XMFLOAT4(x, y, z, w) {};
			constexpr VecT<float, 4u>(const VecT<float, 2u>& vec2, const float& z, const float& w) noexcept: XMFLOAT4(vec2.x, vec2.y, z, w) {};
			constexpr VecT<float, 4u>(const float& x, const VecT<float, 2u>& vec2, const float& w) noexcept: XMFLOAT4(x, vec2.x, vec2.y, w) {};
			constexpr VecT<float, 4u>(const float& x, const float& y, const VecT<float, 2u>& vec2) noexcept: XMFLOAT4(x, y, vec2.x, vec2.y) {};
			constexpr VecT<float, 4u>(const VecT<float, 3u>& vec3, const float& w) noexcept: XMFLOAT4(vec3.x, vec3.y, vec3.z, w) {};
			constexpr VecT<float, 4u>(const float& x, const VecT<float, 3u>& vec3) noexcept: XMFLOAT4(x, vec3.x, vec3.y, vec3.z) {};
			constexpr VecT<float, 4u>(const VecT<float, 4u>& rhs) noexcept: XMFLOAT4(rhs.x, rhs.y, rhs.z, rhs.w) {};
			explicit VecT<float, 4u>(const float rhs[4]) noexcept: XMFLOAT4(rhs[0], rhs[1], rhs[2], rhs[3]) {};

			// Unary Operators

			VecT<float, 4u> operator+ () const noexcept {
				return *this;
			}
			VecT<float, 4u> operator- () const noexcept {
				VecT<float, 4u> out;
				out.x = -x;
				out.y = -y;
				out.z = -z;
				out.w = -w;
				return out;
			}
			const VecT<float, 4u>& operator++ () noexcept {
				Increment(1.f, 1.f, 1.f, 1.f);
				return *this;
			}
			const VecT<float, 4u>& operator++ (int) noexcept {
				Increment(1.f, 1.f, 1.f, 1.f);
				return *this;
			}
			const VecT<float, 4u>& operator-- () noexcept {
				Decrement(1.f, 1.f, 1.f, 1.f);
				return *this;
			}
			const VecT<float, 4u>& operator-- (int) noexcept {
				Decrement(1.f, 1.f, 1.f, 1.f);
				return *this;
			}

			// Assignment Operators

			const VecT<float, 4u>& operator= (const VecT<float, 4u>& rhs) noexcept {
				x = rhs.x;
				y = rhs.y;
				z = rhs.z;
				w = rhs.w;
				return *this;
			}
			const VecT<float, 4u>& operator= (const float rhs[4]) noexcept {
				x = rhs[0];
				y = rhs[1];
				z = rhs[2];
				w = rhs[3];
				return *this;
			}
			const VecT<float, 4u>& operator+= (const VecT<float, 4u>& rhs) noexcept {
				Increment(rhs.x, rhs.y, rhs.z, rhs.w);
				return *this;
			}
			const VecT<float, 4u>& operator+= (const float rhs[4]) noexcept {
				Increment(rhs[0], rhs[1], rhs[2], rhs[3]);
				return *this;
			}
			const VecT<float, 4u>& operator-= (const VecT<float, 4u>& rhs) noexcept {
				Decrement(rhs.x, rhs.y, rhs.z, rhs.w);
				return *this;
			}
			const VecT<float, 4u>& operator-= (const float rhs[4]) noexcept {
				Decrement(rhs[0], rhs[1], rhs[2], rhs[3]);
				return *this;
			}

			// Binary Operator

			const VecT<float, 4u> operator+ (const VecT<float, 4u>& rhs) const noexcept {
				return Add(rhs.x, rhs.y, rhs.z, rhs.w);
			}
			const VecT<float, 4u> operator+ (const float rhs[4]) const noexcept {
				return Add(rhs[0], rhs[1], rhs[2], rhs[3]);
			}
			const VecT<float, 4u> operator- (const VecT<float, 4u>& rhs) const noexcept {
				return Subtract(rhs.x, rhs.y, rhs.z, rhs.w);
			}
			const VecT<float, 4u> operator- (const float rhs[4]) const noexcept {
				return Subtract(rhs[0], rhs[1], rhs[2], rhs[3]);
			}
			const VecT<float, 4u> operator* (const float rhs) const noexcept {
				VecT<float, 4u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorScale(temp, rhs);
				XMStore(&out, temp);
				return out;
			}
			const float operator* (const VecT<float, 4u>& rhs) const noexcept {
				return Dot(rhs.x, rhs.y, rhs.z, rhs.w);
			}
			const float operator* (const float rhs[4]) const noexcept {
				return Dot(rhs[0], rhs[1], rhs[2], rhs[3]);
			}

			// Bitwise Operator

			friend std::ostream& operator<<	(std::ostream& out, const VecT<float, 4u>& rhs) noexcept {
				out << "[" << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << "]";
				return out;
			}

			// Member Access Operator

			float& operator[] (const uint32_t& i) {
				#if _DEBUG
					if(i > 3u) throw std::invalid_argument("Access Violation!");
				#endif
				return reinterpret_cast<float*>(this)[i];
			}
			const float& operator[] (const uint32_t& i) const {
				#if _DEBUG
				if(i > 3u) throw std::invalid_argument("Access Violation!");
				#endif
				return reinterpret_cast<const float*>(this)[i];
			}

			// Cast Operator

			explicit operator const VecT<float, 2u>() const;
			explicit operator const VecT<int, 2u>() const;

			explicit operator const VecT<float, 3u>() const;
			explicit operator const VecT<int, 3u>() const;

			operator const VecT<int, 4u>() const;
			operator const Color() const;
			operator const Quat() const;

			// Functions

			const float Magnitude() const noexcept {
				float out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVector4Length(temp);
				XMStore(&out, temp);
				return out;
			};
			const VecT<float, 4u> Normalized() const noexcept {
				VecT<float, 4u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVector4Normalize(temp);
				XMStore(&out, temp);
				return out;
			}
			const VecT<float, 4u> Sign() const noexcept {
				VecT<float, 4u> out;
				out.x = static_cast<float>(x > 0.f) - static_cast<float>(x < 0.f);
				out.y = static_cast<float>(y > 0.f) - static_cast<float>(y < 0.f);
				out.z = static_cast<float>(z > 0.f) - static_cast<float>(z < 0.f);
				out.w = static_cast<float>(w > 0.f) - static_cast<float>(w < 0.f);
				return out;
			}
			const VecT<float, 4u> Abs() const noexcept {
				VecT<float, 4u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorAbs(temp);
				XMStore(&out, temp);
				return out;
			}

			// Static Variables

			static const VecT<float, 4u> zero;
			static const VecT<float, 4u> one;

			// Private Functions

			private:

			inline void Increment(const float& x, const float& y, const float& z, const float& w) {
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorAdd(temp, DirectX::XMVectorSet(x, y, z, w));
				XMStore(this, temp);
			}
			inline void Decrement(const float& x, const float& y, const float& z, const float& w) {
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorSubtract(temp, DirectX::XMVectorSet(x, y, z, w));
				XMStore(this, temp);
			}
			inline const VecT<float, 4u> Add(const float& x, const float& y, const float& z, const float& w) const noexcept {
				VecT<float, 4u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorAdd(temp, DirectX::XMVectorSet(x, y, z, w));
				XMStore(&out, temp);
				return out;
			}
			inline const VecT<float, 4u> Subtract(const float& x, const float& y, const float& z, const float& w) const noexcept {
				VecT<float, 4u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorSubtract(temp, DirectX::XMVectorSet(x, y, z, w));
				XMStore(&out, temp);
				return out;
			}
			inline const float Dot(const float& x, const float& y, const float& z, const float& w) const noexcept {
				float out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVector3Dot(temp, DirectX::XMVectorSet(x, y, z, w));
				XMStore(&out, temp);
				return out;
			}
		};


		// ----------------------------------------------------------------- //
		//                           Vector4 Int                             //
		// ----------------------------------------------------------------- //
		template<>
		struct VecT<int, 4u> : public DirectX::XMINT4 {

			constexpr VecT<int, 4u>() noexcept: XMINT4(0, 0, 0, 0) {};
			constexpr VecT<int, 4u>(const int& n) noexcept: XMINT4(n, n, n, n) {};
			constexpr VecT<int, 4u>(const int& x, const int& y, const int& z, const int& w) noexcept: XMINT4(x, y, z, w) {};
			constexpr VecT<int, 4u>(const VecT<int, 2u>& vec2, const int& z, const int& w) noexcept: XMINT4(vec2.x, vec2.y, z, w) {};
			constexpr VecT<int, 4u>(const int& x, const VecT<int, 2u>& vec2, const int& w) noexcept: XMINT4(x, vec2.x, vec2.y, w) {};
			constexpr VecT<int, 4u>(const int& x, const int& y, const VecT<int, 2u>& vec2) noexcept: XMINT4(x, y, vec2.x, vec2.y) {};
			constexpr VecT<int, 4u>(const VecT<int, 3u>& vec3, const int& w) noexcept: XMINT4(vec3.x, vec3.y, vec3.z, w) {};
			constexpr VecT<int, 4u>(const int& x, const VecT<int, 3u>& vec3) noexcept: XMINT4(x, vec3.x, vec3.y, vec3.z) {};
			constexpr VecT<int, 4u>(const VecT<int, 4u>& rhs) noexcept: XMINT4(rhs.x, rhs.y, rhs.z, rhs.w) {};
			explicit VecT<int, 4u>(const int rhs[4]) noexcept: XMINT4(rhs[0], rhs[1], rhs[2], rhs[3]) {};

			// Unary Operators

			VecT<int, 4u> operator+ () const noexcept {
				return *this;
			}
			VecT<int, 4u> operator- () const noexcept {
				VecT<int, 4u> out;
				out.x = -x;
				out.y = -y;
				out.z = -z;
				out.w = -w;
				return out;
			}
			const VecT<int, 4u>& operator++ () noexcept {
				Increment(1, 1, 1, 1);
				return *this;
			}
			const VecT<int, 4u>& operator++ (int) noexcept {
				Increment(1, 1, 1, 1);
				return *this;
			}
			const VecT<int, 4u>& operator-- () noexcept {
				Decrement(1, 1, 1, 1);
				return *this;
			}
			const VecT<int, 4u>& operator-- (int) noexcept {
				Decrement(1, 1, 1, 1);
				return *this;
			}

			// Assignment Operators

			const VecT<int, 4u>& operator= (const VecT<int, 4u>& rhs) noexcept {
				x = rhs.x;
				y = rhs.y;
				z = rhs.z;
				w = rhs.w;
				return *this;
			}
			const VecT<int, 4u>& operator= (const int rhs[4]) noexcept {
				x = rhs[0];
				y = rhs[1];
				z = rhs[2];
				w = rhs[3];
				return *this;
			}
			const VecT<int, 4u>& operator+= (const VecT<int, 4u>& rhs) noexcept {
				Increment(rhs.x, rhs.y, rhs.z, rhs.w);
				return *this;
			}
			const VecT<int, 4u>& operator+= (const int rhs[4]) noexcept {
				Increment(rhs[0], rhs[1], rhs[2], rhs[3]);
				return *this;
			}
			const VecT<int, 4u>& operator-= (const VecT<int, 4u>& rhs) noexcept {
				Decrement(rhs.x, rhs.y, rhs.z, rhs.w);
				return *this;
			}
			const VecT<int, 4u>& operator-= (const int rhs[4]) noexcept {
				Decrement(rhs[0], rhs[1], rhs[2], rhs[3]);
				return *this;
			}

			// Binary Operator

			const VecT<int, 4u> operator+ (const VecT<int, 4u>& rhs) const noexcept {
				return Add(rhs.x, rhs.y, rhs.z, rhs.w);
			}
			const VecT<int, 4u> operator+ (const int rhs[4]) const noexcept {
				return Add(rhs[0], rhs[1], rhs[2], rhs[3]);
			}
			const VecT<int, 4u> operator- (const VecT<int, 4u>& rhs) const noexcept {
				return Subtract(rhs.x, rhs.y, rhs.z, rhs.w);
			}
			const VecT<int, 4u> operator- (const int rhs[4]) const noexcept {
				return Subtract(rhs[0], rhs[1], rhs[2], rhs[3]);
			}
			const VecT<int, 4u> operator* (const int rhs) const noexcept {
				VecT<int, 4u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorScale(temp, static_cast<float>(rhs));
				XMStore(&out, temp);
				return out;
			}
			const int operator* (const VecT<int, 4u>& rhs) const noexcept {
				return Dot(rhs.x, rhs.y, rhs.z, rhs.w);
			}
			const int operator* (const int rhs[4]) const noexcept {
				return Dot(rhs[0], rhs[1], rhs[2], rhs[3]);
			}

			// Bitwise Operator

			friend std::ostream& operator<<	(std::ostream& out, const VecT<int, 4u>& rhs) noexcept {
				out << "[" << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << "]";
				return out;
			}

			// Member Access Operator

			int& operator[] (const uint32_t& i) {
				#if _DEBUG
					if(i > 3u) throw std::invalid_argument("Access Violation!");
				#endif
				return reinterpret_cast<int*>(this)[i];
			}
			const int& operator[] (const uint32_t& i) const {
				#if _DEBUG
					if(i > 3u) throw std::invalid_argument("Access Violation!");
				#endif
				return reinterpret_cast<const int*>(this)[i];
			}

			// Cast Operator

			explicit operator const VecT<float, 2u>() const;
			explicit operator const VecT<int, 2u>() const;

			explicit operator const VecT<float, 3u>() const;
			explicit operator const VecT<int, 3u>() const;

			operator const VecT<float, 4u>() const;

			// Functions

			const float Magnitude() const noexcept {
				float out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVector4Length(temp);
				XMStore(&out, temp);
				return out;
			};
			const VecT<int, 4u> Normalized() const noexcept {
				VecT<int, 4u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVector4Normalize(temp);
				XMStore(&out, temp);
				return out;
			}
			const VecT<int, 4u> Sign() const noexcept {
				VecT<int, 4u> out;
				out.x = static_cast<int>(x > 0) - static_cast<int>(x < 0);
				out.y = static_cast<int>(y > 0) - static_cast<int>(y < 0);
				out.z = static_cast<int>(z > 0) - static_cast<int>(z < 0);
				out.w = static_cast<int>(w > 0) - static_cast<int>(w < 0);
				return out;
			}
			const VecT<int, 4u> Abs() const noexcept {
				VecT<int, 4u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorAbs(temp);
				XMStore(&out, temp);
				return out;
			}

			// Static Variables

			static const VecT<int, 4u> zero;
			static const VecT<int, 4u> one;

			// Private Functions

			private:

			inline void Increment(const int& x, const int& y, const int& z, const int& w) {
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorAdd(temp, DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w)));
				XMStore(this, temp);
			}
			inline void Decrement(const int& x, const int& y, const int& z, const int& w) {
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorSubtract(temp, DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w)));
				XMStore(this, temp);
			}
			inline const VecT<int, 4u> Add(const int& x, const int& y, const int& z, const int& w) const noexcept {
				VecT<int, 4u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorAdd(temp, DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w)));
				XMStore(&out, temp);
				return out;
			}
			inline const VecT<int, 4u> Subtract(const int& x, const int& y, const int& z, const int& w) const noexcept {
				VecT<int, 4u> out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVectorSubtract(temp, DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w)));
				XMStore(&out, temp);
				return out;
			}
			inline const int Dot(const int& x, const int& y, const int& z, const int& w) const noexcept {
				float out;
				XMVEC temp = XMLoad<XMVEC>(this);
				temp = DirectX::XMVector3Dot(temp, DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w)));
				XMStore(&out, temp);
				return static_cast<int>(out);
			}
		};


		// Cast Operator Def --------------------------------------------------

		inline VecT<float, 2u>::operator const VecT<int, 2u>() const {
			VecT<int, 2u> out;
			out.x = static_cast<int>(x);
			out.y = static_cast<int>(y);
			return out;
		}
		inline VecT<float, 2u>::operator const VecT<float, 3u>() const {
			VecT<float, 3u> out;
			out.x = x;
			out.y = y;
			return out;
		}
		inline VecT<float, 2u>::operator const VecT<int, 3u>() const {
			VecT<int, 3u> out;
			out.x = static_cast<int>(x);
			out.y = static_cast<int>(y);
			return out;
		}
		inline VecT<float, 2u>::operator const VecT<float, 4u>() const {
			VecT<float, 4u> out;
			out.x = x;
			out.y = y;
			return out;
		}
		inline VecT<float, 2u>::operator const VecT<int, 4u>() const {
			VecT<int, 4u> out;
			out.x = static_cast<int>(x);
			out.y = static_cast<int>(y);
			return out;
		}

		inline VecT<int, 2u>::operator const VecT<float, 2u>() const {
			VecT<float, 2u> out;
			out.x = static_cast<float>(x);
			out.y = static_cast<float>(y);
			return out;
		}
		inline VecT<int, 2u>::operator const VecT<float, 3u>() const {
			VecT<float, 3u> out;
			out.x = static_cast<float>(x);
			out.y = static_cast<float>(y);
			return out;
		}
		inline VecT<int, 2u>::operator const VecT<int, 3u>() const {
			VecT<int, 3u> out;
			out.x = x;
			out.y = y;
			return out;
		}
		inline VecT<int, 2u>::operator const VecT<float, 4u>() const {
			VecT<float, 4u> out;
			out.x = static_cast<float>(x);
			out.y = static_cast<float>(y);
			return out;
		}
		inline VecT<int, 2u>::operator const VecT<int, 4u>() const {
			VecT<int, 4u> out;
			out.x = x;
			out.y = y;
			return out;
		}

		inline VecT<float, 3u>::operator const VecT<float, 2u>() const {
			VecT<float, 2u> out;
			out.x = x;
			out.y = y;
			return out;
		}
		inline VecT<float, 3u>::operator const VecT<int, 2u>() const {
			VecT<int, 2u> out;
			out.x = static_cast<int>(x);
			out.y = static_cast<int>(y);
			return out;
		}
		inline VecT<float, 3u>::operator const VecT<int, 3u>() const {
			VecT<int, 3u> out;
			out.x = static_cast<int>(x);
			out.y = static_cast<int>(y);
			out.z = static_cast<int>(z);
			return out;
		}
		inline VecT<float, 3u>::operator const VecT<float, 4u>() const {
			VecT<float, 4u> out;
			out.x = x;
			out.y = y;
			out.z = z;
			return out;
		}
		inline VecT<float, 3u>::operator const VecT<int, 4u>() const {
			VecT<int, 4u> out;
			out.x = static_cast<int>(x);
			out.y = static_cast<int>(y);
			out.z = static_cast<int>(z);
			return out;
		}

		inline VecT<int, 3u>::operator const VecT<float, 2u>() const {
			VecT<float, 2u> out;
			out.x = static_cast<float>(x);
			out.y = static_cast<float>(y);
			return out;
		}
		inline VecT<int, 3u>::operator const VecT<int, 2u>() const {
			VecT<int, 2u> out;
			out.x = x;
			out.y = y;
			return out;
		}
		inline VecT<int, 3u>::operator const VecT<float, 3u>() const {
			VecT<float, 3u> out;
			out.x = static_cast<float>(x);
			out.y = static_cast<float>(y);
			out.z = static_cast<float>(z);
			return out;
		}
		inline VecT<int, 3u>::operator const VecT<float, 4u>() const {
			VecT<float, 4u> out;
			out.x = static_cast<float>(x);
			out.y = static_cast<float>(y);
			out.z = static_cast<float>(z);
			return out;
		}
		inline VecT<int, 3u>::operator const VecT<int, 4u>() const {
			VecT<int, 4u> out;
			out.x = x;
			out.y = y;
			out.z = z;
			return out;
		}

		inline VecT<float, 4u>::operator const VecT<float, 2u>() const {
			VecT<float, 2u> out;
			out.x = x;
			out.y = y;
			return out;
		}
		inline VecT<float, 4u>::operator const VecT<int, 2u>() const {
			VecT<int, 2u> out;
			out.x = static_cast<int>(x);
			out.y = static_cast<int>(y);
			return out;
		}
		inline VecT<float, 4u>::operator const VecT<float, 3u>() const {
			VecT<float, 3u> out;
			out.x = x;
			out.y = y;
			out.z = z;
			return out;
		}
		inline VecT<float, 4u>::operator const VecT<int, 3u>() const {
			VecT<int, 3u> out;
			out.x = static_cast<int>(x);
			out.y = static_cast<int>(y);
			out.z = static_cast<int>(z);
			return out;
		}
		inline VecT<float, 4u>::operator const VecT<int, 4u>() const {
			VecT<int, 4u> out;
			out.x = static_cast<int>(x);
			out.y = static_cast<int>(y);
			out.z = static_cast<int>(z);
			out.w = static_cast<int>(w);
			return out;
		}

		inline VecT<int, 4u>::operator const VecT<float, 2u>() const {
			VecT<float, 2u> out;
			out.x = static_cast<float>(x);
			out.y = static_cast<float>(y);
			return out;
		}
		inline VecT<int, 4u>::operator const VecT<int, 2u>() const {
			VecT<int, 2u> out;
			out.x = x;
			out.y = y;
			return out;
		}
		inline VecT<int, 4u>::operator const VecT<float, 3u>() const {
			VecT<float, 3u> out;
			out.x = static_cast<float>(x);
			out.y = static_cast<float>(y);
			out.z = static_cast<float>(z);
			return out;
		}
		inline VecT<int, 4u>::operator const VecT<int, 3u>() const {
			VecT<int, 3u> out;
			out.x = x;
			out.y = y;
			out.z = z;
			return out;
		}
		inline VecT<int, 4u>::operator const VecT<float, 4u>() const {
			VecT<float, 4u> out;
			out.x = static_cast<float>(x);
			out.y = static_cast<float>(y);
			out.z = static_cast<float>(z);
			out.w = static_cast<float>(w);
			return out;
		}

};

	// Vector Short Def ------------------------------------

	using Vec2f = Concealed::VecT<float, 2u>;
	using Vec2i = Concealed::VecT<int, 2u>;

	using Vec3f = Concealed::VecT<float, 3u>;
	using Vec3i = Concealed::VecT<int, 3u>;

	using Vec4f = Concealed::VecT<float, 4u>;
	using Vec4i = Concealed::VecT<int, 4u>;
	

	namespace Concealed {

		// ----------------------------------------------------------------- //
		//				  __  __       _        _							 //
		//				 |  \/  | __ _| |_ _ __(_) ___ ___  ___				 //
		//				 | |\/| |/ _` | __| '__| |/ __/ _ \/ __|			 //
		//				 | |  | | (_| | |_| |  | | (_|  __/\__ \			 //
		//				 |_|  |_|\__,_|\__|_|  |_|\___\___||___/			 //
		// ----------------------------------------------------------------- //


		// ----------------------------------------------------------------- //
		//                          Matrix3 Float                            //
		// ----------------------------------------------------------------- //
		template<> 
		struct MatT<float, 3u, 3u> {

			constexpr MatT<float, 3u, 3u>() noexcept: XMMat(
				1.f, 0.f, 0.f, 
				0.f, 1.f, 0.f, 
				0.f, 0.f, 1.f) {};
			constexpr MatT<float, 3u, 3u>(const float& m00,const float& m01,const float& m02, const float& m10,const float& m11,const float& m12, const float& m20,const float& m21,const float& m22) noexcept: XMMat(
				m00, m01, m02, 
				m10, m11, m12, 
				m20, m21, m22) {};
			constexpr MatT<float, 3u, 3u>(const Vec3f& R0, const Vec3f& R1, const Vec3f& R2) noexcept:
				R0(R0),
				R1(R1),
				R2(R2) {};
			constexpr MatT<float, 3u, 3u>(const MatT<float, 3u, 3u>& rhs) noexcept: 
				XMMat(rhs.XMMat) {};
			explicit MatT<float, 3u, 3u>(const float rhs[9]) noexcept:
				XMMat(rhs) {};

			// Assignment Operators

			const MatT<float, 3u, 3u>& operator= (const MatT<float, 3u, 3u>& rhs) {
				XMMat = rhs.XMMat;
				return *this;
			}
			const MatT<float, 3u, 3u>& operator= (const float rhs[9]) {
				XMMat = DirectX::XMFLOAT3X3(rhs);
				return *this;
			}
			const MatT<float, 3u, 3u>& operator= (const MatT<float, 3u, 4u>& rhs);
			const MatT<float, 3u, 3u>& operator= (const MatT<float, 4u, 3u>& rhs);
			const MatT<float, 3u, 3u>& operator= (const MatT<float, 4u, 4u>& rhs);
			const MatT<float, 3u, 3u>& operator*= (const MatT<float, 3u, 3u>& rhs) {
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				temp = DirectX::XMMatrixMultiply(temp, DirectX::XMLoadFloat3x3(&rhs.XMMat));
				XMStore(&XMMat, temp);
				return *this;
			}
			const MatT<float, 3u, 3u>& operator*= (const float rhs[9]) {
				DirectX::XMFLOAT3X3 in(rhs);
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				temp = DirectX::XMMatrixMultiply(temp, DirectX::XMLoadFloat3x3(&in));
				XMStore(&XMMat, temp);
				return *this;
			}

			// Binary Operator

			const MatT<float, 3u, 3u> operator* (const MatT<float, 3u, 3u>& rhs) const {
				MatT<float, 3u, 3u> out;
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				temp = DirectX::XMMatrixMultiply(temp, DirectX::XMLoadFloat3x3(&rhs.XMMat));
				XMStore(&out.XMMat, temp);
				return out;
			}
			const MatT<float, 3u, 3u> operator* (const float rhs[9]) const {
				MatT<float, 3u, 3u> out;
				DirectX::XMFLOAT3X3 in(rhs);
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				temp = DirectX::XMMatrixMultiply(temp, DirectX::XMLoadFloat3x3(&in));
				XMStore(&out.XMMat, temp);
				return out;
			}

			// Bitwise Operator

			friend std::ostream& operator<<	(std::ostream& out, const MatT<float, 3u, 3u>& rhs) noexcept {
				out << rhs.R0 << std::endl << rhs.R1 << std::endl << rhs.R2;
				return out;
			}

			// Member Access Operator

			Vec3f& operator[] (const uint32_t& i) {
				#if _DEBUG
					if(i > 2u) throw std::invalid_argument("Access Violation!");
				#endif
				return reinterpret_cast<Vec3f*>(this)[i];
			}
			const Vec3f& operator[] (const uint32_t& i) const {
				#if _DEBUG
					if(i > 2u) throw std::invalid_argument("Access Violation!");
				#endif
				return reinterpret_cast<const Vec3f*>(this)[i];
			}

			// Cast Operator

			explicit operator MatT<float, 3u, 4u>() const;
			explicit operator MatT<float, 4u, 3u>() const;
			explicit operator MatT<float, 4u, 4u>() const;

			// Functions

			const MatT<float, 3u, 3u> Transposed() const {
				MatT<float, 3u, 3u> out;
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				temp = DirectX::XMMatrixTranspose(temp);
				XMStore(&out.XMMat, temp);
				return out;
			}
			const MatT<float, 3u, 3u> Inverse() const {
				MatT<float, 3u, 3u> out;
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				DirectX::XMVECTOR v = DirectX::XMMatrixDeterminant(temp);
				temp = DirectX::XMMatrixInverse(&v, DirectX::FXMMATRIX(temp));
				XMStore(&out.XMMat, temp);
				return out;
			}
			const float Determinant() const {
				float out;
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				DirectX::XMVECTOR v = DirectX::XMMatrixDeterminant(temp);
				XMStore(&out, v);
				return out;
			}

			// Static Variables

			static const MatT<float, 3u, 3u> identity;

			union {
				DirectX::XMFLOAT3X3 XMMat;
				struct {
					float m00, m01, m02;
					float m10, m11, m12;
					float m20, m21, m22;
				};
				struct {
					Vec3f R0, R1, R2;
				};
			};

		};


		// ----------------------------------------------------------------- //
		//                         Matrix3x4 Float                           //
		// ----------------------------------------------------------------- //
		template<>
		struct MatT<float, 3u, 4u> {

			constexpr MatT<float, 3u, 4u>() noexcept: XMMat(
				1.f, 0.f, 0.f, 0.f,
				0.f, 1.f, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f) {};
			constexpr MatT<float, 3u, 4u>(const float& m00, const float& m01, const float& m02, const float& m03, const float& m10, const float& m11, const float& m12, const float& m13, const float& m20, const float& m21, const float& m22, const float& m23) noexcept: XMMat(
				m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23) {};
			constexpr MatT<float, 3u, 4u>(const Vec4f& R0, const Vec4f& R1, const Vec4f& R2) noexcept:
				R0(R0),
				R1(R1),
				R2(R2) {};
			constexpr MatT<float, 3u, 4u>(const MatT<float, 3u, 4u>& rhs) noexcept:
				XMMat(rhs.XMMat) {};
			explicit MatT<float, 3u, 4u>(const float rhs[12]) noexcept:
				XMMat(rhs) {};

			// Assignment Operators

			const MatT<float, 3u, 4u>& operator= (const MatT<float, 3u, 4u>& rhs) {
				XMMat = rhs.XMMat;
				return *this;
			}
			const MatT<float, 3u, 4u>& operator= (const float rhs[12]) {
				XMMat = DirectX::XMFLOAT3X4(rhs);
				return *this;
			}
			const MatT<float, 3u, 4u>& operator= (const MatT<float, 3u, 3u>& rhs);
			const MatT<float, 3u, 4u>& operator= (const MatT<float, 4u, 3u>& rhs);
			const MatT<float, 3u, 4u>& operator= (const MatT<float, 4u, 4u>& rhs);
			const MatT<float, 3u, 4u>& operator*= (const MatT<float, 3u, 4u>& rhs) {
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				temp = DirectX::XMMatrixMultiply(temp, DirectX::XMLoadFloat3x4(&rhs.XMMat));
				XMStore(&XMMat, temp);
				return *this;
			}
			const MatT<float, 3u, 4u>& operator*= (const float rhs[12]) {
				DirectX::XMFLOAT3X4 in(rhs);
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				temp = DirectX::XMMatrixMultiply(temp, DirectX::XMLoadFloat3x4(&in));
				XMStore(&XMMat, temp);
				return *this;
			}

			// Binary Operator

			const MatT<float, 3u, 4u> operator* (const MatT<float, 3u, 4u>& rhs) const {
				MatT<float, 3u, 4u> out;
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				temp = DirectX::XMMatrixMultiply(temp, DirectX::XMLoadFloat3x4(&rhs.XMMat));
				XMStore(&out.XMMat, temp);
				return out;
			}
			const MatT<float, 3u, 4u> operator* (const float rhs[12]) const {
				MatT<float, 3u, 4u> out;
				DirectX::XMFLOAT3X4 in(rhs);
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				temp = DirectX::XMMatrixMultiply(temp, DirectX::XMLoadFloat3x4(&in));
				XMStore(&out.XMMat, temp);
				return out;
			}

			// Bitwise Operator

			friend std::ostream& operator<<	(std::ostream& out, const MatT<float, 3u, 4u>& rhs) noexcept {
				out << rhs.R0 << std::endl << rhs.R1 << std::endl << rhs.R2;
				return out;
			}

			// Member Access Operator

			Vec3f& operator[] (const uint32_t& i) {
				#if _DEBUG
					if(i > 2u) throw std::invalid_argument("Access Violation!");
				#endif
				return reinterpret_cast<Vec3f*>(this)[i];
			}
			const Vec3f& operator[] (const uint32_t& i) const {
				#if _DEBUG
					if(i > 2u) throw std::invalid_argument("Access Violation!");
				#endif
				return reinterpret_cast<const Vec3f*>(this)[i];
			}

			// Cast Operator

			explicit operator MatT<float, 3u, 3u>() const;
			explicit operator MatT<float, 4u, 3u>() const;
			explicit operator MatT<float, 4u, 4u>() const;

			// Functions

			const MatT<float, 3u, 4u> Transposed() const {
				MatT<float, 3u, 4u> out;
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				temp = DirectX::XMMatrixTranspose(temp);
				XMStore(&out.XMMat, temp);
				return out;
			}
			const MatT<float, 3u, 4u> Inverse() const {
				MatT<float, 3u, 4u> out;
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				DirectX::XMVECTOR v = DirectX::XMMatrixDeterminant(temp);
				temp = DirectX::XMMatrixInverse(&v, DirectX::FXMMATRIX(temp));
				XMStore(&out.XMMat, temp);
				return out;
			}
			const float Determinant() const {
				float out;
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				DirectX::XMVECTOR v = DirectX::XMMatrixDeterminant(temp);
				XMStore(&out, v);
				return out;
			}

			// Static Variables

			static const MatT<float, 3u, 4u> identity;

			union {
				DirectX::XMFLOAT3X4 XMMat;
				struct {
					float m00, m01, m02, m03;
					float m10, m11, m12, m13;
					float m20, m21, m22, m23;
				};
				struct {
					Vec4f R0, R1, R2;
				};
			};

		};


		// ----------------------------------------------------------------- //
		//                         Matrix4x3 Float                           //
		// ----------------------------------------------------------------- //
		template<>
		struct MatT<float, 4u, 3u> {

			constexpr MatT<float, 4u, 3u>() noexcept: XMMat(
				1.f, 0.f, 0.f,
				0.f, 1.f, 0.f,
				0.f, 0.f, 1.f,
				0.f, 0.f, 0.f) {};
			constexpr MatT<float, 4u, 3u>(const float& m00, const float& m01, const float& m02, const float& m10, const float& m11, const float& m12, const float& m20, const float& m21, const float& m22, const float& m30, const float& m31, const float& m32) noexcept: XMMat(
				m00, m01, m02,
				m10, m11, m12,
				m20, m21, m22,
				m30, m31, m32) {};
			constexpr MatT<float, 4u, 3u>(const Vec3f& R0, const Vec3f& R1, const Vec3f& R2, const Vec3f& R3) noexcept:
				R0(R0),
				R1(R1),
				R2(R2),
				R3(R3) {};
			constexpr MatT<float, 4u, 3u>(const MatT<float, 4u, 3u>& rhs) noexcept:
				XMMat(rhs.XMMat) {};
			explicit MatT<float, 4u, 3u>(const float rhs[12]) noexcept:
				XMMat(rhs) {};

			// Assignment Operators

			const MatT<float, 4u, 3u>& operator= (const MatT<float, 4u, 3u>& rhs) {
				XMMat = rhs.XMMat;
				return *this;
			}
			const MatT<float, 4u, 3u>& operator= (const float rhs[12]) {
				XMMat = DirectX::XMFLOAT4X3(rhs);
				return *this;
			}
			const MatT<float, 4u, 3u>& operator= (const MatT<float, 3u, 3u>& rhs);
			const MatT<float, 4u, 3u>& operator= (const MatT<float, 3u, 4u>& rhs);
			const MatT<float, 4u, 3u>& operator= (const MatT<float, 4u, 4u>& rhs);
			const MatT<float, 4u, 3u>& operator*= (const MatT<float, 4u, 3u>& rhs) {
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				temp = DirectX::XMMatrixMultiply(temp, DirectX::XMLoadFloat4x3(&rhs.XMMat));
				XMStore(&XMMat, temp);
				return *this;
			}
			const MatT<float, 4u, 3u>& operator*= (const float rhs[12]) {
				DirectX::XMFLOAT4X3 in(rhs);
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				temp = DirectX::XMMatrixMultiply(temp, DirectX::XMLoadFloat4x3(&in));
				XMStore(&XMMat, temp);
				return *this;
			}

			// Binary Operator

			const MatT<float, 4u, 3u> operator* (const MatT<float, 4u, 3u>& rhs) const {
				MatT<float, 4u, 3u> out;
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				temp = DirectX::XMMatrixMultiply(temp, DirectX::XMLoadFloat4x3(&rhs.XMMat));
				XMStore(&out.XMMat, temp);
				return out;
			}
			const MatT<float, 4u, 3u> operator* (float rhs[12]) const {
				MatT<float, 4u, 3u> out;
				DirectX::XMFLOAT4X3 in(rhs);
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				temp = DirectX::XMMatrixMultiply(temp, DirectX::XMLoadFloat4x3(&in));
				XMStore(&out.XMMat, temp);
				return out;
			}

			// Bitwise Operator

			friend std::ostream& operator<<	(std::ostream& out, const MatT<float, 4u, 3u>& rhs) noexcept {
				out << rhs.R0 << std::endl << rhs.R1 << std::endl << rhs.R2 << std::endl << rhs.R3;
				return out;
			}

			// Member Access Operator

			Vec3f& operator[] (const uint32_t& i) {
				#if _DEBUG
					if(i > 3u) throw std::invalid_argument("Access Violation!");
				#endif
				return reinterpret_cast<Vec3f*>(this)[i];
			}
			const Vec3f& operator[] (const uint32_t& i) const {
				#if _DEBUG
					if(i > 3u) throw std::invalid_argument("Access Violation!");
				#endif
				return reinterpret_cast<const Vec3f*>(this)[i];
			}

			// Cast Operator

			explicit operator MatT<float, 3u, 3u>() const;
			explicit operator MatT<float, 3u, 4u>() const;
			explicit operator MatT<float, 4u, 4u>() const;

			// Functions

			const MatT<float, 4u, 3u> Transposed() const {
				MatT<float, 4u, 3u> out;
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				temp = DirectX::XMMatrixTranspose(temp);
				XMStore(&out.XMMat, temp);
				return out;
			}
			const MatT<float, 4u, 3u> Inverse() const {
				MatT<float, 4u, 3u> out;
				XMMAT temp = DirectX::XMLoadFloat4x3(&XMMat);
				DirectX::XMVECTOR v = DirectX::XMMatrixDeterminant(temp);
				temp = DirectX::XMMatrixInverse(&v, DirectX::FXMMATRIX(temp));
				DirectX::XMStoreFloat4x3(&out.XMMat, temp);
				return out;
			}
			const float Determinant() const {
				float out;
				XMMAT temp = DirectX::XMLoadFloat4x3(&XMMat);
				DirectX::XMVECTOR v = DirectX::XMMatrixDeterminant(temp);
				DirectX::XMStoreFloat(&out, v);
				return out;
			}

			// Static Variables

			static const MatT<float, 4u, 3u> identity;

			union {
				DirectX::XMFLOAT4X3 XMMat;
				struct {
					float m00, m01, m02;
					float m10, m11, m12;
					float m20, m21, m22;
					float m30, m31, m32;
				};
				struct {
					Vec3f R0, R1, R2, R3;
				};
			};

		};


		// ----------------------------------------------------------------- //
		//                          Matrix4 Float                            //
		// ----------------------------------------------------------------- //
		template<>
		struct MatT<float, 4u, 4u> {

			constexpr MatT<float, 4u, 4u>() noexcept: XMMat(
				1.f, 0.f, 0.f, 0.f,
				0.f, 1.f, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f) {};
			constexpr MatT<float, 4u, 4u>(const float& m00, const float& m01, const float& m02, const float& m03, const float& m10, const float& m11, const float& m12, const float& m13, const float& m20, const float& m21, const float& m22, const float& m23, const float& m30, const float& m31, const float& m32, const float& m33) noexcept: XMMat(
				m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23,
				m30, m31, m32, m33) {};
			constexpr MatT<float, 4u, 4u>(const Vec4f& R0, const Vec4f& R1, const Vec4f& R2, const Vec4f& R3) noexcept:
				R0(R0),
				R1(R1),
				R2(R2),
				R3(R3) {};
			constexpr MatT<float, 4u, 4u>(const MatT<float, 4u, 4u>& rhs) noexcept:
				XMMat(rhs.XMMat) {};
			explicit MatT<float, 4u, 4u>(const float rhs[16]) noexcept:
				XMMat(rhs) {};

			// Assignment Operators

			const MatT<float, 4u, 4u>& operator= (const MatT<float, 4u, 4u>& rhs) {
				XMMat = rhs.XMMat;
				return *this;
			}
			const MatT<float, 4u, 4u>& operator= (const float rhs[16]) {
				XMMat = DirectX::XMFLOAT4X4(rhs);
				return *this;
			}
			const MatT<float, 4u, 4u>& operator= (const MatT<float, 3u, 3u>& rhs);
			const MatT<float, 4u, 4u>& operator= (const MatT<float, 3u, 4u>& rhs);
			const MatT<float, 4u, 4u>& operator= (const MatT<float, 4u, 3u>& rhs);
			const MatT<float, 4u, 4u>& operator*= (const MatT<float, 4u, 4u>& rhs) {
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				temp = DirectX::XMMatrixMultiply(temp, DirectX::XMLoadFloat4x4(&rhs.XMMat));
				XMStore(&XMMat, temp);
				return *this;
			}
			const MatT<float, 4u, 4u>& operator*= (const float rhs[16]) {
				DirectX::XMFLOAT4X4 in(rhs);
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				temp = DirectX::XMMatrixMultiply(temp, DirectX::XMLoadFloat4x4(&in));
				XMStore(&XMMat, temp);
				return *this;
			}

			// Binary Operator

			const MatT<float, 4u, 4u> operator* (const MatT<float, 4u, 4u>& rhs) const {
				MatT<float, 4u, 4u> out;
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				temp = DirectX::XMMatrixMultiply(temp, DirectX::XMLoadFloat4x4(&rhs.XMMat));
				XMStore(&out.XMMat, temp);
				return out;
			}
			const MatT<float, 4u, 4u> operator* (const float rhs[16]) const {
				MatT<float, 4u, 4u> out;
				DirectX::XMFLOAT4X4 in(rhs);
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				temp = DirectX::XMMatrixMultiply(temp, DirectX::XMLoadFloat4x4(&in));
				XMStore(&out.XMMat, temp);
				return out;
			}

			// Bitwise Operator

			friend std::ostream& operator<<	(std::ostream& out, const MatT<float, 4u, 4u>& rhs) noexcept {
				out << rhs.R0 << std::endl << rhs.R1 << std::endl << rhs.R2 << std::endl << rhs.R3;
				return out;
			}

			// Member Access Operator

			Vec3f& operator[] (const uint32_t& i) {
				#if _DEBUG
					if(i > 3u) throw std::invalid_argument("Access Violation!");
				#endif
				return reinterpret_cast<Vec3f*>(this)[i];
			}
			const Vec3f& operator[] (const uint32_t& i) const {
				#if _DEBUG
					if(i > 3u) throw std::invalid_argument("Access Violation!");
				#endif
				return reinterpret_cast<const Vec3f*>(this)[i];
			}

			// Cast Operator

			explicit operator MatT<float, 3u, 3u>() const;
			explicit operator MatT<float, 3u, 4u>() const;
			explicit operator MatT<float, 4u, 3u>() const;

			// Functions

			const MatT<float, 4u, 4u> Transposed() const {
				MatT<float, 4u, 4u> out;
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				temp = DirectX::XMMatrixTranspose(temp);
				XMStore(&out.XMMat, temp);
				return out;
			}
			const MatT<float, 4u, 4u> Inverse() const {
				MatT<float, 4u, 4u> out;
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				DirectX::XMVECTOR v = DirectX::XMMatrixDeterminant(temp);
				temp = DirectX::XMMatrixInverse(&v, DirectX::FXMMATRIX(temp));
				XMStore(&out.XMMat, temp);
				return out;
			}
			const float Determinant() const {
				float out;
				XMMAT temp = XMLoad<XMMAT>(&XMMat);
				DirectX::XMVECTOR v = DirectX::XMMatrixDeterminant(temp);
				XMStore(&out, v);
				return out;
			}

			// Static Variables

			static const MatT<float, 4u, 4u> identity;

			union {
				DirectX::XMFLOAT4X4 XMMat;
				struct {
					float m00, m01, m02, m03;
					float m10, m11, m12, m13;
					float m20, m21, m22, m23;
					float m30, m31, m32, m33;
				};
				struct {
					Vec4f R0, R1, R2, R3;
				};
			};

		};


		// Assignment Operator Def --------------------------------------------------

		inline const MatT<float, 3u, 3u>& MatT<float, 3u, 3u>::operator= (const MatT<float, 3u, 4u>& rhs) {
			m00 = rhs.m00;
			m01 = rhs.m01;
			m02 = rhs.m02;
			m10 = rhs.m10;
			m11 = rhs.m11;
			m12 = rhs.m12;
			m20 = rhs.m20;
			m21 = rhs.m21;
			m22 = rhs.m22;
			return *this;
		}
		inline const MatT<float, 3u, 3u>& MatT<float, 3u, 3u>::operator= (const MatT<float, 4u, 3u>& rhs) {
			m00 = rhs.m00;
			m01 = rhs.m01;
			m02 = rhs.m02;
			m10 = rhs.m10;
			m11 = rhs.m11;
			m12 = rhs.m12;
			m20 = rhs.m20;
			m21 = rhs.m21;
			m22 = rhs.m22;
			return *this;
		}
		inline const MatT<float, 3u, 3u>& MatT<float, 3u, 3u>::operator= (const MatT<float, 4u, 4u>& rhs) {
			m00 = rhs.m00;
			m01 = rhs.m01;
			m02 = rhs.m02;
			m10 = rhs.m10;
			m11 = rhs.m11;
			m12 = rhs.m12;
			m20 = rhs.m20;
			m21 = rhs.m21;
			m22 = rhs.m22;
			return *this;
		}
		
		inline const MatT<float, 3u, 4u>& MatT<float, 3u, 4u>::operator= (const MatT<float, 3u, 3u>& rhs) {
			m00 = rhs.m00;
			m01 = rhs.m01;
			m02 = rhs.m02;
			m10 = rhs.m10;
			m11 = rhs.m11;
			m12 = rhs.m12;
			m20 = rhs.m20;
			m21 = rhs.m21;
			m22 = rhs.m22;
			return *this;
		}
		inline const MatT<float, 3u, 4u>& MatT<float, 3u, 4u>::operator= (const MatT<float, 4u, 3u>& rhs) {
			m00 = rhs.m00;
			m01 = rhs.m01;
			m02 = rhs.m02;
			m10 = rhs.m10;
			m11 = rhs.m11;
			m12 = rhs.m12;
			m20 = rhs.m20;
			m21 = rhs.m21;
			m22 = rhs.m22;
			return *this;
		}
		inline const MatT<float, 3u, 4u>& MatT<float, 3u, 4u>::operator= (const MatT<float, 4u, 4u>& rhs) {
			m00 = rhs.m00;
			m01 = rhs.m01;
			m02 = rhs.m02;
			m03 = rhs.m03;
			m10 = rhs.m10;
			m11 = rhs.m11;
			m12 = rhs.m12;
			m13 = rhs.m13;
			m20 = rhs.m20;
			m21 = rhs.m21;
			m22 = rhs.m22;
			m23 = rhs.m23;
			return *this;
		}

		inline const MatT<float, 4u, 3u>& MatT<float, 4u, 3u>::operator= (const MatT<float, 3u, 3u>& rhs) {
			m00 = rhs.m00;
			m01 = rhs.m01;
			m02 = rhs.m02;
			m10 = rhs.m10;
			m11 = rhs.m11;
			m12 = rhs.m12;
			m20 = rhs.m20;
			m21 = rhs.m21;
			m22 = rhs.m22;
			return *this;
		}
		inline const MatT<float, 4u, 3u>& MatT<float, 4u, 3u>::operator= (const MatT<float, 3u, 4u>& rhs) {
			m00 = rhs.m00;
			m01 = rhs.m01;
			m02 = rhs.m02;
			m10 = rhs.m10;
			m11 = rhs.m11;
			m12 = rhs.m12;
			m20 = rhs.m20;
			m21 = rhs.m21;
			m22 = rhs.m22;
			return *this;
		}
		inline const MatT<float, 4u, 3u>& MatT<float, 4u, 3u>::operator= (const MatT<float, 4u, 4u>& rhs) {
			m00 = rhs.m00;
			m01 = rhs.m01;
			m02 = rhs.m02;
			m10 = rhs.m10;
			m11 = rhs.m11;
			m12 = rhs.m12;
			m20 = rhs.m20;
			m21 = rhs.m21;
			m22 = rhs.m22;
			m30 = rhs.m30;
			m31 = rhs.m31;
			m32 = rhs.m32;
			return *this;
		}

		inline const MatT<float, 4u, 4u>& MatT<float, 4u, 4u>::operator= (const MatT<float, 3u, 3u>& rhs) {
			m00 = rhs.m00;
			m01 = rhs.m01;
			m02 = rhs.m02;
			m10 = rhs.m10;
			m11 = rhs.m11;
			m12 = rhs.m12;
			m20 = rhs.m20;
			m21 = rhs.m21;
			m22 = rhs.m22;
			return *this;
		}
		inline const MatT<float, 4u, 4u>& MatT<float, 4u, 4u>::operator= (const MatT<float, 3u, 4u>& rhs) {
			m00 = rhs.m00;
			m01 = rhs.m01;
			m02 = rhs.m02;
			m03 = rhs.m03;
			m10 = rhs.m10;
			m11 = rhs.m11;
			m12 = rhs.m12;
			m13 = rhs.m13;
			m20 = rhs.m20;
			m21 = rhs.m21;
			m22 = rhs.m22;
			m23 = rhs.m23;
			return *this;
		}
		inline const MatT<float, 4u, 4u>& MatT<float, 4u, 4u>::operator= (const MatT<float, 4u, 3u>& rhs) {
			m00 = rhs.m00;
			m01 = rhs.m01;
			m02 = rhs.m02;
			m10 = rhs.m10;
			m11 = rhs.m11;
			m12 = rhs.m12;
			m20 = rhs.m20;
			m21 = rhs.m21;
			m22 = rhs.m22;
			m30 = rhs.m30;
			m31 = rhs.m31;
			m32 = rhs.m32;
			return *this;
		}


		// Cast Operator Def --------------------------------------------------

		inline MatT<float, 3u, 3u>::operator MatT<float, 3u, 4u>() const {
			MatT<float, 3u, 4u> out;
			out.m00 = m00;
			out.m01 = m01;
			out.m02 = m02;
			out.m10 = m10;
			out.m11 = m11;
			out.m12 = m12;
			out.m20 = m20;
			out.m21 = m21;
			out.m22 = m22;
			return out;
		}
		inline MatT<float, 3u, 3u>::operator MatT<float, 4u, 3u>() const {
			MatT<float, 4u, 3u> out;
			out.m00 = m00;
			out.m01 = m01;
			out.m02 = m02;
			out.m10 = m10;
			out.m11 = m11;
			out.m12 = m12;
			out.m20 = m20;
			out.m21 = m21;
			out.m22 = m22;
			return out;
		}
		inline MatT<float, 3u, 3u>::operator MatT<float, 4u, 4u>() const {
			MatT<float, 4u, 4u> out;
			out.m00 = m00;
			out.m01 = m01;
			out.m02 = m02;
			out.m10 = m10;
			out.m11 = m11;
			out.m12 = m12;
			out.m20 = m20;
			out.m21 = m21;
			out.m22 = m22;
			return out;
		}

		inline MatT<float, 3u, 4u>::operator MatT<float, 3u, 3u>() const {
			MatT<float, 3u, 3u> out;
			out.m00 = m00;
			out.m01 = m01;
			out.m02 = m02;
			out.m10 = m10;
			out.m11 = m11;
			out.m12 = m12;
			out.m20 = m20;
			out.m21 = m21;
			out.m22 = m22;
			return out;
		}
		inline MatT<float, 3u, 4u>::operator MatT<float, 4u, 3u>() const {
			MatT<float, 4u, 3u> out;
			out.m00 = m00;
			out.m01 = m01;
			out.m02 = m02;
			out.m10 = m10;
			out.m11 = m11;
			out.m12 = m12;
			out.m20 = m20;
			out.m21 = m21;
			out.m22 = m22;
			return out;
		}
		inline MatT<float, 3u, 4u>::operator MatT<float, 4u, 4u>() const {
			MatT<float, 4u, 4u> out;
			out.m00 = m00;
			out.m01 = m01;
			out.m02 = m02;
			out.m03 = m03;
			out.m10 = m10;
			out.m11 = m11;
			out.m12 = m12;
			out.m13 = m13;
			out.m20 = m20;
			out.m21 = m21;
			out.m22 = m22;
			out.m23 = m23;
			return out;
		}

		inline MatT<float, 4u, 3u>::operator MatT<float, 3u, 3u>() const {
			MatT<float, 3u, 3u> out;
			out.m00 = m00;
			out.m01 = m01;
			out.m02 = m02;
			out.m10 = m10;
			out.m11 = m11;
			out.m12 = m12;
			out.m20 = m20;
			out.m21 = m21;
			out.m22 = m22;
			return out;
		}
		inline MatT<float, 4u, 3u>::operator MatT<float, 3u, 4u>() const {
			MatT<float, 3u, 4u> out;
			out.m00 = m00;
			out.m01 = m01;
			out.m02 = m02;
			out.m10 = m10;
			out.m11 = m11;
			out.m12 = m12;
			out.m20 = m20;
			out.m21 = m21;
			out.m22 = m22;
			return out;
		}
		inline MatT<float, 4u, 3u>::operator MatT<float, 4u, 4u>() const {
			MatT<float, 4u, 4u> out;
			out.m00 = m00;
			out.m01 = m01;
			out.m02 = m02;
			out.m10 = m10;
			out.m11 = m11;
			out.m12 = m12;
			out.m20 = m20;
			out.m21 = m21;
			out.m22 = m22;
			out.m30 = m30;
			out.m31 = m31;
			out.m32 = m32;
			return out;
		}

		inline MatT<float, 4u, 4u>::operator MatT<float, 3u, 3u>() const {
			MatT<float, 3u, 3u> out;
			out.m00 = m00;
			out.m01 = m01;
			out.m02 = m02;
			out.m10 = m10;
			out.m11 = m11;
			out.m12 = m12;
			out.m20 = m20;
			out.m21 = m21;
			out.m22 = m22;
			return out;
		}
		inline MatT<float, 4u, 4u>::operator MatT<float, 3u, 4u>() const {
			MatT<float, 3u, 4u> out;
			out.m00 = m00;
			out.m01 = m01;
			out.m02 = m02;
			out.m03 = m03;
			out.m10 = m10;
			out.m11 = m11;
			out.m12 = m12;
			out.m13 = m13;
			out.m20 = m20;
			out.m21 = m21;
			out.m22 = m22;
			out.m23 = m23;
			return out;
		}
		inline MatT<float, 4u, 4u>::operator MatT<float, 4u, 3u>() const {
			MatT<float, 4u, 3u> out;
			out.m00 = m00;
			out.m01 = m01;
			out.m02 = m02;
			out.m10 = m10;
			out.m11 = m11;
			out.m12 = m12;
			out.m20 = m20;
			out.m21 = m21;
			out.m22 = m22;
			out.m30 = m30;
			out.m31 = m31;
			out.m32 = m32;
			return out;
		}

};


	// Matrix Short Def ------------------------------------

	using Mat3f = Concealed::MatT<float, 3u, 3u>;
	using Mat3x4f = Concealed::MatT<float, 3u, 4u>;
	using Mat4x3f = Concealed::MatT<float, 4u, 3u>;
	using Mat4f = Concealed::MatT<float, 4u, 4u>;
	

	// ----------------------------------------------------------------- //
	//		    ___              _                  _					 //
	//		   / _ \ _   _  __ _| |_ ___ _ __ _ __ (_) ___  _ __		 //
	//		  | | | | | | |/ _` | __/ _ \ '__| '_ \| |/ _ \| '_ \		 //
	//		  | |_| | |_| | (_| | ||  __/ |  | | | | | (_) | | | |		 //
	//		   \__\_\\__,_|\__,_|\__\___|_|  |_| |_|_|\___/|_| |_|		 //
	// ----------------------------------------------------------------- //
	
	
	struct Quat : public DirectX::XMFLOAT4 {

		constexpr Quat() noexcept: XMFLOAT4(0.f, 0.f, 0.f, 1.f) {}
		constexpr Quat(const float& x, const float& y, const float& z, const float& w) noexcept: XMFLOAT4(x, y, z, w) {}
		constexpr Quat(const Quat& rhs) noexcept: XMFLOAT4(rhs) {}
		explicit Quat(const float rhs[4]) noexcept: XMFLOAT4(rhs) {}

		// Unary Operators

		Quat operator+ () const noexcept {
			return *this;
		}
		Quat operator- () const noexcept {
			Quat out;
			out.x = -x;
			out.y = -y;
			out.z = -z;
			out.w = -w;
			return out;
		}
		const Quat& operator++ () noexcept {
			Increment(1.f, 1.f, 1.f, 1.f);
			return *this;
		}
		const Quat& operator++ (int) noexcept {
			Increment(1.f, 1.f, 1.f, 1.f);
			return *this;
		}
		const Quat& operator-- () noexcept {
			Decrement(1.f, 1.f, 1.f, 1.f);
			return *this;
		}
		const Quat& operator-- (int) noexcept {
			Decrement(1.f, 1.f, 1.f, 1.f);
			return *this;
		}

		// Assignment Operators

		const Quat& operator= (const Quat& rhs) noexcept {
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			w = rhs.w;
			return *this;
		}
		const Quat& operator= (const float rhs[4]) noexcept {
			x = rhs[0];
			y = rhs[1];
			z = rhs[2];
			w = rhs[3];
			return *this;
		}
		const Quat& operator+= (const Quat& rhs) noexcept {
			Increment(rhs.x, rhs.y, rhs.z, rhs.w);
			return *this;
		}
		const Quat& operator+= (const float rhs[4]) noexcept {
			Increment(rhs[0], rhs[1], rhs[2], rhs[3]);
			return *this;
		}
		const Quat& operator-= (const Quat& rhs) noexcept {
			Decrement(rhs.x, rhs.y, rhs.z, rhs.w);
			return *this;
		}
		const Quat& operator-= (const float rhs[4]) noexcept {
			Decrement(rhs[0], rhs[1], rhs[2], rhs[3]);
			return *this;
		}

		// Binary Operator

		const Quat operator+ (const Quat& rhs) const noexcept {
			return Add(rhs.x, rhs.y, rhs.z, rhs.w);
		}
		const Quat operator+ (const float rhs[4]) const noexcept {
			return Add(rhs[0], rhs[1], rhs[2], rhs[3]);
		}
		const Quat operator- (const Quat& rhs) const noexcept {
			return Subtract(rhs.x, rhs.y, rhs.z, rhs.w);
		}
		const Quat operator- (const float rhs[4]) const noexcept {
			return Subtract(rhs[0], rhs[1], rhs[2], rhs[3]);
		}
		const Quat operator* (const Quat& rhs) const noexcept {
			return Multiply(rhs.x, rhs.y, rhs.z, rhs.w);
		}
		const Quat operator* (const float rhs[4]) const noexcept {
			return Multiply(rhs[0], rhs[1], rhs[2], rhs[3]);
		}
		const Quat operator* (const float rhs) const noexcept {
			Quat out;
			Concealed::XMVEC temp = Concealed::XMLoad<Concealed::XMVEC>(this);
			temp = DirectX::XMVectorScale(temp, rhs);
			Concealed::XMStore(&out, temp);
			return out;
		}

		// Bitwise Operator

		friend std::ostream& operator<<	(std::ostream& out, const Quat& rhs) noexcept {
			out << "[" << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << "]";
			return out;
		}

		// Member Access Operator

		float& operator[] (const uint32_t& i) {
			if(i > 3) throw std::invalid_argument("Access Violation!");
			return reinterpret_cast<float*>(this)[i];
		}
		const float& operator[] (const uint32_t& i) const {
			if(i > 3) throw std::invalid_argument("Access Violation!");
			return reinterpret_cast<const float*>(this)[i];
		}

		// Cast Operator

		operator const Vec4f() const;

		// Static Variables

		static const Quat identity;

		// Functions

		const float Magnitude() const noexcept {
			float out;
			Concealed::XMVEC temp = Concealed::XMLoad<Concealed::XMVEC>(this);
			temp = DirectX::XMQuaternionLength(temp);
			Concealed::XMStore(&out, temp);
			return out;
		};
		const Quat Normalized() const noexcept {
			Quat out;
			Concealed::XMVEC temp = Concealed::XMLoad<Concealed::XMVEC>(this);
			temp = DirectX::XMVector4Normalize(temp);
			Concealed::XMStore(&out, temp);
			return out;
		}
		const Quat Conjugate() const noexcept {
			Quat out;
			Concealed::XMVEC temp = Concealed::XMLoad<Concealed::XMVEC>(this);
			temp = DirectX::XMQuaternionConjugate(temp);
			Concealed::XMStore(&out, temp);
			return out;
		}
		const Quat Inverse() const noexcept {
			Quat out;
			Concealed::XMVEC temp = Concealed::XMLoad<Concealed::XMVEC>(this);
			temp = DirectX::XMQuaternionInverse(temp);
			Concealed::XMStore(&out, temp);
			return out;
		}

		// Private Functions

		private:

		inline void Increment(const float& x, const float& y, const float& z, const float& w) {
			Concealed::XMVEC temp = Concealed::XMLoad<Concealed::XMVEC>(this);
			temp = DirectX::XMVectorAdd(temp, DirectX::XMVectorSet(x, y, z, w));
			Concealed::XMStore(this, temp);
		}
		inline void Decrement(const float& x, const float& y, const float& z, const float& w) {
			Concealed::XMVEC temp = Concealed::XMLoad<Concealed::XMVEC>(this);
			temp = DirectX::XMVectorSubtract(temp, DirectX::XMVectorSet(x, y, z, w));
			Concealed::XMStore(this, temp);
		}
		inline const Quat Add(const float& x, const float& y, const float& z, const float& w) const noexcept {
			Quat out;
			Concealed::XMVEC temp = Concealed::XMLoad<Concealed::XMVEC>(this);
			temp = DirectX::XMVectorAdd(temp, DirectX::XMVectorSet(x, y, z, w));
			Concealed::XMStore(&out, temp);
			return out;
		}
		inline const Quat Subtract(const float& x, const float& y, const float& z, const float& w) const noexcept {
			Quat out;
			Concealed::XMVEC temp = Concealed::XMLoad<Concealed::XMVEC>(this);
			temp = DirectX::XMVectorSubtract(temp, DirectX::XMVectorSet(x, y, z, w));
			Concealed::XMStore(&out, temp);
			return out;
		}
		inline const Quat Multiply(const float& x, const float& y, const float& z, const float& w) const {
			Quat out;
			Concealed::XMVEC temp = Concealed::XMLoad<Concealed::XMVEC>(this);
			temp = DirectX::XMQuaternionMultiply(temp, DirectX::XMVectorSet(x, y, z, w));
			Concealed::XMStore(&out, temp);
			return out;
		}
	};


	// Cast Operator Def --------------------------------------------------

	inline Quat::operator const Vec4f() const {
		Vec4f out;
		out.x = static_cast<float>(x);
		out.y = static_cast<float>(y);
		out.z = static_cast<float>(z);
		out.w = static_cast<float>(w);
		return out;
	}
	inline Vec4f::operator const Quat() const {
		Quat out;
		out.x = static_cast<float>(x);
		out.y = static_cast<float>(y);
		out.z = static_cast<float>(z);
		out.w = static_cast<float>(w);
		return out;
	}

	
	// ----------------------------------------------------------------- //
	//					     ____      _            					 //
	//					    / ___|___ | | ___  _ __ 					 //
	//					   | |   / _ \| |/ _ \| '__|					 //
	//					   | |__| (_) | | (_) | |   					 //
	//					    \____\___/|_|\___/|_|   					 //
    // ----------------------------------------------------------------- //                       


	struct Color {
		
		constexpr Color(): XMVec(0.f, 0.f, 0.f, 1.f) {}
		constexpr Color(const float& r, const float& g, const float& b, const float& a): XMVec(r, g, b, a) {}
		constexpr Color(const Color& rhs): XMVec(rhs.XMVec) {}
		explicit Color(const float rhs[4]): XMVec(rhs) {}

		// Assignment Operators

		const Color& operator= (const Color& rhs) noexcept {
			r = rhs.r;
			g = rhs.g;
			b = rhs.b;
			a = rhs.a;
			return *this;
		}
		const Color& operator= (const Vec4f& rhs) noexcept {
			r = rhs.x;
			g = rhs.y;
			b = rhs.z;
			a = rhs.w;
			return *this;
		}
		const Color& operator= (const float rhs[4]) noexcept {
			r = rhs[0];
			g = rhs[1];
			b = rhs[2];
			a = rhs[3];
			return *this;
		}

		// Bitwise Operator

		friend std::ostream& operator<<	(std::ostream& out, const Color& rhs) noexcept {
			out << "[" << rhs.r << ", " << rhs.g << ", " << rhs.b << ", " << rhs.a << "]";
			return out;
		}

		// Member Access Operator

		float& operator[] (const uint32_t& i) {
			#if _DEBUG
				if(i > 3u) throw std::invalid_argument("Access Violation!");
			#endif
			return reinterpret_cast<float*>(this)[i];
		}
		const float& operator[] (const uint32_t& i) const {
			#if _DEBUG
				if(i > 3u) throw std::invalid_argument("Access Violation!");
			#endif
			return reinterpret_cast<const float*>(this)[i];
		}

		// Cast Operator

		operator const Vec4f() const;

		// Static Variables

		static const Color AliceBlue;
		static const Color AntiqueWhite;
		static const Color Aqua;
		static const Color Aquamarine;
		static const Color Azure;
		static const Color Beige;
		static const Color Bisque;
		static const Color Black;
		static const Color BlanchedAlmond;
		static const Color Blue;
		static const Color BlueViolet;
		static const Color Brown;
		static const Color BurlyWood;
		static const Color CadetBlue;
		static const Color Chartreuse;
		static const Color Chocolate;
		static const Color Coral;
		static const Color CornflowerBlue;
		static const Color Cornsilk;
		static const Color Crimson;
		static const Color Cyan;
		static const Color DarkBlue;
		static const Color DarkCyan;
		static const Color DarkGoldenrod;
		static const Color DarkGray;
		static const Color DarkGreen;
		static const Color DarkKhaki;
		static const Color DarkMagenta;
		static const Color DarkOliveGreen;
		static const Color DarkOrange;
		static const Color DarkOrchid;
		static const Color DarkRed;
		static const Color DarkSalmon;
		static const Color DarkSeaGreen;
		static const Color DarkSlateBlue;
		static const Color DarkSlateGray;
		static const Color DarkTurquoise;
		static const Color DarkViolet;
		static const Color DeepPink;
		static const Color DeepSkyBlue;
		static const Color DimGray;
		static const Color DodgerBlue;
		static const Color Firebrick;
		static const Color FloralWhite;
		static const Color ForestGreen;
		static const Color Fuchsia;
		static const Color Gainsboro;
		static const Color GhostWhite;
		static const Color Gold;
		static const Color Goldenrod;
		static const Color Gray;
		static const Color Green;
		static const Color GreenYellow;
		static const Color Honeydew;
		static const Color HotPink;
		static const Color IndianRed;
		static const Color Indigo;
		static const Color Ivory;
		static const Color Khaki;
		static const Color Lavender;
		static const Color LavenderBlush;
		static const Color LawnGreen;
		static const Color LemonChiffon;
		static const Color LightBlue;
		static const Color LightCoral;
		static const Color LightCyan;
		static const Color LightGoldenrodYellow;
		static const Color LightGreen;
		static const Color LightGray;
		static const Color LightPink;
		static const Color LightSalmon;
		static const Color LightSeaGreen;
		static const Color LightSkyBlue;
		static const Color LightSlateGray;
		static const Color LightSteelBlue;
		static const Color LightYellow;
		static const Color Lime;
		static const Color LimeGreen;
		static const Color Linen;
		static const Color Magenta;
		static const Color Maroon;
		static const Color MediumAquamarine;
		static const Color MediumBlue;
		static const Color MediumOrchid;
		static const Color MediumPurple;
		static const Color MediumSeaGreen;
		static const Color MediumSlateBlue;
		static const Color MediumSpringGreen;
		static const Color MediumTurquoise;
		static const Color MediumVioletRed;
		static const Color MidnightBlue;
		static const Color MintCream;
		static const Color MistyRose;
		static const Color Moccasin;
		static const Color NavajoWhite;
		static const Color Navy;
		static const Color OldLace;
		static const Color Olive;
		static const Color OliveDrab;
		static const Color Orange;
		static const Color OrangeRed;
		static const Color Orchid;
		static const Color PaleGoldenrod;
		static const Color PaleGreen;
		static const Color PaleTurquoise;
		static const Color PaleVioletRed;
		static const Color PapayaWhip;
		static const Color PeachPuff;
		static const Color Peru;
		static const Color Pink;
		static const Color Plum;
		static const Color PowderBlue;
		static const Color Purple;
		static const Color Red;
		static const Color RosyBrown;
		static const Color RoyalBlue;
		static const Color SaddleBrown;
		static const Color Salmon;
		static const Color SandyBrown;
		static const Color SeaGreen;
		static const Color SeaShell;
		static const Color Sienna;
		static const Color Silver;
		static const Color SkyBlue;
		static const Color SlateBlue;
		static const Color SlateGray;
		static const Color Snow;
		static const Color SpringGreen;
		static const Color SteelBlue;
		static const Color Tan;
		static const Color Teal;
		static const Color Thistle;
		static const Color Tomato;
		static const Color Transparent;
		static const Color Turquoise;
		static const Color Violet;
		static const Color Wheat;
		static const Color White;
		static const Color WhiteSmoke;
		static const Color Yellow;
		static const Color YellowGreen;


		union {
			DirectX::XMFLOAT4 XMVec;
			struct {float r, g, b, a;};
		};

	};


	// Cast Operator Def --------------------------------------------------

	inline Color::operator const Vec4f() const {
		Vec4f out;
		out.x = r;
		out.y = g;
		out.z = b;
		out.w = a;
		return out;
	}
	inline Vec4f::operator const Color() const {
		Color out;
		out.r = x;
		out.g = y;
		out.b = z;
		out.a = w;
		return out;
	}


	// ----------------------------------------------------------------- //
	//			   ____                _              _       			 //
	//			  / ___|___  _ __  ___| |_ __ _ _ __ | |_ ___ 			 //
	//			 | |   / _ \| '_ \/ __| __/ _` | '_ \| __/ __|			 //
	//			 | |__| (_) | | | \__ \ || (_| | | | | |_\__ \			 //
	//			  \____\___/|_| |_|___/\__\__,_|_| |_|\__|___/			 //
	// ----------------------------------------------------------------- //       


	constexpr double C_PI(3.14159265358979323846);
	constexpr double C_2xPI(6.28318530717958647692);
	constexpr double C_PI2(1.57079632679489661923);
	constexpr double C_PI4(0.785398163397448309616);
	constexpr double C_1PI(0.318309886183790671538);
	constexpr double C_2PI(0.636619772367581343076);
	constexpr double C_2SqrtPI(1.12837916709551257390);
	constexpr double C_Sqrt2(1.41421356237309504880);
	constexpr double C_1Sqrt2(0.707106781186547524401);
	constexpr double C_E(2.71828182845904523536);
	constexpr double C_Log2E(1.44269504088896340736);
	constexpr double C_Log10E(0.434294481903251827651);
	constexpr double C_LogE2(0.693147180559945309417);
	constexpr double C_LogE10(2.30258509299404568402);
	constexpr double C_180dPI(57.2957795130823208767);
	constexpr double C_1d180xPI(0.01745329251994329576);
	

	// ----------------------------------------------------------------- //
	//			 ____  ____  ____  _                           			 //
	//			|___ \|  _ \/ ___|| |__   __ _ _ __   ___  ___ 			 //
	//			  __) | | | \___ \| '_ \ / _` | '_ \ / _ \/ __|			 //
	//			 / __/| |_| |___) | | | | (_| | |_) |  __/\__ \			 //
	//			|_____|____/|____/|_| |_|\__,_| .__/ \___||___/			 //
	//									      |_|              			 //
	// ----------------------------------------------------------------- //                 
	

	struct Circle;
	struct Rectf;
	struct Recti;
	struct ORect;


	// ----------------------------------------------------------------- //
	//							    Circle								 //
	// ----------------------------------------------------------------- //
	struct Circle {

		constexpr Circle() noexcept: origin(origin), radius(0.f) {}
		constexpr Circle(const Vec2f& origin, const float& radius) noexcept: origin(origin), radius(radius) {}
		constexpr Circle(const float& x, const float& y, const float& radius) noexcept: origin(x, y), radius(radius) {}
		constexpr Circle(const Circle& rhs) noexcept: origin(origin), radius(rhs.radius) {}

		// Assignment Operators

		const Circle& operator= (const Circle& rhs) noexcept {
			origin = rhs.origin;
			radius = rhs.radius;
			return *this;
		}

		// Bitwise Operator

		friend std::ostream& operator<<	(std::ostream& out, const Circle& rhs) noexcept {
			out << "Origin: " << rhs.origin << "	|" << "Radius: " << rhs.radius;
			return out;
		}

		// Functions

		const float GetArea() noexcept {
			return static_cast<float>(C_PI) * radius * radius;
		}
		const float GetCircum() noexcept {
			return 2.f * static_cast<float>(C_PI) * radius;
		}
		const float GetDiameter() noexcept {
			return radius * 2.f;
		}

		Vec2f origin;
		float radius;

	};


	// ----------------------------------------------------------------- //
	//								Rectf								 //
	// ----------------------------------------------------------------- //
	struct Rectf {

		constexpr Rectf() noexcept: origin(), size() {}
		constexpr Rectf(const Vec2f& origin, const Vec2f& size) noexcept: origin(origin), size(size) {}
		constexpr Rectf(const float& x, const float& y, const float& width, const float& height) noexcept: origin(x, y), size(width, height) {}
		constexpr Rectf(const Rectf& rhs) noexcept: origin(rhs.origin), size(rhs.size) {}

		// Assignment Operators

		const Rectf& operator= (const Rectf& rhs) noexcept {
			origin = rhs.origin;
			size = rhs.size;
			return *this;
		}

		// Bitwise Operator

		friend std::ostream& operator<<	(std::ostream& out, const Rectf& rhs) noexcept {
			out << "Origin: " << rhs.origin << "	|" << "Size: " << rhs.size;
			return out;
		}

		// Cast Operator

		operator const Recti() const;

		// Functions

		const Vec2f GetCenter() const noexcept {
			return origin + size * 0.5f;
		}
		const Vec2f GetTL() const noexcept {
			return origin + Vec2f(DirectX::XMMin(0.f, size.x), DirectX::XMMax(0.f, size.y));
		}
		const Vec2f GetTR() const noexcept {
			return origin + Vec2f(DirectX::XMMax(0.f, size.x), DirectX::XMMax(0.f, size.y));
		}
		const Vec2f GetBL() const noexcept {
			return origin + Vec2f(DirectX::XMMin(0.f, size.x), DirectX::XMMin(0.f, size.y));
		}
		const Vec2f GetBR() const noexcept {
			return origin + Vec2f(DirectX::XMMax(0.f, size.x), DirectX::XMMin(0.f, size.y));
		}
		const float	GetL() const noexcept {
			return origin.x + DirectX::XMMin(0.f, size.x);
		}
		const float	GetR() const noexcept {
			return origin.x + DirectX::XMMax(0.f, size.x);
		}
		const float	GetT() const noexcept {
			return origin.y + DirectX::XMMax(0.f, size.y);
		}
		const float	GetB() const noexcept {
			return origin.y + DirectX::XMMin(0.f, size.y);
		}
		const float Area() const noexcept {
			return size.x * size.y;
		}

		union {
			Vec2f origin;
			struct {float x, y;};
		};

		union {
			Vec2f size;
			struct {float width, height;};
		};

	};


	// ----------------------------------------------------------------- //
	//								Recti								 //
	// ----------------------------------------------------------------- //
	struct Recti {

		constexpr Recti() noexcept: origin(), size() {}
		constexpr Recti(const Vec2i& origin, const Vec2i& size) noexcept: origin(origin), size(size) {}
		constexpr Recti(const int& x, const int& y, const int& width, const int& height) noexcept: origin(x, y), size(width, height) {}
		constexpr Recti(const Recti& rhs) noexcept: origin(rhs.origin), size(rhs.size) {}

		// Assignment Operators

		const Recti& operator= (const Recti& rhs) noexcept {
			origin = rhs.origin;
			size = rhs.size;
			return *this;
		}

		// Bitwise Operator

		friend std::ostream& operator<<	(std::ostream& out, const Recti& rhs) noexcept {
			out << "Origin: " << rhs.origin << "	|" << "Size: " << rhs.size;
			return out;
		}

		// Cast Operator

		operator const Rectf() const;

		// Functions

		const Vec2f GetCenter() const noexcept {
			return static_cast<Vec2f>(origin) + static_cast<Vec2f>(size) * 0.5f;
		}
		const Vec2i GetTL() const noexcept {
			return origin + Vec2i(DirectX::XMMin(0, size.x), DirectX::XMMax(0, size.y));
		}
		const Vec2i GetTR() const noexcept {
			return origin + Vec2i(DirectX::XMMax(0, size.x), DirectX::XMMax(0, size.y));
		}
		const Vec2i GetBL() const noexcept {
			return origin + Vec2i(DirectX::XMMin(0, size.x), DirectX::XMMin(0, size.y));
		}
		const Vec2i GetBR() const noexcept {
			return origin + Vec2i(DirectX::XMMax(0, size.x), DirectX::XMMin(0, size.y));
		}
		const int	GetL() const noexcept {
			return origin.x + DirectX::XMMin(0, size.x);
		}
		const int	GetR() const noexcept {
			return origin.x + DirectX::XMMax(0, size.x);
		}
		const int	GetT() const noexcept {
			return origin.y + DirectX::XMMax(0, size.y);
		}
		const int	GetB() const noexcept {
			return origin.y + DirectX::XMMin(0, size.y);
		}
		const int Area() const noexcept {
			return size.x * size.y;
		}

		union {
			Vec2i origin;
			struct {int x, y;};
		};

		union {
			Vec2i size;
			struct {int width, height;};
		};

	};


	// ----------------------------------------------------------------- //
	//								ORect								 //
	// ----------------------------------------------------------------- //

	namespace Concealed {
		static const Vec2f RotateVec(const Vec2f& v, const float& ang) {
			Vec2f out;
			float a = DirectX::XMConvertToRadians(ang);
			out.x = v.x * cos(a) - v.y * sin(a);
			out.y = v.x * sin(a) + v.y * cos(a);
			return out;
		}
	}

	struct ORect {

		constexpr ORect() noexcept: origin(), size(), offset(), rot(0.f) {}
		constexpr ORect(const Vec2f& origin, const Vec2f& size) noexcept: origin(origin), size(size), offset(), rot(0.f) {}
		constexpr ORect(const Vec2f& origin, const Vec2f& size, const float& rot) noexcept: origin(origin), size(size), offset(), rot(rot) {}
		constexpr ORect(const float& x, const float& y, const float& width, const float& height, const float& rot) noexcept: origin(x, y), size(width, height), offset(), rot(rot) {}
		constexpr ORect(const ORect& rhs) noexcept: origin(rhs.origin), size(rhs.size), offset(), rot(rhs.rot) {}

		// Assignment Operators

		const ORect& operator= (const ORect& rhs) noexcept {
			origin = rhs.origin;
			size = rhs.size;
			return *this;
		}

		// Bitwise Operator

		friend std::ostream& operator<<	(std::ostream& out, const ORect& rhs) noexcept {
			out << "Origin: " << rhs.origin << "	|Size: " << rhs.size << "	|Rot: " << rhs.rot;
			return out;
		}

		// Functions

		const Vec2f GetCenter() const noexcept {
			return origin + Concealed::RotateVec(size * 0.5f - offset, rot);
		}
		const Vec2f GetTL() const noexcept {
			return origin + Concealed::RotateVec(Vec2f(DirectX::XMMin(0.f, size.x), DirectX::XMMax(0.f, size.y)) - offset, rot);
		}
		const Vec2f GetTR() const noexcept {
			return origin + Concealed::RotateVec(Vec2f(DirectX::XMMax(0.f, size.x), DirectX::XMMax(0.f, size.y)) - offset, rot);
		}
		const Vec2f GetBL() const noexcept {
			return origin + Concealed::RotateVec(Vec2f(DirectX::XMMin(0.f, size.x), DirectX::XMMin(0.f, size.y)) - offset, rot);
		}
		const Vec2f GetBR() const noexcept {
			return origin + Concealed::RotateVec(Vec2f(DirectX::XMMax(0.f, size.x), DirectX::XMMin(0.f, size.y)) - offset, rot);
		}
		const Vec2f	GetL() const noexcept {
			return origin + Concealed::RotateVec(Vec2f(1.f, 0.f) * DirectX::XMMin(0.f, size.x) - offset, rot);
		}
		const Vec2f	GetR() const noexcept {
			return origin + Concealed::RotateVec(Vec2f(1.f, 0.f) * DirectX::XMMax(0.f, size.x) - offset, rot);
		}
		const Vec2f	GetT() const noexcept {
			return origin + Concealed::RotateVec(Vec2f(0.f, 1.f) * DirectX::XMMax(0.f, size.y) - offset, rot);
		}
		const Vec2f	GetB() const noexcept {
			return origin + Concealed::RotateVec(Vec2f(0.f, 1.f) * DirectX::XMMin(0.f, size.y) - offset, rot);
		}
		const Vec2f LDir() const noexcept{
			return Concealed::RotateVec(Vec2f(-1.f, 0.f), rot);
		}
		const Vec2f RDir() const noexcept{
			return Concealed::RotateVec(Vec2f(1.f, 0.f), rot);
		}
		const Vec2f UDir() const noexcept{
			return Concealed::RotateVec(Vec2f(0.f, 1.f), rot);
		}
		const Vec2f DDir() const noexcept{
			return Concealed::RotateVec(Vec2f(0.f, -1.f), rot);
		}
		const float Area() const noexcept {
			return size.x * size.y;
		}

		union {
			Vec2f origin;
			struct {float x, y;};
		};

		union {
			Vec2f size;
			struct {float width, height;};
		};

		Vec2f offset;
		float rot;

	};


	// Cast Operator Def --------------------------------------------------

	inline Rectf::operator const Recti() const {
		Recti out;
		out.origin = static_cast<Vec2i>(origin);
		out.size = static_cast<Vec2i>(size);
		return out;
	}
	inline Recti::operator const Rectf() const {
		Rectf out;
		out.origin = static_cast<Vec2f>(origin);
		out.size = static_cast<Vec2f>(size);
		return out;
	}

	
	// ----------------------------------------------------------------- //
	//			 _____ ____  ____  _                           			 //
	//			|___ /|  _ \/ ___|| |__   __ _ _ __   ___  ___ 			 //
	//			  |_ \| | | \___ \| '_ \ / _` | '_ \ / _ \/ __|			 //
	//			 ___) | |_| |___) | | | | (_| | |_) |  __/\__ \			 //
	//			|____/|____/|____/|_| |_|\__,_| .__/ \___||___/			 //
	//			                              |_|              			 //
	// ----------------------------------------------------------------- //


	struct Frustum;
	struct Sphere;
	struct AABB;
	struct OBB;


	// ----------------------------------------------------------------- //
	//								Frustum								 //
	// ----------------------------------------------------------------- //
	struct Frustum {

		Frustum() noexcept: DXFrustum() {}
		Frustum(const Mat4f& projection) noexcept {
			Concealed::XMMAT m = Concealed::XMLoad<Concealed::XMMAT>(&projection);
			DirectX::BoundingFrustum::CreateFromMatrix(DXFrustum, m);
		}
		Frustum(const Frustum& rhs) noexcept: DXFrustum(rhs.DXFrustum) {}
		Frustum(Frustum&& rhs) noexcept: DXFrustum(rhs.DXFrustum) {}

		// Assignment Operators

		Frustum operator= (const Frustum& rhs) noexcept {
			DXFrustum = rhs.DXFrustum;
			return *this;
		}

		// Functions

		const std::array<Vec3f, 8u> GetCorners() const noexcept {
			std::array<Vec3f, 8u> out;
			DXFrustum.GetCorners(out.data());
			return out;
		}
		void Transform(const Mat4f& mat) noexcept {
			Concealed::XMMAT m = Concealed::XMLoad<Concealed::XMMAT>(&mat.XMMat);
			DXFrustum.Transform(DXFrustum, m);
		}
		void CreateFromMatrix(const Mat4f& projection) noexcept {
			Concealed::XMMAT m = Concealed::XMLoad<Concealed::XMMAT>(&projection);
			DirectX::BoundingFrustum::CreateFromMatrix(DXFrustum, m);
		}

		// Static Variables

		static const size_t cornerCount;

		union {
			DirectX::BoundingFrustum DXFrustum;
			struct {
				Vec3f origin; Quat rot;
				float right, left, top, bottom, near, far;
			};
		};

	};


	// ----------------------------------------------------------------- //
	//								Sphere								 //
	// ----------------------------------------------------------------- //
	struct Sphere {

		Sphere() noexcept: DXSphere() {}
		Sphere(const Vec3f& origin, const float& radius) noexcept: DXSphere() {}
		Sphere(const Sphere& rhs) noexcept: DXSphere(rhs.DXSphere) {}
		Sphere(Sphere&& rhs) noexcept: DXSphere(rhs.DXSphere) {}

		// Assignment Operators

		Sphere operator= (const Sphere& rhs) noexcept {
			DXSphere = rhs.DXSphere;
			return *this;
		}

		// Functions

		void Transform(const Mat4f& mat) noexcept {
			Concealed::XMMAT m = Concealed::XMLoad<Concealed::XMMAT>(&mat.XMMat);
			DXSphere.Transform(DXSphere, m);
		}
		void Transform(Sphere& sphere, const Mat4f& mat) noexcept {
			Concealed::XMMAT m = Concealed::XMLoad<Concealed::XMMAT>(&mat.XMMat);
			DXSphere.Transform(sphere.DXSphere, m);
		}
		void CreateFromPoints(Vec3f points[], const size_t& count, const size_t& stride) noexcept {
			DirectX::BoundingSphere::CreateFromPoints(DXSphere, count, points, stride);
		}
		void CreateFromAABB(const OBB& box) noexcept;
		void CreateMerged(const Sphere& s1, const Sphere& s2) noexcept {
			DirectX::BoundingSphere::CreateMerged(DXSphere, s1.DXSphere, s1.DXSphere);
		}
		void CreateMerged(const Frustum& fr) noexcept {
			DirectX::BoundingSphere::CreateFromFrustum(DXSphere, fr.DXFrustum);
		}

		union {
			DirectX::BoundingSphere DXSphere;
			struct { Vec3f origin; float radius; };
		};

	};


	// ----------------------------------------------------------------- //
	//								 AABB								 //
	// ----------------------------------------------------------------- //
	struct AABB {

		AABB() noexcept: DXBox() {}
		AABB(const Vec3f& origin, const Vec3f& bounds) noexcept: DXBox(origin, bounds) {}
		AABB(const AABB& rhs) noexcept: DXBox(rhs.DXBox) {}
		AABB(AABB&& rhs) noexcept: DXBox(rhs.DXBox) {}

		// Assignment Operators

		AABB operator= (const AABB& rhs) noexcept {
			DXBox = rhs.DXBox;
			return *this;
		}

		// Functions

		const std::array<Vec3f, 8u> GetCorners() const noexcept {
			std::array<Vec3f, 8u> out;
			DXBox.GetCorners(out.data());
			return out;
		}
		void Transform(const Mat4f& mat) noexcept {
			Concealed::XMMAT m = Concealed::XMLoad<Concealed::XMMAT>(&mat.XMMat);
			DXBox.Transform(DXBox, m);
		}
		void Transform(AABB& box, const Mat4f& mat) noexcept {
			Concealed::XMMAT m = Concealed::XMLoad<Concealed::XMMAT>(&mat.XMMat);
			DXBox.Transform(box.DXBox, m);
		}
		void CreateFromPoints(const Vec3f& p1, const Vec3f& p2) noexcept {
			Concealed::XMVEC v1 = Concealed::XMLoad<Concealed::XMVEC>(&p1);
			Concealed::XMVEC v2 = Concealed::XMLoad<Concealed::XMVEC>(&p2);
			DirectX::BoundingBox::CreateFromPoints(DXBox, v1, v2);
		}
		void CreateFromSphere(const Sphere& sphere) noexcept {
			DirectX::BoundingBox::CreateFromSphere(DXBox, sphere.DXSphere);
		}
		void CreateMerged(const AABB& b1, const AABB& b2) noexcept {
			DirectX::BoundingBox::CreateMerged(DXBox, b1.DXBox, b2.DXBox);
		}

		// Static Variables

		static const size_t cornerCount;

		union {
			DirectX::BoundingBox DXBox;
			struct {Vec3f origin, bounds;};
		};

	};


	// ----------------------------------------------------------------- //
	//								 OBB								 //
	// ----------------------------------------------------------------- //
	struct OBB {

		OBB() noexcept: DXBox() {}
		OBB(const Vec3f& origin, const Vec3f& bounds, const Quat& rot) noexcept: DXBox(origin, bounds, rot) {}
		OBB(const OBB& rhs) noexcept: DXBox(rhs.DXBox) {}
		OBB(OBB&& rhs) noexcept: DXBox(rhs.DXBox) {}

		// Assignment Operators

		OBB operator= (const OBB& rhs) noexcept {
			DXBox = rhs.DXBox;
			return *this;
		}

		// Functions

		const std::array<Vec3f, 8u> GetCorners() const noexcept {
			std::array<Vec3f, 8u> out;
			DXBox.GetCorners(out.data());
			return out;
		}
		void Transform(const Mat4f& mat) noexcept {
			Concealed::XMMAT m = Concealed::XMLoad<Concealed::XMMAT>(&mat.XMMat);
			DXBox.Transform(DXBox, m);
		}
		void Transform(OBB& box, const Mat4f& mat) noexcept {
			Concealed::XMMAT m = Concealed::XMLoad<Concealed::XMMAT>(&mat.XMMat);
			DXBox.Transform(box.DXBox, m);
		}
		void CreateFromPoints(Vec3f points[], const size_t& count, const size_t& stride) noexcept {
			DirectX::BoundingOrientedBox::CreateFromPoints(DXBox, count, points, stride);
		}
		void CreateFromAABB(const AABB& box) noexcept {
			DirectX::BoundingOrientedBox::CreateFromBoundingBox(DXBox, box.DXBox);
		}

		// Static Variables

		static const size_t cornerCount;

		union {
			DirectX::BoundingOrientedBox DXBox;
			struct {Vec3f origin, bounds; Quat rot;};
		};

	};


	// Function Def --------------------------------------------------

	inline void Sphere::CreateFromAABB(const OBB& box) noexcept {
		DirectX::BoundingSphere::CreateFromBoundingBox(DXSphere, box.DXBox);
	}


	// ----------------------------------------------------------------- //
	//					  _____                        					 //
	//					 |_   _| __ __ _  ___ ___ _ __ 					 //
	//					   | || '__/ _` |/ __/ _ \ '__|					 //
	//					   | || | | (_| | (_|  __/ |   					 //
	//					   |_||_|  \__,_|\___\___|_|   					 //
	// ----------------------------------------------------------------- //


	class Tracer2 {
		public:

		constexpr Tracer2() noexcept: distance(std::numeric_limits<float>::max()), hitNormal(), origin(), direction() {}
		constexpr Tracer2(const Tracer2& rhs) noexcept: distance(rhs.distance), hitNormal(hitNormal), origin(rhs.origin), direction(rhs.direction) {}
		constexpr Tracer2(const Vec2f& origin, const Vec2f& direction) noexcept: distance(std::numeric_limits<float>::max()), hitNormal(), origin(origin), direction(direction) {}

		// Assignment Operators

		Tracer2& operator= (const Tracer2& rhs) noexcept {
			distance = rhs.distance;
			origin = rhs.origin;
			direction = rhs.direction;
			return *this;
		}

		// Functions

		void SetOrigin(const Vec2f& pos) noexcept {
			origin = pos;
		}
		void SetOrigin(const float& x, const float& y) noexcept {
			origin = Vec2f(x, y);
		}
		void SetDirection(const Vec2f& dir) noexcept {
			direction = dir;
		}
		void SetDirection(const float& x, const float& y) noexcept {
			direction = Vec2f(x, y);
		}

		const Vec2f& GetHitNormal() const noexcept {
			return hitNormal;
		}
		const Vec2f& GetOrigin() const noexcept {
			return origin;
		}
		const Vec2f& GetDirection() const noexcept {
			return direction;
		}
		const float& GetDistance() const noexcept {
			return distance;
		}
		const Vec2f GetHitPos() const noexcept {
			return origin + direction * distance;
		}

		private:

		friend inline const bool Intersect(const Rectf& a, Tracer2& b) noexcept;
		friend inline const bool Intersect(Tracer2& a, const Rectf& b) noexcept;
		friend inline const bool Intersect(const Recti& a, Tracer2& b) noexcept;
		friend inline const bool Intersect(Tracer2& a, const Recti& b) noexcept;
		friend inline const bool Intersect(const Circle& a, Tracer2& b) noexcept;
		friend inline const bool Intersect(Tracer2& a, const Circle& b) noexcept;
		friend inline const bool Intersect(const ORect& a, Tracer2& b) noexcept;
		friend inline const bool Intersect(Tracer2& a, const ORect& b) noexcept;

		float distance;
		Vec2f hitNormal;
		Vec2f origin;
		Vec2f direction;
	};
	class Tracer {
		public:

		constexpr Tracer() noexcept: distance(std::numeric_limits<float>::max()), hitNormal(), origin(), direction() {}
		constexpr Tracer(const Tracer& rhs) noexcept: distance(rhs.distance), hitNormal(hitNormal), origin(rhs.origin), direction(rhs.direction) {}
		constexpr Tracer(const Vec3f& origin, const Vec3f& direction) noexcept: distance(std::numeric_limits<float>::max()), hitNormal(), origin(origin), direction(direction) {}

		// Assignment Operators

		Tracer& operator= (const Tracer& rhs) noexcept {
			distance = rhs.distance;
			origin = rhs.origin;
			direction = rhs.direction;
			return *this;
		}

		// Functions

		void SetOrigin(const Vec3f& pos) noexcept {
			origin = pos;
		}
		void SetOrigin(const float& x, const float& y, const float& z) noexcept {
			origin = Vec3f(x, y, z);
		}
		void SetDirection(const Vec3f& dir) noexcept {
			direction = dir;
		}
		void SetDirection(const float& x, const float& y, const float& z) noexcept {
			direction = Vec3f(x, y, z);
		}

		const Vec3f& GetHitNormal() const noexcept {
			return hitNormal;
		}
		const Vec3f& GetOrigin() const noexcept {
			return origin;
		}
		const Vec3f& GetDirection() const noexcept {
			return direction;
		}
		const float& GetDistance() const noexcept {
			return distance;
		}
		const Vec3f GetHitPos() const noexcept {
			return origin + direction * distance;
		}

		private:

		friend inline const bool Intersect(const Frustum& a, Tracer& b) noexcept;
		friend inline const bool Intersect(Tracer& a, const Frustum& b) noexcept;
		friend inline const bool Intersect(const Sphere& a, Tracer& b) noexcept;
		friend inline const bool Intersect(Tracer& a, const Sphere& b) noexcept;
		friend inline const bool Intersect(const AABB& a, Tracer& b) noexcept;
		friend inline const bool Intersect(Tracer& a, const AABB& b) noexcept;
		friend inline const bool Intersect(const OBB& a, Tracer& b) noexcept;
		friend inline const bool Intersect(Tracer& a, const OBB& b) noexcept;

		float distance;
		Vec3f hitNormal;
		Vec3f origin;
		Vec3f direction;
	};
	
	
	// ----------------------------------------------------------------- //
	//			  _____                 _   _                 			 //
	//			 |  ___|   _ _ __   ___| |_(_) ___  _ __  ___ 			 //
	//			 | |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __|			 //
	//			 |  _|| |_| | | | | (__| |_| | (_) | | | \__ \			 //
	//			 |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/			 //
	// ----------------------------------------------------------------- //


	// ----------------------------------------------------------------- //
	//                        General Finctions                          //
	// ----------------------------------------------------------------- //

	template<class T> inline const T Sqrd(const T& n) noexcept {
		return n * n;
	}
	template<class T> inline const T Sqrt(const T& n) noexcept {
		return static_cast<T>(std::sqrtf(static_cast<float>(n)));
	}
	template<> inline const double Sqrt(const double& n) noexcept {
		return std::sqrt(n);
	}
	template<> inline const float Sqrt(const float& n) noexcept {
		return std::sqrtf(n);
	}
	template<class T> inline const int Sign(const T& val) noexcept {
		return (static_cast<T>(0 < val) - static_cast<T>(val < 0));
	}
	template<class T> inline const T Lerp(const T& a, const T& b, const float& t) noexcept {
		return std::_Common_lerp(a, b, t);
	}
	template<class T> inline const T RadToDeg(const T& value) noexcept {
		return DirectX::XMConvertToDegrees(value);
	}
	template<class T> inline const T DegToRad(const T& value) noexcept {
		return DirectX::XMConvertToRadians(value);
	}
	template<class T> inline void Clamp(T& value, const T& min, const T& max) noexcept {
		value = std::clamp(value, min, max);
	}
	template<class T> inline const T Min(const T& a, const T& b) noexcept {
		return DirectX::XMMin(a, b);
	}
	template<class T> inline const T Max(const T& a, const T& b) noexcept {
		return DirectX::XMMax(a, b);
	}
	template<class T> inline const T Abs(const T& num) noexcept {
		return std::abs(num);
	}
	template<class T> inline void Swap(T& a, T& b) noexcept {
		T temp = std::move(a);
		a = std::move(b);
		b = std::move(temp);
	}


	// ----------------------------------------------------------------- //
	//                         Vector Finctions                          //
	// ----------------------------------------------------------------- //


	template<class T, uint32_t N> inline const T Dot(const Concealed::VecT<T, N>& u, const Concealed::VecT<T, N>& v) noexcept {
		return u * v;
	}
	template<class T> inline const Concealed::VecT<T, 3u> Cross(const Concealed::VecT<T, 3u>& u, const Concealed::VecT<T, 3u>& v) noexcept {
		return u % v;
	}
	template<class T, uint32_t N> inline const Concealed::VecT<T, N> Lerp(const Concealed::VecT<T, N>& a, const Concealed::VecT<T, N>& b, const float& t) noexcept {
		Concealed::VecT<T, N> out;
		Concealed::XMVEC v1 = Concealed::XMLoad<Concealed::XMVEC>(&a);
		Concealed::XMVEC v2 = Concealed::XMLoad<Concealed::XMVEC>(&b);
		Concealed::XMVEC temp = DirectX::XMVectorLerp(v1, v2, t);
		Concealed::XMStore(&out, temp);
		return out;
	}
	template<class T, uint32_t N> inline void Clamp(Concealed::VecT<T, N>& value, const Concealed::VecT<T, N>& min, const Concealed::VecT<T, N>& max) noexcept {
		Concealed::XMVEC temp = Concealed::XMLoad<Concealed::XMVEC>(&value);
		Concealed::XMVEC v1 = Concealed::XMLoad<Concealed::XMVEC>(&min);
		Concealed::XMVEC v2 = Concealed::XMLoad<Concealed::XMVEC>(&max);
		temp = DirectX::XMVectorClamp(temp, v1, v2);
		Concealed::XMStore(&value, temp);
	}
	template<class T, uint32_t N> inline const Concealed::VecT<float, N> RadToDeg(const Concealed::VecT<T, N>& value) noexcept {
		Concealed::VecT<T, N> out;
		Concealed::XMVEC temp = Concealed::XMLoad<Concealed::XMVEC>(&value);
		temp = DirectX::XMVectorMultiply(temp, DirectX::XMVectorSet(static_cast<float>(C_180dPI), static_cast<float>(C_180dPI), static_cast<float>(C_180dPI), static_cast<float>(C_180dPI)));
		Concealed::XMStore(&out, temp);
		return out;
	}
	template<class T, uint32_t N> inline const Concealed::VecT<T, N> DegToRad(const Concealed::VecT<T, N>& value) noexcept {
		Concealed::VecT<T, N> out;
		Concealed::XMVEC temp = Concealed::XMLoad<Concealed::XMVEC>(&value);
		temp = DirectX::XMVectorMultiply(temp, DirectX::XMVectorSet(static_cast<float>(C_1d180xPI), static_cast<float>(C_1d180xPI), static_cast<float>(C_1d180xPI), static_cast<float>(C_1d180xPI)));
		Concealed::XMStore(&out, temp);
		return out;
	}
	inline const float ACos(const float& n) noexcept {
		return DirectX::XMScalarACos(n);
	}
	inline const float ASin(const float& n) noexcept {
		return DirectX::XMScalarASin(n);
	}
	inline const float Cos(const float& n) noexcept {
		return DirectX::XMScalarCos(n);
	}
	inline const float Sin(const float& n) noexcept {
		return DirectX::XMScalarSin(n);
	}


	// ----------------------------------------------------------------- //
	//                         Matrix Finctions                          //
	// ----------------------------------------------------------------- //


	namespace Concealed {
		template<uint32_t N> inline const XMVEC XMVecTransform(const XMMAT& mat, const XMVEC& vec) {}

		template<> inline const XMVEC XMVecTransform<2u>(const XMMAT& mat, const XMVEC& vec) {
			return DirectX::XMVector2Transform(vec, mat);
		}
		template<> inline const XMVEC XMVecTransform<3u>(const XMMAT& mat, const XMVEC& vec) {
			return DirectX::XMVector3Transform(vec, mat);
		}
		template<> inline const XMVEC XMVecTransform<4u>(const XMMAT& mat, const XMVEC& vec) {
			return DirectX::XMVector4Transform(vec, mat);
		}
	}

	template<class T0, uint32_t N, class T1, uint32_t R, uint32_t C> inline const Concealed::VecT<T0, N> MatTransform(const Concealed::MatT<T1, R, C>& mat, const Concealed::VecT<T0, N>& vec) noexcept {
		Concealed::VecT<T0, N> out;
		Concealed::XMMAT m = Concealed::XMLoad<Concealed::XMMAT>(&mat.XMMat);
		Concealed::XMVEC v = Concealed::XMLoad<Concealed::XMVEC>(&vec);
		Concealed::XMVEC temp = Concealed::XMVecTransform<N>(m, v);
		Concealed::XMStore(&out, temp);
		return out;
	}
	template<class T> inline const Mat4f MatTranslate(const Concealed::VecT<T, 3u>& vec) noexcept {
		Mat4f out;
		Concealed::XMVEC v = Concealed::XMLoad<Concealed::XMVEC>(&vec);
		Concealed::XMMAT temp = DirectX::XMMatrixTranslationFromVector(v);
		Concealed::XMStore(&out.XMMat, temp);
		return out;
	}
	template<class T> inline const Mat4f MatTranslate(const T& x, const T& y, const T& z) noexcept {
		Mat4f out;
		Concealed::XMMAT temp = DirectX::XMMatrixTranslation(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
		Concealed::XMStore(&out.XMMat, temp);
		return out;
	}
	template<class T> inline const Mat4f MatRotate(const Concealed::VecT<T, 3u>& vec) noexcept {
		Mat4f out;
		Concealed::VecT<T, 3u> rad = DegToRad(vec);
		Concealed::XMVEC v = Concealed::XMLoad<Concealed::XMVEC>(&rad);
		Concealed::XMMAT temp = DirectX::XMMatrixRotationRollPitchYawFromVector(v);
		Concealed::XMStore(&out.XMMat, temp);
		return out;
	}
	template<class T> inline const Mat4f MatRotate(const T& pitch, const T& yaw, const T& roll) noexcept {
		Mat4f out;
		Concealed::VecT<T, 3u> rad = DegToRad(Concealed::VecT<T, 3u>(pitch, yaw, roll));
		Concealed::XMVEC v = Concealed::XMLoad<Concealed::XMVEC>(&rad);
		Concealed::XMMAT temp = DirectX::XMMatrixRotationRollPitchYawFromVector(v);
		Concealed::XMStore(&out.XMMat, temp);
		return out;
	}
	template<class T> inline const Mat4f MatRotateRad(const Concealed::VecT<T, 3u>& vec) noexcept {
		Mat4f out;
		Concealed::XMVEC v = Concealed::XMLoad<Concealed::XMVEC>(&vec);
		Concealed::XMMAT temp = DirectX::XMMatrixRotationRollPitchYawFromVector(v);
		Concealed::XMStore(&out.XMMat, temp);
		return out;
	}
	template<class T> inline const Mat4f MatRotateRad(const T& pitch, const T& yaw, const T& roll) noexcept {
		Mat4f out;
		Concealed::XMMAT temp = DirectX::XMMatrixRotationRollPitchYaw(static_cast<float>(pitch), static_cast<float>(yaw), static_cast<float>(roll));
		Concealed::XMStore(&out.XMMat, temp);
		return out;
	}
	template<class T> inline const Mat4f MatScale(const Concealed::VecT<T, 3u>& vec) noexcept {
		Mat4f out;
		Concealed::XMVEC v = Concealed::XMLoad<Concealed::XMVEC>(&vec);
		Concealed::XMMAT temp = DirectX::XMMatrixScalingFromVector(v);
		Concealed::XMStore(&out.XMMat, temp);
		return out;
	}
	template<class T> inline const Mat4f MatScale(const T& x, const T& y, const T& z) noexcept {
		Mat4f out;
		Concealed::XMMAT temp = DirectX::XMMatrixScaling(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
		Concealed::XMStore(&out.XMMat, temp);
		return out;
	}
	inline const Mat4f MatPerspectiveLH(const float& fov, const float& aspectRatio, const float& near, const float& far) noexcept {
		Mat4f out;
		Concealed::XMMAT temp = DirectX::XMMatrixPerspectiveFovLH(DegToRad(fov), aspectRatio, near, far);
		Concealed::XMStore(&out, temp);
		return out;
	}
	inline const Mat4f MatPerspectiveRH(const float& fov, const float& aspectRatio, const float& near, const float& far) noexcept {
		Mat4f out;
		Concealed::XMMAT temp = DirectX::XMMatrixPerspectiveFovRH(DegToRad(fov), aspectRatio, near, far);
		Concealed::XMStore(&out, temp);
		return out;
	}
	inline const Mat4f MatOrthographicLH(const float& width, const float& height, const float& near, const float& far) noexcept {
		Mat4f out;
		Concealed::XMMAT temp = DirectX::XMMatrixOrthographicLH(width, height, near, far);
		Concealed::XMStore(&out, temp);
		return out;
	}
	inline const Mat4f MatOrthographicRH(const float& width, const float& height, const float& near, const float& far) noexcept {
		Mat4f out;
		Concealed::XMMAT temp = DirectX::XMMatrixOrthographicRH(width, height, near, far);
		Concealed::XMStore(&out, temp);
		return out;
	}
	inline const Mat4f MatLookTowordsLH(const Vec3f& pos, const Vec3f& forward, const Vec3f& up) noexcept {
		Mat4f out;
		Concealed::XMVEC p = Concealed::XMLoad<Concealed::XMVEC>(&pos);
		Concealed::XMVEC d = Concealed::XMLoad<Concealed::XMVEC>(&forward);
		Concealed::XMVEC u = Concealed::XMLoad<Concealed::XMVEC>(&up);
		Concealed::XMMAT temp = DirectX::XMMatrixLookToLH(p, d, u);
		Concealed::XMStore(&out, temp);
		return out;
	}
	inline const Mat4f MatLookTowordsRH(const Vec3f& pos, const Vec3f& forward, const Vec3f& up) noexcept {
		Mat4f out;
		Concealed::XMVEC p = Concealed::XMLoad<Concealed::XMVEC>(&pos);
		Concealed::XMVEC d = Concealed::XMLoad<Concealed::XMVEC>(&forward);
		Concealed::XMVEC u = Concealed::XMLoad<Concealed::XMVEC>(&up);
		Concealed::XMMAT temp = DirectX::XMMatrixLookToRH(p, d, u);
		Concealed::XMStore(&out, temp);
		return out;
	}
	inline const Mat4f MatLookAtLH(const Vec3f& pos, const Vec3f& focalPos, const Vec3f& up) noexcept {
		Mat4f out;
		Concealed::XMVEC p = Concealed::XMLoad<Concealed::XMVEC>(&pos);
		Concealed::XMVEC f = Concealed::XMLoad<Concealed::XMVEC>(&focalPos);
		Concealed::XMVEC u = Concealed::XMLoad<Concealed::XMVEC>(&up);
		Concealed::XMMAT temp = DirectX::XMMatrixLookAtLH(p, f, u);
		Concealed::XMStore(&out, temp);
		return out;
	}
	inline const Mat4f MatLookAtRH(const Vec3f& pos, const Vec3f& focalPos, const Vec3f& up) noexcept {
		Mat4f out;
		Concealed::XMVEC p = Concealed::XMLoad<Concealed::XMVEC>(&pos);
		Concealed::XMVEC f = Concealed::XMLoad<Concealed::XMVEC>(&focalPos);
		Concealed::XMVEC u = Concealed::XMLoad<Concealed::XMVEC>(&up);
		Concealed::XMMAT temp = DirectX::XMMatrixLookAtRH(p, f, u);
		Concealed::XMStore(&out, temp);
		return out;
	}
	inline const Mat4f MatAxisAngle(const Vec4f& vec) noexcept {
		Mat4f out;
		float ang = vec.w;
		Vec3f n = static_cast<Vec3f>(vec);
		Concealed::XMVEC v = Concealed::XMLoad<Concealed::XMVEC>(&n);
		Concealed::XMMAT temp = DirectX::XMMatrixRotationAxis(v, ang);
		Concealed::XMStore(&out, temp);
		return out;
	}
	inline const Mat4f MatAxisAngle(const Vec3f& vec, const float& ang) noexcept {
		Mat4f out;
		Concealed::XMVEC v = Concealed::XMLoad<Concealed::XMVEC>(&vec);
		Concealed::XMMAT temp = DirectX::XMMatrixRotationAxis(v, ang);
		Concealed::XMStore(&out, temp);
		return out;
	}
	inline const Vec3f MatRotationToEuler(const Mat4f& mat) noexcept {
		float cy = sqrtf(mat.m22 * mat.m22 + mat.m20 * mat.m20);
		float cx = atan2f(-mat.m21, cy);
		if(cy > 16.f * FLT_EPSILON)
			return RadToDeg(Vec3f(cx, atan2f(mat.m20, mat.m22), atan2f(mat.m01, mat.m11)));
		else
			return RadToDeg(Vec3f(cx, 0.f, atan2f(-mat.m10, mat.m00)));
	}


	// ----------------------------------------------------------------- //
	//                       Quaternion Finctions                        //
	// ----------------------------------------------------------------- //


	inline const Mat4f MatQuaternion(const Quat& q) noexcept {
		Mat4f out;
		Concealed::XMVEC v = Concealed::XMLoad<Concealed::XMVEC>(&q);
		Concealed::XMMAT temp = DirectX::XMMatrixRotationQuaternion(v);
		Concealed::XMStore(&out, temp);
		return out;
	}
	inline const Mat4f MatQuaternion(const Vec4f& q) noexcept {
		Mat4f out;
		Concealed::XMVEC v = Concealed::XMLoad<Concealed::XMVEC>(&q);
		Concealed::XMMAT temp = DirectX::XMMatrixRotationQuaternion(v);
		Concealed::XMStore(&out, temp);
		return out;
	}
	inline const Vec3f QuatToEuler(const Quat& q) noexcept {
		float xx = q.x * q.x;
		float yy = q.y * q.y;
		float zz = q.z * q.z;

		float m31 = 2.f * q.x * q.z + 2.f * q.y * q.w;
		float m32 = 2.f * q.y * q.z - 2.f * q.x * q.w;
		float m33 = 1.f - 2.f * xx - 2.f * yy;

		float cy = sqrtf(m33 * m33 + m31 * m31);
		float cx = atan2f(-m32, cy);
		if(cy > 16.f * FLT_EPSILON) {
			float m12 = 2.f * q.x * q.y + 2.f * q.z * q.w;
			float m22 = 1.f - 2.f * xx - 2.f * zz;

			return RadToDeg(Vec3f(cx, atan2f(m31, m33), atan2f(m12, m22)));
		} else {
			float m11 = 1.f - 2.f * yy - 2.f * zz;
			float m21 = 2.f * q.x * q.y - 2.f * q.z * q.w;

			return RadToDeg(Vec3f(cx, 0.f, atan2f(-m21, m11)));
		}
	}
	inline const Vec3f QuatToEuler(const Vec4f& q) noexcept {
		float xx = q.x * q.x;
		float yy = q.y * q.y;
		float zz = q.z * q.z;

		float m31 = 2.f * q.x * q.z + 2.f * q.y * q.w;
		float m32 = 2.f * q.y * q.z - 2.f * q.x * q.w;
		float m33 = 1.f - 2.f * xx - 2.f * yy;

		float cy = sqrtf(m33 * m33 + m31 * m31);
		float cx = atan2f(-m32, cy);
		if(cy > 16.f * FLT_EPSILON) {
			float m12 = 2.f * q.x * q.y + 2.f * q.z * q.w;
			float m22 = 1.f - 2.f * xx - 2.f * zz;

			return RadToDeg(Vec3f(cx, atan2f(m31, m33), atan2f(m12, m22)));
		} else {
			float m11 = 1.f - 2.f * yy - 2.f * zz;
			float m21 = 2.f * q.x * q.y - 2.f * q.z * q.w;

			return RadToDeg(Vec3f(cx, 0.f, atan2f(-m21, m11)));
		}
	}
	inline const Quat MatRotationToQuat(const Mat4f& mat) noexcept {
		Quat out;
		Concealed::XMMAT m = Concealed::XMLoad<Concealed::XMMAT>(&mat);
		Concealed::XMVEC temp = DirectX::XMQuaternionRotationMatrix(m);
		Concealed::XMStore(&out, temp);
		return out;
	}
	inline const Quat EulerToQuat(const Vec3f& vec) noexcept {
		Quat out;
		Concealed::XMVEC temp = Concealed::XMLoad<Concealed::XMVEC>(&vec);
		temp = DirectX::XMQuaternionRotationRollPitchYawFromVector(temp);
		Concealed::XMStore(&out, temp);
		return out;
	}
	inline const Quat EulerToQuat(const float& x, const float& y, const float& z) noexcept {
		Quat out;
		 Concealed::XMVEC temp = DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);
		Concealed::XMStore(&out, temp);
		return out;
	}
	inline const Vec4f QuatToAxisAngle(const Quat& q) noexcept {
		Vec4f out;
		float ang;
		Concealed::XMVEC temp;
		Concealed::XMVEC v = Concealed::XMLoad<Concealed::XMVEC>(&q);
		DirectX::XMQuaternionToAxisAngle(&temp, &ang, v);
		Concealed::XMStore(&out, temp);
		out.w = ang;
		return out;
	}
	inline const Quat AxisAngleToQuat(const Vec4f& vec) noexcept {
		Quat out;
		float ang = vec.w;
		Vec3f n = static_cast<Vec3f>(vec);
		Concealed::XMVEC temp = Concealed::XMLoad<Concealed::XMVEC>(&n);
		temp = DirectX::XMQuaternionRotationAxis(temp, ang);
		Concealed::XMStore(&out, temp);
		return out;
	}
	inline const Quat AxisAngleToQuat(const Vec3f& vec, const float& ang) noexcept {
		Quat out;
		Concealed::XMVEC temp = Concealed::XMLoad<Concealed::XMVEC>(&vec);
		temp = DirectX::XMQuaternionRotationAxis(temp, ang);
		Concealed::XMStore(&out, temp);
		return out;
	}
	inline const Quat Slerp(const Quat& a, const Quat& b, const float& t) noexcept {
		Quat out;
		Concealed::XMVEC q0= Concealed::XMLoad<Concealed::XMVEC>(&a);
		Concealed::XMVEC q1 = Concealed::XMLoad<Concealed::XMVEC>(&b);
		Concealed::XMVEC temp = DirectX::XMQuaternionSlerp(q0, q1, t);
		Concealed::XMStore(&out, temp);
		return out;
	}
	inline const Vec4f Slerp(const Vec4f& a, const Vec4f& b, const float& t) noexcept {
		Vec4f out;
		Concealed::XMVEC q0 = Concealed::XMLoad<Concealed::XMVEC>(&a);
		Concealed::XMVEC q1 = Concealed::XMLoad<Concealed::XMVEC>(&b);
		Concealed::XMVEC temp = DirectX::XMQuaternionSlerp(q0, q1, t);
		Concealed::XMStore(&out, temp);
		return out;
	}


	// ----------------------------------------------------------------- //
	//                      Intersection Finctions                       //
	// ----------------------------------------------------------------- //


	// 2D Intersection

	inline const bool Intersect(const Circle& a, const Vec2f& point) noexcept {
		Vec2f dist = point - a.origin;
		return a.radius > dist.Magnitude();
	}
	inline const bool Intersect(const Circle& a, const Circle& b) noexcept {
		Vec2f dist = b.origin - a.origin;
		return (a.radius + b.radius) > dist.Magnitude();
	}
	inline const bool Intersect(const Circle& a, const Rectf& b) noexcept {
		Vec2f point = a.origin;
		Clamp(point, b.GetBL(), b.GetTR());
		Vec2f dist = point - a.origin;
		return a.radius > dist.Magnitude();
	}
	inline const bool Intersect(const Circle& a, const Recti& b) noexcept {
		Vec2i point = a.origin;
		Clamp(point, b.GetBL(), b.GetTR());
		Vec2i dist = point - a.origin;
		return a.radius > dist.Magnitude();
	}
	inline const bool Intersect(const Circle& a, const ORect& b) noexcept {
		Vec2f o = Concealed::RotateVec(a.origin - b.origin, -b.rot);
		Vec2f p = o;
		Vec2f BL = Vec2f(DirectX::XMMin(0.f, b.size.x), DirectX::XMMin(0.f, b.size.y)) - b.offset;
		Vec2f TR = Vec2f(DirectX::XMMax(0.f, b.size.x), DirectX::XMMax(0.f, b.size.y)) - b.offset;
		Clamp(p, BL, TR);
		Vec2f dist = p - o;
		return a.radius > dist.Magnitude();
	}
	inline const bool Intersect(const Circle& a, Tracer2& b) noexcept {
		float dist = std::numeric_limits<float>::max();
		float d = b.GetDirection() * (b.GetOrigin() - a.origin);
		float c = (b.GetOrigin() - a.origin) * (b.GetOrigin() - a.origin) - Sqrd(a.radius);
		float q = Sqrd(d) - c;

		bool hit = false;
		if(q > 0.f) {
			dist = -d - Sqrt(q);
			if(dist > 0.f)
				hit = true;
		}

		b.distance = dist;
		b.hitNormal = (b.GetHitPos() - a.origin).Normalized();
		return hit;
	}

	inline const bool Intersect(const Rectf& a, const Vec2f& point) noexcept {
		bool h = (a.GetR() > point.x) && (point.x > a.GetL());
		bool v = (a.GetT() > point.y) && (point.y > a.GetB());
		return h && v;
	}
	inline const bool Intersect(const Rectf& a, const Circle& b) noexcept {
		Vec2f point = b.origin;
		Clamp(point, a.GetBL(), a.GetTR());
		Vec2f dist = point - b.origin;
		return b.radius > dist.Magnitude();
	}
	inline const bool Intersect(const Rectf& a, const Rectf& b) noexcept {
		bool h = (a.GetR() > b.GetL()) && (b.GetR() > a.GetL());
		bool v = (a.GetT() > b.GetB()) && (b.GetT() > a.GetB());
		return h && v;
	}
	inline const bool Intersect(const Rectf& a, const Recti& b) noexcept {
		bool h = (a.GetR() > b.GetL()) && (b.GetR() > a.GetL());
		bool v = (a.GetT() > b.GetB()) && (b.GetT() > a.GetB());
		return h && v;
	}
	inline const bool Intersect(const Rectf& a, const ORect& b) noexcept {

		Vec2f dir[4]{b.RDir(), b.UDir(), Vec2f(1.f, 0.f), Vec2f(0.f, 1.f)};
		Vec2f pointsA[4]{a.GetBL(), a.GetBR(), a.GetTL(), a.GetTR()};
		Vec2f pointsB[4]{b.GetBL(), b.GetBR(), b.GetTL(), b.GetTR()};

		for(int i = 0; i < 4; i++) {
			float minA = std::numeric_limits<float>::max();
			float maxA = -std::numeric_limits<float>::max();
			float minB = std::numeric_limits<float>::max();
			float maxB = -std::numeric_limits<float>::max();
			float q = 0.f;

			for(int k = 0; k < 4; k++) {
				q = dir[i] * pointsB[k];
				minA = Min(minA, q);
				maxA = Max(maxA, q);

				q = dir[i] * pointsA[k];
				minB = Min(minB, q);
				maxB = Max(maxB, q);
			}

			if(!(maxB > minA && maxA > minB))
				return false;
		}

		return true;
	}
	inline const bool Intersect(const Rectf& a, Tracer2& b) noexcept {
		float tMin = -std::numeric_limits<float>::max();
		float tMax = std::numeric_limits<float>::max();
		b.distance = std::numeric_limits<float>::max();
		Vec2f size = a.size * 0.5f;
		Vec2f n;

		Vec2f p = a.GetCenter() - b.origin;
		for(uint32_t i = 0u; i < 2u; i++) {
			float f = b.direction[i];
			float e = p[i];
			if(Abs(f) >= 0.f) {
				float t1 = (e + size[i]) / f;
				float t2 = (e - size[i]) / f;
				if(t1 > t2) std::swap(t1, t2);
				n[i] = t1;
				tMin = Max(t1, tMin);
				tMax = Min(t2, tMax);
				if(tMin >= tMax || tMax < 0.f)
					return false;
			} else if(-e - a.size[i] > 0.f || -e + a.size[i] < 0.f) return false;
		}

		if(tMin > 0.f) {
			b.distance = tMin;
			if(n.x > n.y) b.hitNormal = (b.direction.x < 0.f) ? Vec2f(1.f, 0.f) : Vec2f(-1.f, 0.f);
			else if(n.x < n.y) b.hitNormal = (b.direction.y < 0.f) ? Vec2f(0.f, 1.f) : Vec2f(0.f, -1.f);
			else b.hitNormal = (b.GetHitPos() - a.GetCenter()).Normalized();

			return true;
		} else
			return false;
	}

	inline const bool Intersect(const Recti& a, const Vec2f& point) noexcept {
		bool h = (a.GetR() > point.x) && (point.x > a.GetL());
		bool v = (a.GetT() > point.y) && (point.y > a.GetB());
		return h && v;
	}
	inline const bool Intersect(const Recti& a, const Circle& b) noexcept {
		Vec2i point = b.origin;
		Clamp(point, a.GetBL(), a.GetTR());
		Vec2i dist = point - b.origin;
		return b.radius > dist.Magnitude();
	}
	inline const bool Intersect(const Recti& a, const Rectf& b) noexcept {
		bool h = (a.GetR() > b.GetL()) && (b.GetR() > a.GetL());
		bool v = (a.GetT() > b.GetB()) && (b.GetT() > a.GetB());
		return h && v;
	}
	inline const bool Intersect(const Recti& a, const Recti& b) noexcept {
		bool h = (a.GetR() > b.GetL()) && (b.GetR() > a.GetL());
		bool v = (a.GetT() > b.GetB()) && (b.GetT() > a.GetB());
		return h && v;
	}
	inline const bool Intersect(const Recti& a, const ORect& b) noexcept {

		Vec2f dir[4]{b.RDir(), b.UDir(), Vec2f(1.f, 0.f), Vec2f(0.f, 1.f)};
		Vec2f pointsA[4]{a.GetBL(), a.GetBR(), a.GetTL(), a.GetTR()};
		Vec2f pointsB[4]{b.GetBL(), b.GetBR(), b.GetTL(), b.GetTR()};

		for(int i = 0; i < 4; i++) {
			float minA = std::numeric_limits<float>::max();
			float maxA = -std::numeric_limits<float>::max();
			float minB = std::numeric_limits<float>::max();
			float maxB = -std::numeric_limits<float>::max();
			float q = 0.f;

			for(int k = 0; k < 4; k++) {
				q = dir[i] * pointsB[k];
				minA = Min(minA, q);
				maxA = Max(maxA, q);

				q = dir[i] * pointsA[k];
				minB = Min(minB, q);
				maxB = Max(maxB, q);
			}

			if(!(maxB > minA && maxA > minB))
				return false;
		}

		return true;
	}
	inline const bool Intersect(const Recti& a, Tracer2& b) noexcept {
		float tMin = -std::numeric_limits<float>::max();
		float tMax = std::numeric_limits<float>::max();
		b.distance = std::numeric_limits<float>::max();
		Vec2f size = static_cast<Vec2f>(a.size) * 0.5f;
		Vec2f n;

		Vec2f p = a.GetCenter() - b.origin;
		for(uint32_t i = 0u; i < 2u; i++) {
			float f = b.direction[i];
			float e = p[i];
			if(Abs(f) >= 0.f) {
				float t1 = (e + size[i]) / f;
				float t2 = (e - size[i]) / f;
				if(t1 > t2) std::swap(t1, t2);
				n[i] = t1;
				tMin = Max(t1, tMin);
				tMax = Min(t2, tMax);
				if(tMin >= tMax || tMax < 0.f)
					return false;
			} else if(-e - a.size[i] > 0.f || -e + a.size[i] < 0.f) return false;
		}

		if(tMin > 0.f) {
			b.distance = tMin;
			if(n.x > n.y) b.hitNormal = (b.direction.x < 0.f) ? Vec2f(1.f, 0.f) : Vec2f(-1.f, 0.f);
			else if(n.x < n.y) b.hitNormal = (b.direction.y < 0.f) ? Vec2f(0.f, 1.f) : Vec2f(0.f, -1.f);
			else b.hitNormal = (b.GetHitPos() - a.GetCenter()).Normalized();

			return true;
		} else
			return false;
	}

	inline const bool Intersect(const ORect& a, const Vec2f& point) noexcept {
		Vec2f o = Concealed::RotateVec(point - a.origin, -a.rot);
		Vec2f p = o;
		Vec2f BL = Vec2f(DirectX::XMMin(0.f, a.size.x), DirectX::XMMin(0.f, a.size.y)) - a.offset;
		Vec2f TR = Vec2f(DirectX::XMMax(0.f, a.size.x), DirectX::XMMax(0.f, a.size.y)) - a.offset;
		Clamp(p, BL, TR);
		Vec2f dist = p - o;
		return dist.Magnitude() == 0.f;
	}
	inline const bool Intersect(const ORect& a, const Circle& b) noexcept {
		Vec2f o = Concealed::RotateVec(b.origin - a.origin, -a.rot);
		Vec2f p = o;
		Vec2f BL = Vec2f(DirectX::XMMin(0.f, a.size.x), DirectX::XMMin(0.f, a.size.y)) - a.offset;
		Vec2f TR = Vec2f(DirectX::XMMax(0.f, a.size.x), DirectX::XMMax(0.f, a.size.y)) - a.offset;
		Clamp(p, BL, TR);
		Vec2f dist = p - o;
		return b.radius > dist.Magnitude();
	}
	inline const bool Intersect(const ORect& a, const Rectf& b) noexcept {

		Vec2f dir[4]{a.RDir(), a.UDir(), Vec2f(1.f, 0.f), Vec2f(0.f, 1.f)};
		Vec2f pointsA[4]{a.GetBL(), a.GetBR(), a.GetTL(), a.GetTR()};
		Vec2f pointsB[4]{b.GetBL(), b.GetBR(), b.GetTL(), b.GetTR()};

		for(int i = 0; i < 4; i++) {
			float minA = std::numeric_limits<float>::max();
			float maxA = -std::numeric_limits<float>::max();
			float minB = std::numeric_limits<float>::max();
			float maxB = -std::numeric_limits<float>::max();
			float q = 0.f;

			for(int k = 0; k < 4; k++) {
				q = dir[i] * pointsB[k];
				minA = Min(minA, q);
				maxA = Max(maxA, q);

				q = dir[i] * pointsA[k];
				minB = Min(minB, q);
				maxB = Max(maxB, q);
			}

			if(!(maxB > minA && maxA > minB))
				return false;
		}

		return true;
	}
	inline const bool Intersect(const ORect& a, const Recti& b) noexcept {

		Vec2f dir[4]{a.RDir(), a.UDir(), Vec2f(1.f, 0.f), Vec2f(0.f, 1.f)};
		Vec2f pointsA[4]{a.GetBL(), a.GetBR(), a.GetTL(), a.GetTR()};
		Vec2f pointsB[4]{b.GetBL(), b.GetBR(), b.GetTL(), b.GetTR()};

		for(int i = 0; i < 4; i++) {
			float minA = std::numeric_limits<float>::max();
			float maxA = -std::numeric_limits<float>::max();
			float minB = std::numeric_limits<float>::max();
			float maxB = -std::numeric_limits<float>::max();
			float q = 0.f;

			for(int k = 0; k < 4; k++) {
				q = dir[i] * pointsB[k];
				minA = Min(minA, q);
				maxA = Max(maxA, q);

				q = dir[i] * pointsA[k];
				minB = Min(minB, q);
				maxB = Max(maxB, q);
			}

			if(!(maxB > minA && maxA > minB))
				return false;
		}

		return true;
	}
	inline const bool Intersect(const ORect& a, const ORect& b) noexcept {

		Vec2f dir[4]{a.RDir(), a.UDir(), b.RDir(), b.UDir()};
		Vec2f pointsA[4]{a.GetBL(), a.GetBR(), a.GetTL(), a.GetTR()};
		Vec2f pointsB[4]{b.GetBL(), b.GetBR(), b.GetTL(), b.GetTR()};

		for(int i = 0; i < 4; i++) {
			float minA = std::numeric_limits<float>::max();
			float maxA = -std::numeric_limits<float>::max();
			float minB = std::numeric_limits<float>::max();
			float maxB = -std::numeric_limits<float>::max();
			float q = 0.f;

			for(int k = 0; k < 4; k++) {
				q = dir[i] * pointsB[k];
				minA = Min(minA, q);
				maxA = Max(maxA, q);

				q = dir[i] * pointsA[k];
				minB = Min(minB, q);
				maxB = Max(maxB, q);
			}

			if(!(maxB > minA && maxA > minB))
				return false;
		}

		return true;
	}
	inline const bool Intersect(const ORect& a, Tracer2& b) noexcept {
		float tMin = -std::numeric_limits<float>::max();
		float tMax = std::numeric_limits<float>::max();
		b.distance = std::numeric_limits<float>::max();
		Vec2f dir[2]{a.RDir(), a.UDir()};
		Vec2f size = a.size * 0.5f;
		Vec2f n;

		Vec2f p = a.GetCenter() - b.GetOrigin();
		for(uint32_t i = 0u; i < 2u; i++) {
			float f = dir[i] * b.GetDirection();
			float e = dir[i] * p;
			if(Abs(f) >= 0.f) {
				float t1 = (e + size[i]) / f;
				float t2 = (e - size[i]) / f;
				if(t1 > t2) std::swap(t1, t2);
				n[i] = t1;
				tMin = Max(t1, tMin);
				tMax = Min(t2, tMax);
				if(tMin >= tMax || tMax < 0.f)
					return false;
			} else if(-e - a.size[i] > 0.f || -e + a.size[i] < 0.f) return false;
		}

		if(tMin > 0.f) {
			b.distance = tMin;
			Vec2f tDir = Concealed::RotateVec(b.direction, -a.rot);
			if(n.x > n.y) b.hitNormal = (tDir.x < 0.f) ? a.RDir() : a.LDir();
			else if(n.x < n.y) b.hitNormal = (tDir.y < 0.f) ? a.UDir() : a.DDir();
			else b.hitNormal = (b.GetHitPos() - a.GetCenter()).Normalized();

			return true;
		} else
			return false;
	}

	inline const bool Intersect(const Vec2f& point, const Circle& b) noexcept {
		Vec2f dist = point - b.origin;
		return b.radius > dist.Magnitude();
	}
	inline const bool Intersect(const Vec2f& point, const Rectf& b) noexcept {
		bool h = (b.GetR() > point.x) && (point.x > b.GetL());
		bool v = (b.GetT() > point.y) && (point.y > b.GetB());
		return h && v;
	}
	inline const bool Intersect(const Vec2f& point, const Recti& b) noexcept {
		bool h = (b.GetR() > point.x) && (point.x > b.GetL());
		bool v = (b.GetT() > point.y) && (point.y > b.GetB());
		return h && v;
	}
	inline const bool Intersect(const Vec2f& point, const ORect& b) noexcept {
		Vec2f o = Concealed::RotateVec(point - b.origin, -b.rot);
		Vec2f p = o;
		Vec2f BL = Vec2f(DirectX::XMMin(0.f, b.size.x), DirectX::XMMin(0.f, b.size.y)) - b.offset;
		Vec2f TR = Vec2f(DirectX::XMMax(0.f, b.size.x), DirectX::XMMax(0.f, b.size.y)) - b.offset;
		Clamp(p, BL, TR);
		Vec2f dist = point - o;
		return dist.Magnitude() == 0.f;
	}

	inline const bool Intersect(Tracer2& a, const Circle& b) noexcept {
		float dist = std::numeric_limits<float>::max();
		float d = a.GetDirection() * (a.GetOrigin() - b.origin);
		float c = (a.GetOrigin() - b.origin) * (a.GetOrigin() - b.origin) - Sqrd(b.radius);
		float q = Sqrd(d) - c;

		bool hit = false;
		if(q > 0.f) {
			dist = -d - Sqrt(q);
			if(dist > 0.f)
				hit = true;
		}

		a.distance = dist;
		a.hitNormal = (a.GetHitPos() - b.origin).Normalized();
		return hit;
	}
	inline const bool Intersect(Tracer2& a, const Rectf& b) noexcept {
		float tMin = -std::numeric_limits<float>::max();
		float tMax = std::numeric_limits<float>::max();
		a.distance = std::numeric_limits<float>::max();
		Vec2f size = b.size * 0.5f;
		Vec2f n;

		Vec2f p = b.GetCenter() - a.origin;
		for(uint32_t i = 0u; i < 2u; i++) {
			float f = a.direction[i];
			float e = p[i];
			if(Abs(f) >= 0.f) {
				float t1 = (e + size[i]) / f;
				float t2 = (e - size[i]) / f;
				if(t1 > t2) std::swap(t1, t2);
				n[i] = t1;
				tMin = Max(t1, tMin);
				tMax = Min(t2, tMax);
				if(tMin >= tMax || tMax < 0.f)
					return false;
			} else if(-e - b.size[i] > 0.f || -e + b.size[i] < 0.f) return false;
		}

		if(tMin > 0.f) {
			a.distance = tMin;
			if(n.x > n.y) a.hitNormal = (a.direction.x < 0.f) ? Vec2f(1.f, 0.f) : Vec2f(-1.f, 0.f);
			else if(n.x < n.y) a.hitNormal = (a.direction.y < 0.f) ? Vec2f(0.f, 1.f) : Vec2f(0.f, -1.f);
			else a.hitNormal = (a.GetHitPos() - b.GetCenter()).Normalized();

			return true;
		} else
			return false;
	}
	inline const bool Intersect(Tracer2& a, const Recti& b) noexcept {
		float tMin = -std::numeric_limits<float>::max();
		float tMax = std::numeric_limits<float>::max();
		a.distance = std::numeric_limits<float>::max();
		Vec2f size = static_cast<Vec2f>(b.size) * 0.5f;
		Vec2f n;

		Vec2f p = b.GetCenter() - a.origin;
		for(uint32_t i = 0u; i < 2u; i++) {
			float f = a.direction[i];
			float e = p[i];
			if(Abs(f) >= 0.f) {
				float t1 = (e + size[i]) / f;
				float t2 = (e - size[i]) / f;
				if(t1 > t2) std::swap(t1, t2);
				n[i] = t1;
				tMin = Max(t1, tMin);
				tMax = Min(t2, tMax);
				if(tMin >= tMax || tMax < 0.f)
					return false;
			} else if(-e - b.size[i] > 0.f || -e + b.size[i] < 0.f) return false;
		}

		if(tMin > 0.f) {
			a.distance = tMin;
			if(n.x > n.y) a.hitNormal = (a.direction.x < 0.f) ? Vec2f(1.f, 0.f) : Vec2f(-1.f, 0.f);
			else if(n.x < n.y) a.hitNormal = (a.direction.y < 0.f) ? Vec2f(0.f, 1.f) : Vec2f(0.f, -1.f);
			else a.hitNormal = (a.GetHitPos() - b.GetCenter()).Normalized();

			return true;
		} else
			return false;
	}
	inline const bool Intersect(Tracer2& a, const ORect& b) noexcept {
		float tMin = -std::numeric_limits<float>::max();
		float tMax = std::numeric_limits<float>::max();
		a.distance = std::numeric_limits<float>::max();
		Vec2f dir[2]{b.RDir(), b.UDir()};
		Vec2f size = b.size * 0.5f;
		Vec2f n;

		Vec2f p = b.GetCenter() - a.GetOrigin();
		for(uint32_t i = 0u; i < 2u; i++) {
			float f = dir[i] * a.GetDirection();
			float e = dir[i] * p;
			if(Abs(f) >= 0.f) {
				float t1 = (e + size[i]) / f;
				float t2 = (e - size[i]) / f;
				if(t1 > t2) std::swap(t1, t2);
				n[i] = t1;
				tMin = Max(t1, tMin);
				tMax = Min(t2, tMax);
				if(tMin >= tMax || tMax < 0.f)
					return false;
			} else if(-e - b.size[i] > 0.f || -e + b.size[i] < 0.f) return false;
		}

		if(tMin > 0.f) {
			a.distance = tMin;
			Vec2f tDir = Concealed::RotateVec(a.direction, -b.rot);
			if(n.x > n.y) a.hitNormal = (tDir.x < 0.f) ? b.RDir() : b.LDir();
			else if(n.x < n.y) a.hitNormal = (tDir.y < 0.f) ? b.UDir() : b.DDir();
			else a.hitNormal = (a.GetHitPos() - b.GetCenter()).Normalized();

			return true;
		} else
			return false;
	}


	// 3D Intersection
	
	inline const bool Intersect(const Frustum& a, const Frustum& b) noexcept {
		return a.DXFrustum.Intersects(b.DXFrustum);
	}
	inline const bool Intersect(const Frustum& a, const Sphere& b) noexcept {
		return a.DXFrustum.Intersects(b.DXSphere);
	}
	inline const bool Intersect(const Frustum& a, const AABB& b) noexcept {
		return a.DXFrustum.Intersects(b.DXBox);
	}
	inline const bool Intersect(const Frustum& a, const OBB& b) noexcept {
		return a.DXFrustum.Intersects(b.DXBox);
	}
	inline const bool Intersect(const Frustum& a, Tracer& b) noexcept {
		Concealed::XMVEC origin = Concealed::XMLoad<Concealed::XMVEC>(&b.GetOrigin());
		Concealed::XMVEC direction = Concealed::XMLoad<Concealed::XMVEC>(&b.GetDirection());
		float dist = std::numeric_limits<float>::max();
		bool hit = a.DXFrustum.Intersects(origin, direction, dist);
		b.distance = dist;
		return hit;
	}

	inline const bool Intersect(const Sphere& a, const Frustum& b) noexcept {
		return a.DXSphere.Intersects(b.DXFrustum);
	}
	inline const bool Intersect(const Sphere& a, const Sphere& b) noexcept {
		return a.DXSphere.Intersects(b.DXSphere);
	}
	inline const bool Intersect(const Sphere& a, const AABB& b) noexcept {
		return a.DXSphere.Intersects(b.DXBox);
	}
	inline const bool Intersect(const Sphere& a, const OBB& b) noexcept {
		return a.DXSphere.Intersects(b.DXBox);
	}
	inline const bool Intersect(const Sphere& a, Tracer& b) noexcept {
		Concealed::XMVEC origin = Concealed::XMLoad<Concealed::XMVEC>(&b.GetOrigin());
		Concealed::XMVEC direction = Concealed::XMLoad<Concealed::XMVEC>(&b.GetDirection());
		float dist = std::numeric_limits<float>::max();
		bool hit = a.DXSphere.Intersects(origin, direction, dist);
		b.distance = dist;
		b.hitNormal = (b.GetHitPos() - a.origin).Normalized();
		return hit;
	}

	inline const bool Intersect(const AABB& a, const Frustum& b) noexcept {
		return a.DXBox.Intersects(b.DXFrustum);
	}
	inline const bool Intersect(const AABB& a, const Sphere& b) noexcept {
		return a.DXBox.Intersects(b.DXSphere);
	}
	inline const bool Intersect(const AABB& a, const AABB& b) noexcept {
		return a.DXBox.Intersects(b.DXBox);
	}
	inline const bool Intersect(const AABB& a, const OBB& b) noexcept {
		return a.DXBox.Intersects(b.DXBox);
	}
	inline const bool Intersect(const AABB& a, Tracer& b) noexcept {
		Concealed::XMVEC origin = Concealed::XMLoad<Concealed::XMVEC>(&b.GetOrigin());
		Concealed::XMVEC direction = Concealed::XMLoad<Concealed::XMVEC>(&b.GetDirection());
		float dist = std::numeric_limits<float>::max();
		bool hit = a.DXBox.Intersects(origin, direction, dist);
		b.distance = dist;
		return hit;
	}

	inline const bool Intersect(const OBB& a, const Frustum& b) noexcept {
		return a.DXBox.Intersects(b.DXFrustum);
	}
	inline const bool Intersect(const OBB& a, const Sphere& b) noexcept {
		return a.DXBox.Intersects(b.DXSphere);
	}
	inline const bool Intersect(const OBB& a, const AABB& b) noexcept {
		return a.DXBox.Intersects(b.DXBox);
	}
	inline const bool Intersect(const OBB& a, const OBB& b) noexcept {
		return a.DXBox.Intersects(b.DXBox);
	}
	inline const bool Intersect(const OBB& a, Tracer& b) noexcept {
		Concealed::XMVEC origin = Concealed::XMLoad<Concealed::XMVEC>(&b.GetOrigin());
		Concealed::XMVEC direction = Concealed::XMLoad<Concealed::XMVEC>(&b.GetDirection());
		float dist = std::numeric_limits<float>::max();
		bool hit = a.DXBox.Intersects(origin, direction, dist);
		b.distance = dist;
		return hit;
	}

	inline const bool Intersect(Tracer& a, const Frustum& b) noexcept {
		Concealed::XMVEC origin = Concealed::XMLoad<Concealed::XMVEC>(&a.GetOrigin());
		Concealed::XMVEC direction = Concealed::XMLoad<Concealed::XMVEC>(&a.GetDirection());
		float dist = std::numeric_limits<float>::max();
		bool hit = b.DXFrustum.Intersects(origin, direction, dist);
		a.distance = dist;
		return hit;
	}
	inline const bool Intersect(Tracer& a, const Sphere& b) noexcept {
		Concealed::XMVEC origin = Concealed::XMLoad<Concealed::XMVEC>(&a.GetOrigin());
		Concealed::XMVEC direction = Concealed::XMLoad<Concealed::XMVEC>(&a.GetDirection());
		float dist = std::numeric_limits<float>::max();
		bool hit = b.DXSphere.Intersects(origin, direction, dist);
		a.distance = dist;
		a.hitNormal = (a.GetHitPos() - b.origin).Normalized();
		return hit;
	}
	inline const bool Intersect(Tracer& a, const AABB& b) noexcept {
		Concealed::XMVEC origin = Concealed::XMLoad<Concealed::XMVEC>(&a.GetOrigin());
		Concealed::XMVEC direction = Concealed::XMLoad<Concealed::XMVEC>(&a.GetDirection());
		float dist = std::numeric_limits<float>::max();
		bool hit = b.DXBox.Intersects(origin, direction, dist);
		a.distance = dist;
		return hit;
	}
	inline const bool Intersect(Tracer& a, const OBB& b) noexcept {
		Concealed::XMVEC origin = Concealed::XMLoad<Concealed::XMVEC>(&a.GetOrigin());
		Concealed::XMVEC direction = Concealed::XMLoad<Concealed::XMVEC>(&a.GetDirection());
		float dist = std::numeric_limits<float>::max();
		bool hit = b.DXBox.Intersects(origin, direction, dist);
		a.distance = dist;
		return hit;
	}


	// ----------------------------------------------------------------- //
	
};  