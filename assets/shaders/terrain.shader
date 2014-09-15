varying vec3 v_pos;
varying vec3 v_uv;
varying vec3 v_norm;
varying vec3 v_light;
varying vec3 v_half;
varying vec3 v_eye;

uniform float u_time;

const vec3 LIGHT_POS = vec3(0,0,-40);

#ifdef VERTEX
    attribute vec3 position;
    attribute vec3 uv;
    attribute vec3 normal;

    uniform mat4  u_model;
    uniform mat4  u_prj;    
    uniform mat4  u_view; 
    uniform vec3 u_eye; 

    void main()
    {
        vec4 p4 = vec4(position,1) * u_model;
        vec3 p3 = vec3(p4);
        mat3 nM = mat3(u_model[0].xyz,u_model[1].xyz,u_model[2].xyz);
        v_uv    = uv;
        v_norm  = normalize(normal * nM);
        v_light = normalize(u_eye - p3);
        v_eye   = normalize(u_eye - p3);
        v_half  = normalize(v_light + v_eye);
        gl_Position = p4 * u_view * u_prj ;
    }
#endif

#ifdef FRAGMENT
    uniform sampler2D   texture0;
        
    void main() 
    {
        vec4 col = texture2D(texture0, v_uv.xy);
        float shadow = max(dot(v_norm,v_light),.2);
        vec3  phong  = reflect(-v_eye,v_norm);
        float spec   = pow(max(dot(v_light,phong),.0), 35.0);
        col *= shadow ;              
        col += spec   ;
        gl_FragColor = col;
    }
#endif
