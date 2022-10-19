#include "Engine.h"
#include <iostream> 

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

int main(int argc,char** argv)
{
	LOG("Application Started...");

	cool::InitializeMemory();
	cool::SetFilePath("../Assets");


	cool::Engine::Instance().Initialize();
	cool::Engine::Instance().Register();

	cool::g_renderer.CreateWindow("Neumont", 800, 600);
	LOG("Window Initalized... ");
	
	std::shared_ptr<cool::VertexBuffer> vb = cool::g_resources.Get<cool::VertexBuffer>("box");
	vb->CreateVertexBuffer(sizeof(vertices), 36, vertices);
	vb->SetAttribute(0, 3, 8 * sizeof(float), 0);
	vb->SetAttribute(1, 3, 8 * sizeof(float), 3 * sizeof(float));
	vb->SetAttribute(2, 2, 8 * sizeof(float), 6 * sizeof(float));
	
	
	// create shader
	std::shared_ptr<cool::Shader> vs = cool::g_resources.Get<cool::Shader>("shaders/basic.vert", GL_VERTEX_SHADER);
	std::shared_ptr<cool::Shader> fs = cool::g_resources.Get<cool::Shader>("shaders/basic.frag", GL_FRAGMENT_SHADER);
	

	// create program
	std::shared_ptr<cool::Program> program = cool::g_resources.Get <cool::Program>("shaders/basic.prog",GL_PROGRAM);
	program->Link();
	program->Use();

	
	//create material
	std::shared_ptr<cool::Material> material = cool::g_resources.Get<cool::Material>("materials/box.mtrl");
	material->Bind();

	//material->GetProgram()->SetUniform("tint", glm::vec3{ 1, 0, 0 });
	material->GetProgram()->SetUniform("scale", 1.0f);

	glm::mat4 model{ 1 };
	glm::mat4 projection = glm::perspective(45.0f, cool::g_renderer.GetWidth() / (float)cool::g_renderer.GetHeight(), 0.01f, 100.0f);

	glm::vec3 cameraPosition = glm::vec3{ 0, 0, 1 };
	float speed = 3;

	bool quit = false;
	while (!quit)
	{
		cool::Engine::Instance().Update();

		if (cool::g_inputSystem.GetKeyState(cool::key_escape) == cool::InputSystem::KeyState::Pressed) quit = true;
		
		//glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3{ 0,0,0 }, glm::vec3{ 0,1,0 });
		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });
		model = glm::eulerAngleXYZ(0.0f, cool::g_time.time, 0.0f);
		glm::mat4 mvp = projection * view * model;

		//left/right
		if (cool::g_inputSystem.GetKeyState(cool::key_a) == cool::InputSystem::KeyState::Held) cameraPosition.x -= speed * cool::g_time.deltaTime;
		if (cool::g_inputSystem.GetKeyState(cool::key_d) == cool::InputSystem::KeyState::Held) cameraPosition.x += speed * cool::g_time.deltaTime;
		
		//up/down
		if (cool::g_inputSystem.GetKeyState(cool::key_w) == cool::InputSystem::KeyState::Held) cameraPosition.y -= speed * cool::g_time.deltaTime;
		if (cool::g_inputSystem.GetKeyState(cool::key_s) == cool::InputSystem::KeyState::Held) cameraPosition.y += speed * cool::g_time.deltaTime;
		
		//forward/back
		if (cool::g_inputSystem.GetKeyState(cool::key_q) == cool::InputSystem::KeyState::Held) cameraPosition.z -= speed * cool::g_time.deltaTime;
		if (cool::g_inputSystem.GetKeyState(cool::key_e) == cool::InputSystem::KeyState::Held) cameraPosition.z += speed * cool::g_time.deltaTime;


		//program->SetUniform("scale", std::sin(cool::g_time.time * 3));
		program->SetUniform("mvp", mvp);

		cool::g_renderer.BeginFrame();

		vb->Draw();

		cool::g_renderer.EndFrame();
	}

	cool::Engine::Instance().Shutdown();
	return 0;
}