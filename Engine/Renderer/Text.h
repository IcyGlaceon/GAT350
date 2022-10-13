#pragma once
#include <string>
#include <memory>

struct SDL_Texture;

namespace cool
{
	class Font;
	class Renderer;
	struct Color;
	struct Vector2;

	class Text
	{
	public:
		Text() = default;
		Text(Font* font) : m_font{ font } {}
		~Text();

		void Create(Renderer& renderer, const std::string& text, const Color& color);
		void Draw(Renderer& renderer, const Vector2& position);

	private:
		Font* m_font = nullptr;
		SDL_Texture* m_texture = nullptr;
	};
}
