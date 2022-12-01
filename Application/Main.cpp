#include "Engine.h"
#include <vector>
#include <iostream>
#define POST_PROCESS

int main(int argc, char** argv)
{
	LOG("Application Started...");

	cool::InitializeMemory();
	cool::SetFilePath("../Assets");

	cool::Engine::Instance().Initialize();
	cool::Engine::Instance().Register();

	cool::g_renderer.CreateWindow("Neumont", 800, 600);
	LOG("Window Initalized... ");

	cool::g_GUI.Initialize(cool::g_renderer);

	// create framebuffer texture
	auto texture = std::make_shared<cool::Texture>();
	texture->CreateTexture(64,64);
	cool::g_resources.Add<cool::Texture>("fb_texture", texture);

	// create framebuffer
	auto framebuffer = cool::g_resources.Get<cool::Framebuffer>("framebuffer", "fb_texture");
	framebuffer->Unbind();


	// load scene 
	auto scene = cool::g_resources.Get<cool::Scene>("Scenes/rtt.scn");

	glm::vec3 pos{ 0, 0, 0 };
	glm::vec3 rot{ 0, 0, 0 };

	float ri = 1.0f;
	bool quit = false;
	while (!quit)
	{
		cool::Engine::Instance().Update();
		cool::g_GUI.BeginFrame(cool::g_renderer);



		if (cool::g_inputSystem.GetState(cool::key_escape) == cool::InputSystem::State::Pressed) quit = true;

		auto actor = scene->GetActorFromName("Model");
		if (actor)
		{
			actor->m_transform.rotation = math::EulerToQuaternion(rot);
		}

		actor = scene->GetActorFromName("Light");
		if (actor)
		{
			// move light using sin wave
			//actor->m_transform.position = pos;
		}

		auto program = cool::g_resources.Get<cool::Program>("Shaders/FX/refraction.prog");

		if (program)
		{
			program->Use();
			program->SetUniform("ri", ri);
		}

		ImGui::Begin("Controls");
		//ImGui::SliderFloat3("Position", &pos[0], -5.0f, 5.0f);
		ImGui::DragFloat3("Rotation", &rot[0]);
		ImGui::DragFloat("Refraction Index", &ri, 0.01f, 1, 3);
		ImGui::End();

		scene->Update();

#ifdef POST_PROCESS
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(false);
			}
		}

		// render pass 1 (render to framebuffer) 
		cool::g_renderer.SetViewport(0, 0, framebuffer->GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();
		cool::g_renderer.BeginFrame();
		scene->PreRender(cool::g_renderer);
		scene->Render(cool::g_renderer);
		framebuffer->Unbind();

		// render pass 2 (render to screen) 
		cool::g_renderer.RestoreViewport();
		cool::g_renderer.BeginFrame();
		scene->PreRender(cool::g_renderer);

		//draw only the post process actor to the screen
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(true);
				actor->Draw(cool::g_renderer);
			}
		}
#else
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);

#endif //POST_PROCESS

		cool::g_GUI.Draw();

		cool::g_renderer.EndFrame();
		cool::g_GUI.EndFrame();
	}

	scene->RemoveAll();
	cool::Engine::Instance().Shutdown();

	return 0;
}