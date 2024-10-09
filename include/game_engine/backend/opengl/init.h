#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#if defined(_WIN32)
// #define Context HGLRC
#elif defined(__APPLE__) && defined(__MACH__)
// #define Context NSOpenGLContext
#else
// #define Context GLXContext
#endif

void* createGLContext(void* handle);
void* loadExtension(const char* name);

#endif
