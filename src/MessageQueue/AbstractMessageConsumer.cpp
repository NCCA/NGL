#include "AbstractMessageConsumer.h"


void AbstractMessageConsumer::setTimeFormat(TimeFormat _f)
{
  switch(_f)
  {
    case TimeFormat::TIME : m_timeString="[%I:%M%p]"; break;
    case TimeFormat::TIMEDATE : m_timeString="[%R %D]"; break;
    case TimeFormat::TIMEDATEDAY : m_timeString="[%c]"; break;
    case TimeFormat::NONE : m_timeString.clear(); break;

  }

}

std::string AbstractMessageConsumer::getTimeString(const  TimeFormat &_t)
{
  std::string time;
  switch(_t)
  {
    case TimeFormat::TIME : time="[%I:%M%p]"; break;
    case TimeFormat::TIMEDATE : time="[%R %D]"; break;
    case TimeFormat::TIMEDATEDAY : time="[%c]"; break;
    case TimeFormat::NONE : time.clear(); break;

  }
  return time;
}


std::string AbstractMessageConsumer::getColourString(const Colours &_colour)
{
  std::string output;
  switch(_colour)
  {
    case Colours::NORMAL : output="\x1B[0m"; break;
    case Colours::RED : output="\x1B[31m"; break;
    case Colours::GREEN : output="\x1B[32m"; break;
    case Colours::YELLOW : output="\x1B[33m"; break;
    case Colours::BLUE : output="\x1B[34m"; break;
    case Colours::MAGENTA : output="\x1B[35m"; break;
    case Colours::CYAN : output="\x1B[36m"; break;
    case Colours::WHITE : output="\x1B[37m"; break;
    case Colours::RESET : output="\033[0m"; break;
  }
  return output;
}

