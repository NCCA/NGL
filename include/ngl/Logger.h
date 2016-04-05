#ifndef LOGGER_H_
#define LOGGER_H_
#include "Types.h"
#include "Singleton.h"
#include <memory>
#include <cstdarg>
#include <iostream>
#include <ostream>
#include <fstream>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/tee.hpp>

/// @brief logger class for writing to stream and file.
namespace ngl
{
  enum class Colours : char {CNORMAL,RED,GREEN ,YELLOW,BLUE,MAGENTA,CYAN,WHITE,RESET};
  enum class TimeFormat : char {TIME,TIMEDATE,TIMEDATEDAY};

  class NGL_DLLEXPORT Logger : public  Singleton<Logger>
  {
    friend class Singleton<Logger>;

    public :

      void logMessage(const char* fmt, ...) noexcept;
      void logError(const char* fmt, ...) noexcept;
      void logWarning(const char* fmt, ...) noexcept;
      void close() noexcept;
      void enableLogToFile() noexcept;
      void disableLogToFile() noexcept;
      void enableLogToConsole() noexcept;
      void disableLogToConsole() noexcept;
      void enableLogToFileAndConsole() noexcept;
      void disableLogToFileAndConsole() noexcept;
      void setLogFile(const std::string &_fname) noexcept;
      void setColour(Colours _c) noexcept;
      void enableLineNumbers() noexcept;
      void disableLineNumbers() noexcept;
      void enableTimeStamp() noexcept;
      void disableTimeStamp() noexcept;
      void disableColours() noexcept;
      void enableColours() noexcept;
      void setLineNumberPad(unsigned int i) noexcept;
      void setTimeFormat(TimeFormat _f) noexcept;
      typedef boost::iostreams::tee_device<std::ostream, std::ofstream > Tee;
      typedef boost::iostreams::stream<Tee> TeeStream;
      boost::iostreams::stream<Logger::Tee> &cout() noexcept;

    private :
      Logger() noexcept;
      Logger(const std::string &_fname) noexcept;
      ~Logger();

      class Impl;
      std::unique_ptr<Impl> m_impl;


  };

} // end namespace

#endif
