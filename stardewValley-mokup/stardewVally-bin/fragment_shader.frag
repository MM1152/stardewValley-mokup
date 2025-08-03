uniform sampler2D u_texture;
uniform float darkness;

void main()
{
    vec4 color = texture2D(u_texture, gl_TexCoord[0].xy);
    vec3 darkened = color.rgb * (1.0 - darkness);
    gl_FragColor = vec4(darkened, color.a);
}