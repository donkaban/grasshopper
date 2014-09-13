#include "common.h"

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
        FATAL("no support for this image format");
    auto size = _bpp * _width * _height / 8;
    _data.resize(size);
    f.read((char *)&_data[0], _data.size());
    for(auto i = _data.begin(); i < _data.end(); i+=_bpp/8)
        std::swap(*i, *(i+2));   
    INFO("create texture '%s' %dx%dx%d",filename.c_str(), _width,_height,_bpp);
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
