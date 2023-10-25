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

try: 
  from pydub import AudioSegment
except ModuleNotFoundError: 
  sys.exit("To use 'trim_samples.py', first install 'pydub' (with pip)")

REPO_PATH = pathlib.Path(__file__).resolve().parent.parent.absolute();

def trim_wav_file(path_to_file: str, maximum_sample_length: int, verbose: bool = False):
  assert path_to_file.suffix == '.wav'
  audio = AudioSegment.from_file(path_to_file, 'wav')

  if len(audio) > maximum_sample_length:
    if verbose:
      print(f'\n| Trimming Sample \n|')
      print(f'| path: {path_to_file}')
      print(f'| length: {len(audio)/ 1000} seconds\n|\n')

    audio[:maximum_sample_length].export(path_to_file, format='wav') # overwrite file

def main():
  argument_parser = argparse.ArgumentParser('A script for clipping long samples')

  argument_parser.add_argument('-d', '--samples-directory',
    help='a directory containing samples and packs, which will be installed',
    default=str(REPO_PATH.joinpath('Assets', 'samples')))

  argument_parser.add_argument('-l', '--length', 
    default=6000, # 6 seconds in milliseconds,
    help='the maximum allowed sample size (measured in milliseconds)')

  argument_parser.add_argument('-v', '--verbose', action='store_true', default=False,
    help='use this flag to print out extra information about the sample trimming')

  args = argument_parser.parse_args()

  for path in pathlib.Path(args.samples_directory).glob(f"**/*.wav"):
    trim_wav_file(path, args.length, verbose=args.verbose)

if __name__ == '__main__': main()
