#include <iostream>
#include <sndfile.h>

int main()
{
  // Open the first audio file for reading
  SF_INFO file_info1 = {};
  SNDFILE *file1 = sf_open("../audio/440Hz.wav", SFM_READ, &file_info1);

  // Open the second audio file for reading
  SF_INFO file_info2 = {};
  SNDFILE *file2 = sf_open("../audio/880Hz.wav", SFM_READ, &file_info2);

  std::cout << file_info1.format << std::endl; //	SF_FORMAT_WAV			= 0x010000,		/* Microsoft WAV format (little endian default). */, SF_FORMAT_PCM_16 Signed 16 bit data
  std::cout << file_info2.format << std::endl;

  std::cout << file_info1.channels << std::endl; // 2
  std::cout << file_info1.frames << std::endl; // 440999
  std::cout << file_info2.frames << std::endl; // 440999

  std::cout << file_info1.samplerate << std::endl; // 44100
  std::cout << file_info1.sections << std::endl; // 1
  std::cout << file_info1.seekable << std::endl; // 1
  
  // Check if input files have the same number of channels and sample rate
  if (file_info1.channels != file_info2.channels)
  {
    printf("Error: input files must have the same number of channels\n");
    return EXIT_FAILURE;
  }

  if (file_info1.samplerate != file_info2.samplerate)
  {
    printf("Error: input files must have the same sample rate\n");
    return EXIT_FAILURE;
  }

  // Create a new audio file for writing
  SF_INFO output_info = file_info1; // Use the same format as the first file
  SNDFILE *output_file = sf_open("../audio/output.wav", SFM_WRITE, &output_info);

  // Allocate a buffer for reading and writing audio data
  const int buffer_size = 1024;
  float buffer1[buffer_size];
  float buffer2[buffer_size];

  sf_count_t total_frames = 0; // Total number of frames read

  // Read and write audio data in chunks
  while (true)
  {
    // Read data from the first file
    const sf_count_t samples_read1 = sf_read_float(file1, buffer1, buffer_size);

    // Read data from the second file
    const sf_count_t samples_read2 = sf_read_float(file2, buffer2, buffer_size);

    // Calculate the number of frames read in this iteration
    const sf_count_t frames_read = std::min(samples_read1, samples_read2) / file_info1.channels;

    // If either file has reached the end, break out of the loop
    if (frames_read == 0)
    {
      break;
    }

    float output_buffer[buffer_size];

    for (int i = 0; i < frames_read; i++)
    {
      for (int j = 0; j < file_info1.channels; j++)
      {
        output_buffer[i * file_info1.channels + j] = buffer1[i * file_info1.channels + j] + buffer2[i * file_info2.channels + j];
      }
    }

    // Write the summed data to the output file
    sf_write_float(output_file, output_buffer, frames_read * file_info1.channels);

    // Update the total number of frames read
    total_frames += frames_read;
  }

  // Update the frame count in the output_info structure
  output_info.frames = total_frames;

  // Close the input and output files
  sf_close(file1);
  sf_close(file2);
  sf_close(output_file);

  // Print the updated output file information
  output_file = sf_open("../audio/output.wav", SFM_READ, &output_info);
  std::cout << "================" << std::endl;
  std::cout << output_info.channels << std::endl;    // 2
  std::cout << output_info.frames << std::endl;      // 440999
  std::cout << output_info.samplerate << std::endl;  // 44100
  std::cout << output_info.sections << std::endl;    // 1
  std::cout << output_info.seekable << std::endl;    // 1
  sf_close(output_file);

  return 0;
}
