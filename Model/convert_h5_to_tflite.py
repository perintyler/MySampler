import tensorflow as tf
import os

from tensorflow.keras.layers import Input, Reshape, Conv2D, BatchNormalization
from tensorflow.keras.layers import MaxPool2D, Dropout, Permute, Flatten, Dense
from tensorflow.keras.models import Model

MODELS_DIRECTORY = os.path.dirname(os.path.realpath(__file__))

def get_model(filepath):

  filename, extension = os.path.splitext(os.path.basename(filepath))
  model_capacity = filename.split('-')[1]

  capacity_multiplier = {
      'tiny': 4, 'small': 8, 'medium': 16, 'large': 24, 'full': 32
  }[model_capacity]

  layers = [1, 2, 3, 4, 5, 6]
  filters = [n * capacity_multiplier for n in [32, 4, 4, 4, 8, 16]]
  widths = [512, 64, 64, 64, 64, 64]
  strides = [(4, 1), (1, 1), (1, 1), (1, 1), (1, 1), (1, 1)]

  x = Input(shape=(1024,), name='input', dtype='float32')
  y = Reshape(target_shape=(1024, 1, 1), name='input-reshape')(x)

  for l, f, w, s in zip(layers, filters, widths, strides):
      y = Conv2D(f, (w, 1), strides=s, padding='same',
                 activation='relu', name="conv%d" % l)(y)
      y = BatchNormalization(name="conv%d-BN" % l)(y)
      y = MaxPool2D(pool_size=(2, 1), strides=None, padding='valid',
                    name="conv%d-maxpool" % l)(y)
      y = Dropout(0.25, name="conv%d-dropout" % l)(y)

  y = Permute((2, 1, 3), name="transpose")(y)
  y = Flatten(name="flatten")(y)
  y = Dense(360, activation='sigmoid', name="classifier")(y)

  model = Model(inputs=x, outputs=y)
  model.load_weights(filepath)
  return model


def get_crepe_model_files():
  crepe_models_directory = os.path.join(MODELS_DIRECTORY, 'crepe-models')
  h5_files = [file for file in os.listdir(crepe_models_directory) if file.endswith('.h5')]
  return [os.path.join(crepe_models_directory, filename) for filename in h5_files]

def convert_h5_to_tflite(infile, outfile):
  assert infile.endswith('.h5')
  assert outfile.endswith('.tflite')
  model = get_model(infile)
  converter = tf.lite.TFLiteConverter.from_keras_model(model)
  tflite_model = converter.convert()
  open(outfile, 'wb').write(tflite_model)

if __name__ == '__main__':
  for h5_file in get_crepe_model_files():
    filename, extension = os.path.splitext(os.path.basename(h5_file))
    assert extension == '.h5'
    tflite_file = os.path.join(MODELS_DIRECTORY, 'crepe-models', f'{filename}.tflite')
    convert_h5_to_tflite(h5_file, tflite_file)

