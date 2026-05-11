#include "glerror.h"
#include <iostream>
#include <GLES3/gl32.h>
#include <cassert>
#include "logutil.h"

using namespace std;

void _check_gl_error(const char *file, int line) {
    GLenum err(glGetError());
    bool gotError = false;

    while (err != GL_NO_ERROR) {
        gotError = true;
        string error;

        switch (err) {
            case GL_INVALID_OPERATION:      error = "INVALID_OPERATION";      break;
            case GL_INVALID_ENUM:           error = "INVALID_ENUM";           break;
            case GL_INVALID_VALUE:          error = "INVALID_VALUE";          break;
            case GL_OUT_OF_MEMORY:          error = "OUT_OF_MEMORY";          break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION";  break;
            default: error = "UNKNOWN"; break;
        }
//#ifdef ANDROID
        LOGE("GLError", "GL_%s - %s:%d", error.c_str(), file, line);
//#else
//        cerr << "GL_" << error.c_str() << " - " << file << ":" << line << endl;
//#endif
        err = glGetError();
    }

    assert(!gotError);
}