"""
  Piano960/Scripts/normalize_samples.py
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This script normalizes the volume levels for all installed samples.
"""

import sys

if not 'pydub' in sys.modules:
  sys.exit("To use 'normalize_samples.py', first install 'pydub' (with pip) and 'ffpeg' (with homebrew)")

from pydub import AudioSegment

def normalize_samples(directory, target_volume, print_details=False):
  for file_name in os.listdir(directory):
    file_path = os.path.join(directory, file_name)
    sound = AudioSegment.from_file(file_path, "wav") # TODO: support all audio files
    gain = TARGET_VOLUME - sound.dBFS
    if print_details: print(f'{file_name} is {gain} decibels off from the target volume of {TARGET_VOLUME}')
    sound.apply_gain(gain)
    normalized_sound.export(file_path, format="wav") # overwrite file

def main():
  argument_parser = argparse.ArgumentParser('A script for normalizing volume levels of Piano960 samples')

  argument_parser.add_argument('--sample-packs',
    help='a directory containing packs of samples that need to be normalized',
    default=str(PATH_TO_PIANO960_REPO.joinpath('Resources', 'Piano960-Sample-Packs')))

  argument_parser.add_argument('-v', '--verbose', action='store_true',
    help='use this flag to print out extra information about the normalization')

  args = argument_parser.parse_args()

  if os.path.exists(args.sample_packs) and os.path.isdir(args.sample_packs):
    normalized_samples(args.sample_packs, args.target_volume, args.verbose)
  else:
    raise FileNotFoundError('{args.sample_packs} must be a directory containing samples and/or sample packs')

if __name__ == '__main__': main()
