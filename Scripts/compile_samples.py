"""MySampler | Scripts/compile_samples.py"""

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

NUM_SAMPLES_PER_CATEGORY = 100

PATH_TO_PIANO960_REPO = pathlib.Path(__file__).resolve().parent.parent.absolute()

ROOT_REPO = pathlib.Path(__file__).resolve().parent.parent.absolute()

PATH_TO_LOG_FILE = PATH_TO_PIANO960_REPO.joinpath('sample-log.json').resolve()

SAMPLE_CATEGORIES = {
  'Guitar': ['guitar', 'guitars'],
  'Keyboard': ['keys', 'key'],
  'Mallet': ['mallet', 'mallets'],
  'Vocal' : ['vocal', 'vocals', 'vo', 'choir', 'choirs'],
  'Strings': ['violin', 'violins', 'strings'],
  'Synth': ['synth', 'synths', 'leads', 'lead'],
  'Texture': ['texture', 'textures'],
  'Bass': ['bass', 'basses', '808'],
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
  'Woodwind': ['woodwind', 'woodwinds', 'oboe', 'clarinet',],
  'Oboe': ['oboe', 'oboes'],
  'Clarinet': ['clarinet', 'clarinets'],
  'Horn': ['horn', 'horns'],
  'Saxophone': ['saxophone', 'saxophones', 'sax'],
  'Glockenspiel': ['glockenspiel', 'glockenspiels'],
  'Tuba': ['tuba', 'tubas'],
  'Trumpet': ['trumpet', 'trumpets', 'horn', 'horns'],
  'Cello': ['cello', 'cellos'],
  'Bassoon': ['bassoon', 'bassoons'],
  'Nature': ['space', 'nebula', 'jwst', 'water', 'leaves', 'wind', 'animal'],
  # TODO: break percussion up into multiple categories
  'Percussion': ['percussion', 'hats', 'hihats', 'hihat', 'toms', 'kick', 'snare', 'crash'],
  'Other': []
}

CATEGORIES_TO_AVOID = (
  'Accent',
  'Percussion',
  'Other'
)

CATEGORY_SAMPLE_COUNTS = {category: 0 for category in SAMPLE_CATEGORIES.keys()}

def generate_sample_paths(sample_packs_directory):

  sample_paths = []
  for filetype in ['mp3', 'wav']:
    sample_paths.extend(pathlib.Path(sample_packs_directory).glob(f"**/*.{filetype}"))

  while sample_paths:
    random_index = random.randint(0, len(sample_paths) - 1)
    yield sample_paths.pop(random_index)

def get_categories(sample_path) -> list:
  path = str(sample_path).lower()
  for deliminator in ('/', ',', '.', '-', '_', '~'):
    path = path.replace(deliminator, ' ')

  categories  = set()

  for category, category_ids in SAMPLE_CATEGORIES.items():
    if category in CATEGORIES_TO_AVOID:
      continue
    for category_identifier in category_ids:
      if category_identifier in path:
        categories.add(category)
        break

  if len(categories) == 0:
    categories.add('Other')

  return categories

def getCategoryDirectory(category, compilation_directory):
  return pathlib.Path(compilation_directory).joinpath(compilation_directory, category)

def compile_samples(installation_directory, sample_packs_directory, print_details=False):
  """
  This function recursively crawls through sample packs and installs them to the given 
  installation directory. Each of the installed files will have a unique ID. The new file 
  names will follow this format: `<Sample-Number>.wav`.
  """
  numSamplesConsidered = 0
  numCompiledSamples = 0

  for sample_number, path_to_sample in enumerate(generate_sample_paths(sample_packs_directory)):
    numSamplesConsidered += 1
    categories = get_categories(path_to_sample)

    if print_details:
      print(f' | #{numSamplesConsidered} sample path: {path_to_sample.relative_to(sample_packs_directory)}')
      print('\n'.join(f' | - {category}' for category in categories))
      print()

    for category in categories:
      if CATEGORY_SAMPLE_COUNTS[category] <= NUM_SAMPLES_PER_CATEGORY:
        relative_path = os.path.relpath(path_to_sample, sample_packs_directory)
        path_components = relative_path.split(os.sep)
        compiled_file_name = '.'.join(path_components)
        compiled_file_path = pathlib.Path(installation_directory).joinpath(category, compiled_file_name)
        
        if print_details: 
          print(f' <> Copying {category} Sample:')
          print(f" <> - from : '{path_to_sample.relative_to(ROOT_REPO)}')")
          print(f" <> -   to : '{compiled_file_path.relative_to(ROOT_REPO)}'")
          print()

        shutil.copy2(path_to_sample, compiled_file_path)
        numCompiledSamples += 1
        CATEGORY_SAMPLE_COUNTS[category] += 1
        break

  if print_details:
    print('\n --- Category Counts ---')
    print('\n'.join(f'   <> ({category}: {count})' for category, count in CATEGORY_SAMPLE_COUNTS.items()))

  print(f'succesfully compiled {numCompiledSamples} samples to {installation_directory}')

def count_existing_samples(compiled_samples_directory):
  for category in CATEGORY_SAMPLE_COUNTS.keys():
    category_directory = os.path.join(compiled_samples_directory, category)
    CATEGORY_SAMPLE_COUNTS[category] = len(os.listdir(category_directory))

def main():
  argument_parser = argparse.ArgumentParser('Piano960 Sample Compilation Script')

  argument_parser.add_argument('--sample-packs',
    help = 'a directory containing samples and packs',
    default = os.path.join(PATH_TO_PIANO960_REPO, 'Sample-Packs')
  )

  argument_parser.add_argument('--compile-to',
    help = 'the directory where all Piano960 samples will be compile to',
    default = os.path.join(PATH_TO_PIANO960_REPO, 'Assets', 'samples')
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
    count_existing_samples(compilation_directory)
    compile_samples(compilation_directory, args.sample_packs, print_details=args.verbose)

  for category in SAMPLE_CATEGORIES.keys():
    category_directory = os.path.join(compilation_directory, category)
    if len(os.listdir(category_directory)) == 0:
      os.rmdir(category_directory)

if __name__ == '__main__': main()
