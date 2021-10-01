// Write a program to perform 2D transformation
// a. Translation
// b. Scaling
// c. Rotation
// d. Shear
// e. Reflection

// Algorithm/ Pseudocode for each process:

// For 2D:
// 1.	Translation- For translation we directly add the Tx and Ty, the values with which we need to scale to the respective coordinates of all points.
// 2.	Scaling- We just multiply the given vector by a matrix ‘TheMatrix’ which is an identity matrix. For scaling, we multiply the 1st row and 2nd row of TheMatrix’ by a scalar quantity sx and sy for the respective scaling along the specified directions.
// 3.	Rotation- We just multiply the given vector by a matrix ‘TheMatrix’ which is an identity matrix. For rotation, we use some combinations of cos and sin angles in ‘theMatrix’ at all the elements in order to get the object rotated by that given angle.
// 4.	Reflection- We simply take the negative of the coordinate along whose axis we are not reflecting. This means that if we want to take reflection of point (2,3) along the x axis, then we will simply multiply the y coordinate by -1 and do the same for all the points of our polygon.
// 5.	Shearing- We here add to the one coordinate the product of the shearing coordinate and the other coordinate to get the final coordinates in place. For example if we want to shear the polygon having vertex (2,3) in x direction, we would add 2+3*s where s is the shearing factor.
// For 3D:
// 1.	Translation- For translation we directly add the Tx, Ty and Tz, the values with which we need to scale to the respective coordinates of all points.
// 2.	Scaling- We just multiply the given vector by a matrix ‘TheMatrix’ which is an identity matrix. For scaling, we multiply the 1st row, 2nd row of TheMatrix’ and 3rd row of ‘TheMatrix’ by a scalar quantity sx, sy, sz for the respective scaling along the specified directions.
// 3.	Rotation- We just multiply the given vector by a matrix ‘TheMatrix’ which is an identity matrix. For rotation, we use some combinations of cos and sin angles in ‘theMatrix’ at all the elements in order to get the object rotated by that given angle.
// 4.	Reflection- We simply take the negative of the coordinate along whose axis we are not reflecting. This means that if we want to take reflection of point (2,3,4) along the x-y plane, then we will simply multiply the z coordinate by -1 and do the same for all the points of our polygon.
// 5.	Shearing- For shearing, in ‘TheMatrix’ we add the shearing factors to the coordinates along whose plane we need to shear. For example, if we want to shear along x-y plane the given matrix would be
// [ 1 0 0 0
//    a 1 0 0
//    b 0 1 0
//    0 0 0 1 ]
// where a and b are shearing factors along the y and z axis respectively.

// Implementation details:

// 2D Transformations :

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <GL/glut.h>
using namespace std;

float pntX1, pntY1, choice = 0, edges;
vector<int> pntX;
vector<int> pntY;
int transX, transY;
double scaleX, scaleY;
double angle, angleRad;
char reflectionAxis, shearingAxis;
float shearingX, shearingY, fact;

double round(double d)
{
    return floor(d + 0.5);
}

void drawPolygon()
{
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    for (int i = 0; i < edges; i++)
    {
        glVertex2i(pntX[i], pntY[i]);
    }
    glEnd();
}

void drawPolygonTrans(int x, int y)
{
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
    for (int i = 0; i < edges; i++)
    {
        glVertex2i(pntX[i] + x, pntY[i] + y);
    }
    glEnd();
}

void drawPolygonScale(double x, double y)
{
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);
    for (int i = 0; i < edges; i++)
    {
        glVertex2i(round(pntX[i] * x), round(pntY[i] * y));
    }
    glEnd();
}

void drawPolygonRotation(double angleRad)
{
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);
    for (int i = 0; i < edges; i++)
    {
        glVertex2i(round((pntX[i] * cos(angleRad)) - (pntY[i] * sin(angleRad))), round((pntX[i] * sin(angleRad)) + (pntY[i] * cos(angleRad))));
    }
    glEnd();
}

void drawPolygonMirrorReflection(char reflectionAxis)
{
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);

    if (reflectionAxis == 'x' || reflectionAxis == 'X')
    {
        for (int i = 0; i < edges; i++)
        {
            glVertex2i(round(pntX[i]), round(pntY[i] * -1));
        }
    }
    else if (reflectionAxis == 'y' || reflectionAxis == 'Y')
    {
        for (int i = 0; i < edges; i++)
        {
            glVertex2i(round(pntX[i] * -1), round(pntY[i]));
        }
    }
    glEnd();
}

void drawPolygonShearing(char shearingAxis, float fact)
{
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);

    if (shearingAxis == 'x' || shearingAxis == 'X')
    {
        for (int i = 0; i < edges; i++)
        {
            glVertex2i(pntX[i] + fact * pntY[i], pntY[i]);
        }
    }
    else if (shearingAxis == 'y' || shearingAxis == 'Y')
    {
        for (int i = 0; i < edges; i++)
        {
            glVertex2i(pntX[i], pntY[i] + fact * pntX[i]);
        }
    }
    glEnd();
}

void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-640.0, 640.0, -480.0, 480.0);
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    if (choice == 1)
    {
        drawPolygon();
        drawPolygonTrans(transX, transY);
    }
    else if (choice == 2)
    {
        drawPolygon();
        drawPolygonScale(scaleX, scaleY);
    }
    else if (choice == 3)
    {
        drawPolygon();
        drawPolygonRotation(angleRad);
    }
    else if (choice == 4)
    {
        drawPolygon();
        drawPolygonMirrorReflection(reflectionAxis);
    }
    else if (choice == 5)
    {
        drawPolygon();
        if (shearingAxis == 'x' || shearingAxis == 'X')
        {
            fact = shearingX;
        }
        else
        {
            fact = shearingY;
        }
        drawPolygonShearing(shearingAxis, fact);
    }

    glFlush();
}

void main(int argc, char **argv)
{
    cout << "Enter your choice:\n\n"
         << endl;

    cout << "1. Translation" << endl;
    cout << "2. Scaling" << endl;
    cout << "3. Rotation" << endl;
    cout << "4. Mirror Reflection" << endl;
    cout << "5. Shearing" << endl;
    cout << "6. Exit" << endl;

    cin >> choice;

    if (choice == 6)
    {
        return;
    }

    cout << "\n\nFor Polygon:\n"
         << endl;

    cout << "Enter no of edges: ";
    cin >> edges;

    for (int i = 0; i < edges; i++)
    {
        cout << "Enter co-ordinates for vertex  " << i + 1 << " : ";
        cin >> pntX1 >> pntY1;
        pntX.push_back(pntX1);
        pntY.push_back(pntY1);
    }

    if (choice == 1)
    {
        cout << "Enter the translation factor for X and Y: ";
        cin >> transX >> transY;
    }
    else if (choice == 2)
    {
        cout << "Enter the scaling factor for X and Y: ";
        cin >> scaleX >> scaleY;
    }
    else if (choice == 3)
    {
        cout << "Enter the angle for rotation: ";
        cin >> angle;
        angleRad = angle * 3.1416 / 180;
    }
    else if (choice == 4)
    {
        cout << "Enter reflection axis ( x or y ): ";
        cin >> reflectionAxis;
    }
    else if (choice == 5)
    {
        cout << "Enter reflection axis ( x or y ): ";
        cin >> shearingAxis;
        if (shearingAxis == 'x' || shearingAxis == 'X')
        {
            cout << "Enter the shearing factor for X: ";
            cin >> shearingX;
        }
        else
        {
            cout << "Enter the shearing factor for Y: ";
            cin >> shearingY;
        }
    }
    //cout << "\n\nPoints:" << pntX[0] << ", " << pntY[0] << endl;
    //cout << angleRad;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Extended Basic Transformations");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
}
