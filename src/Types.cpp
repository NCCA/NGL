#include "Types.h"
#include "NGLMessage.h"
namespace ngl
{
// static Message object for all NGL comms
 std::unique_ptr<NGLMessage> msg;//=std::make_unique<NGLMessage>(NGLMessage(NGLMessage::Mode::CLIENTSERVER,CommunicationMode::STDERR));
}
