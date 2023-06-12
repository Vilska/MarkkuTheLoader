#include "cpch.h"
#include "Camera.h"

#include "Core/Input.h"
#include "Event/KeyMouseCodes.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Core {

	Camera* Camera::s_Instance = nullptr;

	std::unique_ptr<Camera> Camera::Create(float fov, float aspectRatio)
	{
		return std::make_unique<Camera>(fov, aspectRatio);
	}

	Camera::Camera(float fov, float aspectRatio)
		: m_FOV(fov), m_AspectRatio(aspectRatio) 
	{
		s_Instance = this;
	}

	void Camera::Update(float deltaTime)
	{
		float cameraSpeed = 2.5f * deltaTime;

		if (Input::IsKeyPressed(KEY_W))
			m_CameraPosition += cameraSpeed * m_CameraFront;
		if (Input::IsKeyPressed(KEY_S))
			m_CameraPosition -= cameraSpeed * m_CameraFront;
		if (Input::IsKeyPressed(KEY_A))
			m_CameraPosition -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * cameraSpeed;
		if (Input::IsKeyPressed(KEY_D))
			m_CameraPosition += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * cameraSpeed;

		RecalculateMatrices();
	}

	void Camera::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseMovedEvent>(std::bind(&Camera::RotateCamera, this, std::placeholders::_1));
	}

	void Camera::RecalculateMatrices()
	{
		m_ViewMatrix = glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp);
		m_ProjectionMatrix = glm::perspective(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	bool Camera::RotateCamera(MouseMovedEvent& event)
	{
		if (!Input::IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
		{
			m_FirstMouse = true;
			return 0;
		}

		float xPos = event.GetX();
		float yPos = event.GetY();
		if (m_FirstMouse)
		{
			m_LastX = xPos;
			m_LastY = yPos;
			m_FirstMouse = false;
		}

		float offsetX = xPos - m_LastX;
		float offsetY = m_LastY - yPos;
		m_LastX = xPos;
		m_LastY = yPos;

		float sensitivity = 0.1f;
		offsetX *= sensitivity;
		offsetY *= sensitivity;

		m_Yaw += offsetX;
		m_Pitch += offsetY;

		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		glm::vec3 direction(1.0f);
		direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		direction.y = sin(glm::radians(m_Pitch));
		direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_CameraFront = glm::normalize(direction);

		RecalculateMatrices();

		return 0;
	}

}