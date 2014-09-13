#include "micro.h"
 
AAssetManager * stream::_am;

std::string stream::str()
{
    std::string contents;
    contents.resize(_size);
    read(&contents[0],_size);
    return contents;
}
stream::stream(strref filename)      
{
    if(!_am)
        FATAL("asset manager hasn't initalized");
    _file = AAssetManager_open(_am,filename.c_str(), AASSET_MODE_UNKNOWN);
    if(!_file)
        FATAL("can't open file '%s'",filename.c_str());
    _size = AAsset_getLength(_file);   
}
stream::~stream()
{
    if(_file) 
        AAsset_close(_file);
}

void   stream::init(AAssetManager * am)     {_am = am;}
void   stream::read(char *buf, size_t size) {AAsset_read (_file,buf,size);}
void   stream::seek(size_t pos)             {AAsset_seek(_file, pos,SEEK_SET);}
size_t stream::size() const                 {return _size;}




