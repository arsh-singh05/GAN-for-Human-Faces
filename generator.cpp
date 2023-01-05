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
