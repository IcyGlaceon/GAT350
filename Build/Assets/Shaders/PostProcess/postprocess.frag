#version 430 core

in vec2 texcoord; 
  
out vec4 fcolor; 
  
uniform sampler2D textureMap; 
  
void main() 
{ 
 fcolor = texture(textureMap, texcoord); 
}

/*
vec3 color = texture(textureMap, texcoord).rgb; 
 // black / white 
 float avg = (color.r + color.g + color.b) / 3.0; 
 fcolor = vec4(vec3(avg), 1); 
*/
