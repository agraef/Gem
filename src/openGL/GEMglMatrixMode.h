 /* ------------------------------------------------------------------
  * GEM - Graphics Environment for Multimedia
  *
  *  Copyright (c) 2002-2011 IOhannes m zmölnig. forum::für::umläute. IEM. zmoelnig@iem.at
  *     zmoelnig@iem.kug.ac.at
  *  For information on usage and redistribution, and for a DISCLAIMER
  *  OF ALL WARRANTIES, see the file, "GEM.LICENSE.TERMS"
  *
  *  this file has been generated...
  * ------------------------------------------------------------------
  */

#ifndef _INCLUDE__GEM_OPENGL_GEMGLMATRIXMODE_H_
#define _INCLUDE__GEM_OPENGL_GEMGLMATRIXMODE_H_

#include "Base/GemGLBase.h"

/*
 CLASS
        GEMglMatrixMode
 KEYWORDS
        openGL  0
 DESCRIPTION
        wrapper for the openGL-function
        "glMatrixMode( GLenum mode)"
 */

class GEM_EXTERN GEMglMatrixMode : public GemGLBase
{
        CPPEXTERN_HEADER(GEMglMatrixMode, GemGLBase);

        public:
          // Constructor
          GEMglMatrixMode (int, t_atom*); // CON

        protected:
          // Destructor
          virtual ~GEMglMatrixMode ();
          // Do the rendering
          virtual void  render (GemState *state);

        // variables
          GLenum        mode;           // VAR
          virtual void  modeMess(t_atom);       // FUN


        private:

        // we need some inlets
          t_inlet *m_inlet[1];

        // static member functions
          static void    modeMessCallback (void*,t_symbol*,int,t_atom*);
};
#endif // for header file
