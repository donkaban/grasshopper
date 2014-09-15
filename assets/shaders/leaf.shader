varying vec3   v_uv;
uniform float u_time;

#ifdef VERTEX
    attribute vec3 position;
    attribute vec3 uv;
    attribute vec3 normal;
    
    uniform mat4 u_model;
    uniform mat4 u_prj;    
    uniform mat4 u_view; 

    void main()
    {
        vec4 pos = vec4(position,1); 
        pos.x += sin(u_time) * uv.z;
        pos.z += cos(u_time) * uv.z;
        
        v_uv = uv;    
        gl_Position = pos * u_model * u_view * u_prj ;
    }
#endif

#ifdef FRAGMENT
    void main() 
    {
        gl_FragColor = vec4(v_uv.y,v_uv.y+v_uv.z ,.2,1);
    }
#endif
