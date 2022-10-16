//g++ donut.c -o donut -lgdi32
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
 
#pragma hdrstop
#pragma argsused

typedef struct Vector3D {
    float u0;
    float u1;
    float u2;
} vector3D;


typedef struct Vector2D {
    float u0;
    float u1;
} vector2D;


void project_to_screen(vector3D v3D, vector2D *v2D, float screen_width, float screen_dist, vector3D pos, float ptheta, float pphi);
void translate_vector(vector3D *v3D, vector3D translation);
void rotate_vector(vector3D *v3D, vector3D offset, float alpha, float beta, float gamma);
void gen_donut_vector(vector3D *v3D, float r1, float r2, float i, float j, vector3D offset);
void gen_cherry_vector(vector3D *v3D, float r, float i, float j, vector3D offset);
void gen_klein_vector(vector3D *v3D, float r, float i, float j, vector3D offset);


int main()
{
 // Originally Code by Andy Sloane https://www.a1k0n.net/2011/07/20/donut-math.html .
    system("cls"); // Clears the screen.
    float theta=0.02, phi=0.03, i, j;
    printf("\x1b[2J"); // Clear the screen and set cursor to home (apparently unreliable).
    vector3D v3D;
    vector2D v2D;
    vector3D offset;
    offset.u0 = 20;
    offset.u1 = 0;
    offset.u2 = 0;
    vector3D cameraPos;
    cameraPos.u0 = 0;
    cameraPos.u1 = 0;
    cameraPos.u2 = 0;


    COLORREF COLOR= RGB(255,255,255); 
    HWND myconsole = GetConsoleWindow();
    //Get a handle to device context
    HDC mydc = GetDC(myconsole);

    vector3D shapeData[1034];
    int k = 0;
    for(j=0; 6.28>j; j+=2*0.07)
        for(i=0; 6.28>i; i+=4*0.07){
            //gen_donut_vector(&v3D, 2, 1, i, j, offset);
            //gen_cherry_vector(&v3D, 2, i, j, offset);
            gen_klein_vector(&v3D, 2, i, j, offset);
            shapeData[k].u0 = v3D.u0;
            shapeData[k].u1 = v3D.u1;
            shapeData[k].u2 = v3D.u2;
            k+=1;
        }

    for(;;){
            for(k=0; 1034>k; k+=1) { 
                    rotate_vector(&shapeData[k], offset, phi, theta, 0);
                    project_to_screen(shapeData[k],&v2D,80,5,cameraPos,0,0);
                    // Draw position vectors.
                    SetPixel(mydc,v2D.u0*12,v2D.u1*12,COLOR);
                    }
            printf("\e[1;1H\e[2J");
            }
    return 0;
    }


// Function to handle projecting 3D object to 2D screen.
void project_to_screen(vector3D v3D, vector2D *v2D, float screen_width, float screen_dist, vector3D pos, float ptheta, float pphi){
    float k1 = screen_width*screen_dist*3/(8*(2+1)); // 2 and 1 are torus radii.
    float z = 1/(screen_dist + (v3D.u0-pos.u0)); //screen_distr = k2
    v2D->u0 = k1*z*(v3D.u1-pos.u1) + screen_width/2;
    v2D->u1 = k1*z*(v3D.u2-pos.u2) + screen_width/2;
}

// Generic function to rotate a vector.
void rotate_vector(vector3D *v3D, vector3D offset, float alpha, float beta, float gamma){
    float u0 = v3D->u0 - offset.u0;
    float u1 = v3D->u1 - offset.u1;
    float u2 = v3D->u2 - offset.u2;
    v3D->u0 = cos(alpha)*cos(beta)*u0 + (cos(alpha)*cos(beta)*sin(gamma) - sin(alpha)*cos(gamma))*u1 + (cos(alpha)*sin(beta)*cos(gamma) + sin(alpha)*sin(gamma))*u2 + offset.u0;
    v3D->u1 = sin(alpha)*cos(beta)*u0 + (sin(alpha)*sin(beta)*sin(gamma) + cos(alpha)*cos(gamma))*u1 + (sin(alpha)*sin(beta)*cos(gamma) - cos(alpha)*sin(gamma))*u2 + offset.u1;
    v3D->u2 = -sin(beta)*u0 + cos(beta)*sin(gamma)*u1 + cos(beta)*cos(gamma)*u2 + offset.u2;
}

void translate_vector(vector3D *v3D, vector3D translation){
    v3D->u0 = v3D->u0 + translation.u0;
    v3D->u1 = v3D->u1 + translation.u1;
    v3D->u2 = v3D->u2 + translation.u2;
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

void gen_klein_vector(vector3D *v3D, float r, float i, float j, vector3D offset){
        i = i;
        j = 2*j;
        if(j<3.14){
            v3D->u0 = (2.5-1.5*cos(j))*cos(i) + offset.u0;
            v3D->u1 = (2.5-1.5*cos(j))*sin(i) + offset.u1;
            v3D->u2 = 2.5*sin(j) + offset.u2; 
        }
        else if(6.28>j && j>3.14){
            v3D->u0 = (2.5-1.5*cos(j))*cos(i) + offset.u0;
            v3D->u1 = (2.5-1.5*cos(j))*sin(i) + offset.u1;
            v3D->u2 = (3*3.14-3*j) + offset.u2;
        }
        else if(9.42>j && j>6.28){
            v3D->u0 = (-2 + (2 + cos(i))*cos(j)) + offset.u0;
            v3D->u1 = sin(i) + offset.u1;
            v3D->u2 = (-(2+cos(i))*sin(j) - 3*3.14) + offset.u2;
        }
        else{
            v3D->u0 = (-2 + 2*cos(j)-cos(i)) + offset.u0;
            v3D->u1 = sin(i) + offset.u1;
            v3D->u2 = (3*j-12*3.14) + offset.u2;
        }

}
