varying highp vec4 v_position;
uniform vec4 color;
uniform int line_flag;

void main()
{
    if (line_flag == 1) {
        bool in_segment = fract(v_position.y * 5.0) < 0.5;
        if (in_segment) {}
        else
            discard;

        in_segment = fract(v_position.x * 5.0) < 0.5;
        if (in_segment) {}
        else
            discard;

        in_segment = fract(v_position.z * 5.0) < 0.5;
        if (in_segment) {}
        else
            discard;
    }


    gl_FragColor = color;
}
