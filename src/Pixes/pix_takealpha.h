/*-----------------------------------------------------------------
LOG
    GEM - Graphics Environment for Multimedia

    replace the alpha-channel of the 1st image by that of the 2nd image 

    Copyright (c) 1997-1998 Mark Danks
    Copyright (c) G�nther Geiger. geiger@epy.co.at
    Copyright (c) 2001-2002 IOhannes m zmoelnig. forum::f�r::uml�ute. IEM. zmoelnig@iem.kug.ac.at
    For information on usage and redistribution, and for a DISCLAIMER OF ALL
    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.

-----------------------------------------------------------------*/

#ifndef INCLUDE_PIX_TAKEALPHA_H_
#define INCLUDE_PIX_TAKEALPHA_H_

#include "Base/GemPixDualObj.h"

/*-----------------------------------------------------------------
-------------------------------------------------------------------
CLASS
    pix_takealpha
    
    Add two images together.

KEYWORDS
    pix
    
DESCRIPTION

-----------------------------------------------------------------*/
class GEM_EXTERN pix_takealpha : public GemPixDualObj
{
    CPPEXTERN_HEADER(pix_takealpha, GemPixDualObj)

    public:

	    //////////
    	// Constructor
    	pix_takealpha();
    	
    protected:
    	
    	//////////
    	// Destructor
    	virtual ~pix_takealpha();

    	//////////
    	// Do the processing
    	virtual void 	processDualImage(imageStruct &image, imageStruct &right);

    	//////////
    	// Do the processing
    	virtual void 	processDualGray(imageStruct &image, imageStruct &right);

    	//////////
    	// Do the processing
    	virtual void 	processRightGray(imageStruct &image, imageStruct &right);
};

#endif	// for header file
