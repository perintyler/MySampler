"""
  Piano960/Scripts/compile_test_data.py
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
"""

import os
import pathlib
import shutil

TEST_DATA = { # TODO: move this to a JSON file
  'G5-female-vocal-chop.wav'     : 'vocal-chops-by-t3jlzd/Ariana Grande Vocal Chops/14 - G.wav',
  'A4-male-vocal-chop.wav'       : 'eclipse-oneshots-by-kindobands/Vocals/Vocal (11).wav',
  'G#3-female-vocal-chop.wav'    : 'vocal-chops-by-t3jlzd/Lana Del Rey Vocal Chops/1 G#.wav',
  'A2-guitar-oneshot.wav'        : 'recorded/martin-streetmaster-000-15M/A2-open.wav',
  'C3-guitar-oneshot.wav'        : 'recorded/martin-streetmaster-000-15m/D3-open.wav',
  'E4-guitar-oneshot.wav'        : 'recorded/martin-streetmaster-000-15m/E4-open.wav',
  'C4-exchange-bass-oneshot.wav' : 'oneshots-from-songs-by-allstar2x/Bryson Tiller - Exchange Bass (C4).wav',
  'C2-uprite-bass-oneshot.wav'   : 'bass-oneshots-by-youngmxtty/Ensoniq-ZR-76-Uprite-Bass-C2.wav',
  'C3-acoustic-bass-oneshot.wav' : 'bass-oneshots-by-youngmxtty/Korg-Triton-Acoustic-Bass-C3.wav',
  'C5-keyboard-oneshot.wav'      : 'oneshots-from-songs-by-allstar2x/Tyler, The Creator - Run Lead (C5).wav',
  'C6-keyboard-oneshot.wav'      : 'oneshots-from-songs-by-allstar2x/XXXTENTACION, Trippie Redd - Fuck Love Key (C6).wav',
  'C6-piano-oneshot.wav'         : 'oneshots-from-songs-by-allstar2x/Future - POA Piano (C6).wav',
  'G3-piano-oneshot.wav'         : 'oneshots-from-songs-by-allstar2x/DaBaby - Suge Piano.wav',
}

def compile_test():
  piano960_directory = pathlib.Path(__file__).parent.parent.resolve()
  sample_pack_directory = piano960_directory.joinpath('Resources', 'Piano960-Sample-Packs')
  test_data_directory = piano960_directory.joinpath('Tests', 'test-data')

  if not test_data_directory.exists(): 
    test_data_directory.mkdir()

  for test_file, sample_file in TEST_DATA.items():
    test_file_path = test_data_directory.joinpath(test_file)
    sample_file_path = sample_pack_directory.joinpath(sample_file)
    shutil.copy2(sample_file_path, test_file_path)

if __name__ == '__main__': compile_test()
