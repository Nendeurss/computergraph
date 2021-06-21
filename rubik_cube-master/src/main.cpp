// Rubik Cube in OpenGL

#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include "controller.cpp"

using namespace std;

// init rendering parameters
void init_func ()
{ 

  // init parameters
  cube_size = 30.0; // cuboid size
  rot_x = 0.0; // view rotation x
  rot_y = 0.0; // view rotation y
  crement = 5; // rotation (in/de)crement
  gap = 1;
  gap_crement = 3;
  // initialize cuboid rotations

  // init lighting
  GLfloat ambient_lighte[4]={0.2,0.2,0.2,1.0}; 
  GLfloat diffuse_light[4]={0.7,0.7,0.7,1.0};		// color
  GLfloat specular_light[4]={1.0, 1.0, 1.0, 1.0};	// brightness
  GLfloat light_position[4]={0.0, 50.0, 50.0, 1.0};

  // material brightness capacity
  GLfloat specularity[4]={1.0,1.0,1.0,1.0}; 
  GLint material_specularity = 60;

  // black background
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  
  // Gouraud colorization model
  glShadeModel(GL_SMOOTH);

  // material reflectability
  glMaterialfv(GL_FRONT,GL_SPECULAR, specularity);
  // brightness concentration
  glMateriali(GL_FRONT,GL_SHININESS,material_specularity);

  // activate ambient light
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_lighte);

  // define light parameters
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_lighte); 
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light );
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light );
  glLightfv(GL_LIGHT0, GL_POSITION, light_position );

  // enable changing material color
  glEnable(GL_COLOR_MATERIAL);
  // enable lighting
  glEnable(GL_LIGHTING);  
  glEnable(GL_LIGHT0);
  // enable depth buffering
  glEnable(GL_DEPTH_TEST);

  angle=45;

} // init



void draw_cube(int x, int y, int z)
{

  vector<cube_rotate> lrot = cube_rotations[x][y][z];

  glPushMatrix();

  // translate to final position
  glTranslatef((x - 1) * cube_size + x * gap, (y - 1) * cube_size + y * gap, (z - 1) * cube_size + z * gap);

  // rotate cube to correct position
  for(int i = lrot.size() - 1; i >= 0; --i)
    glRotatef(lrot[i].angle, lrot[i].x, lrot[i].y, lrot[i].z);

  glColor3f(1.0f, 0.0f, 0.0f);
  glBegin(GL_QUADS);  // front
    glNormal3f(0.0, 0.0, 1.0);  // face normal
    glVertex3f(cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(-cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, cube_size/2);
  glEnd();

  glColor3f(1.0f, 0.5f, 0.0f);
  glBegin(GL_QUADS);  // back
    glNormal3f(0.0, 0.0, -1.0);  // face normal
    glVertex3f(cube_size/2, cube_size/2, -cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, cube_size/2, -cube_size/2);
  glEnd();

  glColor3f(0.0f, 0.0f, 1.0f);
  glBegin(GL_QUADS);  // left
    glNormal3f(-1.0, 0.0, 0.0);  // face normal
    glVertex3f(-cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(-cube_size/2, cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, cube_size/2);
  glEnd();
  
  glColor3f(0.0f, 1.0f, 0.0f);
  glBegin(GL_QUADS);  // right
    glNormal3f(1.0, 0.0, 0.0);  // face normal
    glVertex3f(cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(cube_size/2, cube_size/2, -cube_size/2);
  glEnd();

  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_QUADS);  // top
    glNormal3f(0.0, 1.0, 0.0);  // face normal
    glVertex3f(-cube_size/2, cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, cube_size/2, -cube_size/2);
  glEnd();

  glColor3f(1.0f, 1.0f, 0.0f);
  glBegin(GL_QUADS);  // bottom
    glNormal3f(0.0, -1.0, 0.0);  // face normal
    glVertex3f(-cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, cube_size/2);
  glEnd();

  glPopMatrix();

} // draw cube function
            
// draw function
void draw_func(void)
{

  int x = -cube_size, y = -cube_size, z = -cube_size;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // reset transformations
  glLoadIdentity();

  // set camera position
  set_camera();

  // apply visualization transformations
  glRotatef(rot_x, 1.0, 0.0, 0.0); // rotate in y axis
  glRotatef(rot_y, 0.0, 1.0, 0.0); // rotate in x axis

  for(int i = 0; i < 3; ++i) // step through x axis
    for(int j = 0; j < 3; ++j) // step through y axis
      for(int k = 0; k < 3; ++k) { // step through z axis

	// draw a single cube
	draw_cube(i, j, k);

      }

  // flush opengl commands
  glutSwapBuffers();

}


// draw a cube






// window reshape callback
void reshape_func(GLsizei w, GLsizei h)
{
  // prevents division by zero
  if ( h == 0 ) h = 1;

  // viewport size
  glViewport(0, 0, w, h);

  // aspect ratio
  fAspect = (GLfloat)w/(GLfloat)h;

  load_visualization_parameters();
} // reshape function

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(700,600);
  glutCreateWindow("Rubik's cube 3D");
  glutDisplayFunc(draw_func);
  glutReshapeFunc(reshape_func);
  glutMouseFunc(mouse_func);
  glutKeyboardFunc(keyboard_func);
  init_func();
  glutMainLoop();
} // main
