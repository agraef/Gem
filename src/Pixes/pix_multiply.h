/*-----------------------------------------------------------------
LOG
    GEM - Graphics Environment for Multimedia

    Multiply two images together.

    Copyright (c) 1997-1998 Mark Danks
    Copyright (c) G�nther Geiger. geiger@epy.co.at
    Copyright (c) 2001-2002 IOhannes m zmoelnig. forum::f�r::uml�ute. IEM. zmoelnig@iem.kug.ac.at
    For information on usage and redistribution, and for a DISCLAIMER OF ALL
    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.

-----------------------------------------------------------------*/

#ifndef INCLUDE_PIX_MULTIPLY_H_
#define INCLUDE_PIX_MULTIPLY_H_

#include "Base/GemPixDualObj.h"

/*-----------------------------------------------------------------
-------------------------------------------------------------------
CLASS
    pix_multiply
    
    Multiply two images together.

KEYWORDS
    pix
    
DESCRIPTION

-----------------------------------------------------------------*/
class GEM_EXTERN pix_multiply : public GemPixDualObj
{
    CPPEXTERN_HEADER(pix_multiply, GemPixDualObj)

    public:

	    //////////
    	// Constructor
    	pix_multiply();
    	
    protected:
    	
    	//////////
    	// Destructor
    	virtual ~pix_multiply();

    	//////////
    	// Do the processing
    	virtual void 	processDualImage(imageStruct &image, imageStruct &right);

    	//////////
    	//  This is called whenever a new image comes through.
		//	The left image is an RGBA, the right is a gray8
    	virtual void 	processRightGray(imageStruct &image, imageStruct &right); 	

    	//////////
    	//  This is called whenever a new image comes through.
		//	Both images are gray8
    	virtual void 	processBothGray(imageStruct &image, imageStruct &right); 	
};

#endif	// for header file
