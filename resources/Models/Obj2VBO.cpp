#ifdef LINUX
	#include <GL/glew.h>
	#include <GL/gl.h>
#endif
#ifdef DARWIN
	#include <OpenGL/gl.h>
#endif
const char ARGUMENTS[]="bh";


#include <cstdlib>
#include <unistd.h> // for get opt
#include <iostream>
#include <ngl/Obj.h>

enum Modes{Binary,Header};
int main(int argc, char **argv)
{
if (argc <4)
	{
	std::cerr<<"Usage :- \nObj2VBO -[b/h] Infile.obj OutFile\n";
	exit(EXIT_FAILURE);
	}

int mode=Header;
char c;

while( (c=getopt(argc,argv,ARGUMENTS)) !=EOF)
		{
		 switch(c) // which option has been chosen
    		{
			case 'h' : // -h
	     		mode=Header;
    	  	break;
			case 'b' : // -h
	     		mode=Binary;
    	  	break;
			default : break;
			}
		}

std::cerr<<"Loading Obj"<<std::endl;
ngl::Obj obj(argv[2]);

if(mode == Binary)
	{
	std::cerr<<"Writing Binary VBO file\n";
	obj.WriteVBO(argv[3],ngl::Obj::BINARY);
	}
else
	{
	std::cerr<<"Writing Header VBO file\n";
	obj.WriteVBO(argv[3],ngl::Obj::HEADER);
	}

return EXIT_SUCCESS;
}

