#define CATCH_CONFIG_MAIN

#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <catch2/catch_session.hpp>

#ifndef TESTMODE
  #define TESTMODE
#endif

#ifndef NO_LOG
  #define NO_LOG
#endif

int main(int argc, char* argv[])
{
    Catch::Session session;

    int returnCode = session.applyCommandLine( argc, argv );

    if (returnCode != 0) { // invalid CLI args
        return returnCode;
    } else {
        return session.run();
    }
}