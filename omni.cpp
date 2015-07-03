#include "alloutil/al_OmniApp.hpp"
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


    int face = mOmni.face();
    int resolution = mOmni.resolution();



    
    mShader.end();
    glLoadIdentity();
    
    double x,y,z,camerax,cameray,cameraz,viewingDirX,viewingDirY,viewingDirZ,upX,upY,upZ;
    double ratio,radians,wd2,ndfl;
    double left,right,top,bottom,near=Lens.nearClip,far=Lens.farClip;
    
    /*if (stereo)
      near = Lens.focalLength / 5;
    */
    ratio  = 1;
    wd2     = resolution/2;
    ndfl    = near / Lens.focalLength;

    x = 1;
    y = 0;
    z = 0;
    camerax=0;
    cameray=0;
    cameraz=-1;
    
    x *= Lens.eyeSep / 2.0;
    y *= Lens.eyeSep / 2.0;
    z *= Lens.eyeSep / 2.0;

    //left eye
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    left  = - ratio * wd2 - 0.5 * Lens.eyeSep * ndfl;
    right =   ratio * wd2 - 0.5 * Lens.eyeSep * ndfl;
    top    =   wd2;
    bottom = - wd2;
    glFrustum(left,right,bottom,top,near,far);
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camerax + x,cameray + y,cameraz + z,
      camerax + x + viewingDirX,
      cameray + y + viewingDirY,
      cameraz + z + viewingDirZ,
      upX,upY,upZ);

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
