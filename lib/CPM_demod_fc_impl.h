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

#ifndef INCLUDED_CHAOS_CPM_DEMOD_FC_IMPL_H
#define INCLUDED_CHAOS_CPM_DEMOD_FC_IMPL_H

#include <chaos/CPM_demod_fc.h>

namespace gr {
  namespace chaos {

    class CPM_demod_fc_impl : public CPM_demod_fc
    {
     private:
     int d_seq_len;
     std::vector<gr_complex> d_constell_tab;
     std::vector<float> d_para_tab;
     std::string d_len_tag_key;
     protected:	
     float mean2para(float mean);
     public:
      CPM_demod_fc_impl(int seq_len, std::vector<gr_complex> constell_tab,std::vector<float> para_tab,std::string len_tag_key);
      ~CPM_demod_fc_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace chaos
} // namespace gr

#endif /* INCLUDED_CHAOS_CPM_DEMOD_FC_IMPL_H */

