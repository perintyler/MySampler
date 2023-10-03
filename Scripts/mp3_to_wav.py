"""MySampler | Scripts/compile_samples.py"""

import sys
import pathlib

try:
  from pydub import AudioSegment
except:
  sys.exit("To use 'normalize_samples.py', first install 'pydub' (with pip) and 'ffmpeg' (with homebrew)")

VERBOSE = True

def crawl_and_convert_mp3_to_wav(samples_directory):
  for path_to_mp3 in pathlib.Path(samples_directory).glob(f"**/*.mp3"):
    sound = AudioSegment.from_mp3(path_to_mp3)

    parent_directory = path_to_mp3.resolve().parent.absolute()
    wav_filename = path_to_mp3.stem + '.wav'
    wav_filepath = parent_directory.joinpath(wav_filename)

    if VERBOSE:
      print()
      print(' ||| Converting MP3 to WAV')
      print(' |')
      print(' | - from :', path_to_mp3)
      print(' | -   to :', wav_filepath)
      print()

    sound.export(wav_filepath, format="wav")

if __name__ == '__main__':
  crawl_and_convert_mp3_to_wav(
    pathlib.Path(__file__).parent.parent.joinpath('Assets', 'samples').absolute()
  )