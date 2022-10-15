//g++ donut.c -o donut -lgdi32
#include <windows.h>
#include <wingdi.h>
#include <conio.h>
#include<stdlib.h>
 
#pragma hdrstop
#pragma argsused

#include <stdio.h>
#include <math.h>

typedef struct Vector3D {
    float u0;
    float u1;
    float u2;
} vector3D;


typedef struct Vector2D {
    float u0;
    float u1;
} vector2D;


void project_to_screen(vector3D v3D, vector2D *v2D, float screen_width, float screen_dist, float p0, float p1, float p2, float ptheta, float pphi);
void rotate_position_vector(vector3D *v3D, vector3D offset, float alpha, float beta, float gamma);
void gen_donut_vector(vector3D *v3D, float r1, float r2, float i, float j, vector3D offset);
void gen_cherry_vector(vector3D *v3D, float r, float i, float j, vector3D offset);
void gen_straw_vector(vector3D *v3D, float r, float h, float i, float j, vector3D offset);


int main()
{
 // Originally Code by Andy Sloane https://www.a1k0n.net/2011/07/20/donut-math.html .
    system("cls"); // Clears the screen.
    float theta=0, phi=0, i, j;
    printf("\x1b[2J"); // Clear the screen and set cursor to home (apparently unreliable).
    vector3D v3D;
    vector2D v2D;
    vector3D offset;
    offset.u0 = 0;
    offset.u1 = 0;
    offset.u2 = 0;


    COLORREF COLOR= RGB(255,255,255); 
    HWND myconsole = GetConsoleWindow();
    //Get a handle to device context
    HDC mydc = GetDC(myconsole);

    for(;;){
            for(j=0; 6.28>j; j+=4*0.07) // Itterates j from 0-6.28 in steps of 0.07.
                for(i=0; 6.28>i; i+=2*0.07) { // For each j Itterates i from 0-6.28 in steps of 0.02. 
                    
                    gen_donut_vector(&v3D, 2, 1, i, j, offset);
                    //gen_cherry_vector(&v3D, 2, i, j, offset);
                    //gen_straw_vector(&v3D, 1, 6, i, j, offset);
                    //error in third rotation somehow?
                    rotate_position_vector(&v3D, offset, theta, theta, 0);
                    project_to_screen(v3D,&v2D,80,5,0,0,0,0,0);
                    
                    // Draw position vectors.
                    SetPixel(mydc,v2D.u0*12,v2D.u1*12,COLOR);
                    
                    }

            printf("\e[1;1H\e[2J");

            // Increase angular offsets.
            // ___To change aspects of the rotation this area muslt be altered d___
            theta+=0.04;
            phi+=0.02;
            // _______
            }
    return 0;
    }


// Function to handle projecting 3D object to 2D screen.
void project_to_screen(vector3D v3D, vector2D *v2D, float screen_width, float screen_dist, float p0, float p1, float p2, float ptheta, float pphi){
    float k1 = screen_width*screen_dist*3/(8*(2+1)); // 2 and 1 are torus radii.
    float z = 1/(screen_dist + (v3D.u0-p0)); //screen_distr = k2
    v2D->u0 = k1*z*(v3D.u1-p1) + screen_width/2;
    v2D->u1 = k1*z*(v3D.u2-p2) + screen_width/2;
}

// Generic function to rotate a vector.
void rotate_position_vector(vector3D *v3D, vector3D offset, float alpha, float beta, float gamma){
    float u0 = v3D->u0 - offset.u0;
    float u1 = v3D->u1 - offset.u1;
    float u2 = v3D->u2 - offset.u2;
    v3D->u0 = cos(alpha)*cos(beta)*u0 + (cos(alpha)*cos(beta)*sin(gamma) - sin(alpha)*cos(gamma))*u1 + (cos(alpha)*sin(beta)*cos(gamma) + sin(alpha)*sin(gamma))*u2 + offset.u0;
    v3D->u1 = sin(alpha)*cos(beta)*u0 + (sin(alpha)*sin(beta)*sin(gamma) + cos(alpha)*cos(gamma))*u1 + (sin(alpha)*sin(beta)*cos(gamma) - cos(alpha)*sin(gamma))*u2 + offset.u1;
    v3D->u2 = -sin(beta)*u0 + cos(beta)*sin(gamma)*u1 + cos(beta)*cos(gamma)*u2 + offset.u2;
}

// Generate a torus.
void gen_donut_vector(vector3D *v3D, float r1, float r2, float i, float j, vector3D offset){
        v3D->u0 = (r1+cos(j)*r2)*cos(i) + offset.u0;
        v3D->u1 = (r1+cos(j)*r2)*sin(i) + offset.u1;
        v3D->u2 = r2*sin(j) + offset.u2;
}

// Generate a sphere.
void gen_cherry_vector(vector3D *v3D, float r, float i, float j, vector3D offset){
        v3D->u0 = r*cos(i)*cos(j) + offset.u0;
        v3D->u1 = r*cos(j)*sin(i) + offset.u1;
        v3D->u2 = r*sin(j) + offset.u2;
}

// Generate a cylinder.
void gen_straw_vector(vector3D *v3D, float r, float h, float i, float j, vector3D offset){
        v3D->u0 = r*cos(i) + offset.u0;
        v3D->u1 = r*sin(i) + offset.u1;
        v3D->u2 = h*j/6.28 + offset.u2;
}
