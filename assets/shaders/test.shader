varying vec3 v_position;
varying vec3 v_uv;
varying vec3 v_tangent;
varying vec3 v_binormal;
varying vec3 v_normal;


#ifdef VERT_SHADER
    attribute vec3 position;
    attribute vec3 uv;
    attribute vec3 tangent;
    attribute vec3 binormal;
    attribute vec3 normal;

    uniform mat4  u_model;
    uniform mat4  u_projection;    
    uniform mat4  u_iview; 
    uniform vec3  u_eye;
    void main()
    {
        v_position = position;
        v_uv = uv;
        v_tangent = tangent;
        v_binormal = binormal;
        v_normal = normal;
        
        gl_Position = vec4(position,1) * u_model * u_projection * u_iview;
    }

#elif FRAG_SHADER)

    uniform sampler2D   texture0;
    uniform sampler2D   texture1;

    void main()
    {
        gl_FragColor = vec4(1,0,0,1);
    }
#endif