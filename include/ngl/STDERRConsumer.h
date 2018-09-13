#ifndef STDERRCONSUMER_H_
#define STDERRCONSUMER_H_
#include <iostream>
#include <iomanip>
#include "AbstractMessageConsumer.h"

class StdErrConsumer : public AbstractMessageConsumer
{
  public :
    StdErrConsumer()=default;
    virtual void consume(const message &_message) override;
};


void StdErrConsumer::consume(const message &_message)
{

  // put_time returns a " " if time string is empty which is annoying!
  if(_message.timeFormat !=TimeFormat::NONE)
  {
    setTimeFormat(_message.timeFormat);
    std::time_t tm = std::chrono::system_clock::to_time_t(_message.time);
    std::cerr<<getColourString(_message.colour)<<std::put_time(std::localtime(&tm),m_timeString.c_str())<<' '<<  _message.message<<'\n';
  }
  else
  {
    std::cerr<<getColourString(_message.colour)<<  _message.message<<'\n';
  }
}


#endif
