#ifndef __GRASSHOPPER_LOGGER__
#define __GRASSHOPPER_LOGGER__

#include <android/log.h>

#include <iostream>
#include <cstdlib>
#include <sstream>

#define _MODULE(tag) static auto LOCAL_LOGGER = std::make_shared<logger>(tag)

#define INFO(...)  LOCAL_LOGGER->info(__VA_ARGS__) 
#define ERROR(...) LOCAL_LOGGER->error(__VA_ARGS__) 
#define PRINT(...) LOCAL_LOGGER->print(__VA_ARGS__)
#define ABORT(...) LOCAL_LOGGER->fatal(__VA_ARGS__) 

using strref = const std::string &;

class logger
{
public:
  
    logger(strref tag = "[LOG]") : 
        _tag(tag) 
    {}
    ~logger() 
    {}

    template<typename ... T> 
    void message(strref prefix, T && ... a)
    {
        _prn(a...);
        __android_log_print(ANDROID_LOG_DEBUG,"[GRASSHOPPER]","[%s] %s",_tag.c_str(),_ss.str().c_str());
        _ss.str("");
    }
    template<typename ... T> 
    void print(T && ... a) 
    {
        _prn(a...);
        gui(_ss.str());
        _ss.str("");
    }
    template<typename ... T> void info(T && ... a)  {message("[I]", a...);} 
    template<typename ... T> void error(T && ... a) {message("[E]", a...);} 
    template<typename ... T> void fatal(T && ... a) {message("[F]", a...); std::abort();} 
   
private:
    std::string       _tag;
    std::stringstream _ss;
    
    void _prn() {_ss << std::endl;}
    
    template <typename T> 
    void _prn(const T &t) {_ss << t << std::endl;}
    
    template <typename T, typename... A> 
    void _prn(const T &head, const A&... tail) {_ss << head;_prn(tail...); }
    
    void gui(strref);

};
#endif