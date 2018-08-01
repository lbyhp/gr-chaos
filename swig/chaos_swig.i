/* -*- c++ -*- */

#define CHAOS_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "chaos_swig_doc.i"

%{
#include "chaos/chaotic_seq_source_f.h"
#include "chaos/CPM_cf.h"
#include "chaos/CPM_demod_fc.h"
#include "chaos/CPM2_cf.h"
#include "chaos/DCSK_mod_cc.h"
#include "chaos/DCSK_demod_cc.h"
#include "chaos/chaotic_prefix_bc.h"
#include "chaos/CPM2_demod_fc.h"
#include "chaos/CPM2_demod_fc.h"
%}





%include "chaos/chaotic_seq_source_f.h"
GR_SWIG_BLOCK_MAGIC2(chaos, chaotic_seq_source_f);

%include "chaos/CPM_cf.h"
GR_SWIG_BLOCK_MAGIC2(chaos, CPM_cf);


%include "chaos/CPM_demod_fc.h"
GR_SWIG_BLOCK_MAGIC2(chaos, CPM_demod_fc);
%include "chaos/CPM2_cf.h"
GR_SWIG_BLOCK_MAGIC2(chaos, CPM2_cf);

%include "chaos/DCSK_mod_cc.h"
GR_SWIG_BLOCK_MAGIC2(chaos, DCSK_mod_cc);
%include "chaos/DCSK_demod_cc.h"
GR_SWIG_BLOCK_MAGIC2(chaos, DCSK_demod_cc);


%include "chaos/chaotic_prefix_bc.h"
GR_SWIG_BLOCK_MAGIC2(chaos, chaotic_prefix_bc);
%include "chaos/CPM2_demod_fc.h"
GR_SWIG_BLOCK_MAGIC2(chaos, CPM2_demod_fc);
