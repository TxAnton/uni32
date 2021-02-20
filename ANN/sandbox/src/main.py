import numpy as np#импорт библиотеки NumPy с тензорами

import pandas
import matplotlib.pyplot as plt #импорт модуля для графиков
import tensorflow as tf
import tensorflow.keras as keras #подключение библиотеки
from keras import models #импорт моделей
from keras import layers #импорт слоев
# import scikit_learn

n_samp = 3
n_epochs = 5

from keras.datasets import imdb
(train_data, train_labels), (test_data, test_labels) = imdb.load_data(num_words=n_samp)
#num_words = 10000 – означает, что рассматриваться будут только 10000 самых популярных слов в отзывах


#определение ф-ции векторизации
def vectorize_sequences(sequences, dimension=n_samp):
    results = np.zeros((len(sequences), dimension))
    for i, sequence in enumerate(sequences):
        results[i, sequence] = 1.
    return results




if __name__ == "__main__":
    x_train = vectorize_sequences(train_data)  # векторизация обучающих данных
    x_test = vectorize_sequences(test_data)  # векторизация тестовых данных

    # векторизация меток данных с вещественным типом
    y_train = np.asarray(train_labels).astype('float32')
    y_test = np.asarray(test_labels).astype('float32')

    # Построение модели

    # создание последовательной модели
    model = models.Sequential()
    # добавление слоев
    model.add(layers.Dense(16, activation='relu', input_shape=(n_samp,)))
    model.add(layers.Dense(8, activation='relu'))
    model.add(layers.Dense(4, activation='relu'))
    model.add(layers.Dense(1, activation='sigmoid'))

    model.compile(optimizer='rmsprop', loss='binary_crossentropy', metrics=['accuracy'])

    x_val = x_train[:n_samp]
    partial_x_train = x_train[n_samp:]

    y_val = y_train[:n_samp]
    partial_y_train = y_train[n_samp:]

    history = model.fit(partial_x_train,
                        partial_y_train,
                        epochs=n_epochs,
                        batch_size=512,
                        validation_data=(x_val, y_val))

    history_dict = history.history
    print(history_dict.keys())
    # dict_keys(['val_loss', 'val_acc', 'loss', 'acc'])

    model.evaluate(x_test, y_test)

    # Построение графиков

    loss_values = history_dict['loss']
    val_loss_values = history_dict['val_loss']
    epochs = range(1, len(loss_values) + 1)
    # plt.plot(epochs, loss_values, 'bo', label='Training loss')
    # plt.plot(epochs, val_loss_values, 'b', label='Validation loss')
    # plt.title('Training and validation loss')
    # plt.xlabel('Epochs')
    # plt.ylabel('Loss')
    # plt.legend()
    # plt.show()

    plt.clf()
    acc_values = history_dict['accuracy']
    val_acc_values = history_dict['val_accuracy']
    plt.plot(epochs, acc_values, 'bo', label='Training acc')
    plt.plot(epochs, val_acc_values, 'b', label='Validation acc')
    plt.title('Training and validation accuracy')
    plt.xlabel('Epochs')
    plt.ylabel('Accuracy')
    plt.legend()
    plt.show()