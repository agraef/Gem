////////////////////////////////////////////////////////
//
// GEM - Graphics Environment for Multimedia
//
// Implementation file
//
// Copyright (c) 2002-2011 IOhannes m zmölnig. forum::für::umläute. IEM. zmoelnig@iem.at
//      zmoelnig@iem.kug.ac.at
//  For information on usage and redistribution, and for a DISCLAIMER
//  *  OF ALL WARRANTIES, see the file, "GEM.LICENSE.TERMS"
//
//  this file has been generated...
////////////////////////////////////////////////////////

#include "GEMglVertex3sv.h"

CPPEXTERN_NEW_WITH_THREE_ARGS ( GEMglVertex3sv , t_floatarg, A_DEFFLOAT, t_floatarg, A_DEFFLOAT, t_floatarg, A_DEFFLOAT);

/////////////////////////////////////////////////////////
//
// GEMglVertex3sv
//
/////////////////////////////////////////////////////////
// Constructor
//
GEMglVertex3sv :: GEMglVertex3sv        (t_floatarg arg0, t_floatarg arg1, t_floatarg arg2) {
vMess(arg0, arg1, arg2);
        m_inlet = inlet_new(this->x_obj, &this->x_obj->ob_pd, &s_float, gensym("v"));
}
/////////////////////////////////////////////////////////
// Destructor
//
GEMglVertex3sv :: ~GEMglVertex3sv () {
        inlet_free(m_inlet);
}

/////////////////////////////////////////////////////////
// Render
//
void GEMglVertex3sv :: render(GemState *state) {
        glVertex3sv (v);
}

/////////////////////////////////////////////////////////
// variable
//
void GEMglVertex3sv :: vMess (t_float arg0, t_float arg1, t_float arg2) {       // FUN
        v[0]=static_cast<GLshort>(arg0);
        v[1]=static_cast<GLshort>(arg1);
        v[2]=static_cast<GLshort>(arg2);
        setModified();
}

/////////////////////////////////////////////////////////
// static member functions
//

void GEMglVertex3sv :: obj_setupCallback(t_class *classPtr) {
         class_addmethod(classPtr, reinterpret_cast<t_method>(&GEMglVertex3sv::vMessCallback),          gensym("v"), A_DEFFLOAT, A_DEFFLOAT, A_DEFFLOAT, A_NULL);
}

void GEMglVertex3sv :: vMessCallback (void* data, t_float arg0, t_float arg1, t_float arg2) {
        GetMyClass(data)->vMess ( arg0, arg1, arg2);
}
