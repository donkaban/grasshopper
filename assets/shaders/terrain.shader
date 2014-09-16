varying vec3 v_uv;
varying vec3 v_eye;
varying float v_dist;


#ifdef VERTEX
    attribute vec3 position;
    attribute vec3 uv;
    attribute vec3 normal;

    uniform mat4 u_model;
    uniform mat4 u_prj;    
    uniform mat4 u_view; 
    uniform vec3 u_eye; 

    void main()
    {
        v_uv    = uv;
        vec4 pos = vec4(position,1) * u_model;
        v_eye   = normalize(u_eye - pos.xyz);
        v_dist = distance(u_eye, pos.xyz);
        gl_Position = pos * u_view * u_prj ;
    }
#endif

#ifdef FRAGMENT
    uniform sampler2D   texture0;
    uniform sampler2D   texture1;
    
        
    void main() 
    {
    
        vec4 col = texture2D(texture0, v_uv.xy);
        vec4 nrm = texture2D (texture1,v_uv.xy);
        vec3 normal = normalize(2.0 * vec3(nrm) - 1.0);
  
        float shadow = max(dot(normal,v_eye),0.0);
        vec3  blinn  = normalize(v_eye + normal);
        vec3  phong  = reflect(-v_eye,normal);
        float spec   = pow(max(dot(v_eye,blinn),0.), 55.0) ;
        
        gl_FragColor = col * shadow + spec;
    }
#endif
