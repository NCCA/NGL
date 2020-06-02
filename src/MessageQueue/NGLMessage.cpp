#include "NGLMessage.h"
#include <thread>
#include <mutex>
#include <atomic>
#include <future>
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sstream>
#include <cstdarg>
#include "fmt/format.h"
#include "MessageQueue/AbstractMessageConsumer.h"
#include "MessageQueue/STDERRConsumer.h"
#include "MessageQueue/STDOutConsumer.h"
#include "MessageQueue/FileConsumer.h"
namespace ngl
{
  std::vector <Message> NGLMessage::s_messageQueue;
  bool NGLMessage::s_consuming=false;
  std::atomic_flag NGLMessage::s_server=ATOMIC_FLAG_INIT;
  std::unique_ptr<AbstractMessageConsumer> NGLMessage::m_consumer=std::make_unique<StdErrConsumer>();
  NGLMessage::Mode NGLMessage::s_mode=Mode::CLIENT;
  static std::mutex g_messageQueueLock;
  static std::mutex g_serverLock;
  std::promise<bool> g_exitSignal;
  std::future<bool> NGLMessage::s_futureExit;
  bool NGLMessage::s_active=true;
  CommunicationMode NGLMessage::s_comMode=CommunicationMode::STDERR;
  Colours NGLMessage::s_currentColour=Colours::NORMAL;
  NGLMessage::NGLMessage(Mode _mode,CommunicationMode _comMode)
  {
    g_exitSignal.set_value(false);
    g_exitSignal = std::promise<bool>();
    s_mode=_mode;
    s_comMode=_comMode;
    s_consuming=true;
    s_server.test_and_set();
    s_futureExit = g_exitSignal.get_future();

    switch (s_comMode)
    {
      case CommunicationMode::STDERR : m_consumer=std::make_unique<StdErrConsumer>(); s_mode=Mode::CLIENTSERVER; break;
      case CommunicationMode::STDOUT : m_consumer=std::make_unique<StdOutConsumer>(); s_mode=Mode::CLIENTSERVER; break;
      case CommunicationMode::NULLCONSUMER : m_consumer=std::make_unique<NullMessageConsumer>(); s_mode=Mode::CLIENTSERVER; break;
      case CommunicationMode::FILE :  m_consumer=std::make_unique<FileConsumer>("NGLMessageDebug.out"); s_mode=Mode::CLIENTSERVER; break;

    }

  }

  void NGLMessage::clearMessageQueue()
  {
    s_messageQueue.clear();
  }


  NGLMessage::~NGLMessage() noexcept
  {
  }

  void NGLMessage::setFilename(const std::string &_fname)
  {
    FileConsumer *f=reinterpret_cast<FileConsumer *>(m_consumer.get());
    if(f!=nullptr)
      f->setFilename(_fname);
  }

  NGLMessage::NGLMessage(const FromFilename &_f)
  {
    s_comMode=CommunicationMode::FILE;
    s_mode=Mode::CLIENTSERVER;
    m_consumer=std::make_unique<FileConsumer>(_f.m_name);

  }


  void NGLMessage::addMessage(const std::string &_message, Colours _c, TimeFormat _timeFormat)
  {
    std::lock_guard<std::mutex> lock(g_messageQueueLock);
    if(_c != s_currentColour)
      s_currentColour=_c;
    // add to front
    s_messageQueue.insert(std::begin(s_messageQueue),{std::chrono::system_clock::now(),_message,s_currentColour,_timeFormat});
    //std::this_thread::sleep_for(std::chrono::milliseconds(4));

  }





  void NGLMessage::operator<<(const char *_message)
  {
    std::lock_guard<std::mutex> lock(g_messageQueueLock);
    s_messageQueue.insert(std::begin(s_messageQueue),{std::chrono::system_clock::now(),_message});
  }



  void NGLMessage::addMessage(int x, int y,const std::string &_message,Colours _c)
  {
    std::lock_guard<std::mutex> lock(g_messageQueueLock);
    if(_c != s_currentColour)
      s_currentColour=_c;
    // add to front
    std::string loc=fmt::format("\033[{0};{1}H",x,y);
    loc+=_message;
    s_messageQueue.insert(std::begin(s_messageQueue),{std::chrono::system_clock::now(),loc,_c,TimeFormat::NONE});

  }



  void NGLMessage::sendClearTerminal()
  {
    std::lock_guard<std::mutex> lock(g_messageQueueLock);
    s_messageQueue.insert(std::begin(s_messageQueue),{std::chrono::system_clock::now(),"\033[2J\033[1;1H"});

  }

  void NGLMessage::startMessageConsumer()
  {
    if(s_mode == Mode::SERVER)
    {
      std::cerr<<"Trying to launch consumer on Server \n";
      return;
    }
    if( s_comMode == CommunicationMode::NULLCONSUMER ||
        s_comMode == CommunicationMode::FILE ||
        s_comMode == CommunicationMode::STDERR ||
        s_comMode == CommunicationMode::STDOUT)
    {
      std::thread t([]()
      {
        while(s_futureExit.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
        {
          std::lock_guard<std::mutex> lock(g_messageQueueLock);
          if(s_messageQueue.size() !=0 && s_consuming)
          {
            auto msg=s_messageQueue.back();
            s_messageQueue.pop_back();
            m_consumer->consume(msg);
          }
        }
      });
      s_active=true;
      t.detach();
     } // client server in one versions

  }

  void NGLMessage::addError(const std::string &_message, TimeFormat _timeFormat)
  {
    auto colour=s_currentColour;
    addMessage(fmt::format("[ERROR] :- {0}",_message),Colours::RED,_timeFormat);
    s_currentColour=colour;
  }
  void NGLMessage::drawLine(const Colours &_c)
  {
    auto colour=s_currentColour;
    addMessage("-------------------------------------------------------------------------------",_c,TimeFormat::NONE);
    s_currentColour=colour;
  }
  void NGLMessage::addWarning(const std::string &_message, TimeFormat _timeFormat)
  {
    auto colour=s_currentColour;
    addMessage(fmt::format("[WARNING] :- {0}",_message),Colours::YELLOW,_timeFormat);
    s_currentColour=colour;
  }


  bool NGLMessage::startServer()
  {
    std::cerr<<"starting server\n";
    if(s_mode !=Mode::SERVER)
    {
      std::cerr<<"Error attempting to start server in Client Mode \n";
      return false;
    }

    else return false;
  }


  void NGLMessage::stopServer()
  {
    s_server.clear();
    g_exitSignal.set_value(false);
    g_exitSignal = std::promise<bool>();
  }


}
