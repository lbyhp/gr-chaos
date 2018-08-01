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
#include "DCSK_demod_cc_impl.h"

namespace gr {
  namespace chaos {

    DCSK_demod_cc::sptr
    DCSK_demod_cc::make(int seq_len)
    {
      return gnuradio::get_initial_sptr
        (new DCSK_demod_cc_impl(seq_len));
    }

    /*
     * The private constructor
     */
    DCSK_demod_cc_impl::DCSK_demod_cc_impl(int seq_len)
      : gr::sync_decimator("DCSK_demod_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)), seq_len),
	d_seq_len(seq_len)
    {
	set_tag_propagation_policy(TPP_DONT);// dont propagate tags
    }

    /*
     * Our virtual destructor.
     */
    DCSK_demod_cc_impl::~DCSK_demod_cc_impl()
    {
    }

    int
    DCSK_demod_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
	
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];
      int ninput_items=noutput_items*d_seq_len;
      // Do <+signal processing+>
      for(int i=0;i<noutput_items;i++)
      {
	std::vector<gr_complex> reference;
	std::vector<gr_complex> signal;
	for(int j=0;j<d_seq_len/2;j++)
	{
	  reference.push_back(in[(i)*d_seq_len+j]);
	  signal.push_back(in[(i)*d_seq_len+d_seq_len/2+j]);
	}
	float sum=0;
	for(int j=0;j<d_seq_len/2;j++)
	{
	  gr_complex product=reference[j]*signal[j];
	  sum+=product.real();
	}
	if (sum<0)
	{
	  out[i]=gr_complex(-1,0);
	}
	else
	{
	  out[i]=gr_complex(1,0);
	}
	
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace chaos */
} /* namespace gr */

