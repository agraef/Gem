///////////////////////////////////////////////////////
//
// GEM - Graphics Environment for Multimedia
//
// zmoelnig@iem.at
//
// Implementation file
//
//    Copyright (c) 1997-2000 Mark Danks.
//    Copyright (c) Günther Geiger.
//    Copyright (c) 2001-2013 IOhannes m zmölnig. forum::für::umläute. IEM. zmoelnig@iem.at
//    For information on usage and redistribution, and for a DISCLAIMER OF ALL
//    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.
//
/////////////////////////////////////////////////////////
#include "Gem/GemConfig.h"

#include "gemglutwindow.h"
#include "Gem/GemGL.h"
#if defined __APPLE__
# include <GLUT/glut.h>
# define glutCloseFunc glutWMCloseFunc
# define glutMainLoopEvent glutCheckLoop
#else
# include <GL/glut.h>
# ifdef FREEGLUT
#  include <GL/freeglut.h>
# endif
#endif


#include "RTE/MessageCallbacks.h"


#define DEBUG ::startpost("%s:%d [%s]:: ", __FILE__, __LINE__, __FUNCTION__), ::post

#include <map>
static std::map<int, gemglutwindow*>s_windowmap;

namespace
{
static std::string key2symbol(unsigned char c)
{
  std::string sym;
  sym+=c;
  return sym;
}

static std::string key2symbol(int c)
{
  switch(c) {
  case GLUT_KEY_F1:
    return std::string("F1");
  case GLUT_KEY_F2:
    return std::string("F2");
  case GLUT_KEY_F3:
    return std::string("F3");
  case GLUT_KEY_F4:
    return std::string("F4");
  case GLUT_KEY_F5:
    return std::string("F5");
  case GLUT_KEY_F6:
    return std::string("F6");
  case GLUT_KEY_F7:
    return std::string("F7");
  case GLUT_KEY_F8:
    return std::string("F8");
  case GLUT_KEY_F9:
    return std::string("F9");
  case GLUT_KEY_F10:
    return std::string("F10");
  case GLUT_KEY_F11:
    return std::string("F11");
  case GLUT_KEY_F12:
    return std::string("F12");
  case GLUT_KEY_LEFT:
    return std::string("Left");
  case GLUT_KEY_UP:
    return std::string("Up");
  case GLUT_KEY_RIGHT:
    return std::string("Right");
  case GLUT_KEY_DOWN:
    return std::string("Down");
  case GLUT_KEY_PAGE_UP:
    return std::string("PageUp");
  case GLUT_KEY_PAGE_DOWN:
    return std::string("PageDown");
  case GLUT_KEY_HOME:
    return std::string("Home");
  case GLUT_KEY_END:
    return std::string("End");
  case GLUT_KEY_INSERT:
    return std::string("Insert");
  default:
    break;
  }

  return std::string("<unknown>");
}

/* callbacks */
#define CALLBACK4WIN gemglutwindow*ggw=s_windowmap[glutGetWindow()]; if(!ggw){pd_error(0, "couldn't find [gemglutwindow] for window#%d", glutGetWindow()); return;} else ggw


void displayCb(void)
{
  CALLBACK4WIN ->bang(); // fixme??
}
void visibleCb(int state)
{
  CALLBACK4WIN->info("visible", state);
}
void closeCb(void)
{
  CALLBACK4WIN->info("window", "destroy");
}
void keyboardCb(unsigned char c, int x, int y)
{
  CALLBACK4WIN->motion( 0,x,y);
  ggw->key( 0,key2symbol(c), c, 1);
}
void keyboardupCb(unsigned char c, int x, int y)
{
  CALLBACK4WIN->motion( 0,x,y);
  ggw->key( 0,key2symbol(c), c, 0);
}
void specialCb(int c, int x, int y)
{
  CALLBACK4WIN->motion(0,x,y);
  ggw->key(0,key2symbol(c), c, 1);
}
void specialupCb(int c, int x, int y)
{
  CALLBACK4WIN->motion(0,x,y);
  ggw->key(0,key2symbol(c), c, 0);
}
void reshapeCb(int x, int y)
{
  CALLBACK4WIN->dimension(x, y);
}
void mouseCb(int button, int state, int x, int y)
{
  CALLBACK4WIN->motion(0,x,y);
  ggw->button(0,button, !state);
}
void motionCb(int x, int y)
{
  CALLBACK4WIN->motion(0,x,y);
}
void passivemotionCb(int x, int y)
{
  CALLBACK4WIN->motion(0,x,y);
}
void entryCb(int state)
{
  CALLBACK4WIN->entry(0, state);
}
void joystickCb(unsigned int a, int x, int y, int z)
{
}
void menuCb(int menu)
{
  CALLBACK4WIN->info("menu", menu);
}
void menustateCb(int value)
{
}
void menustatusCb(int x, int y, int z)
{
}
void windowstatusCb(int value)
{
  std::string s;

  switch(value) {
  case GLUT_HIDDEN:
    s=std::string("hidden");
    break;
  case GLUT_FULLY_RETAINED:
    s=std::string("full");
    break;
  case GLUT_PARTIALLY_RETAINED:
    s=std::string("partial");
    break;
  case GLUT_FULLY_COVERED:
    s=std::string("covered");
    break;
  default:
    s=std::string("unknown");
  }
  CALLBACK4WIN->info("window", s);
}
#if (defined GLUT_HAS_MULTI) && (GLUT_HAS_MULTI > 0)
void multiButtonCb(int id, int x, int y, int button, int state)
{
  CALLBACK4WIN->motion(id,x,y);
  ggw->button(id,button, !state);
}
void multiMotionCb(int id, int x, int y)
{
  CALLBACK4WIN->motion(id,x,y);
}
void multiPassivemotionCb(int id, int x, int y)
{
  CALLBACK4WIN->motion(id,x,y);
}
void multiEntryCb(int id, int state)
{
  CALLBACK4WIN->entry(id, state);
}
#endif
}; /* namespace */


CPPEXTERN_NEW(gemglutwindow);

/////////////////////////////////////////////////////////
//
// gemglutwindow
//
/////////////////////////////////////////////////////////
// Constructor
//
/////////////////////////////////////////////////////////
gemglutwindow :: gemglutwindow(void) :
  m_window(0)
{ }

/////////////////////////////////////////////////////////
// Destructor
//
/////////////////////////////////////////////////////////
gemglutwindow :: ~gemglutwindow()
{
  destroyMess();
}


bool gemglutwindow :: makeCurrent(void)
{
  if(!m_window) {
    return false;
  }
  glutSetWindow(m_window);

  return(true);
}

void gemglutwindow :: swapBuffers(void)
{
  if(makeCurrent()) { // FIXME: is this needed?
    glutSwapBuffers();
  }
}

void gemglutwindow :: doRender()
{
  // FIXME: ?????
  bang();
}
void gemglutwindow :: dispatch()
{
  if(!m_window) {
    return;
  }

  // mark the render-buffer as dirty, so the displayCb() gets called
  // other things that mark dirty are (e.g.) resizing, making (parts of) the window visible,...
  glutSetWindow(m_window);
#if 0
  // setting glutPostRedisplay() here will emit a render-bang for each dispatch-cycle...
  // ...NOT what we want
  glutPostRedisplay();
#endif
  glutMainLoopEvent();
}


/////////////////////////////////////////////////////////
// bufferMess
//
/////////////////////////////////////////////////////////
void gemglutwindow :: bufferMess(int buf)
{
  switch(buf) {
  case 1:
  case 2:
    m_buffer=buf;
    if(m_window) {
      post("changing buffer type will only effect newly created windows");
    }
    break;
  default:
    error("buffer can only be '1' (single) or '2' (double) buffered");
    break;
  }
}

/////////////////////////////////////////////////////////
// titleMess
//
/////////////////////////////////////////////////////////
void gemglutwindow :: titleMess(const std::string&s)
{
  m_title = s;
  if(makeCurrent()) {
    glutSetWindowTitle(m_title.c_str());
    glutSetIconTitle(m_title.c_str());
  }
}
/////////////////////////////////////////////////////////
// dimensionsMess
//
/////////////////////////////////////////////////////////
void gemglutwindow :: dimensionsMess(unsigned int width,
                                     unsigned int height)
{
  if (width < 1) {
    error("width must be greater than 0");
    return;
  }

  if (height < 1 ) {
    error ("height must be greater than 0");
    return;
  }
  m_width = width;
  m_height = height;
  if(makeCurrent()) {
    glutReshapeWindow(width, height);
    glutHideWindow();
    glutShowWindow();
    glutPositionWindow(m_xoffset, m_yoffset);
    glutMainLoopEvent();
  }
}
/////////////////////////////////////////////////////////
// fullscreenMess
//
/////////////////////////////////////////////////////////
void gemglutwindow :: fullscreenMess(int on)
{
  m_fullscreen = on;
  if(makeCurrent()) {
    if(m_fullscreen) {
      glutFullScreen();
    } else {
      glutReshapeWindow(m_width, m_height);
      glutPositionWindow(m_xoffset, m_yoffset);
    }
  }
}

/////////////////////////////////////////////////////////
// offsetMess
//
/////////////////////////////////////////////////////////
void gemglutwindow :: offsetMess(int x, int y)
{
  m_xoffset = x;
  m_yoffset = y;
  if(makeCurrent()) {
    glutPositionWindow(x, y);
  }
}

/////////////////////////////////////////////////////////
// createMess
//
/////////////////////////////////////////////////////////
bool gemglutwindow :: create(void)
{
  if(m_window) {
    error("window already made!");
    return false;
  }


#ifdef FREEGLUT
  // display list sharing (with FreeGLUT)
  if(s_windowmap.size()>0) {
    std::map<int,gemglutwindow*>::iterator it = s_windowmap.begin();
    gemglutwindow*other=NULL;
    // FIXXME: shouldn't we iterate over all the windows?
    other=it->second;
    if(other && other->makeCurrent()) {
      glutSetOption(GLUT_RENDERING_CONTEXT, GLUT_USE_CURRENT_CONTEXT );
    }
  }
#endif

  unsigned int mode=GLUT_RGB | GLUT_DEPTH;
  if(2==m_buffer) {
    mode|=GLUT_DOUBLE;
  } else {
    mode|=GLUT_SINGLE;
  }
  if(!m_border) {
#ifdef GLUT_BORDERLESS
    mode|=GLUT_BORDERLESS;
#endif
#ifdef GLUT_CAPTIONLESS
    mode|=GLUT_CAPTIONLESS;
#endif
  }

  glutInitDisplayMode(mode);

#ifdef FREEGLUT
  //  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
  glutSetOption(GLUT_INIT_WINDOW_X, m_xoffset);
  glutSetOption(GLUT_INIT_WINDOW_Y, m_yoffset);
  glutSetOption(GLUT_INIT_WINDOW_WIDTH, m_width);
  glutSetOption(GLUT_INIT_WINDOW_HEIGHT, m_height);
#endif

  m_window=glutCreateWindow(m_title.c_str());
  s_windowmap[m_window]=this;

  glutReshapeWindow(m_width, m_height);
  glutPositionWindow(m_xoffset, m_yoffset);

  glutCloseFunc     (&closeCb);

  glutKeyboardFunc(&keyboardCb);
  glutSpecialFunc(&specialCb);
  glutReshapeFunc(&reshapeCb);
  glutKeyboardUpFunc(&keyboardupCb);
  glutSpecialUpFunc(&specialupCb);
  glutJoystickFunc(&joystickCb, 20);

  glutMenuStateFunc(&menustateCb);
  glutMenuStatusFunc(&menustatusCb);

  glutWindowStatusFunc(&windowstatusCb);

#if (defined GLUT_HAS_MULTI) && (GLUT_HAS_MULTI > 0)
  glutMultiEntryFunc(multiEntryCb);
  glutMultiButtonFunc(multiButtonCb);
  glutMultiMotionFunc(multiMotionCb);
  glutMultiPassiveFunc(multiPassivemotionCb);
#else
  glutEntryFunc(&entryCb);
  glutMouseFunc(&mouseCb);
  glutMotionFunc(&motionCb);
  glutPassiveMotionFunc(&passivemotionCb);
#endif

  //  glutNameFunc(&nameCb);
  glutDisplayFunc   (&displayCb);
  glutVisibilityFunc(&visibleCb);


  if(!createGemWindow()) {
    destroyMess();
    return false;
  }
  titleMess(m_title);
  fullscreenMess(m_fullscreen);

  dispatch();
  return true;
}
void gemglutwindow :: createMess(const std::string&)
{
  create();
}


/////////////////////////////////////////////////////////
// destroy window
//
/////////////////////////////////////////////////////////
void gemglutwindow :: destroy(void)
{
  destroyGemWindow();
  m_window=0;
  info("window", "closed");
}
void gemglutwindow :: destroyMess(void)
{
  if(makeCurrent()) {
    int window=m_window;
    m_window=0; // so that we no longer receive any event
    glutCloseFunc     (NULL);
    glutDestroyWindow(window);
    glutMainLoopEvent();
    glutMainLoopEvent();

    /* now that the window is destroyed, remove it from the list of available windows */
    s_windowmap.erase(window);
  }
  destroy();
}

/////////////////////////////////////////////////////////
// cursorMess
//
/////////////////////////////////////////////////////////
void gemglutwindow :: cursorMess(bool setting)
{
  m_cursor=setting;
  if(makeCurrent()) {
    glutSetCursor(setting?GLUT_CURSOR_INHERIT:GLUT_CURSOR_NONE);
  }
}


void gemglutwindow :: menuMess(void)
{
  int id=glutCreateMenu(menuCb);

  glutAttachMenu(GLUT_RIGHT_BUTTON);

  std::vector<t_atom>alist;
  t_atom a;
  SETSYMBOL(&a, gensym("menu"));
  alist.push_back(a);
  SETSYMBOL(&a, gensym("new") );
  alist.push_back(a);
  SETFLOAT (&a, id            );
  alist.push_back(a);
  info(alist);
}
void gemglutwindow :: addMenuMess(t_symbol*sym, int argc, t_atom*argv)
{
  if (argc!=3) {
    return;
  }
  int menu=atom_getint(argv+0);
  const char*s=atom_getsymbol(argv+1)->s_name;
  int v=atom_getint(argv+2);

  glutSetMenu(menu);
  glutAddMenuEntry(s, v);
}



/////////////////////////////////////////////////////////
// static member function
//
/////////////////////////////////////////////////////////
void gemglutwindow :: obj_setupCallback(t_class *classPtr)
{
  int argc=0;
  char*argv=NULL;

  static bool firsttime=true;

  if(firsttime) {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutInit(&argc,&argv);
  }
  firsttime=false;

  CPPEXTERN_MSG0(classPtr, "menu", menuMess);
  CPPEXTERN_MSG(classPtr, "addMenu", addMenuMess);
}
