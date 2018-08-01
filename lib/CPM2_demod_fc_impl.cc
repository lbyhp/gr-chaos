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
#include "CPM2_demod_fc_impl.h"

namespace gr {
  namespace chaos {

    CPM2_demod_fc::sptr
    CPM2_demod_fc::make(int spreading_gain, const std::string &len_tag_key)
    {
      return gnuradio::get_initial_sptr
        (new CPM2_demod_fc_impl(spreading_gain, len_tag_key));
    }

    /*
     * The private constructor
     */
    CPM2_demod_fc_impl::CPM2_demod_fc_impl(int spreading_gain, const std::string &len_tag_key)
      : gr::sync_decimator("CPM2_demod_fc",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)), spreading_gain),
		d_spreading_gain(spreading_gain),
		d_len_tag_key(len_tag_key)
    {
	set_tag_propagation_policy(TPP_DONT); 
    }

    /*
     * Our virtual destructor.
     */
    CPM2_demod_fc_impl::~CPM2_demod_fc_impl()
    {
    }

    int
    CPM2_demod_fc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];
	

      // Do <+signal processing+>
	for (int i=0;i<noutput_items;i++)
	{
	  float mean=0;
	  for (int j=0;j<d_spreading_gain;j++)
	  {
		mean=mean+in[i*d_spreading_gain+j];
	  }
	  mean=mean/d_spreading_gain;
	  if (mean<0)
	  {
	    *out=-1+0j;
	    
	  }
	  else
	  {
	    *out=1+0j;
	  }
	  out++;
	}
	
      //tag propagation
      std::vector<tag_t> tags;
      pmt::pmt_t key=pmt::intern(d_len_tag_key);
      get_tags_in_range(tags,0,nitems_read(0),nitems_read(0)+noutput_items*d_spreading_gain,key);
      if(tags.size()!=0)
      {
        for (unsigned int i=0;i<tags.size();i++)
	{
	  int offset=tags[i].offset;
	  offset=offset/d_spreading_gain;
	  long value=pmt::to_long(tags[i].value);
	  value=value/d_spreading_gain;
	  add_item_tag(0,offset,tags[i].key,pmt::from_long(value),tags[i].srcid);
	} 
      }	
	
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace chaos */
} /* namespace gr */

