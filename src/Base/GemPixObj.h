/*-----------------------------------------------------------------
LOG
    GEM - Graphics Environment for Multimedia

    Base class for pix class gem objects

    Copyright (c) 1997-1999 Mark Danks. mark@danks.org
    Copyright (c) G�nther Geiger. geiger@epy.co.at
    Copyright (c) 2001-2002 IOhannes m zmoelnig. forum::f�r::uml�ute. IEM. zmoelnig@iem.kug.ac.at
    For information on usage and redistribution, and for a DISCLAIMER OF ALL
    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.

-----------------------------------------------------------------*/

#ifndef INCLUDE_GEMPIXOBJ_H_
#define INCLUDE_GEMPIXOBJ_H_

#include "Base/GemBase.h"
#include "Base/GemPixUtil.h"

/*-----------------------------------------------------------------
-------------------------------------------------------------------
CLASS
    GemPixObj
    
    Base class for pix class gem objects

DESCRIPTION

-----------------------------------------------------------------*/
class GEM_EXTERN GemPixObj : public GemBase
{
    public:

        //////////
        // Constructor
    	GemPixObj() : m_processOnOff(1)		{ }
    	
    protected:
    	
    	//////////
    	// Destructor
    	virtual ~GemPixObj()				{ }

    	//////////
    	// The derived class HAS TO override this.
    	// This is called whenever a new image comes through.
    	virtual void 	processImage(imageStruct &image) = 0;
    	
    	//////////
    	// The derived class should override this.
    	// This is called whenever a new gray8 image comes through.
	// The default is to output an error.
    	virtual void 	processGrayImage(imageStruct &image);
    	
    	//////////
    	// If the derived class needs the image resent.
    	//  	This sets the dirty bit on the pixBlock.
    	void	    	setPixModified();
    	
        //////////
        // Turn on/off processing
        void            processOnOff(int on);

        //////////
        int             m_processOnOff;

    	//////////
    	// creation callback
    	static void 	real_obj_setupCallback(t_class *classPtr) { GemBase::real_obj_setupCallback(classPtr);
                                                                    GemPixObj::obj_setupCallback(classPtr); }

    	//////////
    	// The derived class should NOT override this unless they have some
		//		very special behavior.
    	// Do the rendering, which calls processImage or processGrayImage
    	virtual void 	render(GemState *state);

    private:

    	static inline GemPixObj *GetMyClass(void *data) {return((GemPixObj *)((Obj_header *)data)->data);}
    
    	//////////
    	// static member functions
    	static void     obj_setupCallback(t_class *classPtr);
        static void 	floatMessCallback(void *data, float n);
};

#endif	// for header file
