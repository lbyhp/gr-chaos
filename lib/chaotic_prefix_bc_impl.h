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

#ifndef INCLUDED_CHAOS_CHAOTIC_PREFIX_BC_IMPL_H
#define INCLUDED_CHAOS_CHAOTIC_PREFIX_BC_IMPL_H

#include <chaos/chaotic_prefix_bc.h>

namespace gr {
  namespace chaos {

    class chaotic_prefix_bc_impl : public chaotic_prefix_bc
    {
     private:
	float d_init;
	float d_parameter;
	unsigned int d_header_len;
	

      // Nothing to declare in this block.
     

     protected:
      int calculate_output_stream_length(const gr_vector_int &ninput_items);

     public:
      chaotic_prefix_bc_impl(float init, float parameter, unsigned int header_len, const std::string &len_tag_key);
      ~chaotic_prefix_bc_impl();
     std::vector<float> Logistic_map(float init, float parameter, unsigned int seq_len); 
      // Where all the action really happens
      int work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace chaos
} // namespace gr

#endif /* INCLUDED_CHAOS_CHAOTIC_PREFIX_BC_IMPL_H */

