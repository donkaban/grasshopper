#include "micro.h"
 
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
       stream::~stream()                    {if(_file) close();}
void   stream::close()                      {AAsset_close(_file);} 
void   stream::read(char *buf, size_t size) {AAsset_read (_file,buf,size);}
void   stream::seek(long pos)               {AAsset_seek(_file, pos,SEEK_SET);}
void   stream::init(AAssetManager * am)     {_am = am;}
size_t stream::size() const                 {return _size;}




