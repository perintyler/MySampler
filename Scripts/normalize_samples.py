"""MySampler | Scripts/normalize_samples.py

This script normalizes volume levels of all samples inside 'Assets/samples'
"""


import sys
import os
import argparse
import pathlib
import random

try:
  from pydub import AudioSegment
except:
  sys.exit("To use 'normalize_samples.py', first install 'pydub' (with pip) and 'ffmpeg' (with homebrew)")

PATH_TO_PIANO960_REPO = pathlib.Path(__file__).parent.parent.absolute()

def generate_sample_paths(sample_packs_directory):
  sample_paths = list(pathlib.Path(sample_packs_directory).glob(f"**/*.wav"))
  assert len(sample_paths) > 0

  while sample_paths:
    random_index = random.randint(0, len(sample_paths) - 1)
    yield sample_paths.pop(random_index)

def normalize_samples(directory, target_volume, verbose=False):
  for file_path in generate_sample_paths(directory):
    sound = AudioSegment.from_wav(file_path) # TODO: support all audio files
    gain = target_volume - sound.dBFS
    
    if gain == 0: 
      continue
    elif verbose: 
      print(f'{file_path} is {gain} decibels off from the target volume of {target_volume}')

    normalized_sound = sound.apply_gain(gain)
    normalized_sound.export(file_path, format="wav") # overwrite file

def main():
  argument_parser = argparse.ArgumentParser('A script for normalizing volume levels of Piano960 samples')

  argument_parser.add_argument('--sample-packs',
    help='a directory containing packs of samples that need to be normalized',
    default=str(PATH_TO_PIANO960_REPO.joinpath('Assets', 'samples')))

  argument_parser.add_argument('--target-volume',
    help='the ideal volume level for the samples in decibals',
    default=0)

  argument_parser.add_argument('-v', '--verbose', action='store_true',
    help='use this flag to print out extra information about the normalization')

  args = argument_parser.parse_args()

  if os.path.exists(args.sample_packs) and os.path.isdir(args.sample_packs):
    normalize_samples(args.sample_packs, args.target_volume, args.verbose)
  else:
    raise FileNotFoundError('{args.sample_packs} must be a directory containing samples and/or sample packs')

if __name__ == '__main__': main()
