attribute highp vec4 a_position;

uniform highp mat4 u_projectionMatrix;
uniform highp mat4 u_viewMatrix;
uniform highp mat4 u_modelMatrix;
varying highp vec4 v_position;

void main(void) {
    mat4 mv_matrix = u_viewMatrix * u_modelMatrix;

    gl_Position = u_projectionMatrix * mv_matrix * a_position;

    v_position = a_position;

}
