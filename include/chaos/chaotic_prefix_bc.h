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


#ifndef INCLUDED_CHAOS_CHAOTIC_PREFIX_BC_H
#define INCLUDED_CHAOS_CHAOTIC_PREFIX_BC_H

#include <chaos/api.h>
#include <gnuradio/tagged_stream_block.h>

namespace gr {
  namespace chaos {

    /*!
     * \brief <+description of block+>
     * \ingroup chaos
     *
     */
    class CHAOS_API chaotic_prefix_bc : virtual public gr::tagged_stream_block
    {
     public:
      typedef boost::shared_ptr<chaotic_prefix_bc> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of chaos::chaotic_prefix_bc.
       *
       * To avoid accidental use of raw pointers, chaos::chaotic_prefix_bc's
       * constructor is in a private implementation
       * class. chaos::chaotic_prefix_bc::make is the public interface for
       * creating new instances.
       */
      virtual std::vector<float> Logistic_map(float init, float parameter, unsigned int seq_len)=0;
      static sptr make(float init, float parameter, unsigned int header_len, const std::string &len_tag_key);
    };

  } // namespace chaos
} // namespace gr

#endif /* INCLUDED_CHAOS_CHAOTIC_PREFIX_BC_H */

