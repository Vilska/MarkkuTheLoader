#pragma once

#include <memory>

#include "glm/glm.hpp"

#include "Event/Event.h"
#include "Event/MouseEvent.h"

namespace Core {

	class Camera
	{
	public:
		Camera(float fov, float aspectRatio);

		void Update(float deltaTime);
		void OnEvent(Event& event);

		inline static glm::vec3& GetPosition() { return s_Instance->m_CameraPosition; }
		inline static glm::mat4& GetViewProjectionMatrix() { return s_Instance->m_ViewProjectionMatrix; }

		inline static void SetAspectRatio(float aspectRatio) { s_Instance->m_AspectRatio = aspectRatio; }

		static std::unique_ptr<Camera> Create(float fov, float aspectRatio);
	private:
		inline void RecalculateMatrices();
		bool RotateCamera(MouseMovedEvent& event);
	private:
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewProjectionMatrix = glm::mat4(1.0f);

		glm::vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 10.0f);
		glm::vec3 m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		float m_FOV = glm::radians(45.0f);
		float m_NearClip = 0.1f, m_FarClip = 100.0f;
		float m_AspectRatio = 0.0f;

		bool m_FirstMouse = true;
		float m_LastX, m_LastY;
		float m_Yaw = -90.0f;
		float m_Pitch = 0.0f;

		static Camera* s_Instance;
	};

}
