/*-----------------------------------------------------------------
LOG
    GEM - Graphics Environment for Multimedia

    A textoutline

    Copyright (c) 1997-1999 Mark Danks. mark@danks.org
    Copyright (c) G�nther Geiger. geiger@epy.co.at
    Copyright (c) 2001-2002 IOhannes m zmoelnig. forum::f�r::uml�ute. IEM. zmoelnig@iem.kug.ac.at
    For information on usage and redistribution, and for a DISCLAIMER OF ALL
    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.

-----------------------------------------------------------------*/

#ifndef INCLUDE_TEXTOUTLINE_H_
#define INCLUDE_TEXTOUTLINE_H_

#include "Base/TextBase.h"

class GLTTOutlineFont;
class FTFace;

/*-----------------------------------------------------------------
-------------------------------------------------------------------
CLASS
    textoutline
    
    Creates a textoutline string

DESCRIPTION

-----------------------------------------------------------------*/
class GEM_EXTERN textoutline : public TextBase
{
    CPPEXTERN_HEADER(textoutline, TextBase)

    public:

		//////////
		// Constructor
    	textoutline(int argc, t_atom *argv);
    	
    protected:
    	
    	//////////
    	// Destructor
    	virtual ~textoutline();

    	//////////
    	// Do the rendering
    	virtual void 	render(GemState *state);

    	//////////
    	// The font to use
    	virtual void   	fontNameMess(const char *filename);

		//////////
		// Create the actual font from the face
		int				makeFontFromFace();

		//////////
		// Set the font size
		virtual void	setFontSize(int size);

		//////////
		// Set the precision for rendering
		virtual void	setPrecision(float prec);

	    //-----------------------------------
	    // GROUP:	Member variables
	    //-----------------------------------
    
	   	//////////
    	// The font structure
    	GLTTOutlineFont	*m_font;

    	//////////
    	// The font structure
    	FTFace 			*m_face;
};

#endif	// for header file
