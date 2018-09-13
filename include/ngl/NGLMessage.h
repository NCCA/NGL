#ifndef NGLMESSAGE_H_
#define NGLMESSAGE_H_

#include <chrono>
#include <string>
#include <vector>
#include <ostream>
#include "MessageQueue/AbstractMessageConsumer.h"
namespace ngl
{


enum class CommunicationMode{NULLCONSUMER,STDOUT,STDERR,FILE,TCPIP,NAMEDPIPE,UDP,SHAREDMEMORY};
enum class DataType{NONE,VEC2,VEC3,VEC4,MAT2,MAT3,MAT4,QUATERNION};

class NGLMessage
{

  public :
    enum class Mode  {CLIENT,SERVER,CLIENTSERVER};
    // see here for discussion on why I do this https://stackoverflow.com/questions/5120768/how-to-implement-the-factory-method-pattern-in-c-correctly
    struct FromFilename
    {
      FromFilename(const std::string_view &_name) : m_name(_name){}
      std::string_view m_name;
    };

    struct FromNamedPipe
    {
      FromNamedPipe(const std::string_view &_name, Mode _mode) : m_name(_name),m_mode(_mode){}
      std::string_view m_name;
      Mode m_mode;

    };
    NGLMessage(Mode _mode,CommunicationMode _comMode=CommunicationMode::STDERR);
    NGLMessage(const FromFilename &_fname);
    NGLMessage(const FromNamedPipe &_fname);
    ~NGLMessage();
    static bool isActive()  {return s_active;}
    static Mode getMode()   {return s_mode;}
    static void addMessage(const std::string &_message,Colours _c=Colours::NORMAL,TimeFormat _timeFormat=TimeFormat::TIME);
    static void addMessage(int x, int y,const std::string &_message,Colours _c=Colours::NORMAL);
    static void sendClearTerminal();
    static size_t numMessages()  {return s_messageQueue.size();}
    static void startMessageConsumer();
    static void stopMessageConsumer(){ s_consuming.clear();}

    static bool startServer();
    static void stopServer(){ s_server.clear();}
    void operator <<(const char *msg);
    static void clearMessageQueue();
    void setFilename(const std::string_view &_fname);
  private :
    static bool s_active;
    static Mode s_mode;
    static CommunicationMode s_comMode;
    static std::vector <message> s_messageQueue;
    static std::atomic_flag	 s_consuming;
    static std::atomic_flag	 s_server;
    static std::unique_ptr<AbstractMessageConsumer> m_consumer;
    static bool createFiFo();
    static bool createSocket();
    static bool createSharedMemory();
    static bool createNamedPipeServer();

};



}
#endif
