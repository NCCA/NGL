#include "MessageQueue/PipeConsumer.h"
#include <iostream>
#include <iomanip>
#include <fcntl.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

PipeConsumer::PipeConsumer(const std::string &_fifoName) :m_fifoName(_fifoName)
{
    m_fifoID = open(m_fifoName.c_str(), O_RDWR | O_NONBLOCK);
    if(m_fifoID == -1)
    {
      std::cerr<<"unable to open FIFO\n";
      std::abort();
    }
}

PipeConsumer::~PipeConsumer()
{
  close(m_fifoID);
}

void PipeConsumer::setPipeName(const std::string &_fifoName)
{
  m_fifoName=_fifoName;
}

void PipeConsumer::consume(const message &)
{

}

