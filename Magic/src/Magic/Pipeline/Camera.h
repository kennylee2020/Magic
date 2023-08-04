#pragma once
#include "Transform.h"

namespace Magic {
	class Camera
	{
	public:
		Camera(float sizeOrFov, float aspect, bool orthographic);
		void SetSizeOrFov(float sizeOrFov);
		void SetAspect(float aspect);
		void SetOrthographic(bool orthographic);
		void SetClipPlane(float nearPlane, float farPlane);
		inline const glm::mat4x4& GetProjection() const { return m_Projection; }
		inline const Transform& GetTransform() const { return m_Transform; }
		inline const float GetSizeOrFov() const { return m_SizeOrFov; }
		inline const float GetAspect() const { return m_Aspect; }
		inline const float GetNearPlane() const { return m_Near; }
		inline const float GetFarPlane() const { return m_Far; }
		inline const bool IsOrthographic() const { return m_Orthographic; }
	public:
		static Ref<Camera> CreatePerspective(float fov, float aspect);
		static Ref<Camera> CreateOrthographic(float size, float aspect);
	private:
		void CalculateProjection();
	private:
		float m_SizeOrFov, m_Aspect;
		float m_Near,m_Far;
		bool m_Orthographic;
		Transform m_Transform;
		glm::mat4x4 m_Projection;
	};
}