Snippets
========
### N audio buffers
```cpp
const int num_buffers = 3; // Number of audio buffers to sum
float output_buffer[buffer_size];

// Declare an array of input buffers
float* input_buffers[num_buffers] = {buffer1, buffer2, buffer3}; // Replace buffer1, buffer2, buffer3 with your actual buffer names

for (int i = 0; i < frames_read; i++)
{
    for (int j = 0; j < file_info1.channels; j++)
    {
        output_buffer[i * file_info1.channels + j] = 0; // Initialize the output buffer element to 0

        for (int k = 0; k < num_buffers; k++)
        {
            output_buffer[i * file_info1.channels + j] += input_buffers[k][i * file_info1.channels + j];
        }
    }
}
```
