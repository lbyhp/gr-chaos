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
import pmt


def make_tag(key, value, offset, srcid=None):
    tag = gr.tag_t()
    tag.key = pmt.string_to_symbol(key)
    tag.value = pmt.to_pmt(value)
    tag.offset = offset
    if srcid is not None:
        tag.srcid = pmt.to_pmt(srcid)
    return tag

def compare_tags(a, b):
    return a.offset == b.offset and pmt.equal(a.key, b.key) and \
           pmt.equal(a.value, b.value) and pmt.equal(a.srcid, b.srcid)


class qa_chaotic_seq_source_f(gr_unittest.TestCase):
    def setUp(self):
        self.tb = gr.top_block()

    # self.tsb_key="testtag"

    def tearDown(self):
        self.tb = None

    def test_001_t(self):
        #testing non-repeat data no tags
        seed = 0.8
        qa_seq_len = 2
        qa_repeat = False
        qa_map_parameter = 3.98
        #tags = tuple([make_tag('key', 'val', 0, 'src')])
        #tags=['key', 'val', 0, 'src']
        src = chaos.chaotic_seq_source_f(seed,qa_seq_len,qa_map_parameter,repeat=qa_repeat)
        expected_result = (0.6368, 0.9205173254013062)
        dst = blocks.vector_sink_f()
        self.tb.connect(src, dst)
	#print(expected_result)
        self.tb.run()
        # check data
        result = dst.data()
        #print(result)
        self.assertFloatTuplesAlmostEqual(expected_result, result)


    def test_002_t(self):
	#testing tags 
        seed = 0.8
        qa_seq_len = 2
        qa_repeat = False
        qa_map_parameter = 3.98
        tags = tuple([make_tag('key', 'val', 0, 'src')])
        #tags=['key', 'val', 0, 'src']
        src = chaos.chaotic_seq_source_f(seed,qa_seq_len,qa_map_parameter,tags,qa_repeat)
        expected_result = (0.6368, 0.9205173254013062)
	expected_tags=tags[:]
        dst = blocks.vector_sink_f()
        self.tb.connect(src, dst)
	#print(expected_result)
        self.tb.run()
        # check data
	result_data=dst.data()
        result_tags = dst.tags()
        #print(result)
        self.assertFloatTuplesAlmostEqual(expected_result, result_data)
	self.assertTrue(compare_tags(expected_tags[0],result_tags[0]))
	self.assertEqual(len(result_tags),1)

    def test_003(self):
	#testing repeat
	seed = 0.8
        qa_seq_len = 2
        qa_repeat = True
        qa_map_parameter = 3.98
        src_tags = tuple([make_tag('key', 'val', 0, 'src')])
        expected_tags=tuple([make_tag('key','val',0,'src'),
			     make_tag('key','val',2,'src')])
        src = chaos.chaotic_seq_source_f(seed,qa_seq_len,qa_map_parameter,src_tags,qa_repeat)
        expected_result = (0.6368, 0.9205173254013062,0.6368, 0.9205173254013062)
	head=blocks.head(gr.sizeof_float,2*qa_seq_len)
        dst = blocks.vector_sink_f()
        self.tb.connect(src, head, dst)
	#print(expected_result)
        self.tb.run()
        # check data
	result_data=dst.data()
        result_tags = dst.tags()
        #print(result)
	
        self.assertFloatTuplesAlmostEqual(expected_result, result_data)
	self.assertTrue(compare_tags(expected_tags[0],result_tags[0]))
	self.assertTrue(compare_tags(expected_tags[1],result_tags[1]))
	self.assertEqual(len(result_tags),2)


if __name__ == '__main__':
    gr_unittest.run(qa_chaotic_seq_source_f, "qa_chaotic_seq_source_f.xml")
