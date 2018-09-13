#include "FileConsumer.h"
#include <iostream>
#include <iomanip>

FileConsumer::FileConsumer(const std::string_view &_fname)
{
  m_output.open(_fname.data());
  // check to see if we can open the file
  if (!m_output.is_open())
  {
    std::cerr <<"Could not open File : "<<_fname<<" for writing \n";
    exit(EXIT_FAILURE);
  }

}

FileConsumer::~FileConsumer()
{
  m_output.close();
}

bool FileConsumer::setFilename(const std::string_view &_fname)
{
  if(m_output.is_open())
  {
    m_output.close();
  }
  m_output.open(_fname.data());
  // check to see if we can open the file
  if (!m_output.is_open())
  {
    std::cerr <<"Could not open File : "<<_fname<<" for writing \n";
    return false;
  }
  else return true;
}

void FileConsumer::consume(const message &_message)
{

  // put_time returns a " " if time string is empty which is annoying!
  if(_message.timeFormat !=TimeFormat::NONE)
  {
    std::time_t tm = std::chrono::system_clock::to_time_t(_message.time);
    setTimeFormat(_message.timeFormat);
    m_output<<std::put_time(std::localtime(&tm),m_timeString.c_str())<<' '<<  _message.message<<'\n';
  }
  else
  {
    m_output<<_message.message<<'\n';
  }
}
