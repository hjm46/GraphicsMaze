#version 120

varying vec4 N;
varying vec4 L;
varying vec4 V;
varying float distance;
varying vec2 texCoord;

uniform sampler2D texture;
uniform float shininess;
uniform float attenuation_constant, attenuation_linear, attenuation_quadratic;
uniform int light_ind, amb_ind, diff_ind, spec_ind;

vec4 ambient, diffuse, specular;

void main()
{
	if(light_ind == 1) {
		vec4 color = texture2D(texture, texCoord);
		vec4 NN = normalize(N);
		vec4 VV = normalize(V);
		vec4 LL = normalize(L);
		vec4 H = normalize(LL + VV);

		ambient = color * 0.2;
		diffuse = max(dot(LL, NN), 0.0) * color;
		specular = pow(max(dot(NN, H), 0.0), shininess) * vec4(1.0, 1.0, 1.0, 1.0);
		float attenuation = 1/(attenuation_constant + (attenuation_linear * distance) + (attenuation_quadratic * distance * distance));
		gl_FragColor = ambient + attenuation * (diffuse + specular);

		if(amb_ind == 0) {
			gl_FragColor -= ambient;
		}
		if(diff_ind == 0) {
			gl_FragColor -= attenuation * diffuse;
		} 
		if(spec_ind == 0) {
			gl_FragColor -= attenuation * specular;
		}

		if(amb_ind == 1) {
			gl_FragColor += ambient;
		}
		if(diff_ind == 1) {
			gl_FragColor += attenuation * diffuse;
		} 
		if(spec_ind == 1) {
			gl_FragColor += attenuation * specular;
		}
	}
	else {
		gl_FragColor = texture2D(texture, texCoord);
	}	
}
