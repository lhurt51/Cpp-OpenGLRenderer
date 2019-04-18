#version 120

void main()
{
	// This shouldnt be used in basic shadow map generation
	gl_FragColor = vec4(gl_FragCoord.z);
}