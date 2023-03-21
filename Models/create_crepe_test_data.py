""" Piano960 | Models/create_crepe_test_data.py """

import json
import numpy as np
from numpy.lib.stride_tricks import as_strided
from resampy import resample
from scipy.io import wavfile
import pathlib

CREPE_MODEL_SAMPLE_RATE = 16000

MODELS_DIRECTORY = pathlib.Path(__file__).resolve().parent.parent.resolve()

TEST_AUDIO_DIRECTORY = MODELS_DIRECTORY.parent.resolve().joinpath('Tests').joinpath('test-data').resolve()

OUTPUT_FILE = TEST_AUDIO_DIRECTORY.joinpath('crepe-inputs.json').resolve()

TEST_FILES = [TEST_AUDIO_DIRECTORY.joinpath(filename) for filename in (
  'G#3-female-vocal-chop.wav',
  'A4-male-vocal-chop.wav',
  'C3-guitar-oneshot.wav'
)]

def downsample(audio, sample_rate):
  return resample(audio, sample_rate, CREPE_MODEL_SAMPLE_RATE).copy()

def create_audio_frames(audio):
  step_size = 10
  hop_length = int(CREPE_MODEL_SAMPLE_RATE * step_size / 1000)
  n_frames = 1 + int((len(audio) - 1024) / hop_length)
  frames = as_strided(
      audio, 
      shape=(1024, n_frames),
      strides=(audio.itemsize, hop_length * audio.itemsize)
  )
  return frames.transpose().copy()

def normalize_audio(audio):
  audio -= np.mean(audio, axis=1)[:, np.newaxis]
  audio /= np.clip(np.std(audio, axis=1)[:, np.newaxis], 1e-8, None)
  return audio.copy()

def create_test_data():
  """saves test data to a JSON file"""
  test_data = {}
  for file in TEST_FILES:
      sample_rate, audio = wavfile.read(str(file))

      audio = audio.astype(np.float32)
      monoAudio = audio.copy().mean(1)
      downsampledAudio = downsample(monoAudio.copy(), sample_rate);
      framedAudio = create_audio_frames(downsampledAudio.copy()),
      normalizedAudio = normalize_audio(tuple(framedAudio))

      test_data[file.name] = {
        'audio': [channel.tolist() for channel in audio],
        'mono': monoAudio.tolist(),
        'downsampled': downsampledAudio.tolist(),
        'framedAudio': [frame.tolist() for frame in framedAudio],
        'normalize': normalizedAudio.tolist()
      }

  return test_data

if __name__ == '__main__':
  listOfTestFiles = "\n\t - ".join([str(file) for file in TEST_FILES])
  print(f'\ncompiling test data for:\n\t - {listOfTestFiles}\n')
  test_data = create_test_data()
  with open('crepe-inputs.json', 'w') as test_data_file:
    json.dump(test_data, test_data_file, indent=4)
