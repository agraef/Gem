////////////////////////////////////////////////////////
//
// GEM - Graphics Environment for Multimedia
//
// zmoelnig@iem.kug.ac.at
//
// Implementation file
//
//    Copyright (c) 1997-1998 Mark Danks.
//    Copyright (c) G�nther Geiger.
//    Copyright (c) 2001-2002 IOhannes m zmoelnig. forum::f�r::uml�ute. IEM
//    For information on usage and redistribution, and for a DISCLAIMER OF ALL
//    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.
//
/////////////////////////////////////////////////////////

#include "pix_normalize.h"

CPPEXTERN_NEW(pix_normalize)

/////////////////////////////////////////////////////////
//
// pix_normalize
//
/////////////////////////////////////////////////////////
// Constructor
//
/////////////////////////////////////////////////////////
pix_normalize :: pix_normalize()
{
  //    inlet_new(this->x_obj, &this->x_obj->ob_pd, gensym("float"), gensym("ft1"));
  //    inlet_new(this->x_obj, &this->x_obj->ob_pd, gensym("list"), gensym("vec_mask"));

  //    m_mask[chRed] = m_mask[chGreen] = m_mask[chBlue] = m_mask[chAlpha] = 255;
}

/////////////////////////////////////////////////////////
// Destructor
//
/////////////////////////////////////////////////////////
pix_normalize :: ~pix_normalize()
{ }

/////////////////////////////////////////////////////////
// processImage
//
/////////////////////////////////////////////////////////
void pix_normalize :: processImage(imageStruct &image)
{
  unsigned char min=255, max=0;
  int datasize = image.xsize * image.ysize;// *image.csize;
  unsigned char *pixels = image.data;
  int n = datasize;

  while(n--){
    // think about this more carefully, to allow normalization for single channels...
    unsigned char red=pixels[chRed], green=pixels[chGreen], blue=pixels[chBlue];
#if 0
    unsigned char val;
    // shell sort the TriColor
    if (red>green){
      val=red;
      red=green;
      green=val;
    }
    if (green>blue){
      val=green;
      green=blue;
      blue=val;
    }
    if (red>green){
      val=red;
      red=green;
      green=val;
    }      

    if (min>red) min=red;
    if (max<blue)max=blue;
#else
    if (min>red)  min=red;
    if (min>green)min=green;
    if (min>blue) min=blue;
    if (max<red)  max=red;
    if (max<green)max=green;
    if (max<blue) max=blue;    
#endif
    pixels+=4;
  }

  t_float scale=(max-min)?255./(max-min):0;
 
  n = datasize*image.csize;
  pixels=image.data;
  while(n--){
    *pixels = (unsigned char)(*(pixels-min)*scale);
    pixels++;
  }
}

/////////////////////////////////////////////////////////
// static member function
//
/////////////////////////////////////////////////////////
void pix_normalize :: obj_setupCallback(t_class *classPtr)
{
    class_addmethod(classPtr, (t_method)&pix_normalize::vecMaskMessCallback,
    	    gensym("vec_mask"), A_GIMME, A_NULL);
    class_addmethod(classPtr, (t_method)&pix_normalize::floatMaskMessCallback,
    	    gensym("ft1"), A_FLOAT, A_NULL);
}
void pix_normalize :: vecMaskMessCallback(void *data, t_symbol *, int argc, t_atom *argv)
{
}
void pix_normalize :: floatMaskMessCallback(void *data, t_floatarg mask)
{
}
