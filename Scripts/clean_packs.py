"""
  Piano960/Scripts/clean_packs.py
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This script deletes any non WAV files contained inside a directory
of sample packs.
"""

import os
import argparse

def delete_non_WAV_files(sample_pack_directory, print_details=False):
  pass

def main():
  argument_parser = argparse.ArgumentParser('A script for cleansing sample packs of non WAV files')

  argument_parser.add_argument('--sample-packs', 
    help='a directory containing samples and packs, which will be cleaned')

  argument_parser.add_argument('-v', '--verbose', action='store_true',
    help='use this flag to print out extra information about the cleaning')

  args = argument_parser.parse_args()

  assert os.path.exists(args.sample_packs)
  assert os.path.isdir(args.sample_packs)
  delete_non_WAV_files(args.sample_packs, print_details=args.verbose)

if __name__ == '__main__': main()
