/*-----------------------------------------------------------------
LOG
    GEM - Graphics Environment for Multimedia

	Set the target size for a particle system

    Copyright (c) 1997-2000 Mark Danks. mark@danks.org
    Copyright (c) G�nther Geiger. geiger@epy.co.at
    Copyright (c) 2001-2002 IOhannes m zmoelnig. forum::f�r::uml�ute. IEM. zmoelnig@iem.kug.ac.at
    For information on usage and redistribution, and for a DISCLAIMER OF ALL
    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.

-----------------------------------------------------------------*/

#ifndef INCLUDE_PART_TARGETSIZE_H_
#define INCLUDE_PART_TARGETSIZE_H_

#include "Base/GemBase.h"

/*-----------------------------------------------------------------
-------------------------------------------------------------------
CLASS

	part_targetsize
    
	Set the target color for a particle system

DESCRIPTION

-----------------------------------------------------------------*/
class GEM_EXTERN part_targetsize : public GemBase
{
    CPPEXTERN_HEADER(part_targetsize, GemBase)

    public:

	    //////////
	    // Constructor
    	part_targetsize(t_floatarg size, t_floatarg scale);
    	
    	//////////
    	virtual void 	render(GemState *state);

    protected:
    	
    	//////////
    	// Destructor
    	virtual ~part_targetsize();

    	//////////
    	// The scale factor angle
    	float	    	m_scale;

		//////////
		// The target size
		float			m_size;

    	//////////
    	// Scale changed
    	void	    	scaleMess(float scale);
    	
    	//////////
    	// Size changed
    	void	    	sizeMess(float size);
    	
    private:
    	
    	//////////
    	// static member functions
    	static void 	scaleMessCallback(void *data, t_floatarg scale);
    	static void 	sizeMessCallback(void *data, t_floatarg size);
};

#endif	// for header file
