#version 330 core

in vec2 tc;
out vec4 color;

uniform sampler2D texSampler;

void main()
{
	vec3 texrgb = texture(texSampler, tc).rgb * 255.0f;
	float scaleFactor = 2.0f;
	color = vec4((floor(texrgb / scaleFactor ) * scaleFactor) / 255.0f, 1.0f);
}