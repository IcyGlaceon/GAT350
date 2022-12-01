#include "CameraController.h"
#include "Engine.h"

namespace cool 
{
	void CameraController::Initialize()
	{
		glm::vec3 v = math::QuaternionToEuler(m_owner->m_transform.rotation);
		m_pitch = v.x;
		m_yaw = v.y;
	}

	void CameraController::Update()
	{
		// get camera rotation
		if (g_inputSystem.GetButtonState(2) == InputSystem::State::Held)
		{
			glm::vec2 axis = g_inputSystem.GetMouseRelative() * sensitivity;

			m_yaw += axis.x;
			m_pitch -= axis.y;
			m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);
		}

		glm::vec3 forward;
		forward.x = cos(glm::radians(m_yaw - 90.0f)) * cos(glm::radians(m_pitch));
		forward.y = sin(glm::radians(m_pitch));
		forward.z = sin(glm::radians(m_yaw - 90.0f)) * cos(glm::radians(m_pitch));
		forward = glm::normalize(forward);

		glm::mat4 view = glm::lookAt(glm::vec3{ 0.0f }, -forward, glm::vec3{ 0, 1, 0 });
		m_owner->m_transform.rotation = glm::conjugate(glm::quat_cast(view));

		glm::vec3 direction{ 0 };

		if (g_inputSystem.GetState(key_a) == InputSystem::State::Held)	direction.x += 1;
		if (g_inputSystem.GetState(key_d) == InputSystem::State::Held)	direction.x -= 1;
		if (g_inputSystem.GetState(key_w) == InputSystem::State::Held)	direction.y += 1;
		if (g_inputSystem.GetState(key_s) == InputSystem::State::Held)	direction.y -= 1;
		if (g_inputSystem.GetState(key_q) == InputSystem::State::Held)	direction.z += 1;
		if (g_inputSystem.GetState(key_e) == InputSystem::State::Held)	direction.z -= 1;
	}

	bool CameraController::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool CameraController::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, speed);
		READ_DATA(value, sensitivity);

		return true;
	}
}