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


#ifndef INCLUDED_CHAOS_CPM2_CF_H
#define INCLUDED_CHAOS_CPM2_CF_H

#include <chaos/api.h>
#include <gnuradio/sync_interpolator.h>

namespace gr {
  namespace chaos {

    /*!
     * \brief <+description of block+>
     * \ingroup chaos
     *
     */
    class CHAOS_API CPM2_cf : virtual public gr::sync_interpolator
    {
     public:
      typedef boost::shared_ptr<CPM2_cf> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of chaos::CPM2_cf.
       *
       * To avoid accidental use of raw pointers, chaos::CPM2_cf's
       * constructor is in a private implementation
       * class. chaos::CPM2_cf::make is the public interface for
       * creating new instances.
       */
      static sptr make(int seq_len,std::vector<gr_complex> constell_tab, float parameter);
    };

  } // namespace chaos
} // namespace gr

#endif /* INCLUDED_CHAOS_CPM2_CF_H */

