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


/////////////////////////////////////////////////////////
//
// tv_rtx
//
// this the RealTimeX - transformator, that does  a kind of swapping the time and the x axis
// of a video (or any series of pictures) ON THE FLY 
//
// for more information, on how this works, look at
// http://umlaeute.mur.at/rtx
//
//   2803:forum::f�r::uml�ute:2000
//   0409:forum::f�r::uml�ute:2000
//   1801:forum::f�r::uml�ute:2001  added the second mode
//   IOhannes m zmoelnig
//   mailto:zmoelnig@iem.kug.ac.at
//
//   this code is published under the Gnu GeneralPublicLicense that should be distributed with gem & pd
//
/////////////////////////////////////////////////////////

#include "tv_rtx.h"
#include <string.h>

CPPEXTERN_NEW(tv_rtx)

/////////////////////////////////////////////////////////
//
// tv_rtx
//
/////////////////////////////////////////////////////////
// Constructor
//
/////////////////////////////////////////////////////////
tv_rtx :: tv_rtx()
{ 
   imageStruct image;

   image.xsize  = image.ysize = 64;
   image.format = GL_RGBA;
   image.csize  = 4;

   create_buffer(image);

   bufcount  = 0;
   mode = true;

   set_buffer=true;
}

/////////////////////////////////////////////////////////
// Destructor
//
/////////////////////////////////////////////////////////
tv_rtx :: ~tv_rtx()
{
   // clean my buffer
   delete_buffer();
}

/////////////////////////////////////////////////////////
// CreateBuffer
//
/////////////////////////////////////////////////////////
void tv_rtx :: create_buffer(imageStruct image)
{
   long dataSize = image.xsize * image.xsize * image.ysize * image.csize * sizeof(unsigned char); // only 1 channel !!, to keep data-size handy

   buffer.xsize = image.xsize;
   buffer.ysize = image.ysize;
   buffer.csize = image.csize;

   buffer.data = new unsigned char[dataSize];
   memset(buffer.data, 0, dataSize);
}

/////////////////////////////////////////////////////////
// DeleteBuffer
//
/////////////////////////////////////////////////////////
void tv_rtx :: delete_buffer()
{
    delete [] buffer.data;
    buffer.data = NULL;
}


/////////////////////////////////////////////////////////
// ClearBuffer
//
/////////////////////////////////////////////////////////
void tv_rtx :: clear_buffer()
{
		memset(buffer.data, 0, buffer.xsize * buffer.xsize * buffer.ysize * buffer.csize * sizeof(unsigned char));
}

/////////////////////////////////////////////////////////
// processImage
//
/////////////////////////////////////////////////////////
void tv_rtx :: processImage(imageStruct &image)
{
  // assume that the pix_size does not change !
  if (image.xsize != buffer.xsize || image.ysize != buffer.ysize || image.csize != buffer.csize) {
    long dataSize = image.xsize * image.xsize * image.ysize * image.csize * sizeof(unsigned char);
    delete [] buffer.data;
    buffer.data = new unsigned char[dataSize];
    buffer.xsize = image.xsize;
    buffer.ysize = image.ysize;
    buffer.csize = image.csize;
    memset(buffer.data, 0, dataSize);
  }

   int pixsize = image.ysize * image.xsize;
   int count = pixsize;

   int cols=image.xsize, c=0, c1=0;
   int rows=image.ysize, r=0;

   unsigned char *pixels = image.data;
   unsigned char *wp;			// write pointer
   unsigned char *rp;			// read pointer

   // first copy the pixels into our buffer
   if (!set_buffer) {
     wp = buffer.data + pixsize * buffer.csize * bufcount;
     memcpy(wp, pixels, pixsize * buffer.csize * sizeof(unsigned char));
   } else { // fill the buffer with the current frame
     // this might be useful to prevent the black screen in the beginning.
     // "set" message
     c=cols;
     while (c--) {
       wp = buffer.data + pixsize * buffer.csize * c;
       memcpy(wp, pixels, pixsize * buffer.csize * sizeof(unsigned char));
       set_buffer=false;
     }
   }

   // then copy the buffer rtx-transformed back to the pixels
   while (c < cols) {
	   c1 = mode?((c+cols-bufcount)%cols):(c+1)%cols;

	   while (r < rows) {
		   rp = buffer.data + buffer.csize * (buffer.xsize * buffer.ysize * c + buffer.xsize * r + (bufcount - c + cols) % cols );
		   pixels = image.data + image.csize * (image.xsize * r + cols - c1);

		   pixels[chRed]   = rp[chRed];
		   pixels[chBlue]  = rp[chBlue];
		   pixels[chGreen] = rp[chGreen];
		   pixels[chAlpha] = rp[chAlpha];

		   r++;
	   }
	   r=0;
	   c++;
   }

   bufcount++;
   bufcount%=image.xsize;
}

/////////////////////////////////////////////////////////
// static member function
//
/////////////////////////////////////////////////////////
void tv_rtx :: obj_setupCallback(t_class *classPtr)
{
  class_addcreator((t_newmethod)_classtv_rtx, gensym("pix_rtx"), A_NULL);


	class_addmethod(classPtr, (t_method)&tv_rtx::modeMessCallback,
 					  gensym("mode"), A_FLOAT, A_NULL);
	class_addmethod(classPtr, (t_method)&tv_rtx::clearMessCallback,
 					  gensym("clear"), A_NULL);
	class_addmethod(classPtr, (t_method)&tv_rtx::setMessCallback,
 					  gensym("set"), A_NULL);

}
void tv_rtx :: modeMessCallback(void *data, t_floatarg newmode)
{
    GetMyClass(data)->mode=(newmode!=0);
}
void tv_rtx :: clearMessCallback(void *data)
{
    GetMyClass(data)->clear_buffer();
}
void tv_rtx :: setMessCallback(void *data)
{
  GetMyClass(data)->set_buffer = true;
}
