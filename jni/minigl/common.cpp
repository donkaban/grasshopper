#include "common.h"
 
AAssetManager * stream::_am;

void stream::open(strref filename)
{
    _file = AAssetManager_open(_am,filename.c_str(), AASSET_MODE_UNKNOWN);
    if(!_file)
        FATAL("can't load '%s'",filename.c_str());
    _size = AAsset_getLength(_file);   
}
std::string stream::str()
{
    std::string contents;
    contents.resize(_size);
    read(&contents[0],_size);
    return contents;
}
	   stream::stream(strref filename)      {open(filename);}
	   stream::~stream() 				    {if(_file) close();}
void   stream::close() 					    {AAsset_close(_file);} 
void   stream::read(char *buf, size_t size) {AAsset_read (_file,buf,size);}
void   stream::seek(long pos) 		        {AAsset_seek(_file, pos,SEEK_SET);}
void   stream::init(AAssetManager * am)     {_am = am;}
size_t stream::size() const                 {return _size;}

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
}



