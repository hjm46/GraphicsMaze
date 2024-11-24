#version 120

varying vec4 N;
varying vec4 L;
varying vec4 V;
varying float distance;
varying vec2 texCoord;

uniform sampler2D texture;
uniform float shininess;
uniform float attenuation_constant, attenuation_linear, attenuation_quadratic;
uniform int light_ind, amb_ind, diff_ind, spec_ind, spot_ind;

vec4 ambient, diffuse, specular, light_position;

void main()
{
	if(mod(light_ind, 2) == 0) {
		vec4 color = texture2D(texture, texCoord);
		vec4 NN = normalize(N);
		vec4 VV = normalize(V);
		vec4 LL = normalize(L);
		vec4 H = normalize(LL + VV);

		ambient = color * 0.2;
		diffuse = max(dot(LL, NN), 0.0) * 0.6 * color;
		specular = pow(max(dot(NN, H), 0.0), shininess) * vec4(1.0, 1.0, 1.0, 1.0);
		float attenuation = 1/(attenuation_constant + (attenuation_linear * distance) + (attenuation_quadratic * distance * distance));
		gl_FragColor = ambient + attenuation * (diffuse + specular);

		// off
		if(mod(amb_ind, 2) != 0) {
			gl_FragColor -= ambient;
		}
		if(mod(diff_ind, 2) != 0) {
			gl_FragColor -= attenuation * diffuse;
		} 
		if(mod(spec_ind, 2) != 0) {
			gl_FragColor -= attenuation * specular;
		}

		// on
		if(mod(amb_ind, 2) == 0) {
			gl_FragColor += ambient;
		}
		if(mod(diff_ind, 2) == 0) {
			gl_FragColor += attenuation * diffuse;
		} 
		if(mod(spec_ind, 2) == 0) {
			gl_FragColor += attenuation * specular;
		}
		if(mod(spot_ind, 2) == 0) {
			float spotlight = 0;
			float angle = dot(-LL, -NN);
			if (angle > cos(0.03)) {
				spotlight = angle;
				gl_FragColor += attenuation * spotlight * diffuse;
			}
			else {
				gl_FragColor = ambient * 0.5;
			}
		}
	}
	else {
		gl_FragColor = texture2D(texture, texCoord);
	}	
}
