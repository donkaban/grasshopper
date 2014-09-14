varying vec3 v_position;
varying vec3 v_uv;
varying vec3 v_normal;

uniform float       u_time;


#ifdef VERTEX
    attribute vec3 position;
    attribute vec3 uv;
    attribute vec3 normal;

    uniform mat4  u_model;
    uniform mat4  u_prj;    
    uniform mat4  u_iview; 
    void main()
    {
        vec4 pos = vec4(position,1);
        pos.z += uv.z * 0.1;//sin(u_time * 5.0) * 0.5;

        v_uv = uv;
        
        gl_PointSize = 10.;


        gl_Position = pos * u_model * u_iview * u_prj ;
    }
#endif

#ifdef FRAGMENT
    uniform sampler2D   texture0;
        
    void main() 
    {
        vec4 col1 = texture2D(texture0, v_uv.xy);
        gl_FragColor = col1;
    }
#endif
