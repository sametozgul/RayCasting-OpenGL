#version 460 core
out vec4 frag_colour;

uniform float blue = 0.0;
void main()
{
    frag_colour = vec4 (1.0, 0.0, blue, 1.0);
            // use z position to shader darker to help perception of distance
}
