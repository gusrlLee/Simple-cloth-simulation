#version 330 core
out vec4 FragColor;

in vec3 FragPos;  

uniform vec3 viewPos; 

void main()
{
    vec3 lightPos = vec3(1.2f, 1.0f, 2.0f);
    vec3 objectColor = vec3(1.0f, 0.5f, 0.31f);
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
    
    // ambient
    float ambientStrength = 0.6;
    vec3 ambient = ambientStrength * lightColor;

    FragColor = vec4(ambient, 1.0);
} 