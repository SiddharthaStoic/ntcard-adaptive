#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#define open _open
#define close _close
#define fdopen _fdopen
#endif

#include "Fcontrol.h"
#include "SignalHandler.h"
#include "StringUtil.h"
#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

bool uncompress_init() {
    signalInit();
    return true;
}