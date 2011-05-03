/*-----------------------------------------------------------------
LOG
    GEM - Graphics Environment for Multimedia

    apply a FreeFrame effect to an image

    Copyright (c) 1997-1999 Mark Danks. mark@danks.org
    Copyright (c) 2001-2002 IOhannes m zmoelnig. forum::f�r::uml�ute. IEM. zmoelnig@iem.kug.ac.at
    Copyright (c) 2002 James Tittle & Chris Clepper
    For information on usage and redistribution, and for a DISCLAIMER OF ALL
    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.

-----------------------------------------------------------------*/

#ifndef INCLUDE_PIX_FREEFRAME_H_
#define INCLUDE_PIX_FREEFRAME_H_

#include "Base/GemPixObj.h"
/*
#if defined SIZEOF_VOID_P && defined SIZEOF_UNSIGNED_INT
# if SIZEOF_VOID_P != SIZEOF_UNSIGNED_INT
#  define DONT_WANT_FREEFRAME
# endif
#endif
*/
#ifndef DONT_WANT_FREEFRAME

#if defined _WIN32 && !defined WIN32
# define WIN32
#endif
#include "FreeFrame.h"

#if defined(__linux__) || defined(__FreeBSD_kernel__)
# define T_FFPLUGMAIN plugMainType*
#else
# define T_FFPLUGMAIN FF_Main_FuncPtr
#endif

#endif /* DONT_WANT_FREEFRAME */



/*-----------------------------------------------------------------
-------------------------------------------------------------------
CLASS
    pix_freeframe
    
    load a FreeFrame-plugin and use it do process the image-data

KEYWORDS
    pix
    
DESCRIPTION
   
-----------------------------------------------------------------*/

class GEM_EXTERN pix_freeframe : public GemPixObj
{
    CPPEXTERN_HEADER(pix_freeframe, GemPixObj)

    public:

    //////////
    // Constructor
    pix_freeframe(t_symbol*s);
    	
 protected:
    	
    //////////
    // Destructor
    virtual ~pix_freeframe();

#ifndef DONT_WANT_FREEFRAME

    //////////
    // Do the processing
    void 	processImage(imageStruct &image);

    imageStruct m_image;
    T_FFPLUGMAIN m_plugin;
    unsigned int m_instance;

    char	 m_pluginName[17];
    char	 m_pluginId[5];
    unsigned int m_numparameters;

    t_inlet**m_inlet;

    void parmMess(int param, t_atom*value);

    void openMess(t_symbol*name);
    void closeMess(void);
#endif /* DONT_WANT_FREEFRAME */

 private:
    static void parmCallback(void *data, t_symbol*s, int argc, t_atom*argv);
    static void openCallback(void *data, t_symbol*s);
};

#endif	// for header file
