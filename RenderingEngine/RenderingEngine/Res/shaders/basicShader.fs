#version 120

varying vec2 etxCoord0;

uniform sampler2D diffuse;

void main()
{
	gl_fragColor = texture2D(diffuse, texCoords);
}