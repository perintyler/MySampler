"""MySampler | Scripts/print_sound_sources.py

This script prints the name of each directory inside 'Assets/samples'. It also
prints the code for the enum decleration and vector assignment, which occurs
inside 'Source/sound_source.h' and 'Source/sound_source.cpp' respectively, using 
the most up to date list of sound sources.
"""

import os
import pathlib

def get_sound_sources(samples_directory):
  sound_sources = []
  for file in samples_directory.iterdir():
    if file.is_dir():
      sound_sources.append(file.stem)
  return sound_sources

def print_sound_sources(samples_directory):
  print('\n'.join(get_sound_sources(samples_directory)) + '\n')

def print_sound_sources_cpp_enum(samples_directory):
  print(
    "enum class SoundSource: int\n{\n    NONE=0,\n"
      + '\n'.join(f'    {sound_source.upper()},' for sound_source in get_sound_sources(samples_directory))
      + '\n};'
      + '\n'
  )

def print_sound_sources_cpp_vector(samples_directory):
  print(
    'const std::vector<std::string> SOUND_SOURCE_STRINGS {\n    "None",\n'
    + '\n'.join(f'    "{sound_source}",' for sound_source in get_sound_sources(samples_directory))
    + '\n};'
    + '\n'
  )


if __name__ == '__main__':
  samples_directory = pathlib.Path(__file__).parent.parent.joinpath('Assets', 'samples').absolute()
  print_sound_sources(samples_directory)
  print_sound_sources_cpp_enum(samples_directory)
  print_sound_sources_cpp_vector(samples_directory)

