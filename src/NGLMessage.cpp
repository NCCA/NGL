#include "NGLMessage.h"
#include <fmt/format.h>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <thread>
namespace ngl
{

std::future< void > NGLMessage::s_futureExit;
static std::mutex g_messageQueueLock;
std::vector< Message > NGLMessage::s_messageQueue;
std::promise< void > g_exitSignal;
Colours NGLMessage::s_currentColour = Colours::NORMAL;
std::ofstream NGLMessage::s_logFile;

NGLMessage::NGLMessage()
{

  s_logFile.open("NGLDebug.log");
  // check to see if we can open the file
  if(!s_logFile.is_open())
  {
    std::cerr << "Could not open File NGLDebug.log for writing \n";
    exit(EXIT_FAILURE);
  }
  s_futureExit = g_exitSignal.get_future();
  std::thread t([this]()
                {
        while(s_futureExit.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
        {
          std::scoped_lock<std::mutex> lock(g_messageQueueLock);
          if(s_messageQueue.size() !=0)
          {
            auto msg=s_messageQueue.back();
            s_messageQueue.pop_back();
            consume(msg);
          }
        } });
  t.detach();
}


void NGLMessage::clear()
{
  g_exitSignal.set_value();
  s_messageQueue.clear();
}

NGLMessage::~NGLMessage()
{
  while(s_messageQueue.size() != 0)
    std::this_thread::sleep_for(std::chrono::microseconds(1));

  s_logFile.close();
}

NGLMessage &NGLMessage::init()
{
  static NGLMessage s_instance = NGLMessage();
  return s_instance;
}

void NGLMessage::consume(const Message &_message)
{
  // put_time returns a " " if time string is empty which is annoying!
  if(_message.timeFormat != TimeFormat::NONE)
  {
    setTimeFormat(_message.timeFormat);
    std::time_t tm = std::chrono::system_clock::to_time_t(_message.time);
    std::cerr << getColourString(_message.colour) << std::put_time(std::localtime(&tm), m_timeString.c_str()) << ' ' << _message.message << '\n';
    s_logFile << std::put_time(std::localtime(&tm), m_timeString.c_str()) << ' ' << _message.message << '\n';
  }
  else
  {
    std::cerr << getColourString(_message.colour) << _message.message << '\n';
    s_logFile << _message.message << '\n';
  }
}

void NGLMessage::setTimeFormat(TimeFormat _f)
{
  switch(_f)
  {
    case TimeFormat::TIME:
      m_timeString = "[%I:%M%p]";
      break;
    case TimeFormat::TIMEDATE:
      m_timeString = "[%R %D]";
      break;
    case TimeFormat::TIMEDATEDAY:
      m_timeString = "[%c]";
      break;
    case TimeFormat::NONE:
      m_timeString.clear();
      break;
  }
}

std::string NGLMessage::getTimeString(const TimeFormat &_t) const
{
  std::string time;
  switch(_t)
  {
    case TimeFormat::TIME:
      time = "[%I:%M%p]";
      break;
    case TimeFormat::TIMEDATE:
      time = "[%R %D]";
      break;
    case TimeFormat::TIMEDATEDAY:
      time = "[%c]";
      break;
    case TimeFormat::NONE:
      time.clear();
      break;
  }
  return time;
}

std::string NGLMessage::getColourString(const Colours &_colour) const
{
  std::string output;
  switch(_colour)
  {
    case Colours::NORMAL:
      output = "\x1B[0m";
      break;
    case Colours::RED:
      output = "\x1B[31m";
      break;
    case Colours::GREEN:
      output = "\x1B[32m";
      break;
    case Colours::YELLOW:
      output = "\x1B[33m";
      break;
    case Colours::BLUE:
      output = "\x1B[34m";
      break;
    case Colours::MAGENTA:
      output = "\x1B[35m";
      break;
    case Colours::CYAN:
      output = "\x1B[36m";
      break;
    case Colours::WHITE:
      output = "\x1B[37m";
      break;
    case Colours::RESET:
      output = "\033[0m";
      break;
  }
  return output;
}


void NGLMessage::addMessage(std::string_view _message, Colours _c, TimeFormat _timeFormat)
{
  std::scoped_lock< std::mutex > lock(g_messageQueueLock);
  if(_c != s_currentColour)
    s_currentColour = _c;
  // add to front
  s_messageQueue.emplace(std::begin(s_messageQueue), Message(std::chrono::system_clock::now(), _message.data(), s_currentColour, _timeFormat));
}

void NGLMessage::addError(std::string_view _message, TimeFormat _timeFormat)
{
  auto colour = s_currentColour;
  addMessage(fmt::format("[ERROR] :- {0}", _message), Colours::RED, _timeFormat);
  s_currentColour = colour;
}
void NGLMessage::drawLine(const Colours &_c)
{
  auto colour = s_currentColour;
  addMessage("-------------------------------------------------------------------------------", _c, TimeFormat::NONE);
  s_currentColour = colour;
}
void NGLMessage::addWarning(std::string_view _message, TimeFormat _timeFormat)
{
  auto colour = s_currentColour;
  addMessage(fmt::format("[WARNING] :- {0}", _message), Colours::YELLOW, _timeFormat);
  s_currentColour = colour;
}

} // end namespace ngl
