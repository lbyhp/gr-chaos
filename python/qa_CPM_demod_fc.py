#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2017 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import chaos_swig as chaos

class qa_CPM_demod_fc (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # set up fg
	qa_seed=0.8
	qa_seq_len=50
	qa_constell_tab=(-1+0j,1+0j)
	qa_para_tab_chebyshev=(1.4,1.8)
	
	
	expected_data=[-1+0j,1+0j,-1+0j,1+0j]
	src=blocks.file_source(gr.sizeof_float, '/home/edwin/Documents/GNURadio/gr-chaos/python/inputdata_CPM_demod',False)
	tagged_stream=blocks.stream_to_tagged_stream(gr.sizeof_float,1,100,'len_streamtag')
	dst=blocks.vector_sink_c()
	CPDM=chaos.CPM_demod_fc(qa_seq_len,qa_constell_tab,qa_para_tab_chebyshev,'len_streamtag')
	expected_tags=[('len_streamtag',2L,0L),('len_streamtag',2L,2L)]
	self.tb.connect(src,tagged_stream,CPDM,dst)
        self.tb.run ()
	result_data=dst.data()
	result_tags=dst.tags()	
	result_tags=[gr.tag_to_python(x) for x in result_tags];
	result_tags=sorted([(x.key,x.value,x.offset) for x in result_tags])
        # check data
	#print(result_data)
	#print(result_tags)
	self.assertFloatTuplesAlmostEqual(expected_data, result_data,4)
	self.assertEqual(result_tags,expected_tags)

if __name__ == '__main__':
    gr_unittest.run(qa_CPM_demod_fc, "qa_CPM_demod_fc.xml")
