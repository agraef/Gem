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

#include "GEMglColor3dv.h"

CPPEXTERN_NEW_WITH_THREE_ARGS ( GEMglColor3dv , t_floatarg, A_DEFFLOAT, t_floatarg, A_DEFFLOAT, t_floatarg, A_DEFFLOAT);

/////////////////////////////////////////////////////////
//
// GEMglColor3dv
//
/////////////////////////////////////////////////////////
// Constructor
//
GEMglColor3dv :: GEMglColor3dv  (t_floatarg arg0, t_floatarg arg1, t_floatarg arg2) {
vMess(arg0, arg1, arg2);
        m_inlet = inlet_new(this->x_obj, &this->x_obj->ob_pd, &s_float, gensym("v"));
}
/////////////////////////////////////////////////////////
// Destructor
//
GEMglColor3dv :: ~GEMglColor3dv () {
        inlet_free(m_inlet);
}

/////////////////////////////////////////////////////////
// Render
//
void GEMglColor3dv :: render(GemState *state) {
        glColor3dv (v);
}

/////////////////////////////////////////////////////////
// variable
//
void GEMglColor3dv :: vMess (t_float arg0, t_float arg1, t_float arg2) {        // FUN
        v[0]=static_cast<GLdouble>(arg0);
        v[1]=static_cast<GLdouble>(arg1);
        v[2]=static_cast<GLdouble>(arg2);
        setModified();
}

/////////////////////////////////////////////////////////
// static member functions
//

void GEMglColor3dv :: obj_setupCallback(t_class *classPtr) {
         class_addmethod(classPtr, reinterpret_cast<t_method>(&GEMglColor3dv::vMessCallback),   gensym("v"), A_DEFFLOAT, A_DEFFLOAT, A_DEFFLOAT, A_NULL);
}

void GEMglColor3dv :: vMessCallback (void* data, t_float arg0, t_float arg1, t_float arg2) {
        GetMyClass(data)->vMess ( arg0, arg1, arg2);
}
