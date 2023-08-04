#include "magicpch.h"
#include "Camera.h"

namespace Magic {
	Ref<Camera> Camera::CreatePerspective(float fov, float aspect)
	{
		return CreateRef<Camera>(fov, aspect, false);
	}

	Ref<Camera> Camera::CreateOrthographic(float size, float aspect)
	{
		return CreateRef<Camera>(size, aspect, true);
	}

	Camera::Camera(float sizeOrFov, float aspect, bool orthographic)
		: m_SizeOrFov(sizeOrFov), m_Aspect(aspect), m_Orthographic(orthographic),
		  m_Near(0.1f), m_Far(100.0f),
		  m_Transform(glm::vec3(0),glm::vec3(0),glm::vec3(1))
	{
		CalculateProjection();
	}

	void Camera::SetSizeOrFov(float sizeOrFov)
	{
		m_SizeOrFov = sizeOrFov;
		CalculateProjection();
	}

	void Camera::SetAspect(float aspect)
	{
		m_Aspect = aspect;
		CalculateProjection();
	}

	void Camera::SetOrthographic(bool orthographic)
	{
		m_Orthographic = orthographic;
		CalculateProjection();
	}

	void Camera::SetClipPlane(float nearPlane, float farPlane)
	{
		m_Near = nearPlane;
		m_Far = farPlane;
		CalculateProjection();
	}

	void Camera::CalculateProjection() {
		if (m_Orthographic) {
			float height = m_SizeOrFov;
			float width = height * m_Aspect;
			m_Projection = glm::ortho(-width, width, -height, height, m_Near, m_Far);
		}else {
			m_Projection = glm::perspective(m_SizeOrFov, m_Aspect, m_Near, m_Far);
		}
	}
}