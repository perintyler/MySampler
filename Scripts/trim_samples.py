"""
  Piano960/Scripts/trim_samples.py
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This script trims and overwrites any samples longer than 10 seconds.
"""

import sys
import os
import pathlib
import argparse
import random

try: from pydub import AudioSegment
except ModuleNotFoundError: 
  sys.exit("To use 'trim_samples.py', first install 'pydub' (with pip)")

PATH_TO_PIANO960_REPO = pathlib.Path(__file__).parent.parent;

def generate_sample_paths(sample_packs_directory):
  sample_paths = list(pathlib.Path(sample_packs_directory).glob(f"**/*.wav"))
  assert len(sample_paths) > 0

  while sample_paths:
    random_index = random.randint(0, len(sample_paths) - 1)
    yield sample_paths.pop(random_index)

def trim_wav_file(path_to_file: str, maximum_sample_length: int, print_details: bool = False):
  assert path_to_file.suffix == '.wav'
  audio = AudioSegment.from_file(path_to_file, 'wav')
  if len(audio) > maximum_sample_length:
    if print_details: print(f'trimming {len(audio) / 1000} second audio file: {path_to_file}')
    first_10_seconds_of_audio = audio[:maximum_sample_length]
    first_10_seconds_of_audio.export(path_to_file, format='wav') # overwrite file

def main():
  argument_parser = argparse.ArgumentParser('A script for clipping long samples')

  argument_parser.add_argument('--sample-packs',
    help='a directory containing samples and packs, which will be installed',
    default=str(PATH_TO_PIANO960_REPO.joinpath('Resources', 'Piano960-Sample-Packs')))

  argument_parser.add_argument('--max-length', 
    default=5000, # 5 seconds in milliseconds,
    help='the maximum allowed sample size (measured in milliseconds)')

  argument_parser.add_argument('-v', '--verbose', action='store_true', default=False,
    help='use this flag to print out extra information about the sample trimming')

  args = argument_parser.parse_args()
  assert os.path.exists(args.sample_packs)
  assert os.path.isdir(args.sample_packs)

  for sample_file in generate_sample_paths(args.sample_packs):
    trim_wav_file(sample_file, args.max_length, print_details=args.verbose)

if __name__ == '__main__': main()
