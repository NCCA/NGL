#include "Logger.h"
#include <cstdarg>
#include <vector>
//#include <pthread.h>
//#include <QtCore/QMutexLocker>
#include <boost/format.hpp>


namespace ngl
{
// PIMPL Idiom to make lib cleaner
class Logger::Impl
{

public:
  bool          m_logFileAndConsole;
  bool          m_logFile;
  bool          m_logConsole;
  bool          m_timeStamp;
  bool          m_lineNumber;
  bool          m_disableColours;
  Colours       m_colour;
  char x;
  std::ofstream m_file;
  std::string   m_timeString;
  std::string   m_logfileName;
  unsigned int  m_lineNumberCount;
  unsigned int  m_pad;
  TeeStream     m_output;

  Impl(const std::string& _fname) noexcept;
  void write(const std::string& _text) noexcept;
  void        writeLineNumber() noexcept;
  void        writeTimeStamp() noexcept;
  std::string currentTime() noexcept;
  void setColour(Colours c) noexcept;
};


Logger::Impl::Impl(const std::string& _fname) noexcept
: m_logFileAndConsole(false),
  m_logFile(true),
  m_logConsole(false),
  m_timeStamp(true),
  m_lineNumber(true),
  m_disableColours(false),
  m_colour(Colours::RESET),
  m_logfileName(_fname),
  m_lineNumberCount(0),
  m_pad(4)
{

  m_file.open(m_logfileName.c_str());
  if (!m_file.is_open())
  {
    std::cerr << "error opening log file for writing\n";
    exit(EXIT_FAILURE);
  }
  Tee tee(std::cout, m_file);

  m_output.open(tee);
  m_output.set_auto_close(true);

  if (!m_output.is_open())
  {
    std::cerr << "problem opening log stream tee\n";
    exit(EXIT_FAILURE);
  }
  m_timeString = "%I:%M%p";
}
std::string Logger::Impl::currentTime() noexcept
{
  std::string timeStr;
  time_t      rawTime;
  struct tm*  timeinfo;
  char        buffer[80];
  time(&rawTime);
  timeStr  = ctime(&rawTime);
  timeinfo = localtime(&rawTime);
  //without the newline character
  strftime(buffer, 80, m_timeString.c_str(), timeinfo);
  return buffer;
}


void Logger::Impl::writeLineNumber() noexcept
{
  setColour(m_colour);
  if (m_lineNumber == true)
  {
    std::string st = boost::str(boost::format("%%0%dd") % m_pad);
    std::string t  = boost::str(boost::format(st.c_str()) % ++m_lineNumberCount);
    m_output << t << " ";
  }
}
void Logger::Impl::writeTimeStamp() noexcept
{
  setColour(m_colour);

  if (m_timeStamp == true)
  {
    m_output << currentTime() << " ";
  }
}

void Logger::Impl::write(const std::string& _text) noexcept
{
  setColour(m_colour);
  m_output << _text;
}

// from http://stackoverflow.com/questions/3585846/color-text-in-terminal-aplications-in-unix
void Logger::Impl::setColour(Colours c) noexcept
{
  if (m_disableColours) return;

  switch (c)
  {
    case Colours::CNORMAL: m_output << "\x1B[0m"; break;
    case Colours::RED: m_output << "\x1B[31m"; break;
    case Colours::GREEN: m_output << "\x1B[32m"; break;
    case Colours::YELLOW: m_output << "\x1B[33m"; break;
    case Colours::BLUE: m_output << "\x1B[34m"; break;
    case Colours::MAGENTA: m_output << "\x1B[35m"; break;
    case Colours::CYAN: m_output << "\x1B[36m"; break;
    case Colours::WHITE: m_output << "\x1B[37m"; break;
    case Colours::RESET: m_output << "\033[0m"; break;
  }
}


Logger::Logger() noexcept
: m_impl(new Logger::Impl("output.log"))
{
  m_impl->setColour(Colours::BLUE);
  m_impl->m_output << "Logger started " << m_impl->currentTime() << "\n";
  m_impl->setColour(Colours::RESET);
}

Logger::Logger(const std::string& _fname) noexcept
: m_impl(new Logger::Impl(_fname))
{
  m_impl->setColour(Colours::BLUE);
  m_impl->m_output << "Logger started " << m_impl->currentTime() << "\n";
  m_impl->setColour(Colours::RESET);
}

Logger::~Logger()
{
  m_impl->setColour(Colours::RESET);
  m_impl->m_output << "\n";
  m_impl->m_output.flush();
  m_impl->m_output.close();
}

void Logger::close() noexcept
{
  m_impl->setColour(Colours::RESET);
  m_impl->m_output << "\n";
  m_impl->m_output.flush();
  m_impl->m_output.close();
}


void Logger::logMessage(const char* fmt, ...) noexcept
{
  // create a mutux to stop other threads accessing
  // QMutex m;
  // the locker will auto unlock when out of scope
  //QMutexLocker locker(&m);

  //    pthread_mutex_lock (&m_impl->m_mutex);
  m_impl->writeLineNumber();
  m_impl->writeTimeStamp();
  char    buffer[1024];
  va_list args;
  va_start(args, fmt);
  vsprintf(buffer, fmt, args);
  std::string text = buffer;
  va_end(args);
  m_impl->write(text);
  fflush(stdout);
  //    pthread_mutex_unlock(&m_impl->m_mutex);
}

void Logger::logError(const char* fmt, ...) noexcept
{
  // create a mutux to stop other threads accessing
  //  QMutex m;
  // the locker will auto unlock when out of scope
  //  QMutexLocker locker(&m);

  //    pthread_mutex_lock (&m_impl->m_mutex);
  m_impl->writeLineNumber();
  m_impl->writeTimeStamp();
  char    buffer[1024];
  va_list args;
  va_start(args, fmt);
  vsprintf(buffer, fmt, args);
  m_impl->setColour(Colours::RED);
  m_impl->m_output << "[ERROR] ";
  std::string text = buffer;
  va_end(args);
  m_impl->write(text);
  fflush(stdout);
  //    pthread_mutex_unlock(&m_impl->m_mutex);
}

void Logger::logWarning(const char* fmt...) noexcept
{
  //   pthread_mutex_lock (&m_impl->m_mutex);
  // create a mutux to stop other threads accessing
  //   QMutex m;
  // the locker will auto unlock when out of scope
  //   QMutexLocker locker(&m);
  m_impl->writeLineNumber();
  m_impl->writeTimeStamp();
  char    buffer[1024];
  va_list args;
  va_start(args, fmt);
  vsprintf(buffer, fmt, args);
  m_impl->setColour(Colours::GREEN);
  m_impl->m_output << "[Warning] ";
  std::string text = buffer;
  va_end(args);
  m_impl->write(text);
  fflush(stdout);
  //    pthread_mutex_unlock(&m_impl->m_mutex);
}


void Logger::enableLogToFile() noexcept
{
  m_impl->m_logFile = true;
}
void Logger::disableLogToFile() noexcept
{
  m_impl->m_logFile = false;
}
void Logger::enableLogToConsole() noexcept
{
  m_impl->m_logConsole = true;
}
void Logger::disableLogToConsole() noexcept
{
  m_impl->m_logConsole = false;
}
void Logger::enableLogToFileAndConsole() noexcept
{
  m_impl->m_logConsole = true;
  m_impl->m_logFile    = true;
}
void Logger::disableLogToFileAndConsole() noexcept
{
  m_impl->m_logConsole = false;
  m_impl->m_logFile    = false;
}
void Logger::setLogFile(const std::string& _fname) noexcept
{
  // close the file
  m_impl->m_output.flush();
  m_impl->m_output.close();

  m_impl->m_file.close();
  m_impl->m_logfileName = _fname;
  m_impl->m_file.open(m_impl->m_logfileName.c_str());
  if (!m_impl->m_file.is_open())
  {
    std::cerr << "error opening log file for writing\n";
    exit(EXIT_FAILURE);
  }
  Tee tee(std::cout, m_impl->m_file);

  m_impl->m_output.open(tee);
  m_impl->m_output.set_auto_close(true);

  if (!m_impl->m_output.is_open())
  {
    std::cerr << "problem opening log stream tee\n";
    exit(EXIT_FAILURE);
  }
}
void Logger::setColour(Colours _c) noexcept
{
  m_impl->m_colour = _c;
}
void Logger::enableLineNumbers() noexcept
{
  m_impl->m_lineNumber = true;
}
void Logger::disableLineNumbers() noexcept
{
  m_impl->m_lineNumber = false;
}
void Logger::enableTimeStamp() noexcept
{
  m_impl->m_timeStamp = true;
}
void Logger::disableTimeStamp() noexcept
{
  m_impl->m_timeStamp = false;
}

void Logger::disableColours() noexcept
{
  m_impl->m_disableColours = true;
}

void Logger::enableColours() noexcept
{
  m_impl->m_disableColours = false;
}

void Logger::setLineNumberPad(unsigned int _i) noexcept
{
  m_impl->m_pad = _i;
}

boost::iostreams::stream<Logger::Tee>& Logger::cout() noexcept
{
  return m_impl->m_output;
}

//Fri Nov 21 12:20:09 2014
void Logger::setTimeFormat(TimeFormat _f) noexcept
{
  switch (_f)
  {
    case TimeFormat::TIME: m_impl->m_timeString        = "%I:%M%p"; break;
    case TimeFormat::TIMEDATE: m_impl->m_timeString    = "%R %D"; break;
    case TimeFormat::TIMEDATEDAY: m_impl->m_timeString = "%c"; break;
  }
}
}
