////////////////////////////////////////////////////////
//
// GEM - Graphics Environment for Multimedia
//
// zmoelnig@iem.kug.ac.at
//
// Implementation file
//
//    Copyright (c) 1997-1998 Mark Danks.
//    Copyright (c) Günther Geiger.
//    Copyright (c) 2001-2011 IOhannes m zmölnig. forum::für::umläute. IEM. zmoelnig@iem.at
//    Copyright (c) 2002 James Tittle & Chris Clepper
//    For information on usage and redistribution, and for a DISCLAIMER OF ALL
//    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.
//
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//
//  pix_dump
//
//  0409:forum::für::umläute:2000
//  IOhannes m zmoelnig
//  mailto:zmoelnig@iem.kug.ac.at
//
/////////////////////////////////////////////////////////


#include "pix_dump.h"

CPPEXTERN_NEW_WITH_TWO_ARGS(pix_dump, t_floatarg, A_DEFFLOAT, t_floatarg, A_DEFFLOAT);

  /////////////////////////////////////////////////////////
  //
  // pix_dump
  //
  /////////////////////////////////////////////////////////
  // Constructor
  //
  /////////////////////////////////////////////////////////
pix_dump :: pix_dump(t_floatarg fx, t_floatarg fy) :
    m_dataOut(0),
    xsize(0), ysize(0),
    m_xsize(0), m_ysize(0), m_csize(3),
    m_buffer(0),
    m_bufsize(0),
    oldimagex(0), oldimagey(0),
    m_xstep(1), m_ystep(1),
    m_data(0),
    m_normalize(1),
    m_mode(GL_RGBA)
{
  xsize = static_cast<int>(fx);
  ysize = static_cast<int>(fy);

  if (xsize < 0) xsize = 0;
  if (ysize < 0) ysize = 0;

  m_xsize = xsize;
  m_ysize = ysize;

  oldimagex = xsize;
  oldimagey = ysize;

  m_bufsize = m_xsize * m_ysize * m_csize;

  m_buffer = new t_atom[m_bufsize];

  m_dataOut = outlet_new(this->x_obj, &s_list);
}

/////////////////////////////////////////////////////////
// Destructor
//
/////////////////////////////////////////////////////////
pix_dump :: ~pix_dump()
{
  outlet_free(m_dataOut);
  delete[]m_buffer;
}

/////////////////////////////////////////////////////////
// processImage
//
/////////////////////////////////////////////////////////
void pix_dump :: processImage(imageStruct &image)
{
  int x = m_xsize, y = m_ysize, c = m_csize;

  if (image.xsize != oldimagex) {
    oldimagex = image.xsize;
    m_xsize = ((!xsize) || (xsize > oldimagex))?oldimagex:xsize;
  }
  if (image.ysize != oldimagey) {
    oldimagey = image.ysize;
    m_ysize = ((!ysize) || (ysize > oldimagey))?oldimagey:ysize;
  }

  if (image.csize != m_csize) m_csize = image.csize;

  if ( (m_xsize != x) || (m_ysize != y) || (m_csize != c) ) {
    // resize the image buffer
    if(m_buffer)delete [] m_buffer;
    m_bufsize = m_xsize * m_ysize * m_csize;
    m_buffer = new t_atom[m_bufsize];

    m_xstep = m_csize * (static_cast<float>(image.xsize)/static_cast<float>(m_xsize));
    m_ystep = m_csize * (static_cast<float>(image.ysize)/static_cast<float>(m_ysize)) * image.xsize;
  }

  m_data = image.data;
}

/////////////////////////////////////////////////////////
// processYUVImage
//
/////////////////////////////////////////////////////////
void pix_dump :: processYUVImage(imageStruct &image)
{
    int x = m_xsize, y = m_ysize, c = m_csize;

  if (image.xsize != oldimagex) {
    oldimagex = image.xsize;
    m_xsize = ((!xsize) || (xsize > oldimagex))?oldimagex:xsize;
  }
  if (image.ysize != oldimagey) {
    oldimagey = image.ysize;
    m_ysize = ((!ysize) || (ysize > oldimagey))?oldimagey:ysize;
  }

  if (image.csize != m_csize) m_csize = image.csize;

  if ( (m_xsize != x) || (m_ysize != y) || (m_csize != c) ) {
    // resize the image buffer
    if(m_buffer)delete [] m_buffer;
    m_bufsize = m_xsize * m_ysize * m_csize;
    m_buffer = new t_atom[m_bufsize];

    m_xstep = m_csize * (static_cast<float>(image.xsize)/static_cast<float>(m_xsize));
    m_ystep = m_csize * (static_cast<float>(image.ysize)/static_cast<float>(m_ysize)) * image.xsize;
  }

  m_data = image.data;
}

/////////////////////////////////////////////////////////
// trigger
//
/////////////////////////////////////////////////////////
void pix_dump :: trigger()
{
  if (!m_data) return;

  int n = 0, m = 0;
  int i = 0;

  unsigned char *data, *line;

  data = line = m_data;
  switch(m_csize){
  case 4:
    while (n < m_ysize) {
      while (m < m_xsize) {
      if (m_normalize) {
      float r, g, b, a;
      r = static_cast<float>(data[chRed]) / 255.f;
      SETFLOAT(&m_buffer[i], r);
      i++;
      g = static_cast<float>(data[chGreen]) / 255.f;
      SETFLOAT(&m_buffer[i], g);
      i++;
      b = static_cast<float>(data[chBlue]) / 255.f;
      SETFLOAT(&m_buffer[i], b);
      i++;
      if ( m_mode == GL_RGBA ) {
      a = static_cast<float>(data[chAlpha]) / 255.f;
      SETFLOAT(&m_buffer[i], a);
      i++;
      }
      } else {
          float r, g, b, a;
          r = static_cast<float>(data[chRed]);
      SETFLOAT(&m_buffer[i], r);
      i++;
      g = static_cast<float>(data[chGreen]);
      SETFLOAT(&m_buffer[i], g);
      i++;
      b = static_cast<float>(data[chBlue]);
      SETFLOAT(&m_buffer[i], b);
      i++;
      if ( m_mode == GL_RGBA ) {
        a = static_cast<float>(data[chAlpha]);
        SETFLOAT(&m_buffer[i], a);
        i++;
      }
      }
    m++;
      data = line + static_cast<int>(m_xstep * static_cast<float>(m));
      }
      m = 0;
      n++;
      line = m_data + static_cast<int>(m_ystep*n);
      data = line;
    }
    break;
  case 2:
    while (n < m_ysize) {
      while (m < m_xsize/2) {
        if (m_normalize) {
      float y,u,y1,v;
          u = static_cast<float>(data[0]) / 255.f;
          SETFLOAT(&m_buffer[i], u);
          i++;
          y = static_cast<float>(data[1]) / 255.f;
          SETFLOAT(&m_buffer[i], y);
          i++;
          v = static_cast<float>(data[2]) / 255.f;
          SETFLOAT(&m_buffer[i], v);
          i++;
          if ( m_mode == GL_RGBA ) {
            y1 = static_cast<float>(data[3]) / 255.f;
            SETFLOAT(&m_buffer[i], y1);
            i++;
      }
      } else {
      float y,u,y1,v;
          u = static_cast<float>(data[0]);
          SETFLOAT(&m_buffer[i], u);
          i++;
          y = static_cast<float>(data[1]);
          SETFLOAT(&m_buffer[i], y);
          i++;
          v = static_cast<float>(data[2]);
          SETFLOAT(&m_buffer[i], v);
          i++;
          if ( m_mode == GL_RGBA ) {
            y1 = static_cast<float>(data[3]);
            SETFLOAT(&m_buffer[i], y1);
            i++;
      }
    }
        m++;
        data = line + static_cast<int>(m_xstep * static_cast<float>(m));
      }
      m = 0;
      n++;
      line = m_data + static_cast<int>(m_ystep*n);
      data = line;
    }
  case 1:  default:
    int datasize=m_xsize*m_ysize*m_csize/4;
    int leftover=m_xsize*m_ysize*m_csize-datasize*4;
    while (datasize--) {
      float v;
      if ( m_normalize ) {
        v = static_cast<float>(*data++) / 255.f;    SETFLOAT(&m_buffer[i], v);
        v = static_cast<float>(*data++) / 255.f;    SETFLOAT(&m_buffer[i+1], v);
        v = static_cast<float>(*data++) / 255.f;    SETFLOAT(&m_buffer[i+2], v);
        i+3;
        if ( m_mode == GL_RGBA ) {
      v = static_cast<float>(*data++) / 255.f;    SETFLOAT(&m_buffer[i+3], v);
      i++;
    }
    } else {
    v = static_cast<float>(*data++);    SETFLOAT(&m_buffer[i], v);
        v = static_cast<float>(*data++);    SETFLOAT(&m_buffer[i+1], v);
        v = static_cast<float>(*data++);    SETFLOAT(&m_buffer[i+2], v);
        i+3;
        if ( m_mode == GL_RGBA ) {
      v = static_cast<float>(*data++);    SETFLOAT(&m_buffer[i+3], v);
      i++;
    }
    }
    }
    while (leftover--) {
      float v = static_cast<float>(*data++) / 255.f;    SETFLOAT(&m_buffer[i], v);
      i++;
    }


  }
  outlet_list(m_dataOut, gensym("list"), i, m_buffer);
}

/////////////////////////////////////////////////////////
// RGBAMess
//
/////////////////////////////////////////////////////////
void pix_dump :: RGBAMess(void)
{
  m_mode = GL_RGBA;
}
/////////////////////////////////////////////////////////
// RGBMess
//
/////////////////////////////////////////////////////////
void pix_dump :: RGBMess(void)
{
  m_mode = GL_RGB;
}

void pix_dump :: normalizeMess(t_float v)
{
  m_normalize=v>0 ? 1 : 0;
}
/////////////////////////////////////////////////////////
// static member function
//
/////////////////////////////////////////////////////////
void pix_dump :: obj_setupCallback(t_class *classPtr)
{
  CPPEXTERN_MSG0(classPtr, "bang", trigger);
  CPPEXTERN_MSG1(classPtr, "normalize", normalizeMess, int);
  CPPEXTERN_MSG0(classPtr, "RGBA", RGBAMess);
  CPPEXTERN_MSG0(classPtr, "rgba", RGBAMess);
  CPPEXTERN_MSG0(classPtr, "RGB" , RGBMess);
  CPPEXTERN_MSG0(classPtr, "rgb" , RGBMess);
}
