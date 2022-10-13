#include "Engine.h"
#include <iostream> 

//float points[] = {​​​​​​​
//-0.5f, -0.5f,  0.0f,
// 0.0f,  0.5f,  0.0f,
// 0.5f, -0.5f,  0.0f
//}​​​;

float points[] = {
	1.0f, 1.0f, 0.0f,
	-1.0f,  -1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f,

	-1.0f, -1.0f, 0.0f,
	1.0f,  1.0f, 0.0f,
	1.0f, -1.0f, 0.0f
};

glm::vec3 colors[] = {
	{0,0,1},
	{1,0,1},
	{0,1,1},
	{0,1,0},
	{1,0,1},
	{0,0,1},
	{1,0,1},
	{0,1,1},
};

glm::vec2 texcoords[]{
	{0,0},
	{0,1},
	{1,0},
	{0,1},
	{1,1},
	{1,0}
};

int main(int argc,char** argv)
{
	LOG("Application Started...");

	cool::InitializeMemory();
	cool::SetFilePath("../Assests");


	cool::Engine::Instance().Initialize();
	cool::Engine::Instance().Register();

	cool::g_renderer.CreateWindow("Neumont", 800, 600);
	LOG("Window Initalized... ");

	// create vertex buffer
	GLuint pvbo = 0;
	glGenBuffers(1, &pvbo);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);
	
	//Color
	GLuint cvbo = 0;
	glGenBuffers(1, &cvbo);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), colors, GL_STATIC_DRAW);

	//Texture
	GLuint tvbo = 0;
	glGenBuffers(1, &tvbo);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), texcoords, GL_STATIC_DRAW);

	// create vertex array
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	// create shader
	std::shared_ptr<cool::Shader> vs = cool::g_resources.Get<cool::Shader>("shader/basic.vert", GL_VERTEX_SHADER);
	std::shared_ptr<cool::Shader> fs = cool::g_resources.Get<cool::Shader>("shader/basic.frag", GL_FRAGMENT_SHADER);
	

	// create program
	GLuint program = glCreateProgram();
	glAttachShader(program, fs->m_shader);
	glAttachShader(program, vs->m_shader);
	glLinkProgram(program);
	glUseProgram(program);

	//create texture
	std::shared_ptr<cool::Texture> texture1 = cool::g_resources.Get<cool::Texture>("texture/catcall.jpg");
	texture1->Bind();
	std::shared_ptr<cool::Texture> texture2 = cool::g_resources.Get<cool::Texture>("texture/hamtr.png");
	texture2->Bind();

	GLint uniform1 = glGetUniformLocation(program, "scale");
	GLint uniform2 = glGetUniformLocation(program, "tint");
	GLint uniform3 = glGetUniformLocation(program, "transform");

	glUniform3f(uniform2, 1, 0, 0);




	glm::mat4 mx{ 1 };

	bool quit = false;
	while (!quit)
	{
		cool::Engine::Instance().Update();

		if (cool::g_inputSystem.GetKeyState(cool::key_escape) == cool::InputSystem::KeyState::Pressed) quit = true;

		glUniform1f(uniform1, std::sin(cool::g_time.time));
		mx = glm::eulerAngleXYZ(0.0f,0.0f,cool::g_time.time);
		glUniformMatrix4fv(uniform3,1, GL_FALSE, glm::value_ptr(mx));


		cool::g_renderer.BeginFrame();

		glDrawArrays(GL_TRIANGLES, 0, 9);
		glDrawArrays(GL_TRIANGLES, 9, 18);

		cool::g_renderer.EndFrame();
	}

	cool::Engine::Instance().Shutdown();
	return 0;
}