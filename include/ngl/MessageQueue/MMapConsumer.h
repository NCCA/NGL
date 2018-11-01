#ifndef MMAPCONSUMER_H_
#define MMAPCONSUMER_H_

#include <fstream>
#include <string>
#include "AbstractMessageConsumer.h"

class MMapConsumer : public AbstractMessageConsumer
{
  public :
    MMapConsumer(const std::string &_fifoName);
    virtual ~MMapConsumer() override;
    bool setPipeName(const std::string &_fifoName);
    virtual void consume(const message &_message) override;
  private :
    std::string m_fifoName;
    int m_fifoID;
};




#endif
