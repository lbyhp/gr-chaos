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

#ifndef INCLUDED_CHAOS_DCSK_MOD_CC_IMPL_H
#define INCLUDED_CHAOS_DCSK_MOD_CC_IMPL_H

#include <chaos/DCSK_mod_cc.h>

namespace gr {
  namespace chaos {

    class DCSK_mod_cc_impl : public DCSK_mod_cc
    {
     private:
      // Nothing to declare in this block.
	float d_seed;
	int d_seq_len;
	gr_complex CPF(gr_complex x_n);
	gr_complex Mean(std::vector<gr_complex> sequence);
	float MaxNorm(std::vector<gr_complex> sequence);
	
     public:
      DCSK_mod_cc_impl(float seed, int seq_len);
      ~DCSK_mod_cc_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace chaos
} // namespace gr

#endif /* INCLUDED_CHAOS_DCSK_MOD_CC_IMPL_H */

