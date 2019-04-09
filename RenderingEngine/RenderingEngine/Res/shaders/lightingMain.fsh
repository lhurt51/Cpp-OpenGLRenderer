void main ()
{
	gl_FragColor = tecture2D(diffuse, texCoord0.xy) *
		CalcLightingEffect(normalize(normal0), worldPos0);
}