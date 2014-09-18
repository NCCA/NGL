#include <QGLContext>


void* setGL32VisualMac(bool _multisample=true)
{
    static const int Max = 40;
    NSOpenGLPixelFormatAttribute attribs[Max];
    int cnt = 0;

    attribs[cnt++] = NSOpenGLPFAOpenGLProfile;
    attribs[cnt++] = NSOpenGLProfileVersion3_2Core;


    attribs[cnt++] = NSOpenGLPFADoubleBuffer;

    attribs[cnt++] = NSOpenGLPFADepthSize;
    attribs[cnt++] = (NSOpenGLPixelFormatAttribute)16;
    // contributed by Mathieu Le Muzic
    if(_multisample==true)
    {
      // Enable multisampling
      attribs[cnt++] = NSOpenGLPFAMultisample;
      attribs[cnt++] = NSOpenGLPFASampleBuffers;
      attribs[cnt++] = (NSOpenGLPixelFormatAttribute)1;
      attribs[cnt++] = NSOpenGLPFASamples;
      attribs[cnt++] = (NSOpenGLPixelFormatAttribute)4;
    }
    attribs[cnt] = 0;
    Q_ASSERT(cnt < Max);
    NSLog(@"setting gl core visual");

    return [[NSOpenGLPixelFormat alloc] initWithAttributes:attribs];
}
