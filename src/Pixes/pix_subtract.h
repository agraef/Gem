/*-----------------------------------------------------------------
LOG
    GEM - Graphics Environment for Multimedia

    Subtract two images.

    Copyright (c) 1997-1998 Mark Danks. mark@danks.org
    Copyright (c) G�nther Geiger. geiger@epy.co.at
    Copyright (c) 2001-2002 IOhannes m zmoelnig. forum::f�r::uml�ute. IEM. zmoelnig@iem.kug.ac.at
    For information on usage and redistribution, and for a DISCLAIMER OF ALL
    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.

-----------------------------------------------------------------*/

#ifndef INCLUDE_PIX_SUBTRACT_H_
#define INCLUDE_PIX_SUBTRACT_H_

#include "Base/GemPixDualObj.h"

/*-----------------------------------------------------------------
-------------------------------------------------------------------
CLASS
    pix_subtract
    
    Subtract two images.

KEYWORDS
    pix
    
DESCRIPTION

-----------------------------------------------------------------*/
class GEM_EXTERN pix_subtract : public GemPixDualObj
{
    CPPEXTERN_HEADER(pix_subtract, GemPixDualObj)

    public:

        //////////
    	// Constructor
    	pix_subtract();
    	
    protected:
    	
    	//////////
    	// Destructor
    	virtual ~pix_subtract();

    	//////////
    	// Do the processing
    	virtual void 	processDualImage(imageStruct &image, imageStruct &right);
};

#endif	// for header file
