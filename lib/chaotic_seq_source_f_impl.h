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

#ifndef INCLUDED_CHAOS_CHAOTIC_SEQ_SOURCE_F_IMPL_H
#define INCLUDED_CHAOS_CHAOTIC_SEQ_SOURCE_F_IMPL_H

#include <chaos/chaotic_seq_source_f.h>

namespace gr {
  namespace chaos {

    class chaotic_seq_source_f_impl : public chaotic_seq_source_f
    {
     
     private:
      // Nothing to declare in this block.
      float d_seed;
      std::vector<tag_t> d_tags;
      bool d_settags;
      bool d_repeat;
      int d_seq_len;
      unsigned int d_offset;
      float d_map_parameter;
      float d_x_n;
      std::vector<float> d_chaotic_seq;

     public:
      chaotic_seq_source_f_impl(float seed,int seq_len, float map_parameter, const std::vector<tag_t> &tags, bool repeat);
      ~chaotic_seq_source_f_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
      float chaotic_map(float map_parameter, float x_n);
    };

  } // namespace chaos
} // namespace gr

#endif /* INCLUDED_CHAOS_CHAOTIC_SEQ_SOURCE_F_IMPL_H */

