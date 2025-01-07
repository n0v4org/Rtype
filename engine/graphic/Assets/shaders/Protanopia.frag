uniform sampler2D texture;

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec4 pixtel = vec4(gl_Color.r * pixel.r * 0.56667 + gl_Color.g * pixel.g * 0.43333 + gl_Color.b * pixel.b * 0.0,
                       gl_Color.r * pixel.r * 0.55833 + gl_Color.g * pixel.g * 0.44167 + gl_Color.b * pixel.b * 0.0,
                       gl_Color.r * pixel.r * 0.0 + gl_Color.g * pixel.g * 0.24167 + gl_Color.b * pixel.b * 0.75833,
                       gl_Color.a);
    gl_FragColor = pixtel * pixel;
}