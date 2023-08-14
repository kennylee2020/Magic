#pragma once

#include "Magic/Core/Math.h"
#include "Magic/Graphics/Graphics.h"

namespace Magic {
	struct NameComponent {
		std::string Name;
		NameComponent() = default;
		NameComponent(const NameComponent&) = default;
		NameComponent(const std::string& name) : Name(name){}
	};

	struct TransformComponent
	{
	public:
		TransformComponent() { CalculateMatrix(); }
		TransformComponent(const TransformComponent&) = default;
		
		TransformComponent(const glm::vec3& position) : m_Position(position){
			CalculateMatrix();
		}

		TransformComponent(const glm::vec3& position, const glm::vec3& eulerAngles) : m_Position(position), m_EulerAngles(eulerAngles){
			CalculateMatrix();
		}

		TransformComponent(const glm::vec3& position, const glm::vec3& eulerAngles, const glm::vec3& scale) : m_Position(position), m_EulerAngles(eulerAngles), m_Scale(scale){
			CalculateMatrix();
		}

		void SetPosition(const glm::vec3& position)
		{
			m_Position = position;
			CalculateMatrix();
		}

		void SetEulerAngles(const glm::vec3& eulerAngles)
		{
			m_EulerAngles = eulerAngles;
			CalculateMatrix();
		}

		void SetScale(const glm::vec3& scale)
		{
			m_Scale = scale;
			CalculateMatrix();
		}

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline const glm::vec3& GetEulerAngles()const { return m_EulerAngles; }
		inline const glm::vec3& GetScale() const { return m_Scale; }
		inline const glm::mat4x4& GetLocalToWorldMatrix() const { return m_localToWorld; }
		inline const glm::mat4x4& GetWorldToLocalMatrix() const { return m_worldToLocal; }
	private:
		void CalculateMatrix()
		{
			m_localToWorld = glm::translate(glm::mat4(1.0f), m_Position)
				* glm::eulerAngleXYZ(m_EulerAngles.x, m_EulerAngles.y, m_EulerAngles.z)
				* glm::scale(glm::mat4(1.0f), m_Scale);
			m_worldToLocal = glm::inverse(m_localToWorld);
		}

	private:
		glm::vec3 m_Position = {0.0f, 0.0f ,0.0f};
		glm::vec3 m_EulerAngles = { 0.0f, 0.0f ,0.0f };
		glm::vec3 m_Scale = { 1.0f, 1.0f ,1.0f };
		glm::mat4x4 m_localToWorld;
		glm::mat4x4 m_worldToLocal;
	};

	struct CameraComponent {
	public:
		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(float sizeOrFov, float aspect, bool orthographic, float nearPlane = 0.01f, float farPlane = 100.0f)
			: m_SizeOrFov(sizeOrFov), m_Aspect(aspect), m_Orthographic(orthographic), m_Near(nearPlane),m_Far(farPlane) {
			CalculateProjection();
		}

		void SetSizeOrFov(float sizeOrFov)
		{
			m_SizeOrFov = sizeOrFov;
			CalculateProjection();
		}

		void SetAspect(float aspect)
		{
			m_Aspect = aspect;
			CalculateProjection();
		}

		void SetOrthographic(bool orthographic)
		{
			m_Orthographic = orthographic;
			CalculateProjection();
		}

		void SetClipPlane(float nearPlane, float farPlane)
		{
			m_Near = nearPlane;
			m_Far = farPlane;
			CalculateProjection();
		}

		inline const glm::mat4x4& GetProjection() const { return m_Projection; }
		inline const float GetSizeOrFov() const { return m_SizeOrFov; }
		inline const float GetAspect() const { return m_Aspect; }
		inline const float GetNearPlane() const { return m_Near; }
		inline const float GetFarPlane() const { return m_Far; }
		inline const bool IsOrthographic() const { return m_Orthographic; }
	private:
		void CalculateProjection() {
			if (m_Orthographic) {
				float height = m_SizeOrFov;
				float width = height * m_Aspect;
				m_Projection = glm::ortho(-width, width, -height, height, m_Near, m_Far);
			}
			else {
				m_Projection = glm::perspective(m_SizeOrFov, m_Aspect, m_Near, m_Far);
			}
		}
	private:
		float m_SizeOrFov, m_Aspect;
		float m_Near, m_Far;
		bool m_Orthographic;
		glm::mat4x4 m_Projection;
	};

	struct MeshComponent
	{
		Ref<Mesh> mesh;
		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;
	};

	struct MaterialComponent
	{
		Ref<Material> material;
		MaterialComponent() = default;
		MaterialComponent(const MaterialComponent&) = default;
	};
}
