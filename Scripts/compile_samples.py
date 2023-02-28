"""
  Piano960/Scripts/compile_samples.py
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TODO: link files instead of copying files

"""

import os
import pathlib
import shutil
import functools
import operator
import json
import argparse
import random
from typing import Set
import re

NUM_SAMPLES = 500 # TODO: make this a command line argument

PATH_TO_PIANO960_REPO = pathlib.Path(__file__).parent.parent;

PATH_TO_LOG_FILE = PATH_TO_PIANO960_REPO.joinpath('sample-log.json').resolve()

SAMPLE_CATEGORIES = {
  'Guitar': ['guitar', 'guitars'],
  'Keyboard': ['keys', 'key'],
  'Mallet': ['mallet', 'mallets'],
  'Vocal' : ['vocal', 'vocals', 'vo', 'choir', 'choirs'],
  'Voilin': ['violin', 'violins', 'strings'],
  'Synth': ['synth', 'synths', 'leads', 'lead'],
  'Texture': ['texture', 'textures'],
  'Bass': ['bass', 'basses'],
  'Pluck': ['plucked', 'pluck', 'plucks'],
  'World': ['world', 'ethnic'],
  'Bell': ['bell', 'bells'],
  'Accent': ['accent', 'accents'],
  'Flute': ['flute', 'flutes'],
  'SFX': ['sfx', 'fx', 'effect', 'effects', 'noise'],
  'Brass': ['brass'],
  'Pad': ['pad', 'pads'],
  'Trombone': ['trombone', 'trombones'],
  'Arp': ['arp', 'arps'],
  'Piano': ['piano', 'pianos', 'upright', 'grand'],
  'Organ': ['organ', 'organs'],
  'Woodwind': ['woodwind', 'woodwinds'],
  'Glockenspiel': ['glockenspiel', 'glockenspiels'],
  'Trumpet': ['trumpet', 'trumpets', 'horn', 'horns'],
  'Cello': ['cello', 'cellos']
}

CATEGORIES_TO_AVOID = (
  'accents',
)

SAMPLE_PACKS_TO_IGNORE = (
  'eclipse-oneshots-by-kindobands',
)

def is_sample_from_valid_pack(path_to_sample, sample_packs_directory):
  relative_path = os.path.relpath(path_to_sample, sample_packs_directory)
  for pack_to_ignore in SAMPLE_PACKS_TO_IGNORE:
    if relative_path.startswith(pack_to_ignore):
      return False
  return True

def generate_sample_paths(sample_packs_directory):
  sample_paths = list(pathlib.Path(sample_packs_directory).glob(f"**/*.wav"))
  assert len(sample_paths) > 0

  while sample_paths:
    random_index = random.randint(0, len(sample_paths) - 1)
    path_to_sample = sample_paths.pop(random_index)
    if is_sample_from_valid_pack(path_to_sample, sample_packs_directory):
      yield path_to_sample

def get_categories(sample_path) -> list:
  path = str(sample_path).lower()
  for deliminator in ('/', ',', '.', '-', '_', '~'):
    path = path.replace(deliminator, ' ')

  potential_category_identifiers = path.split(' ')
  categorizations  = set()
  for potential_category_id in potential_category_identifiers:
    for category, category_identifiers in SAMPLE_CATEGORIES.items():
      if potential_category_id in category_identifiers:
        categorizations.add(category)

  return categorizations

def valid_category_exists(categories):
  for category in categories:
    if category not in CATEGORIES_TO_AVOID:
      return True
  return False

def compile_samples(installation_directory, sample_packs_directory, print_details=False):
  """
  This function recursively crawls through sample packs and installs them to the given 
  installation directory. Each of the installed files will have a unique ID. The new file 
  names will follow this format: `<Sample-Number>.wav`.
  """
  numCompiledSamples = 0

  for sample_number, path_to_sample in enumerate(generate_sample_paths(sample_packs_directory)):
    if numCompiledSamples >= NUM_SAMPLES: break
    categories = get_categories(path_to_sample)
    if len(categories) == 0:
      print(f'could not categorize {path_to_sample}')
    elif valid_category_exists(categories):
      relative_path = os.path.relpath(path_to_sample, sample_packs_directory)
      path_components = relative_path.split(os.sep)
      compiled_file_name = '.'.join(path_components)
      for category in categories:
        compiled_file_path = os.path.join(installation_directory, category, compiled_file_name)
        shutil.copy2(path_to_sample, compiled_file_path)
      if print_details: print(f'copying {path_to_sample} to {compiled_file_path}')
      numCompiledSamples += 1

  print(f'succesfully compiled {numCompiledSamples} samples to {installation_directory}')

def main():
  argument_parser = argparse.ArgumentParser('Piano960 Sample Compilation Script')

  argument_parser.add_argument('--sample-packs',
    help = 'a directory containing samples and packs',
    default = os.path.join(PATH_TO_PIANO960_REPO, 'Sample-Packs')
  )

  argument_parser.add_argument('--compile-to',
    help = 'the directory where all Piano960 samples will be compile to',
    default = os.path.join(PATH_TO_PIANO960_REPO, 'Resources')
  )

  argument_parser.add_argument('-v', '--verbose', 
    action = 'store_true',
    help = 'use this flag to print out extra information about the compilation'
  )

  args = argument_parser.parse_args()

  compilation_directory = str(pathlib.Path(args.compile_to).resolve())
  sample_packs_directory = str(pathlib.Path(args.sample_packs).resolve())

  stupid_mac_generated_file = os.path.join(compilation_directory, '.DS_Store')
  if os.path.exists(stupid_mac_generated_file): os.remove(stupid_mac_generated_file)

  if not os.path.exists(compilation_directory):
    os.mkdir(compilation_directory)
  elif len(os.listdir(compilation_directory)) > 0 and input("clear samples directory (y/n)?") == 'y':
    for filename in os.listdir(compilation_directory):
      path_to_file = os.path.join(compilation_directory, filename)
      if filename.endswith('.wav'):
        print(f'deleting wav file: {path_to_file}')
        os.remove(path_to_file)
      if os.path.isdir(path_to_file):
        print(f'deleting catagory directory {path_to_file}')
        shutil.rmtree(path_to_file)

  for category in SAMPLE_CATEGORIES.keys():
    category_directory = os.path.join(compilation_directory, category)
    if not os.path.exists(category_directory):
      os.mkdir(category_directory)

  if not os.path.isdir(sample_packs_directory):
    print(f'sample pack path is not a directory ({sample_packs_directory})')
  else:
    compile_samples(compilation_directory, args.sample_packs, print_details=args.verbose)

  for category in SAMPLE_CATEGORIES.keys():
    category_directory = os.path.join(compilation_directory, category)
    if len(os.listdir(category_directory)) == 0:
      os.rmdir(category_directory)

if __name__ == '__main__': main()
