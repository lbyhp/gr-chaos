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
#include "CPM_cf_impl.h"
#include <stdexcept>
#include "stdlib.h"

namespace gr {
  namespace chaos {

    CPM_cf::sptr
    CPM_cf::make(float seed, int seq_len,std::vector<gr_complex> constell_tab,std::vector<float> para_tab)
    {
      return gnuradio::get_initial_sptr
        (new CPM_cf_impl(seed, seq_len, constell_tab, para_tab));
    }

    /*
     * The private constructor
     */
    CPM_cf_impl::CPM_cf_impl(float seed, int seq_len,std::vector<gr_complex> constell_tab,std::vector<float> para_tab)
      : gr::sync_interpolator("CPM_cf",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(float)), seq_len),
        d_seed(seed),
	d_seq_len(seq_len),
	d_constell_tab(constell_tab),
	d_para_tab(para_tab)
    {
	set_tag_propagation_policy(TPP_DONT);// dont propagate tags
	if(para_tab.size()!=constell_tab.size())
	{
	  throw std::invalid_argument("seq_len and constell_tab should have the same size");
	}
	set_output_multiple(d_seq_len);//set output buffer size to be multiple times of d_seq_len
    }

    /*
     * Our virtual destructor.
     */
    CPM_cf_impl::~CPM_cf_impl()
    {
    }
    float CPM_cf_impl::chaotic_map(float map_parameter, float x_n)
    {
	// logistic map
	//float x_nn=map_parameter*x_n*(1-x_n);

	//chebyshev map
	if(x_n>1||x_n<-1)
	throw std::invalid_argument("x_n out of range [-1,1]");
	//std::cout<<"map_parameter"<<map_parameter<<std::endl;
	if(map_parameter>2||map_parameter<=1.3)
	throw std::invalid_argument("map parameter out of range (1.3,2]");
	float x_nn=std::cos(map_parameter*std::acos(x_n));
	return x_nn;

    }
    int
    CPM_cf_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      float *out = (float *) output_items[0];

      // Do <+signal processing+>
      int ninput_items=noutput_items/d_seq_len;//the input number is the output number/interpolation
      for (unsigned int i=0;i<ninput_items;i++)//for every input items in port 0
      {
	int indicator=-1;
	for (unsigned j=0;j<d_constell_tab.size();j++)
	{
	  //std::cout<<"input of CPM:"<<in[i]<<std::endl;
	  //std::cout<<"type of input:"<<typeid(in[i]).name()<<std::endl;
	  if(in[i]==d_constell_tab[j])
	  {
	    indicator=j;
	    break;
	  }
	}
	if (indicator==-1)
	throw std::runtime_error("Can't find the correct indicator/n");

	float para=d_para_tab[indicator];
	std::vector<float> chaotic_seq;

	// random initial condition
	  float x_nn=static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	  //std::cout<<x_nn<<std::endl;
	  
	  if (d_seed==233)
	  {
        	float x_nn=0.8; //fixed seed
	  //std::cout<<"d_seed=233"<<(d_seed==233)<<std::endl;
          
	//  std::cin.get();
	  }
	//std::cout<<"x_nn"<<x_nn<<std::endl;


	for (unsigned int j=0;j<d_seq_len;j++)
	{

	  

	  float temp=chaotic_map(para,x_nn);
	  chaotic_seq.push_back(temp);
	  x_nn=temp;
	}
	memcpy((void *)out, &chaotic_seq[0],d_seq_len*sizeof(float));
	out+=d_seq_len;
      }
      //modify tag length value
      std::vector<tag_t> tags;
      //read the tags in current input buffer	
      get_tags_in_range(tags,0,nitems_read(0),nitems_read(0)+ninput_items);
      if(tags.size()!=0)
      {
        for (unsigned int i=0;i<tags.size();i++)
        {
	  int offset=tags[i].offset;
	  offset=offset*d_seq_len;
	  pmt::pmt_t key=tags[i].key;
	  long value=pmt::to_long(tags[i].value);
	  value=value*d_seq_len;
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

