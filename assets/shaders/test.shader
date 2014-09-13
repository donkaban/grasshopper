varying vec3 v_position;
varying vec3 v_uv;
varying vec3 v_tangent;
varying vec3 v_binormal;
varying vec3 v_normal;

#ifdef VERTEX
    attribute vec3 position;
    attribute vec3 uv;
    attribute vec3 tangent;
    attribute vec3 binormal;
    attribute vec3 normal;

    uniform mat4  u_model;
    uniform mat4  u_prj;    
    uniform mat4  u_iview; 
    void main()
    {
        v_uv = uv;
        gl_Position = vec4(position,1) * u_model * u_iview * u_prj ;
    }
#endif

#ifdef FRAGMENT
    uniform sampler2D   texture0;
    uniform sampler2D   texture1;
    uniform float       u_time;

    void main() 
    {
        vec4 col1 = texture2D(texture0, v_uv.xy);
        vec4 col2 = texture2D(texture1, v_uv.yx);
        
        gl_FragColor = col1 - col2* sin(u_time);
    }
#endif
