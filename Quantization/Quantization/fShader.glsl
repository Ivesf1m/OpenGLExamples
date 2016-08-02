#version 330 core

in vec2 tc;
out vec4 color;

uniform sampler2D texSampler;

void main()
{
	//color = texture(texSampler, tc);
	vec3 texrgb = texture(texSampler, tc).rgb * 255.0f;
	color = vec4((floor(texrgb / 8.0f ) * 8.0f) / 255.0f, 1.0f);
}