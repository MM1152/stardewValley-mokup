// fragment_shader.frag
#version 120
uniform sampler2D texture;
uniform float time;

void main()
{
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);
    float redShift = 0.5 + 0.5 * sin(time);
    gl_FragColor = vec4(color.r * redShift, color.g, color.b, color.a);
}