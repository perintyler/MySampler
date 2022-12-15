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
from typing import Set

MAX_NUM_SAMPLES = 100

PATH_TO_PIANO960_REPO = pathlib.Path(__file__).parent.parent;

PATH_TO_LOG_FILE = PATH_TO_PIANO960_REPO.joinpath('sample-log.json').resolve()


def generate_WAV_file_paths(sample_pack_directory, print_details=False) -> Set[pathlib.PosixPath]:
  """returns the absolute path of all WAV files contained anywhere inside the sample pack directory""" 
  sample_paths = set()

  def crawl(path_to_directory):
    num_samples_found_in_directory = 0
    for file_name in os.listdir(path_to_directory):
      absolute_path = os.path.join(path_to_directory, file_name)
      if os.path.isdir(absolute_path):
        posix_path = pathlib.Path(absolute_path).resolve()
        crawl(posix_path)
      elif file_name.endswith('.wav'):
        sample_paths.add(absolute_path)
        num_samples_found_in_directory += 1

    if num_samples_found_in_directory: print(f'found {num_samples_found_in_directory} samples in {path_to_directory}')

  crawl(sample_pack_directory)
  return sample_paths

def compile_samples(installation_directory, sample_packs_directory, print_details=False):
  """
  This function recursively crawls through sample packs and installs them to the given 
  installation directory. Each of the installed files will have a unique ID. The new file 
  names will follow this format: `<Sample-Number>.wav`.
  """
  installation_log = {} # name of installed file -> path to the copied audio file
  sample_iterator = enumerate(generate_WAV_file_paths(sample_packs_directory, print_details=print_details))
  for sample_number, path_to_sample in sample_iterator:
    # posix_path = pathlib.Path(path_to_sample)
    # relative_path = posix_path.relative_to(sample_packs_directory)
    # assert posix_path.suffix == '.wav'
    compiled_file_name = f'{sample_number}.wav'
    compiled_file_path = os.path.join(installation_directory, compiled_file_name)
    installation_log[compiled_file_name] = str(path_to_sample)
    # os.symlink(path_to_sample, compiled_file_path)
    shutil.copy2(path_to_sample, compiled_file_path)
    if print_details: print(f'linking {path_to_sample} to {compiled_file_path}')
    if sample_number >= MAX_NUM_SAMPLES: break

  with open(PATH_TO_LOG_FILE, 'w') as logfile:
    json.dump(installation_log, logfile, indent=4)
    if print_details: print(f'refer to {PATH_TO_LOG_FILE} for sample installation logs')

def main():
  argument_parser = argparse.ArgumentParser('Piano960 Sample Installation Script')

  argument_parser.add_argument('--sample-packs',
    help = 'a directory containing samples and packs, which will be installed',
    default = './Piano960-Sample-Packs'
  )

  argument_parser.add_argument('--compile-to',
    help = 'the directory where all Piano960 samples will be installed to',
    default = './Resources'
  )

  argument_parser.add_argument('-v', '--verbose', 
    action = 'store_true',
    help = 'use this flag to print out extra information about the installation'
  )

  args = argument_parser.parse_args()

  installation_directory = str(pathlib.Path(args.install_to).resolve())
  sample_packs_directory = str(pathlib.Path(args.sample_packs).resolve())
  
  if not os.path.exists(installation_directory):
    os.mkdir(installation_directory)

  if not os.path.isdir(sample_packs_directory):
    print(f'sample pack path is not a directory ({sample_packs_directory})')
  else:
    compile_samples(installation_directory, args.sample_packs, print_details=args.verbose)
    print(f'succesfully installed {len(os.listdir(installation_directory))} samples to {installation_directory}')

if __name__ == '__main__': main()
