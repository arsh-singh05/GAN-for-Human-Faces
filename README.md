# GAN-for-Human-Faces

This project contains a generative adversarial network (GAN) trained to generate synthetic images of human faces. A GAN consists of two networks: a generator and a discriminator. The generator takes a noise vector as input and generates a synthetic image, while the discriminator takes an image as input and classifies it as either real (from a training dataset) or fake (generated by the generator). The two networks are trained simultaneously, with the generator trying to produce images that are indistinguishable from real ones, and the discriminator trying to correctly classify the images as real or fake.

The GAN in this project is trained on a dataset of grayscale images of human faces. The generator and discriminator networks each have three hidden layers and use the sigmoid activation function. The generator produces synthetic images with the same dimensions as the training images, and the discriminator produces a single output for each image, which is a value between 0 and 1. A value close to 0 indicates that the image is fake, while a value close to 1 indicates that the image is real.

During training, the generator and discriminator networks are trained alternately. First, the discriminator is trained on a real image from the training data, and the generator is trained to produce a synthetic image that the discriminator will classify as real. Then, the generator is trained on a noise vector, and the discriminator is trained to classify the resulting synthetic image as fake. The weights and biases of both networks are updated based on the error between the network's output and the target value (0 for the generator, 1 for the discriminator). This process is repeated for multiple iterations, until the GAN has learned to generate synthetic images that are realistic enough to fool the discriminator.

## Getting Started

To run the code, you will need to have the following dependencies installed:

- C++ compiler
- OpenCV

To compile the code, navigate to the project directory in your terminal and run the following command:

g++ main.cpp -o main `pkg-config --cflags --libs opencv`

To run the code, enter the following command:

./main

The code will output synthetic images to the output directory as it trains. The training process can be stopped at any time by pressing CTRL+C.

## Options

The following options can be modified in the code:

LEARNING_RATE: the learning rate for the generator and discriminator networks (default: 0.001)
NUM_EPOCHS: the number of epochs to train for (default: 200)
BATCH_SIZE: the batch size for training (default: 64)

### Acknowledgements
This project was inspired by the GAN tutorial at https://towardsdatascience.com/gan-by-example-using-keras-on-tensorflow-backend-1a6d515a60d0.

### License
This project is licensed under the MIT License - see the LICENSE file for details.

Thank you for using this GAN! I hope it is able to generate some interesting and realistic synthetic images for you!
Follow me for more such interesting projects.
