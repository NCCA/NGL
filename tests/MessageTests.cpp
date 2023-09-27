#include <gtest/gtest.h>
#include <array>
#include <string>
#include <thread>
#include <ngl/NGLMessage.h>



TEST(NGLMessage,addMessage)
{
    ngl::NGLMessage::addMessage("Message");
    ngl::NGLMessage::addWarning("Warning");
    ngl::NGLMessage::addError("Error");
    ngl::NGLMessage::drawLine();
}

TEST(NGLMessage,colours)
{
    ngl::NGLMessage::drawLine(ngl::Colours::RED);
    ngl::NGLMessage::drawLine(ngl::Colours::GREEN);
    ngl::NGLMessage::drawLine(ngl::Colours::YELLOW);
    ngl::NGLMessage::drawLine(ngl::Colours::BLUE);
    ngl::NGLMessage::drawLine(ngl::Colours::MAGENTA);
    ngl::NGLMessage::drawLine(ngl::Colours::CYAN);
    ngl::NGLMessage::drawLine(ngl::Colours::WHITE);
    ngl::NGLMessage::drawLine(ngl::Colours::RESET);
}

TEST(NGLMessage,timeformats)
{
    ngl::NGLMessage::addMessage("None",ngl::Colours::RED,ngl::TimeFormat::NONE);
    ngl::NGLMessage::addMessage("Time",ngl::Colours::RED,ngl::TimeFormat::TIME);
    ngl::NGLMessage::addMessage("Time Data",ngl::Colours::RED,ngl::TimeFormat::TIMEDATE);
    ngl::NGLMessage::addMessage("Time Date Day",ngl::Colours::RED,ngl::TimeFormat::TIMEDATEDAY);
}
