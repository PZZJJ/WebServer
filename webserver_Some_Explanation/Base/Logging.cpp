#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include "Logging.h"
#include "CurrentThread.h"
#include "Thread.h"
#include "AsynsLogging.h"


static pthread_once_t once_control_ = PTHREAD_ONCE_INIT;
static AsynsLogging *AsynsLogger_;

std::string Logger::logFileName_ = "./WebServer.log";
















