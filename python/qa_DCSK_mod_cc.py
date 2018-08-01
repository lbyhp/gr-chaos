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

class qa_DCSK_mod_cc (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # set up fg
	srcData=(1+0j, -1+0j)
	src=blocks.vector_source_c(srcData);
	DCSK_mod=chaos.DCSK_mod_cc(0.8,6)
	dst=blocks.vector_sink_c()
	self.tb.connect(src,DCSK_mod)
	self.tb.connect(DCSK_mod,dst)
        self.tb.run ()
        # check data
	resultData=dst.data()
	expectedResult=(-0.4108+0j,1+0j,-0.5892+0j,-0.4108+0j,1+0j,-0.5892+0j,-0.4108+0j,1+0j,-0.5892+0j,0.4108+0j,-1+0j,0.5892+0j,)
	print resultData
	for i in range(len(resultData)):
	  
	  self.assertAlmostEqual(resultData[i],expectedResult[i],4)
	

if __name__ == '__main__':
    gr_unittest.run(qa_DCSK_mod_cc, "qa_DCSK_mod_cc.xml")
