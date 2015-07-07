#include "alloutil/al_OmniApp.hpp"
#include <GL/glut.h>
using namespace al;

struct MyApp : OmniApp {
  Mesh mesh;
  Light light;

  MyApp() {
    mesh.primitive(Graphics::TRIANGLES);
    addSphere(mesh, 1.0, 32, 32);
    for (int i = 0; i < mesh.vertices().size(); ++i) {
      float f = (float)i / mesh.vertices().size();
      mesh.color(Color(HSV(f, 1 - f, 1), 1));
    }
    mesh.generateNormals();
    light.ambient(Color(0.4, 0.4, 0.4, 1.0));
    light.pos(5, 5, 5);
    initAudio();
  }

  virtual ~MyApp() {}

  virtual void onDraw(Graphics& g) {
    glShadeModel(GL_SMOOTH); 
glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);
    mShader.end();
    /*int face = mOmni.face();
    int resolution = mOmni.resolution();

 
    Lens l = lens();
    
    mShader.end();
    //glLoadIdentity();
    
    double x,y,z,camerax,cameray,cameraz,viewingDirX,viewingDirY,viewingDirZ,upX,upY,upZ;
    double ratio,radians,wd2,ndfl;
    double left,right,top,bottom,near=l.near(),far=l.far();
    
    //if (stereo)
    //  near = l.focalLength / 5;
    
    ratio  = 1;
    wd2     = resolution/2;
    ndfl    = near / l.focalLength();

    x = 1;
    y = 0;
    z = 0;
    camerax=0;
    cameray=0;
    cameraz=-1;
    viewingDirX=0;
    viewingDirY=0;
    viewingDirZ=1;
    upX=0;
    upY=1;
    upZ=0;
    
    x *= l.eyeSep() / 2.0;
    y *= l.eyeSep() / 2.0;
    z *= l.eyeSep() / 2.0;

    //left eye
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    left  = - ratio * wd2 - 0.5 * l.eyeSep() * ndfl;
    right =   ratio * wd2 - 0.5 * l.eyeSep() * ndfl;
    top    =   wd2;
    bottom = - wd2;
    glFrustum(left,right,bottom,top,near,far);
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camerax + x,cameray + y,cameraz + z,
      0,//camerax + x + viewingDirX,
      0,//cameray + y + viewingDirY,
      0,//cameraz + z + viewingDirZ,
      upX,upY,upZ);*/

    light();
  // say how much lighting you want
  //shader().uniform("lighting", 1.0);
  //glUseProgramObjectARB(0);
  //glUseProgram(NULL);

    g.draw(mesh);
    
    
  }

  virtual void onAnimate(al_sec dt) {
    // light.pos(nav().pos());
    pose = nav();
    // std::cout << dt << std::endl;
  }

  virtual void onSound(AudioIOData& io) {
    while (io()) {
      io.out(0) = rnd::uniformS() * 0.05;
    }
  }

  virtual void onMessage(osc::Message& m) {
    OmniApp::onMessage(m);
  }

  virtual bool onKeyDown(const Keyboard& k) { return true; }
};

int main(int argc, char* argv[]) {
  MyApp().start();
  return 0;
}
