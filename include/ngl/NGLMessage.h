/*
  Copyright (C) 2022 Jon Macey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef NGLMESSAGE_H_
#define NGLMESSAGE_H_
#include <chrono>
#include <fstream>
#include <future>
#include <string>
#include <vector>
namespace ngl
{

enum class Colours : char
{
  NORMAL,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
  RESET
};
enum class TimeFormat : char
{
  NONE,
  TIME,
  TIMEDATE,
  TIMEDATEDAY
};

struct Message
{
  Message(std::chrono::system_clock::time_point _time, std::string _msg, Colours _c, TimeFormat _t)
  {
    time = _time;
    message = _msg;
    colour = _c;
    timeFormat = _t;
  }
  std::chrono::system_clock::time_point time;
  std::string message;
  Colours colour = Colours::NORMAL;
  TimeFormat timeFormat = TimeFormat::TIME;
};

class NGLMessage
{
public:
  static NGLMessage &init();
  static void addMessage(std::string_view _message, Colours _c = Colours::NORMAL, TimeFormat _timeFormat = TimeFormat::TIME);
  static void addError(std::string_view _message, TimeFormat _timeFormat = TimeFormat::TIME);
  static void addWarning(std::string_view _message, TimeFormat _timeFormat = TimeFormat::TIME);
  static void drawLine(const Colours &_c = Colours::CYAN);
  ~NGLMessage();
private:
  NGLMessage();
  static std::vector< Message > s_messageQueue;
  static std::future< void > s_futureExit;
  void consume(const Message &_message);
  void setTimeFormat(TimeFormat _f);
  static std::string getTimeString(const TimeFormat &_t)  ;
  static std::string getColourString(const Colours &_colour) ;
  std::string m_timeString = "%I:%M%p";
  static Colours s_currentColour;
  static std::ofstream s_logFile;
};

} // namespace ngl

#endif