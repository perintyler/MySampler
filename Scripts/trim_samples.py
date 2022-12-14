"""
  Piano960/Scripts/trim_samples.py
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This script trims and overwrites any samples longer than 10 seconds.
"""

import sys
import os
import pathlib
import argparse

if not 'pydub' in sys.modules:
  sys.exit("To use 'normalize_samples.py', first install 'pydub' (with pip) and 'ffpeg' (with homebrew)")

from pydub import AudioSegment

PATH_TO_PIANO960_REPO = pathlib.Path(__file__).parent.parent;

def generate_WAV_file_paths(sample_pack_directory, print_details=False) -> Set[pathlib.PosixPath]:
  """
  """ 
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

    if print_details and num_samples_found_in_directory > 0: 
      print(f'found {num_samples_found_in_directory} samples '
          + f'in {path_to_directory.relative_to(sample_pack_directory)}')

  crawl(sample_pack_directory)
  return sample_paths

def trim_wav_file(path_to_file: str, maximum_sample_length: int, print_details: bool = False):
  assert path_to_file.endswith('.wav')
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
    default=10000, # 10 seconds in milliseconds,
    help='the maximum allowed sample size (measured in milliseconds)')

  argument_parser.add_argument('-v', '--verbose', action='store_true', default=False,
    help='use this flag to print out extra information about the sample trimming')

  args = argument_parser.parse_args()
  assert os.path.exists(args.sample_packs)
  assert os.path.isdir(args.sample_packs)

  for sample_file in generate_WAV_file_paths(args.sample_packs, print_details=args.verbose):
    absolute_path_to_sample = os.path.join(args.sample_packs, sample_file)
    assert absolute_path_to_sample.endswith('.wav')
    trim_wav_file(absolute_path_to_sample, print_details=args.verbose)

if __name__ == '__main__': main()
