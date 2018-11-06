#ifndef FILECONSUMER_H_
#define FILECONSUMER_H_

#include <fstream>
#include <string>
#include "AbstractMessageConsumer.h"

class FileConsumer : public AbstractMessageConsumer
{
  public :
    FileConsumer(const std::string &_fname);
    virtual ~FileConsumer() override;
    bool setFilename(const std::string &_fname);
    virtual void consume(const Message &_message) override;
  private :
    std::ofstream m_output;
};




#endif
