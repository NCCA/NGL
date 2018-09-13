#ifndef PIPECONSUMER_H_
#define PIPECONSUMER_H_

#include <fstream>
#include <string_view>
#include "AbstractMessageConsumer.h"

class PipeConsumer : public AbstractMessageConsumer
{
  public :
    PipeConsumer(const std::string_view &_fifoName);
    virtual ~PipeConsumer() override;
    void setPipeName(const std::string_view &_fifoName);
    virtual void consume(const message &_message) override;
  private :
    std::string m_fifoName;
    int m_fifoID;
};




#endif
