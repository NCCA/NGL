#include <gtest/gtest.h>
#include <array>
#include <string>
#include <thread>
#include <ngl/NGLMessage.h>


TEST(NGLMessage,defaultctor)
{
   {
    ngl::NGLMessage message(ngl::NGLMessage::Mode::CLIENTSERVER,ngl::CommunicationMode::FILE);
    EXPECT_TRUE(message.getMode()==ngl::NGLMessage::Mode::CLIENTSERVER);
  }


}

TEST(NGLMessage,addMessage)
{
  ngl::NGLMessage message(ngl::NGLMessage::Mode::SERVER);
  message.addMessage("test message");
  EXPECT_TRUE(message.numMessages()==1);
  message.clearMessageQueue();
}

TEST(NGLMessage,stdOut)
{
  ngl::NGLMessage message(ngl::NGLMessage::Mode::SERVER,ngl::CommunicationMode::STDOUT);
  message.addMessage("test message to std out");
  EXPECT_TRUE(message.numMessages()==1);
  ngl::NGLMessage::startMessageConsumer();
  while(ngl::NGLMessage::numMessages() !=0)
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

  ngl::NGLMessage::stopMessageConsumer();
  EXPECT_TRUE(message.numMessages()==0);

}


TEST(NGLMessage,writeOutput)
{
  ngl::NGLMessage message(ngl::NGLMessage::Mode::CLIENT);

  ngl::NGLMessage::startMessageConsumer();
  for(size_t i=97; i<97+26; ++i)
  {
    std::string msg="test message ";
    msg+=std::to_string(i);
    message.addMessage(msg,Colours::NORMAL,TimeFormat::TIME);
    message.addMessage(msg,Colours::RED);
    message.addMessage(msg,Colours::GREEN);
    message.addMessage(msg,Colours::YELLOW,TimeFormat::TIMEDATE);
    message.addMessage(msg,Colours::BLUE);

    message.addMessage(msg,Colours::MAGENTA,TimeFormat::TIMEDATEDAY);
    message.addMessage(msg,Colours::CYAN);
    message.addMessage(msg,Colours::WHITE,TimeFormat::NONE);
    message.addMessage(msg,Colours::RESET,TimeFormat::NONE);

  }
  while(ngl::NGLMessage::numMessages() !=0)
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

  ngl::NGLMessage::stopMessageConsumer();
  EXPECT_TRUE(message.numMessages()==0);

}

TEST(NGLMessage,nullConsumer)
{
  ngl::NGLMessage message(ngl::NGLMessage::Mode::SERVER,ngl::CommunicationMode::NULLCONSUMER);
  ngl::NGLMessage::startMessageConsumer();
  for(size_t i=97; i<97+26; ++i)
  {
    std::string msg="test message ";
    msg+=std::to_string(i);
    message.addMessage(msg,Colours::NORMAL,TimeFormat::TIME);
    message.addMessage(msg,Colours::RED);
    message.addMessage(msg,Colours::GREEN);
    message.addMessage(msg,Colours::YELLOW,TimeFormat::TIMEDATE);
    message.addMessage(msg,Colours::BLUE);

    message.addMessage(msg,Colours::MAGENTA,TimeFormat::TIMEDATEDAY);
    message.addMessage(msg,Colours::CYAN);
    message.addMessage(msg,Colours::WHITE);
    message.addMessage(msg,Colours::RESET);

  }
  while(ngl::NGLMessage::numMessages() !=0)
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

  ngl::NGLMessage::stopMessageConsumer();
  EXPECT_TRUE(message.numMessages()==0);
}


TEST(NGLMessage,fileConsumer)
{
  ngl::NGLMessage message(ngl::NGLMessage::Mode::SERVER,ngl::CommunicationMode::FILE);
  ngl::NGLMessage::startMessageConsumer();
  for(size_t i=97; i<97+26; ++i)
  {
    std::string msg="test message ";
    msg+=std::to_string(i);
    message.addMessage(msg,Colours::NORMAL,TimeFormat::TIME);
    message.addMessage(msg,Colours::RED);
    message.addMessage(msg,Colours::GREEN);
    message.addMessage(msg,Colours::YELLOW,TimeFormat::TIMEDATE);
    message.addMessage(msg,Colours::BLUE);

    message.addMessage(msg,Colours::MAGENTA,TimeFormat::TIMEDATEDAY);
    message.addMessage(msg,Colours::CYAN);
    message.addMessage(msg,Colours::WHITE,TimeFormat::TIMEDATEDAY);
    message.addMessage(msg,Colours::RESET,TimeFormat::TIMEDATEDAY);

  }
  while(ngl::NGLMessage::numMessages() !=0)
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

  ngl::NGLMessage::stopMessageConsumer();
  EXPECT_TRUE(message.numMessages()==0);
}





TEST(NGLMessage,fileConsumerFromFileName)
{
  ngl::NGLMessage message(ngl::NGLMessage::FromFilename("testFromFilename.out"));
  ngl::NGLMessage::startMessageConsumer();
  for(size_t i=97; i<97+26; ++i)
  {
    std::string msg="test message ";
    msg+=(int)i;
    message.addMessage(msg,Colours::NORMAL,TimeFormat::TIME);
    message.addMessage(msg,Colours::RED);
    message.addMessage(msg,Colours::GREEN);
    message.addMessage(msg,Colours::YELLOW,TimeFormat::TIMEDATE);
    message.addMessage(msg,Colours::BLUE);

    message.addMessage(msg,Colours::MAGENTA,TimeFormat::TIMEDATEDAY);
    message.addMessage(msg,Colours::CYAN);
    message.addMessage(msg,Colours::WHITE,TimeFormat::NONE);
    message.addMessage(msg,Colours::RESET);

  }
  while(ngl::NGLMessage::numMessages() !=0)
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

  ngl::NGLMessage::stopMessageConsumer();
  EXPECT_TRUE(message.numMessages()==0);
}


TEST(NGLMessage,fileConsumerChangeFileName)
{
  ngl::NGLMessage message(ngl::NGLMessage::FromFilename("testFromFilename.out"));
  ngl::NGLMessage::startMessageConsumer();
  for(size_t i=97; i<97+26; ++i)
  {
    std::string msg="test message ";
    msg+=std::to_string(i);
    message.addMessage(msg,Colours::NORMAL,TimeFormat::TIME);
    message.addMessage(msg,Colours::RED);
    message.addMessage(msg,Colours::GREEN);
    message.addMessage(msg,Colours::YELLOW,TimeFormat::TIMEDATE);
    message.addMessage(msg,Colours::BLUE);

    message.addMessage(msg,Colours::MAGENTA,TimeFormat::TIMEDATEDAY);
    message.addMessage(msg,Colours::CYAN);
    message.addMessage(msg,Colours::WHITE,TimeFormat::NONE);
    message.addMessage(msg,Colours::RESET);
    std::string fname="testChange"+std::to_string(i)+".out";
    message.setFilename(fname);
  }
  while(ngl::NGLMessage::numMessages() !=0)
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

  ngl::NGLMessage::stopMessageConsumer();
  EXPECT_TRUE(message.numMessages()==0);
}



TEST(NGLMessage,testMultiThread)
{
  ngl::NGLMessage message(ngl::NGLMessage::Mode::CLIENT);
  message.clearMessageQueue();
  ngl::NGLMessage::stopMessageConsumer();

  auto func=[]()
  {
    for(size_t i=0; i<20; ++i)
    {
      ngl::NGLMessage::addMessage("test threads",Colours::CYAN);
    }
    };
  std::array<std::thread,10> threads;
  for (auto &t : threads)
  {
    t=std::thread(func);
  }
  for (auto &t : threads)
  {
    t.join();
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  ASSERT_EQ(ngl::NGLMessage::numMessages() , 200);
  ngl::NGLMessage::startMessageConsumer();
  while(ngl::NGLMessage::numMessages() !=0)
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

  ngl::NGLMessage::stopMessageConsumer();
  EXPECT_TRUE(message.numMessages()==0);
}

TEST(NGLMessage,testoperator)
{
  ngl::NGLMessage message(ngl::NGLMessage::Mode::CLIENT);
  message.clearMessageQueue();
  message<<"test if this works\n";

  EXPECT_TRUE(message.numMessages()==1);


}

