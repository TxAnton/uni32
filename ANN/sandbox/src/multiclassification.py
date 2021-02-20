from keras.datasets import reuters

n_samp = 5000
n_subset = 1000
n_epochs = 10

(train_data, train_labels), (test_data, test_labels) = reuters.load_data(num_words=n_samp)

import numpy as np



def vectorize_sequences(sequences, dimension=n_samp):
    results = np.zeros((len(sequences), dimension))
    for i, sequence in enumerate(sequences):
        results[i, sequence] = 1.
    return results


x_train = vectorize_sequences(train_data)
x_test = vectorize_sequences(test_data)

# def to_one_hot(labels, dimension=46):
#     results = np.zeros((len(labels), dimension))
#     for i, label in enumerate(labels):
#         results[i, label] = 1.
#     return results
#
# one_hot_train_labels = to_one_hot(train_labels)
# one_hot_test_labels = to_one_hot(test_labels)

# from keras.utils.np_utils import to_categorical
#
# one_hot_train_labels = to_categorical(train_labels)
# one_hot_test_labels = to_categorical(test_labels)

from keras import models
from keras import layers

model = models.Sequential()
model.add(layers.Dense(64, activation='relu', input_shape=(n_samp,)))
model.add(layers.Dense(64, activation='relu'))
model.add(layers.Dense(46, activation='softmax'))

model.compile(optimizer='rmsprop',
              loss='categorical_crossentropy',
              metrics=['accuracy'])

x_val = x_train[:n_subset]
partial_x_train = x_train[n_subset:]
y_val = one_hot_train_labels[:n_subset]
partial_y_train = one_hot_train_labels[n_subset:]
history = model.fit(partial_x_train,
                    partial_y_train,
                    epochs=n_epochs,
                    batch_size=512,
                    validation_data=(x_val, y_val))

history_dict = history.history
print(history_dict.keys())
# dict_keys(['val_loss', 'val_acc', 'loss', 'acc'])

import matplotlib.pyplot as plt

loss = history_dict['loss']
val_loss = history_dict['val_loss']
epochs = range(1, len(loss) + 1)
plt.plot(epochs, loss, 'bo', label='Training loss')
plt.plot(epochs, val_loss, 'b', label='Validation loss')
plt.title('Training and validation loss')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.legend()
plt.show()

plt.clf()
acc = history_dict['accuracy']
val_acc = history_dict['val_accuracy']
plt.plot(epochs, acc, 'bo', label='Training acc')
plt.plot(epochs, val_acc, 'b', label='Validation acc')
plt.title('Training and validation accuracy')
plt.xlabel('Epochs')
plt.ylabel('Accuracy')
plt.legend()
plt.show()

results = model.evaluate(x_test, one_hot_test_labels)
print(results)

predictions = model.predict(x_test)
print(predictions[0].shape)
#(46,) #размер выходного вектора
print(np.sum(predictions[0]))
#1.0 #сумма вероятностей, из-за погрешности не ровно 1
print(np.argmax(predictions[0]))
#3 #к какому классу отнесено наблюдение
print(np.max(predictions[0]))
#0.8662524 #с какой вероятностью отнесено к классу

if __name__ == "__main__":
    print("done")
