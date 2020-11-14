/*
 * ASIF encoder, written by Brandon Walters (based on the .wav encoder)
 * CS 3505, Spring 2020
 * 
 * This encoder is designed to take frames of data from another format's decoding, and turn the data from the frames
 * into a single packet that contains all of the encoded file's data. This packet will be sent to the muxer to be
 * turned into a proper .asif file to be used inside ffmpeg.
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/*
 * This function is used to transfer samples from the given frame into our private data array, converting 
 * the samples into the delta form we would like to have. Once every frame is done, we will have a singular packet
 * containing all of the file's data that we can send to the muxer.
 */
static int asif_send_frame(AVCodecContext *avctx, const AVFrame *frame)
{
  asif_encoder_data *data;
  array *sample_array;
  data = avctx->priv_data;
  sample_array = data->growing_array;
  int sample_to_add;
  uint8_t difference;
  int8_t converted_sample;
  uint8_t *subarray;

  // If the frame is not null, it is not the last frame, carry on as normal
  if (frame != NULL)
    {
      // Extend our private array to accomodate these new samples.
      asif_extend_array(&sample_array, data->number_of_channels);
      // If the first frame, we want our first sample from each channel in a different form.
      if (data->is_first_frame == 1)
	{
	  // Nested for loops to scan through each sample of each channel and add it to the private array.
	  for(int i = 0; i < data->number_of_channels - 1; i++)
	    {
	      subarray = frame->extended_data[i];

	      sample_array->array[14 + data->total_samples] = subarray[0];

	      for(int j = 1; j < frame->nb_samples - 1; j++)
		{ 
		  sample_to_add = subarray[j] - subarray[j - 1];

		  // If the sample is too high or too low, clamp it and add the difference to catch up later.
		  if(sample_to_add > 127)
		    {
		      difference = difference + (sample_to_add - 127);
		      sample_to_add = 127;
		    }

		  else if(sample_to_add < -128)
		    {
		      difference = difference + (sample_to_add + 128);
		      sample_to_add = -128;
		    }

		  converted_sample = (int8_t) sample_to_add;
		  sample_array->array[14 + (1000000 * i) + j] = converted_sample;
		}
	    }
	  data->is_first_frame = 0;
	}

      // If not the first frame, go without the first sample's different format
      else
        {
	  // Nested for loops to scan through each sample of each channel and add it to the private array.
	  for(int i = 0; i < data->number_of_channels - 1; i++)
	    {
	      subarray = frame->extended_data[i];

	      for(int j = 0; j < frame->nb_samples - 1; j++)
		{
		  sample_to_add = subarray[j] - subarray[j - 1];

		  // If the sample is too high or too low, clamp it and add the difference to catch up later.
		  if(sample_to_add > 127)
		    {
		      difference = difference + (sample_to_add - 127);
		      sample_to_add = 127;
		    }

		  else if(sample_to_add < -128)
		    {
		      difference = difference + (sample_to_add + 128);
		      sample_to_add = -128;
		    }

		  converted_sample = (int8_t) sample_to_add;
		  sample_array->array[14 + (1000000 * i) + j] = converted_sample;

		}
	    }
	}
      // Increments the number of frames and the total samples processed.
      data->number_of_frames += 1;
      data->total_samples += frame->nb_samples;
    }

  // If the frame was null, mark as done for receive_packet.
  else
    {
      data->last_frame_done = 1;
    }

  return 0;
}