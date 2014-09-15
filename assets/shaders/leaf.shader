varying vec3  v_uv;
uniform float u_time;

#ifdef VERTEX
    attribute vec3 position;
    attribute vec3 uv;
    attribute vec3 normal;
    uniform mat4  u_model;
    uniform mat4  u_prj;    
    uniform mat4  u_view; 
    void main()
    {
        v_uv = uv;
        vec4 pos = vec4(position,1); 
        pos.x += sin(u_time) * v_uv.z;
        gl_Position = pos * u_model * u_view * u_prj ;
    }
#endif

#ifdef FRAGMENT
    void main() 
    {
        gl_FragColor = vec4(0,v_uv.x * .4,0,1);
    }
#endif
