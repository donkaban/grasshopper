#ifndef __GRASSHOPPER_COMMON__
#define __GRASSHOPPER_COMMON__

#include <iostream>
#include <functional>
#include <algorithm>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <cstring>
#include <cmath>
#include <chrono>

#include <android/log.h>
#include <android/asset_manager.h>
#include <GLES2/gl2.h>

using strref = const std::string &;

#define TAG "[GRASSHOPPER]"
#define D_LOG(...)  __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__)
#define E_LOG(...)  __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
#define FATAL(...)  {E_LOG(__VA_ARGS__); exit(-1);}

struct stream
{
public:
    stream(strref);
   ~stream();

    void open(strref);
    void close();
    void read(char *, size_t);
    void seek(long pos);
    size_t size() const;
    std::string str();

static void init(AAssetManager *);

private:
    static AAssetManager * _am;
    AAsset * _file;
    size_t   _size {};
};

struct image 
{
public:
    image(strref);
   ~image();

private:    
    std::vector<uint8_t> _data;
    size_t _bpp;    
    size_t _width;   
    size_t _height;
};

#endif



