#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include <string>

using namespace std;


struct cube_rotate{

  GLfloat angle, x, y, z;

};

GLfloat angle, fAspect, cube_size;
GLint rot_x, rot_y, crement, x_0, x_k, y_0, y_k, z_0, z_k, gap, gap_crement;

//cube_rotate cube_rotations[3][3][3];
vector<cube_rotate> cube_rotations[3][3][3];

void set_camera()
{

  gluLookAt(0,80,200, 0,0,0, 0,1,0);

}

// specify what's shown in the window
void load_visualization_parameters(void)
{
  // specify projection coordinate system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // specify projection perspective
  gluPerspective(angle,fAspect,0.4,500);

  // init model coordinate system
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // specify observer and target positions
  set_camera();
} // load visualization parameters

// mouse function callback
void mouse_func(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON)
    if (state == GLUT_DOWN) {  // Zoom-in
	    if (angle >= 10) angle -= 5;
    }
  if (button == GLUT_RIGHT_BUTTON)
    if (state == GLUT_DOWN) {  // Zoom-out
	    if (angle <= 130) angle += 5;
    }
  load_visualization_parameters();
  glutPostRedisplay();
} // mouse functio

void reset_selected_face(){

  x_0 = 0;
  x_k = 2;
  y_0 = 0;
  y_k = 2;
  z_0 = 0;
  z_k = 2;

}

void apply_rotation(GLfloat angle){

  vector<cube_rotate> face[3][3];
  int index;
  cube_rotate rotation;

  // copy face to be rotated
  // apply rotation to face
  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 3; ++j) {

      index = 2 - j%3;

      if(x_0 == x_k){
	rotation = {angle, 1.0, 0.0, 0.0};
	face[index][i] = cube_rotations[x_k][i][j];
      }

      if(y_0 == y_k){
	rotation = {angle, 0.0, 1.0, 0.0};
	face[index][i] = cube_rotations[j][y_k][i];
      }

      if(z_0 == z_k){
	rotation = {-1 * angle, 0.0, 0.0, 1.0};
	face[index][i] = cube_rotations[j][i][z_k];
      }

      face[index][i].push_back(rotation);

    }

  // copy back rotated face
  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 3; ++j) {

      if(x_0 == x_k)
	cube_rotations[x_k][i][j] = face[i][j];

      if(y_0 == y_k)
	cube_rotations[j][y_k][i] = face[i][j];

      if(z_0 == z_k)
	cube_rotations[j][i][z_k] = face[i][j];
    }

}

// keyboard function callback
void keyboard_func(unsigned char key, int x, int y)
{

  switch(key) {

    case '+':
      gap += gap_crement;
      break;

    case '-':
      gap -= gap_crement;
      break;
    // view rotation
    // INcrement or DEcrement
    case 'L': // right
    case 'l':
      rot_y = (rot_y - crement) % 360;
      break;

    case 'J': // left
    case 'j':
      rot_y = (rot_y + crement) % 360;
      break;

    case 'I': // down
    case 'i':
      rot_x = (rot_x + crement) % 360;
      break;

    case 'K': // up
    case 'k':
      rot_x = (rot_x - crement) % 360;
      break;
    // end of view rotation

    // cube movements

    // select cube face
    // x-axis faces
    case 'Q':
    case 'q':
      reset_selected_face();
      x_0 = 0;
      x_k = 0;
      break;

    case 'W':
    case 'w':
      reset_selected_face();
      x_0 = 1;
      x_k = 1;
      break;

    case 'E':
    case 'e':
      reset_selected_face();
      x_0 = 2;
      x_k = 2;
      break;

    // y-axis faces
    case 'A':
    case 'a':
      reset_selected_face();
      y_0 = 0;
      y_k = 0;
      break;

    case 'S':
    case 's':
      reset_selected_face();
      y_0 = 1;
      y_k = 1;
      break;

    case 'D':
    case 'd':
      reset_selected_face();
      y_0 = 2;
      y_k = 2;
      break;

    // z-axis faces
    case 'C':
    case 'c':
      reset_selected_face();
      z_0 = 0;
      z_k = 0;
      break;

    case 'X':
    case 'x':
      reset_selected_face();
      z_0 = 1;
      z_k = 1;
      break;

    case 'Z':
    case 'z':
      reset_selected_face();
      z_0 = 2;
      z_k = 2;
      break;

    // move selected face
    case 'U': // counter-clockwise
    case 'u':
      apply_rotation(-90);
      break;

    case 'O': // clockwise
    case 'o':
      apply_rotation(90);
      break;

    // end of cube movements

    default:
      break;

  }

  glutPostRedisplay();

}

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