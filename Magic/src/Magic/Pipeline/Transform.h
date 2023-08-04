#pragma once
#include "Magic/Core/Math.h"

namespace Magic {
	class Transform
	{
	public:
		Transform(const glm::vec3& position,const glm::vec3& euler, const glm::vec3& scale);
		void SetPosition(const glm::vec3& position);
		void SetEuler(const glm::vec3& euler);
		void SetScale(const glm::vec3& scale);
		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline const glm::vec3& GetEuler() const { return m_Euler; }
		inline const glm::vec3& GetScale() const { return m_Scale; }
		inline const glm::mat4x4& GetLocalToWorldMatrix() const { return m_localToWorld; }
		inline const glm::mat4x4& GetWorldToLocalMatrix() const { return m_worldToLocal; }
	private:
		void CalculateMatrix();
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Euler;
		glm::vec3 m_Scale;
		glm::mat4x4 m_localToWorld;
		glm::mat4x4 m_worldToLocal;
	};
}