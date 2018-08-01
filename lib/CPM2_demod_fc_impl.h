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

#ifndef INCLUDED_CHAOS_CPM2_DEMOD_FC_IMPL_H
#define INCLUDED_CHAOS_CPM2_DEMOD_FC_IMPL_H

#include <chaos/CPM2_demod_fc.h>

namespace gr {
  namespace chaos {

    class CPM2_demod_fc_impl : public CPM2_demod_fc
    {
     private:
	int d_spreading_gain;
	std::string d_len_tag_key;
      // Nothing to declare in this block.

     public:
      CPM2_demod_fc_impl(int spreading_gain, const std::string &len_tag_key);
      ~CPM2_demod_fc_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace chaos
} // namespace gr

#endif /* INCLUDED_CHAOS_CPM2_DEMOD_FC_IMPL_H */

