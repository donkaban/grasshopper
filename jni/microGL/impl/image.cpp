#include "micro.h"

_MODULE("IMAGE");

image::image(strref filename) 
{
    struct
    {
        uint8_t  useless[12];
        uint16_t width;                
        uint16_t height;               
        uint8_t  bits;                
        uint8_t  descriptor;         
    } header;
    stream f(filename);
    f.read((char *) &header, sizeof(header));
    _bpp    = header.bits;
    _width  = header.width;
    _height = header.height;
    if(((_bpp != 24) && (_bpp != 32)) || header.useless[2] != 2)
        ABORT("no support for this tga image format");
    auto size = _bpp * _width * _height / 8;
    _data.resize(size);
    f.read((char *)&_data[0], _data.size());
    for(auto i = _data.begin(); i < _data.end(); i+=_bpp/8)
        std::swap(*i, *(i+2));   
    INFO("create : ", filename,"  ",_width,"x",_height,"x",_bpp);
    auto BPP = (_bpp == 32) ? GL_RGBA : GL_RGB;
    glGenTextures(1,&_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexImage2D(GL_TEXTURE_2D, 0,BPP , _width, _height, 0, BPP, GL_UNSIGNED_BYTE, &_data[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

image::~image()
{
    if(!glIsTexture(getID())) return;
    glDeleteTextures(1, &_id);
}

pixel image::get_pixel(float x, float y)
{
    if(x > 1 || x < 0 || y > 1 || y < 0)
        return {0,0,0,0};
    int bpp = _bpp / 8;
    uint tx  = x * _width;
    int ty  = y * _height;
    int ndx = (tx * bpp) + (ty * _width * bpp);
    return {_data[ndx],_data[ndx+1],_data[ndx+2],_data[ndx+3]};          
};