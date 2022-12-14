// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - Piano960 | VST3, AU - - - - - - - - - - - - - - - - - - - -
// - - Created by Tyler Perin  - - - - - - - - - - - - - - - - - -
// - - Copyright © 2022 Sound Voyager. All rights reserved.- - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   main_test.cpp
//   ~~~~~~~~~~~~~
//
// This file contains the entry point (i.e. main function) for
// the `piano960-test` build.
//
// TODO: this file shouldn't be neccessary...
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#include <catch2/catch_session.hpp>

int main(int argc, char* argv[]) {
    Catch::Session session;
    return session.run();
}
