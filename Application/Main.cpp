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


	// load scene 
	auto scene = std::make_unique<cool::Scene>();

	rapidjson::Document document;
	bool success = cool::json::Load("scenes/basic.scn", document);
	if (!success)
	{
		LOG("error loading scene file %s.", "scenes/basic.scn");
	}
	else
	{
		scene->Read(document);
		scene->Initialize();
	}
	
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
	//std::shared_ptr<cool::Material> material = cool::g_resources.Get<cool::Material>("materials/box.mtrl");
	//material->Bind();

	std::shared_ptr<cool::Material> material = cool::g_resources.Get<cool::Material>("materials/ogre.mtrl");
	material->Bind();

	//material->GetProgram()->SetUniform("tint", glm::vec3{ 1, 0, 0 });
	material->GetProgram()->SetUniform("scale", 1.0f);

	glm::mat4 model{ 1 };
	glm::mat4 projection = glm::perspective(45.0f, cool::g_renderer.GetWidth() / (float)cool::g_renderer.GetHeight(), 0.01f, 100.0f);

	glm::vec3 cameraPosition = glm::vec3{ 0, 0, 1 };
	float speed = 3;


	std::vector<cool::Transform> transform;
	for (size_t i = 0; i < 1; i++) 
	{
		//transform.push_back({ { cool::randomf(-10,10) , cool::randomf(-10,10) ,cool::randomf(-10,10)}, {cool::randomf(360),90,0} });
		transform.push_back({ {0,0,-2 }, { 0,90,0 } });
	}
	
	auto m = cool::g_resources.Get<cool::Model>("models/ogre.obj");


	bool quit = false;
	while (!quit)
	{
		cool::Engine::Instance().Update();

		if (cool::g_inputSystem.GetKeyState(cool::key_escape) == cool::InputSystem::KeyState::Pressed) quit = true;
		//left/right
		if (cool::g_inputSystem.GetKeyState(cool::key_a) == cool::InputSystem::KeyState::Held) cameraPosition.x -= speed * cool::g_time.deltaTime;
		if (cool::g_inputSystem.GetKeyState(cool::key_d) == cool::InputSystem::KeyState::Held) cameraPosition.x += speed * cool::g_time.deltaTime;
		
		//up/down
		if (cool::g_inputSystem.GetKeyState(cool::key_w) == cool::InputSystem::KeyState::Held) cameraPosition.y += speed * cool::g_time.deltaTime;
		if (cool::g_inputSystem.GetKeyState(cool::key_s) == cool::InputSystem::KeyState::Held) cameraPosition.y -= speed * cool::g_time.deltaTime;
		
		//forward/back
		if (cool::g_inputSystem.GetKeyState(cool::key_q) == cool::InputSystem::KeyState::Held) cameraPosition.z -= speed * cool::g_time.deltaTime;
		if (cool::g_inputSystem.GetKeyState(cool::key_e) == cool::InputSystem::KeyState::Held) cameraPosition.z += speed * cool::g_time.deltaTime;
		

		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });
		//model = glm::eulerAngleXYZ(0.0f, cool::g_time.time, 0.0f);

		scene->Update();

		cool::g_renderer.BeginFrame();
		
		for (size_t i = 0; i < transform.size(); i++)
		{
			transform[i].rotation += glm::vec3{ 0,90 * cool::g_time.deltaTime,0 };
			glm::mat4 mvp = projection * view * model * (glm::mat4)transform[i];
			program->SetUniform("mvp", mvp);

			m->m_vertexBuffer.Draw();
		}

		scene->Draw(cool::g_renderer);

		cool::g_renderer.EndFrame();
	}
	scene->RemoveAll();
	cool::Engine::Instance().Shutdown();
	return 0;
}