/*-----------------------------------------------------------------
LOG
    GEM - Graphics Environment for Multimedia

    Turn on alpha blending
    
    Copyright (c) 1997-1999 Mark Danks. mark@danks.org
    Copyright (c) G�nther Geiger. geiger@epy.co.at
    Copyright (c) 2001-2002 IOhannes m zmoelnig. forum::f�r::uml�ute. IEM. zmoelnig@iem.kug.ac.at
    For information on usage and redistribution, and for a DISCLAIMER OF ALL
    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.

-----------------------------------------------------------------*/

#ifndef INCLUDE_ALPHA_H_
#define INCLUDE_ALPHA_H_

#include "Base/GemBase.h"

/*-----------------------------------------------------------------
-------------------------------------------------------------------
CLASS
    alpha
    
    Turn on alpha blending

DESCRIPTION
    
    "alphastate" - whether to use alpha blending
    
-----------------------------------------------------------------*/
class GEM_EXTERN alpha : public GemBase
{
    CPPEXTERN_HEADER(alpha, GemBase)

    public:

        //////////
        // Constructor
    	alpha();
    	
    protected:
    	
    	//////////
    	// Destructor
    	virtual ~alpha();

    	//////////
    	// Do the rendering
    	virtual void 	render(GemState *state);

    	//////////
    	// Turn off alpha blending
    	virtual void 	postrender(GemState *state);

    	//////////
    	// alpha blending state
    	int	    	    m_alphaState;

    	//////////
    	// alpha test state
    	int	    	    m_alphaTest;

    	//////////
    	// Alpha state changed
    	void	    	alphaMess(int alphaState);
    	
     	//////////
    	// Alpha test changed
    	void	    	testMess(int alphaTest);
    	
   private:
    	
    	//////////
    	// static member functions
    	static void 	alphaMessCallback(void *data, t_floatarg alpha);
        static void     testMessCallback(void *data, t_floatarg alphaTest);

};

#endif	// for header file
