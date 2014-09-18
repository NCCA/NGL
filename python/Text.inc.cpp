namespace ngl
{

void (Text::*setColourF)(ngl::Real ,ngl::Real ,ngl::Real ) = &Text::setColour;
void (Text::*setColourC)(const ngl::Colour &) = &Text::setColour;

}; // end namespace
