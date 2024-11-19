#version 120

attribute vec4 vPosition;
attribute vec4 vNormal;
attribute vec2 vTexCoord;

varying vec2 texCoord;
varying vec4 N, V, L;
varying float distance;

uniform mat4 ctm;
uniform mat4 model_view;
uniform mat4 projection;
uniform vec4 light_position;
uniform vec4 eye_point;

void main()
{
	N = normalize(model_view * ctm * vNormal);
	vec4 Ltemp = normalize(model_view * (light_position - ctm * vPosition));
	L = normalize(Ltemp);
	V = normalize(eye_point - (model_view * ctm * vPosition));
	distance = length(Ltemp);

	texCoord = vTexCoord;
	gl_Position = projection * model_view * ctm * vPosition;
}
