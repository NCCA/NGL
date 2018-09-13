#ifndef FILECONSUMER_H_
#define FILECONSUMER_H_

#include <fstream>
#include <string_view>
#include "AbstractMessageConsumer.h"

class FileConsumer : public AbstractMessageConsumer
{
  public :
    FileConsumer(const std::string_view &_fname);
    virtual ~FileConsumer() override;
    bool setFilename(const std::string_view &_fname);
    virtual void consume(const message &_message) override;
  private :
    std::ofstream m_output;
};




#endif
