#include "Scene.h"
#include "Factory.h"
#include "Engine.h"
#include <algorithm>
#include <iostream>

namespace cool
{
	bool Scene::Create(std::string name, ...)
	{
		rapidjson::Document document;
		bool success = cool::json::Load(name, document);
		if (!success)
		{
			LOG("error loading scene file %s.", name);
			return false;
		}
		else
		{
			Read(document);
			Initialize();

			return true;
		}
	}

	void Scene::Initialize()
	{
		for (auto& actor : m_actors) { actor->Initialize(); }
	}

	void Scene::Update()
	{
		auto iter = m_actors.begin();
		while (iter != m_actors.end())
		{
			(*iter)->Update();
			if ((*iter)->m_destroy)
			{
				iter = m_actors.erase(iter);
			}
			else 
			{
				iter++;
			}
		}
	}

	void Scene::PreRender(Renderer& renderer)
	{
		CameraComponent* camera = nullptr;
		for (auto& actor : m_actors) {
			if (!actor->IsActive()) {
				continue;
			}

			auto component = actor->GetComponent<CameraComponent>();
			if (component) {
				camera = component;
				break;
			}
		}

		std::vector<LightComponent*> lights;
		for (auto& actor : m_actors) {
			if (!actor->IsActive()) {
				continue;
			}

			auto component = actor->GetComponent<LightComponent>();
			if (component) {
				lights.push_back(component);
			}
		}

		auto programs = g_resources.Get<Program>();
		for (auto& program : programs) {
			camera->SetProgram(program);

			int index = 0;
			for (auto light : lights) {
				light->SetProgram(program, index++);
			}

			program->SetUniform("light_count", index);
			program->SetUniform("ambient_color", g_renderer.ambient_color);
		}
	}

	void Scene::Render(Renderer& renderer)
	{
		// get camera / set renderer view/projection 
		auto camera = GetActorFromName("Camera");
		if (camera)
		{
			g_renderer.SetView(camera->GetComponent<CameraComponent>() -> GetView());
			g_renderer.SetProjection(camera->GetComponent<CameraComponent>() -> GetProjection());
		}

		// draw actors 
		for (auto& actor : m_actors)
		{
			actor->Draw(renderer);
		}
	}

	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAll()
	{
		for (auto& actor : m_actors) { actor->SetDestroy(); }

		m_actors.clear();
	}


	bool Scene::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool Scene::Read(const rapidjson::Value& value)
	{
		if (!value.HasMember("actors") || !value["actors"].IsArray())
		{
			return false;
		}

		// read actors
		for (auto& actorValue : value["actors"].GetArray())
		{
			std::string type;
			READ_DATA(actorValue, type);

			auto actor = Factory::Instance().Create<Actor>(type);
			if (actor)
			{
				// read actor
				actor->Read(actorValue);

				bool prefab = false;
				READ_DATA(actorValue, prefab);

				if (prefab)
				{
					std::string name = actor->GetName();
					Factory::Instance().RegisterPrefab(name, std::move(actor));
				}
				else
				{
					Add(std::move(actor));
				}
			}
		}
		

		return true;
	}

}
