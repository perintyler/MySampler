/*** MySampler | Source/sample.h ***/

#pragma once

#include <string>
#include <iostream>
#include <filesystem>

#include "notes.h"

/*** 
 ** A locally installed audio file 
 ***/
struct Sample 
{
  std::string name;
  std::filesystem::path filepath;
  Note rootNote;

  void pretty_print() const
  {
      std::cout << "<Sample"
                << " name="     << name
                << " filepath=" << filepath.string()
                << " rootNote=" << std::to_string(rootNote) 
                << ">"          << std::endl;
  }
};
