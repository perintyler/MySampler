"""MySampler | Scripts/delete_duplicate_samples.py"""

import os
import pathlib

VERBOSE = True
PATH_TO_PIANO960_REPO = pathlib.Path(__file__).resolve().parent.parent.absolute()
PATH_TO_SAMPLES_DIRECTORY = PATH_TO_PIANO960_REPO.joinpath('Assets', 'samples')

sampleNameToPath = {}

def delete_duplicate_samples():
  numSamplesDeleted = 0
  sampleNameToPath = {}
  for category_directory in PATH_TO_SAMPLES_DIRECTORY.iterdir():
    for sample_path in category_directory.iterdir():
      if sample_path.name in sampleNameToPath:
        numSamplesDeleted+=1
        os.remove(sample_path)
        if VERBOSE: 
          print(f'Found Duplicate Sample #{numSamplesDeleted+1}')
          print(f' - Existing Sample: {sampleNameToPath[sample_path.name]}')
          print(f' - Deleted Sample: {sample_path}')

      else:
        sampleNameToPath[sample_path.name] = sample_path

  print(f'Deleted {numSamplesDeleted} duplicate samples')

if __name__ == '__main__':
  delete_duplicate_samples()