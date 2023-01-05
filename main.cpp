// necessary C++ standard library headers for input/output, general purpose functions, math functions, time functions, and a boolean type.

#include<iostream.h>
#include<cstdio.h>
#include<cstdlib.h>
#include<cmath.h>
#include<ctime.h>
#include<stdbool.h>

// define constants for the width and height of the generated images, the number of color channels in the images, the batch size for training, the number of training epochs, and the learning rate for the networks.

#define IMAGE_WIDTH 128
#define IMAGE_HEIGHT 128
#define NUM_CHANNELS 3
#define BATCH_SIZE 64
#define NUM_EPOCHS 10
#define LEARNING_RATE 0.001

struct pixel //structure to represent a pixel in an image, with three fields for the red, green, and blue color channels.
{
  unsigned char r, g, b;
};

float sigmoid(float x) 
{
  return 1 / (1 + exp(-x));
}

/*defines the sigmoid activation function, which takes a float value as input and returns the sigmoid of that value.
The sigmoid function is used as an activation function in the networks to introduce nonlinearity.
*/

int main() 
{
    pixel train_data[BATCH_SIZE][IMAGE_WIDTH][IMAGE_HEIGHT]; //load the training data from a binary file into a 3D array of pixels
    FILE * infile = fopen("train_data.bin", "rb");
    fread(train_data, sizeof(pixel), BATCH_SIZE * IMAGE_WIDTH * IMAGE_HEIGHT, infile);
    fclose(infile);
    // Initialize generator and discriminator weights and biases
    float gen_w1[IMAGE_WIDTH][IMAGE_HEIGHT], gen_w2[IMAGE_WIDTH][IMAGE_HEIGHT], gen_w3[IMAGE_WIDTH][IMAGE_HEIGHT];
    float gen_b1[IMAGE_WIDTH][IMAGE_HEIGHT], gen_b2[IMAGE_WIDTH][IMAGE_HEIGHT], gen_b3[IMAGE_WIDTH][IMAGE_HEIGHT];
    float dis_w1[IMAGE_WIDTH][IMAGE_HEIGHT], dis_w2[IMAGE_WIDTH][IMAGE_HEIGHT], dis_w3[IMAGE_WIDTH][IMAGE_HEIGHT];
    float dis_b1[IMAGE_WIDTH][IMAGE_HEIGHT], dis_b2[IMAGE_WIDTH][IMAGE_HEIGHT], dis_b3[IMAGE_WIDTH][IMAGE_HEIGHT];
    srand(time(NULL));
    for (int i = 0; i < IMAGE_WIDTH; i++) 
    {
      for (int j = 0; j < IMAGE_HEIGHT; j++) 
      {
        gen_w1[i][j] = (float) rand() / RAND_MAX;
        gen_w2[i][j] = (float) rand() / RAND_MAX;
        gen_w3[i][j] = (float) rand() / RAND_MAX;
        gen_b1[i][j] = (float) rand() / RAND_MAX;
        gen_b2[i][j] = (float) rand() / RAND_MAX;
        gen_b3[i][j] = (float) rand() / RAND_MAX;
        dis_w1[i][j] = (float) rand() / RAND_MAX;
        dis_w2[i][j] = (float) rand() / RAND_MAX;
        dis_w3[i][j] = (float) rand() / RAND_MAX;
        dis_b1[i][j] = (float) rand() / RAND_MAX;
        dis_b2[i][j] = (float) rand() / RAND_MAX;
        dis_b3[i][j] = (float) rand() / RAND_MAX;
      }
    }

    /* 
    initialize the weights and biases for the generator and discriminator networks. 
    use the rand function to generate random values between 0 and 1. 
    srand function is used to seed the random number generator with the current time, so that the generated random numbers will be different each time the program is run.
    */

    // Train networks
    for (int epoch = 0; epoch < NUM_EPOCHS; epoch++) 
    {
      for (int i = 0; i < BATCH_SIZE; i++) 
      {
        // Generate synthetic image
        float input_noise[IMAGE_WIDTH][IMAGE_HEIGHT];
        for (int j = 0; j < IMAGE_WIDTH; j++) 
        {
          for (int k = 0; k < IMAGE_HEIGHT; k++) 
          {
            input_noise[j][k] = (float) rand() / RAND_MAX;
          }
        }
        float gen_h1[IMAGE_WIDTH][IMAGE_HEIGHT];
        for (int j = 0; j < IMAGE_WIDTH; j++) 
        {
          for (int k = 0; k < IMAGE_HEIGHT; k++) 
          {
            float sum = 0;
            for (int l = 0; l < NUM_CHANNELS; l++) 
            {
              sum += input_noise[j][k] * gen_w1[j][k];
            }
            gen_h1[j][k] = sigmoid(sum + gen_b1[j][k]);
          }
        }
        float gen_h2[IMAGE_WIDTH][IMAGE_HEIGHT];
        for (int j = 0; j < IMAGE_WIDTH; j++) 
        {
          for (int k = 0; k < IMAGE_HEIGHT; k++) 
          {
            float sum = 0;
            for (int l = 0; l < NUM_CHANNELS; l++) 
            {
              sum += gen_h1[j][k] * gen_w2[j][k];
            }
            gen_h2[j][k] = sigmoid(sum + gen_b2[j][k]);
          }
        }
        pixel synthetic_image[IMAGE_WIDTH][IMAGE_HEIGHT];
        for (int j = 0; j < IMAGE_WIDTH; j++) 
        {
          for (int k = 0; k < IMAGE_HEIGHT; k++) 
          {
            float sum = 0;
            for (int l = 0; l < NUM_CHANNELS; l++) 
            {
              sum += gen_h2[j][k] * gen_w3[j][k];
            }
            synthetic_image[j][k] = (pixel) 
            {
              (unsigned char)(sigmoid(sum + gen_b3[j][k]) * 255), (unsigned char)(sigmoid(sum + gen_b3[j][k]) * 255), (unsigned char)(sigmoid(sum + gen_b3[j][k]) * 255)
            };
          }
        }

        /*
        generate a synthetic image using the generator network. 
        The input to the generator is a noise vector, which is generated randomly. 
        The generator has three hidden layers, and the sigmoid activation function is applied to the outputs of each layer. 
        The final layer produces the synthetic image, which is stored in a 2D array of pixels.
        */

        // Train discriminator
        float dis_h1[IMAGE_WIDTH][IMAGE_HEIGHT];
        for (int j = 0; j < IMAGE_WIDTH; j++) 
        {
          for (int k = 0; k < IMAGE_HEIGHT; k++) 
          {
            float sum = 0;
            for (int l = 0; l < NUM_CHANNELS; l++) 
            {
              sum += train_data[i][j][k].r * dis_w1[j][k];
            }
            dis_h1[j][k] = sigmoid(sum + dis_b1[j][k]);
          }
        }
        float dis_h2[IMAGE_WIDTH][IMAGE_HEIGHT];
        for (int j = 0; j < IMAGE_WIDTH; j++) 
        {
          for (int k = 0; k < IMAGE_HEIGHT; k++) 
          {
            float sum = 0;
            for (int l = 0; l < NUM_CHANNELS; l++) 
            {
              sum += dis_h1[j][k] * dis_w2[j][k];
            }
            dis_h2[j][k] = sigmoid(sum + dis_b2[j][k]);
          }
        }
        float dis_out[IMAGE_WIDTH][IMAGE_HEIGHT];
        for (int j = 0; j < IMAGE_WIDTH; j++) 
        {
          for (int k = 0; k < IMAGE_HEIGHT; k++) 
          {
            float sum = 0;
            for (int l = 0; l < NUM_CHANNELS; l++) 
            {
              sum += dis_h2[j][k] * dis_w3[j][k];
            }
            dis_out[j][k] = sigmoid(sum + dis_b3[j][k]);
          }
        }
        float dis_loss = 0;
        for (int j = 0; j < IMAGE_WIDTH; j++) 
        {
          for (int k = 0; k < IMAGE_HEIGHT; k++) 
          {
            dis_loss += (dis_out[j][k] - 1) * (dis_out[j][k] - 1);
          }
        }

        /* 
        train the discriminator network on the real image from the training data.
        discriminator has three hidden layers, and the sigmoid activation function is applied to the outputs of each layer.
        final layer produces the output of the network, which is stored in a 2D array.
        loss of the network is calculated as the mean squared error between the output and the target value of 1.
        */

        // Train generator
        float gen_h1_[IMAGE_WIDTH][IMAGE_HEIGHT];
        for (int j = 0; j < IMAGE_WIDTH; j++) 
        {
          for (int k = 0; k < IMAGE_HEIGHT; k++) 
          {
            float sum = 0;
            for (int l = 0; l < NUM_CHANNELS; l++) 
            {
              sum += input_noise[j][k] * gen_w1[j][k];
            }
            gen_h1_[j][k] = sigmoid(sum + gen_b1[j][k]);
          }
        }
        float gen_h2_[IMAGE_WIDTH][IMAGE_HEIGHT];
        for (int j = 0; j < IMAGE_WIDTH; j++) 
        {
          for (int k = 0; k < IMAGE_HEIGHT; k++) 
          {
            float sum = 0;
            for (int l = 0; l < NUM_CHANNELS; l++) 
            {
              sum += gen_h1_[j][k] * gen_w2[j][k];
            }
            gen_h2_[j][k] = sigmoid(sum + gen_b2[j][k]);
          }
        }
        pixel synthetic_image_[IMAGE_WIDTH][IMAGE_HEIGHT];
        for (int j = 0; j < IMAGE_WIDTH; j++) 
        {
          for (int k = 0; k < IMAGE_HEIGHT; k++) 
          {
            float sum = 0;
            for (int l = 0; l < NUM_CHANNELS; l++) 
            {
              sum += gen_h2_[j][k] * gen_w3[j][k];
            }
            synthetic_image_[j][k] = (pixel) 
            {
              (unsigned char)(sigmoid(sum + gen_b3[j][k]) * 255), (unsigned char)(sigmoid(sum + gen_b3[j][k]) * 255), (unsigned char)(sigmoid(sum + gen_b3[j][k]) * 255)
            };
          }
        }
        float dis_h1_[IMAGE_WIDTH][IMAGE_HEIGHT];
        for (int j = 0; j < IMAGE_WIDTH; j++) 
        {
          for (int k = 0; k < IMAGE_HEIGHT; k++) 
          {
            float sum = 0;
            for (int l = 0; l < NUM_CHANNELS; l++) 
            {
              sum += synthetic_image_[j][k].r * dis_w1[j][k];
            }
            dis_h1_[j][k] = sigmoid(sum + dis_b1[j][k]);
          }
        }
        float dis_h2_[IMAGE_WIDTH][IMAGE_HEIGHT];
        for (int j = 0; j < IMAGE_WIDTH; j++) 
        {
          for (int k = 0; k < IMAGE_HEIGHT; k++) 
          {
            float sum = 0;
            for (int l = 0; l < NUM_CHANNELS; l++) 
            {
              sum += dis_h1_[j][k] * dis_w2[j][k];
            }
            dis_h2_[j][k] = sigmoid(sum + dis_b2[j][k]);
          }
        }
        float dis_out_[IMAGE_WIDTH][IMAGE_HEIGHT];
        for (int j = 0; j < IMAGE_WIDTH; j++) 
        {
          for (int k = 0; k < IMAGE_HEIGHT; k++) 
          {
            float sum = 0;
            for (int l = 0; l < NUM_CHANNELS; l++) 
            {
              sum += dis_h2_[j][k] * dis_w3[j][k];
            }
            dis_out_[j][k] = sigmoid(sum + dis_b3[j][k]);
          }
        }
        float gen_loss = 0;
        for (int j = 0; j < IMAGE_WIDTH; j++) 
        {
          for (int k = 0; k < IMAGE_HEIGHT; k++) 
          {
            gen_loss += (dis_out_[j][k] - 0) * (dis_out_[j][k] - 0);
          }
        }
        for (int i = 0; i < IMAGE_WIDTH; i++) 
        {
          for (int j = 0; j < IMAGE_HEIGHT; j++) 
          {
            float gradient = dis_out[i][j] - 1;
            for (int k = 0; k < NUM_CHANNELS; k++) 
            {
              dis_w3[i][j] -= gradient * dis_h2[i][j] * LEARNING_RATE;
              dis_b3[i][j] -= gradient * LEARNING_RATE;
            }
          }
        }
        for (int i = 0; i < IMAGE_WIDTH; i++) 
        {
          for (int j = 0; j < IMAGE_HEIGHT; j++) 
          {
            float gradient = dis_out[i][j] - 1;
            for (int k = 0; k < NUM_CHANNELS; k++) 
            {
              dis_w2[i][j] -= gradient * dis_h1[i][j] * LEARNING_RATE;
              dis_b2[i][j] -= gradient * LEARNING_RATE;
            }
          }
        }
        for (int i = 0; i < IMAGE_WIDTH; i++) 
        {
          for (int j = 0; j < IMAGE_HEIGHT; j++) 
          {
            float gradient = dis_out[i][j] - 1;
            for (int k = 0; k < NUM_CHANNELS; k++) 
            {
              dis_w1[i][j] -= gradient * train_data[i][j][k].r * LEARNING_RATE;
              dis_b1[i][j] -= gradient * LEARNING_RATE;
            }
          }
        }
        for (int i = 0; i < IMAGE_WIDTH; i++) 
        {
          for (int j = 0; j < IMAGE_HEIGHT; j++) 
          {
            float gradient = dis_out_[i][j] - 0;
            for (int k = 0; k < NUM_CHANNELS; k++) 
            {
              gen_w3[i][j] -= gradient * gen_h2_[i][j] * LEARNING_RATE;
              gen_b3[i][j] -= gradient * LEARNING_RATE;
            }
          }
        }
        for (int i = 0; i < IMAGE_WIDTH; i++) 
        {
          for (int j = 0; j < IMAGE_HEIGHT; j++) 
          {
            float gradient = dis_out_[i][j] - 0;
            for (int k = 0; k < NUM_CHANNELS; k++) 
            {
              gen_w2[i][j] -= gradient * gen_h1_[i][j] * LEARNING_RATE;
              gen_b2[i][j] -= gradient * LEARNING_RATE;
            }
          }
        }
        for (int i = 0; i < IMAGE_WIDTH; i++) 
        {
          for (int j = 0; j < IMAGE_HEIGHT; j++) 
          {
            float gradient = dis_out_[i][j] - 0;
            for (int k = 0; k < NUM_CHANNELS; k++) 
            {
              gen_w1[i][j] -= gradient * input_noise[i][j] * LEARNING_RATE;
              gen_b1[i][j] -= gradient * LEARNING_RATE;
            }
          }
        }
      }
    }
    return 0;
}
