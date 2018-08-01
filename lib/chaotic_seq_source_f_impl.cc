/* -*- c++ -*- */
/*
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include <iostream>
#include "chaotic_seq_source_f_impl.h"

namespace gr {
  namespace chaos {

    chaotic_seq_source_f::sptr
    chaotic_seq_source_f::make(float seed, int seq_len, float map_parameter, const std::vector<tag_t> &tags, bool repeat)
    {
      return gnuradio::get_initial_sptr
        (new chaotic_seq_source_f_impl(seed, seq_len, map_parameter, tags, repeat));
    }

    /*
     * The private constructor
     */
    chaotic_seq_source_f_impl::chaotic_seq_source_f_impl(float seed, int seq_len, float map_parameter, const std::vector<tag_t> &tags, bool repeat )
      : gr::sync_block("chaotic_seq_source_f",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, sizeof(float))),

	d_seed(seed),
	d_tags(tags),
	d_repeat(repeat),
	d_seq_len(seq_len),
	d_offset(0),
	d_x_n(seed),
	d_map_parameter(map_parameter)


    {

	
        for (int i=0;i<d_seq_len;i++)
        {
	  float temp=chaotic_map(d_map_parameter,d_x_n);
	  d_chaotic_seq.push_back(temp);
	  d_x_n=temp;
	  //std::cout<<"i="<<i<<std::endl;
        }


	if(d_tags.size()==0){
	  d_settags=0;
	  //std::cout<<d_settags<<std::endl;
        }
        else
        {
            d_settags=1;
            set_output_multiple(d_seq_len);//set output buffer size to be multiple times of d_seq_len
        }
    }
    /*
     * Our virtual destructor.
     */
    chaotic_seq_source_f_impl::~chaotic_seq_source_f_impl()
    {
    }

    float chaotic_seq_source_f_impl::chaotic_map(float map_parameter, float x_n)
    {
	// logistic map
	float x_nn=map_parameter*x_n*(1-x_n);

	//chebyshev map
	//if(x_n>1||x_n<0)
	//throw std::invalid_argument("x_n out of range [0,1]");
	//float x_nn=std::cos(map_parameter*std::acos(x_n));
	return x_nn;

    }

    int
    chaotic_seq_source_f_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      float *out = (float *) output_items[0];//cast buffer


      if (d_seq_len==0)
      return -1;

	
      if (d_repeat)
      {
	unsigned int size=d_chaotic_seq.size();
	if(d_settags)
	{

	  int noutputitems_per_vector=d_chaotic_seq.size();
	  
	  for(int i=0;i<noutput_items;i+=noutputitems_per_vector)
	  {
	    memcpy((void *) out, &d_chaotic_seq[0], size*sizeof(float));
	    out+=size;
	    for(unsigned t=0;t<d_tags.size();t++)
	    {
		add_item_tag(0,nitems_written(0)+i+d_tags[t].offset,d_tags[t].key,
                              d_tags[t].value,d_tags[t].srcid);
	    }
	  }
	}
	else
	{

	  for (int i=0;i<noutput_items;i++)
	  {
	    out[i]=d_chaotic_seq[d_offset++];
	    if (d_offset>=d_seq_len)
		d_offset=0;
	  }
	}
	return noutput_items;
      }
      else
      {
	if(d_settags)
	{
	  if(d_offset>=d_seq_len)
	  return -1; //-1 means done

	  unsigned n=std::min((unsigned)d_chaotic_seq.size()-d_offset,(unsigned)noutput_items);
	  for(unsigned i=0;i<n;i++)
	  {
	    out[i]=d_chaotic_seq[d_offset+i];
	  }
	  //tag operation here
	  for(unsigned t = 0; t < d_tags.size(); t++)
	  {
            if((d_tags[t].offset >= d_offset) && (d_tags[t].offset < d_offset+n))
              add_item_tag(0, d_tags[t].offset, d_tags[t].key, d_tags[t].value,
                         d_tags[t].srcid);
          }
	
  	  d_offset+=n;
	  return n;
	}
	else
	{
	  if(d_offset>=d_seq_len)
	  return -1; //-1 means done

	  unsigned n=std::min((unsigned)d_chaotic_seq.size()-d_offset,(unsigned)noutput_items);
	  for(unsigned i=0;i<n;i++)
	  {
	    out[i]=d_chaotic_seq[d_offset+i];
	  }
	  d_offset+=n;
	  return n;
	}
	
      }



      // Tell runtime system how many output items we produced.
      //return noutput_items;
    }

  } /* namespace chaos */
} /* namespace gr */

