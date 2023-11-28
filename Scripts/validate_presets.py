"""Piano960 Script | validate_presets.py"""

import os
import json
import pathlib
import argparse

PATH_TO_PIANO960_REPO = pathlib.Path(__file__).parent.parent.absolute();
DEFAULT_PRESETS_FILE = PATH_TO_PIANO960_REPO.absolute().joinpath('presets.json').absolute()
INSTALLED_PRESETS_FILE = pathlib.Path(os.path.abspath(os.sep)).joinpath(
  'usr', 'local', 'include', 'MySampler', 'presets.json'
).absolute()

class InvalidPresetsFile(Exception): pass

def validate_presets_file(filepath):
  """
  """
  try:
    with open(filepath) as presetsFile:
      presets = json.load(presetsFile)

    assert type(presets) is dict
    assert not len(presets.items()) == 0

    for presetName, samples in presets.items():
      assert type(presetName) is str
      assert len(presetName) > 0
      assert type(samples) is list
      assert len(samples) > 0

      for sample in samples:
        assert type(sample) is dict
        assert len(sample.keys()) == 3

        assert "assignedKey" in sample
        key = sample["assignedKey"]
        assert type(key) is int
        assert key > 0 and key < 100

        assert "detectedNote" in sample
        detectedNote = sample["detectedNote"]
        assert type(detectedNote) is int
        assert detectedNote > 0 and detectedNote < 100

        assert "pathToSample" in sample
        path = sample["pathToSample"]
        assert os.path.exists(path)
        assert path.endswith('.mp3') or path.endswith('.wav')
  except Exception as exception:
    raise InvalidPresetsFile(f'Invalid presets file: {filepath} | {exception}')

if __name__ == '__main__':
  argument_parser = argparse.ArgumentParser('A script for validating MySampler presets')

  argument_parser.add_argument('-f', '--presets-file', default=None, help='a path to a presets file')
  
  args = argument_parser.parse_args()

  if args.presets_file:
    print(f'validating presets file: {args.presets_file}')
    validate_presets_file(args.presets_file)
  else:
    # no presets file provided. validate the presets files (both default and installed) 
    # that are stored in the default location.
    print()
    print('| ')
    print('| Validating Presets Files')
    print('| ')
    validate_presets_file(DEFAULT_PRESETS_FILE)
    print(f'| - Default presets file is valid ({DEFAULT_PRESETS_FILE})')
    validate_presets_file(INSTALLED_PRESETS_FILE)
    print(f'| - Installed presets file is valid ({INSTALLED_PRESETS_FILE})')
    print('| ')
    print()


