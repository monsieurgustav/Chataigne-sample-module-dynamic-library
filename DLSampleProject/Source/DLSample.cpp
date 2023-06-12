#include "JuceHeader.h"


// BEGIN CHATAIGNE DYNAMIC LIBRARY DEFINITIONS
#define LOG(textToWrite) JUCE_BLOCK_WITH_FORCED_SEMICOLON (juce::String tempDbgBuf;\
String fullPath = String(__FILE__);\
tempDbgBuf << fullPath.substring (fullPath.lastIndexOfChar (juce::File::getSeparatorChar()) + 1 ,fullPath.lastIndexOfChar('.') ) << "::" <<  textToWrite;\
juce::Logger::writeToLog(tempDbgBuf);)

#define LOGWARNING(textToWrite) JUCE_BLOCK_WITH_FORCED_SEMICOLON (juce::String tempDbgBuf;\
String fullPath = String(__FILE__);\
tempDbgBuf << fullPath.substring (fullPath.lastIndexOfChar (juce::File::getSeparatorChar()) + 1 ,fullPath.lastIndexOfChar('.') ) << "::!!" <<  textToWrite;\
juce::Logger::writeToLog(tempDbgBuf);)

#define LOGERROR(textToWrite) JUCE_BLOCK_WITH_FORCED_SEMICOLON (juce::String tempDbgBuf;\
String fullPath = String(__FILE__);\
tempDbgBuf<< fullPath.substring (fullPath.lastIndexOfChar (juce::File::getSeparatorChar()) + 1 ,fullPath.lastIndexOfChar('.') ) << "::!!!"  <<  textToWrite;\
juce::Logger::writeToLog(tempDbgBuf);)

#define SHARE_LOGGER(logger) Logger::setCurrentLogger(logger)

#define SHARE_OBJECT_PROPERTY(hostStringPool, name) StringPool::getGlobalPool().getPooledString(hostStringPool.getPooledString(name))

#if JUCE_MSVC
#define DLL_EXPORT __declspec (dllexport)
#elif
#define DLL_EXPORT __attribute__ ((visibility("default")))
#endif
// END CHATAIGNE DYNAMIC LIBRARY DEFINITIONS


extern "C" {

DLL_EXPORT var hello(const var::NativeFunctionArgs& args, Logger* logger, StringPool&)
{
    SHARE_LOGGER(logger);
    if (args.numArguments < 1)
    {
        LOGWARNING("Hello? Is there anyone?!");
    }
    else
    {
        LOG("Hello " << args.arguments[0].toString());
    }
    return {};
}

DLL_EXPORT var math(const var::NativeFunctionArgs& args, Logger* logger, StringPool& hostStringPool)
{
    SHARE_LOGGER(logger);
    SHARE_OBJECT_PROPERTY(hostStringPool, "left");  // required to read properties of objects in arguents
    SHARE_OBJECT_PROPERTY(hostStringPool, "right");
    SHARE_OBJECT_PROPERTY(hostStringPool, "sum");  // required to write properties of returned objects
    SHARE_OBJECT_PROPERTY(hostStringPool, "diff");

    if (args.numArguments != 1 || args.arguments[0].isUndefined())
    {
        LOGWARNING("Expects an object parameter");
        return {};
    }
    const DynamicObject* obj = args.arguments[0].getDynamicObject();
    if (!obj || !obj->hasProperty("left") || !obj->getProperty("left").isDouble() || !obj->hasProperty("right") || !obj->getProperty("right").isDouble())
    {
        LOGWARNING("Expects an object like {left: 12, right: 42}");
        return {};
    }

    const double left = obj->getProperty("left");
    const double right = obj->getProperty("right");

    DynamicObject* result = new DynamicObject;
    result->setProperty("sum", left + right);
    result->setProperty("diff", left - right);
    return result;
}

}  // extern "C"
