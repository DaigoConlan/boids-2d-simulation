#ifndef BOIDS_H
#define BOIDS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <chrono>
#include <random>

#define PI 3.14159265

class Vector2d{

    public:

        //Create a velocity
        Vector2d(double x = 0.0f,double y = 0.0f);

        //Add two velocities together
        Vector2d operator+(const Vector2d& v);

        //The difference between two vectors
        Vector2d operator-(const Vector2d& v);

        //The scalar multiple
        Vector2d operator*(const double& scalar);

        //The scalar division
        Vector2d operator/(const double& scalar);

        double abs();
        
        //For printing vector
        //friend std::ostream& operator<<(std::ostream &out, const Vector2d& v);
        
        //The x and y component of vector
        double x,y;

};

//Data structure of a boid
typedef struct Boid{

    Vector2d posVec;
    Vector2d velocityVec;

} Boid;

class Boids{

    public:

        //Constructor
        Boids();

        //Deconstructor
        ~Boids();
        
        // Set the texture to the image from the path
        // If successful return true
        // Else return false
        bool setTexture(SDL_Renderer* gRenderer,std::string path);

        // Set the range in which the boids can move
        void setBoundary(int minimumX,int minimumY,int maximumX,int maximumY);

        //Set the width and the height of the boids
        void setBoidsSize(int w,int h);

        // Initializes the position of the boids Boids
        // If successfully initializes return true
        // else return false
        void init(int numberOfBoids = 7);

        //Update the position
        void update();

        /*
        // Update the postions manually
        bool update2();
        */

        // Draw the boids (copy the boids to renderer) 
        void draw(SDL_Renderer* gRenderer);

        /*
        // Move all boids towards the centre of mass
        void moveCenterOfMass();
        */

        // Frees all allocated data
        void free();


    private:

        //Fly toward centre of mass
        Vector2d centreOfMass(int i);

        //Fly towards the centre of mass of neighbours
        Vector2d centreOfMassOfNeighbours(int i);

        //Keep small distance away from other objects
        Vector2d preventCollide(int i);

        //Match velocity with near boids
        Vector2d averageVelo(int i);

        //Limit the speed of the boids
        void limitSpeed(int i); 
        
        //Bound position
        void boundPostion(int i);

        //Texture for boids
        SDL_Texture* boidsTexture;

        //Vector that holds both present and future boids
        std::vector<std::vector<Boid> > boidsArray;
        
        //The number of boids
        int numberOfBoids;
        
        //The width and height of the boids
        int boidsWidth,boidsHeight;

        //presentBoids and futureBoids
        int pastBoids,presentBoids;

        //The range in which the boids can move
        //[x,y] st 0<=x<=maxX, 0<=y<=maxY
        int minX,minY,maxX,maxY;

};



#endif