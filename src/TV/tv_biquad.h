/*-----------------------------------------------------------------
  LOG
  GEM - Graphics Environment for Multimedia

  apply a 2p2z-filter on a sequence of pixBlocks
  
  Copyright (c) 1997-1999 Mark Danks. mark@danks.org
  Copyright (c) G�nther Geiger. geiger@epy.co.at
  Copyright (c) 2001-2002 IOhannes m zmoelnig. forum::f�r::uml�ute. IEM. zmoelnig@iem.kug.ac.at
  For information on usage and redistribution, and for a DISCLAIMER OF ALL
  WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.
	
  -----------------------------------------------------------------*/

/*-----------------------------------------------------------------
  tv_biquad

  IOhannes m zmoelnig
  mailto:zmoelnig@iem.kug.ac.at
	
  this code is published under the Gnu GeneralPublicLicense that should be distributed with gem & pd
	  
  -----------------------------------------------------------------*/

#ifndef INCLUDE_TV_BIQUAD_H_
#define INCLUDE_TV_BIQUAD_H_

#include "Base/GemPixObj.h"

/*-----------------------------------------------------------------
  -------------------------------------------------------------------
  CLASS
  tv_biquad

  KEYWORDS
  pix
  
  DESCRIPTION
	
  -----------------------------------------------------------------*/
class GEM_EXTERN tv_biquad : public GemPixObj
{
  CPPEXTERN_HEADER(tv_biquad, GemPixObj)
		
    public:
	
  //////////
  // Constructor
  tv_biquad();
	
 protected:
	
  //////////
  // Destructor
  virtual ~tv_biquad();
	
  //////////
  // create a buffer that fits to the current imageSize
  virtual void   create_buffer(imageStruct image);
	
  //////////
  // delete the buffer
  virtual void   delete_buffer();
	
  //////////
  // clear the buffer
  virtual void   clear_buffer();

  //////////
  // Do the processing
  virtual void 	processImage(imageStruct &image);

  //////////
  // set-flag
  bool set;
	
  //////////
  // the image-latches
  imageStruct    prev;
  imageStruct	 last;
	
  //////////
  // the biquad-factors
  t_float ff1, ff2, ff3, fb1, fb2, fb0;
	
  //////////
  // the methods
  static void setMessCallback(void *data);
  static void faktorMessCallback(void *data, t_symbol *s, int argc, t_atom* argv);

};

#endif	// for header file
