/* -*- c++ -*- */
/* 
 * Copyright 2018 <+YOU OR YOUR COMPANY+>.
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
#include "chaotic_prefix_bc_impl.h"

namespace gr {
  namespace chaos {

    chaotic_prefix_bc::sptr
    chaotic_prefix_bc::make(float init, float parameter, unsigned int header_len, const std::string &len_tag_key)
    {
      return gnuradio::get_initial_sptr
        (new chaotic_prefix_bc_impl(init, parameter, header_len, len_tag_key));
    }

    /*
     * The private constructor
     */
    chaotic_prefix_bc_impl::chaotic_prefix_bc_impl(float init, float parameter, unsigned int header_len, const std::string &len_tag_key)
      : gr::tagged_stream_block("chaotic_prefix_bc",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)), len_tag_key),
              d_init(init),
	      d_parameter(parameter),
	      d_header_len(header_len)
    {
	set_tag_propagation_policy(TPP_DONT);// dont propagate tags
    }

    /*
     * Our virtual destructor.
     */
    chaotic_prefix_bc_impl::~chaotic_prefix_bc_impl()
    {
    }

    std::vector<float> chaotic_prefix_bc_impl::Logistic_map(float init, float parameter, unsigned int seq_len)
    {
	//float parameter=3.62;
	std::vector<float> chaotic_seq;
	chaotic_seq.push_back(init);
	float x_nn;
	float sum=d_init;
	for (int i=1;i<seq_len;i++)
	{
	   x_nn=parameter*chaotic_seq[i-1]*(1-chaotic_seq[i-1]);
	   
	//   x_nn=0;
	   sum+=x_nn;
	   chaotic_seq.push_back(x_nn);	
	}
	//normalize chaotic_seq
	sum=sum/seq_len;

	float maxabs=0;
	for (int i=0;i<seq_len;i++)
	{
	  chaotic_seq[i]=chaotic_seq[i]-sum;
	  if (std::abs(chaotic_seq[i])>maxabs)
          {
	     maxabs=std::abs(chaotic_seq[i]);
	  }
		
	}

	for (int i=0;i<seq_len;i++)
	{
	  chaotic_seq[i]=chaotic_seq[i]/maxabs;
	  
	}
	return chaotic_seq;

    }

    int
    chaotic_prefix_bc_impl::calculate_output_stream_length(const gr_vector_int &ninput_items)
    {
      int noutput_items = d_header_len;
      return noutput_items ;
    }

    int
    chaotic_prefix_bc_impl::work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];
	
      std::vector<float> chaotic_float=Logistic_map(d_init, d_parameter, d_header_len);
      std::vector<gr_complex> chaotic_complex;
      for (int i=0;i<d_header_len;i++)
      {

	chaotic_complex.push_back(gr_complex(chaotic_float[i],0));
	
      }
      //std::vector<gr_complex> *p=&chaotic_complex; 
      memcpy((void *)out,&chaotic_complex[0],d_header_len*sizeof(gr_complex));
	out+=d_header_len;
      // Do <+signal processing+>
	noutput_items=d_header_len;
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace chaos */
} /* namespace gr */

