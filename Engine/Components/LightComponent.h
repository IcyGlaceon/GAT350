#pragma once
#include "Framework/Component.h"

namespace cool
{
	class Program;
	class LightComponent : public Component
	{
	public:
		enum class Type 
		{
			Point, 
			Directional, 
			Spot
		};

	public:
		CLASS_DECLARATION(LightComponent)

		void Update() override;
		void SetProgram(std::shared_ptr<Program> program, int index);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		glm::vec3 color{ 0 };
		Type type = Type::Point;
		float cutoff{ 45.0f };
		float exponent{ 50.0f };
	};
}