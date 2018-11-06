#ifndef ABSTRACTMESSAGECONSUMER_H_
#define ABSTRACTMESSAGECONSUMER_H_
#include <string>
#include <chrono>

enum class Colours : char {NORMAL,RED,GREEN ,YELLOW,BLUE,MAGENTA,CYAN,WHITE,RESET};
enum class TimeFormat : char {NONE,TIME,TIMEDATE,TIMEDATEDAY};

struct Message
{
  std::chrono::system_clock::time_point time;
  std::string message;
  Colours colour=Colours::NORMAL;
  TimeFormat timeFormat=TimeFormat::TIME;
};


class AbstractMessageConsumer
{
  public :

    AbstractMessageConsumer()=default;
    virtual void consume(const Message &_message)=0;
    virtual ~AbstractMessageConsumer()=default;
    AbstractMessageConsumer(const AbstractMessageConsumer &)=delete;
    AbstractMessageConsumer &operator=(AbstractMessageConsumer &)=delete;
    void setTimeFormat(TimeFormat _f);
    static std::string getColourString(const Colours &_colour) ;
    static std::string getTimeString(const  TimeFormat &_t);
  protected :
    std::string getTimeString(const Message &_message);
    std::string m_timeString="%I:%M%p";
    Colours m_activeColour=Colours::NORMAL;

};

class NullMessageConsumer : public AbstractMessageConsumer
{
  public :
    NullMessageConsumer()=default;

    virtual ~NullMessageConsumer()=default;
    virtual void consume(const Message &){;}

};

#endif
