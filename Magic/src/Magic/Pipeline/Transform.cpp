#include "Transform.h"

namespace Magic {
	Transform::Transform(const glm::vec3& position, const glm::vec3& euler, const glm::vec3& scale)
		: m_Position(position), m_Euler(euler), m_Scale(scale)
	{
		CalculateMatrix();
	}

	void Transform::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		CalculateMatrix();
	}

	void Transform::SetEuler(const glm::vec3& euler)
	{
		m_Euler = euler;
		CalculateMatrix();
	}

	void Transform::SetScale(const glm::vec3& scale)
	{
		m_Scale = scale;
		CalculateMatrix();
	}

	void Transform::CalculateMatrix()
	{
		m_localToWorld = glm::translate(glm::mat4(1.0f), m_Position)
			* glm::eulerAngleXYZ(m_Euler.x, m_Euler.y, m_Euler.z)
			* glm::scale(glm::mat4(1.0f), m_Scale);
		m_worldToLocal = glm::inverse(m_localToWorld);
	}
}