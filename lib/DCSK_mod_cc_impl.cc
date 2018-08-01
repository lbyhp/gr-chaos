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
#include "DCSK_mod_cc_impl.h"
#include <algorithm>

namespace gr {
  namespace chaos {

    DCSK_mod_cc::sptr
    DCSK_mod_cc::make(float seed, int seq_len)
    {
      return gnuradio::get_initial_sptr
        (new DCSK_mod_cc_impl(seed, seq_len));
    }

    /*
     * The private constructor
     */
    DCSK_mod_cc_impl::DCSK_mod_cc_impl(float seed, int seq_len)
      : gr::sync_interpolator("DCSK_mod_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)), seq_len),
	d_seed(seed),
	d_seq_len(seq_len)
    {}

    /*
     * Our virtual destructor.
     */
    DCSK_mod_cc_impl::~DCSK_mod_cc_impl()
    {
    }

    gr_complex DCSK_mod_cc_impl::CPF(gr_complex x_n)
    {
	
	gr_complex x_nn=gr_complex(1)-gr_complex(2.0)*pow(x_n,2);
	return x_nn;
    }

    gr_complex DCSK_mod_cc_impl::Mean(std::vector<gr_complex> sequence)
    {
	gr_complex sum=0;
	for (int i=0;i<sequence.size();i++)
	{
	  sum+=sequence[i];
	}
	gr_complex meanValue=sum/gr_complex(sequence.size());
	return meanValue;
    }

    float DCSK_mod_cc_impl::MaxNorm(std::vector<gr_complex> sequence)
    {
	std::vector<float> norms;
	for (int i=0;i<sequence.size();i++)
	{
	  float temp=std::abs(sequence[i]);
	  norms.push_back(temp);
	}
	float max=*std::max_element(norms.begin(),norms.end());
	return max;
    }

    int
    DCSK_mod_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];
	//generate chaotic sequence
	std::vector<gr_complex> chaotic_seq;
	gr_complex x_nn=d_seed;
	for (int i=0;i<d_seq_len/2;i++)
	{
	  gr_complex temp=CPF(x_nn);
	  x_nn=temp;
	  chaotic_seq.push_back(temp);
	}
	gr_complex meanValue=Mean(chaotic_seq);

	for (int i=0;i<chaotic_seq.size();i++)
	{
	  chaotic_seq[i]=chaotic_seq[i]-meanValue;
	}
	float coe_norm=MaxNorm(chaotic_seq);

	//shrink to [-1 1]
	for (int i=0;i<chaotic_seq.size();i++)
	{
	  chaotic_seq[i].real()/=coe_norm;
	  chaotic_seq[i].imag()/=coe_norm;
	  
	}
        //sign-reversed sequence
	std::vector<gr_complex> negative_seq;
	for (int i=0;i<chaotic_seq.size();i++)
	{
	  negative_seq.push_back(-chaotic_seq[i]);
	  
	}
	int ninput_items=noutput_items/d_seq_len;

 
	for (int i=0;i<ninput_items;i++)
	{
	  memcpy((void *)out, &chaotic_seq[0],chaotic_seq.size()*sizeof(gr_complex));
	  out+=chaotic_seq.size();
  

	  if (in[i]==gr_complex(-1,0))
	  {
		memcpy((void *) out, &negative_seq[0],negative_seq.size()*sizeof(gr_complex));
		out+=negative_seq.size();
	
	  }
	  else
	  {	
		if(in[i]==gr_complex(1,0))
		{
		memcpy((void *) out, &chaotic_seq[0],chaotic_seq.size()*sizeof(gr_complex));
		out+=chaotic_seq.size();
		}
		else
		{
		throw;
		}
	  }
	}
      // Do <+signal processing+>

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace chaos */
} /* namespace gr */

