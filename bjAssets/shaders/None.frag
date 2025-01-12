uniform sampler2D tex;

void main()
{
        vec4 c = texture2D(tex, gl_TexCoord[0].xy);
        gl_FragColor = c * gl_Color;
}
