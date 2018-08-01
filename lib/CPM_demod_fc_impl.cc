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
#include "CPM_demod_fc_impl.h"
#include "math.h"

namespace gr {
  namespace chaos {

    CPM_demod_fc::sptr
    CPM_demod_fc::make(int seq_len, std::vector<gr_complex> constell_tab,std::vector<float> para_tab,std::string len_tag_key)
    {
      return gnuradio::get_initial_sptr
        (new CPM_demod_fc_impl(seq_len, constell_tab, para_tab,len_tag_key));
    }

    /*
     * The private constructor
     */
    CPM_demod_fc_impl::CPM_demod_fc_impl(int seq_len, std::vector<gr_complex> constell_tab,std::vector<float> para_tab, std::string len_tag_key)
      : gr::sync_decimator("CPM_demod_fc",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)), seq_len),
	d_seq_len(seq_len),
	d_constell_tab(constell_tab),
	d_para_tab(para_tab),
        d_len_tag_key(len_tag_key)
    {
	set_tag_propagation_policy(TPP_DONT);// dont propagate tags
	if(para_tab.size()!=constell_tab.size())
	{
	  throw std::invalid_argument("seq_len and constell_tab should have the same size");
	}
	
    }

    /*
     * Our virtual destructor.
     */
    CPM_demod_fc_impl::~CPM_demod_fc_impl()
    {
    }
	
    float CPM_demod_fc_impl::mean2para(float mean)
    {
	// convert mean to the parameter of chebyshev map
	//std::cout<<"Mean:"<<mean<<std::endl;
	//if (mean>0.0119||mean<-0.8477)
	//throw std::invalid_argument("mean out of range [0.2318,0.5]");
	if(mean>0.0119)
	mean=0.0119;
	else if(mean<-0.8477)
	mean=-0.8477;
	
	float para=-3.197*pow(mean,4)-5.133*pow(mean,3)-2.971*pow(mean,2)+0.04477*mean+1.99;
	//std::cout<<"Para"<<para<<std::endl;
	return para;
    }

    int
    CPM_demod_fc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];
      int ninput_items=noutput_items*d_seq_len;
      // Do <+signal processing+>
      for (int j=0;j<noutput_items;j++)
      {
        float sum=0;
        for (int i=0;i<d_seq_len;i++)
        {
	  sum+=in[j*d_seq_len+i];
        }
        float mean=sum/d_seq_len;
        float para=mean2para(mean);
        //decide the parameter	
        int tab_size=d_para_tab.size();
        std::vector<float> distanceVec;
        for (int i=0;i<tab_size;i++)
        {
	  distanceVec.push_back(std::abs(para-d_para_tab[i]));//find out the distance to each level
        }	
        //find out the mininum distance
        int min_index=std::min_element(distanceVec.begin(),distanceVec.end())-distanceVec.begin();
        para=d_para_tab[min_index];
	//std::cout<<"out"<<d_para_tab[min_index]<<std::endl;
        *out=d_constell_tab[min_index];
	
        out++;
      }
      //Tag operation

      std::vector<tag_t> tags;
      pmt::pmt_t key=pmt::intern(d_len_tag_key);
      get_tags_in_range(tags,0,nitems_read(0),nitems_read(0)+ninput_items,key);
      if(tags.size()!=0)
      {
        for (unsigned int i=0;i<tags.size();i++)
        {
	  int offset=tags[i].offset;
	  offset=offset/d_seq_len;
	  //pmt::pmt_t key=tags[i].key;
	  long value=pmt::to_long(tags[i].value);
	  value=value/d_seq_len;
	  pmt::pmt_t srcid=tags[i].srcid;
	  //tags[i].value=pmt::from_long(value);	  
	  add_item_tag(0,offset, tags[i].key, pmt::from_long(value),tags[i].srcid);
	  //std::cout<<"tag value:"<<tags[i].value<<std::endl;  
        }
      }	
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace chaos */
} /* namespace gr */

