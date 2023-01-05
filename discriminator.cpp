// Training the discriminator

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
