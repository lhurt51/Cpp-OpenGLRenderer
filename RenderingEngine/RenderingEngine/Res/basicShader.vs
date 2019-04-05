#version 120

attribute vec3 position;

// Identity program
void main()
{
	gl_Position = vec4(position, 1.0);
}