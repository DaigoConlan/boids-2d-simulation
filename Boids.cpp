#include "Boids.h"

//Create a vector
Vector2d::Vector2d(double initX ,double initY){

    //Set the x and y positions
    x = initX;
    y = initY;

}

//Add two vectors together
Vector2d Vector2d::operator+(const Vector2d& v){

    Vector2d vector2dSum(0,0);
    vector2dSum.x = x + v.x;
    vector2dSum.y = y + v.y;

    return vector2dSum;
}

//Find the difference of two vectors
Vector2d Vector2d::operator-(const Vector2d& v){

    Vector2d vector2dSub(0,0);
    vector2dSub.x = x - v.x;
    vector2dSub.y = y - v.y;

    return vector2dSub;
}

//Scalar multiply
Vector2d Vector2d::operator*(const double& scalar){

    Vector2d returnVec;
    returnVec.x = x * scalar;
    returnVec.y = y * scalar;

    return returnVec;
}

//Scalar division
Vector2d Vector2d::operator/(const double& scalar){

    Vector2d returnVec;
    returnVec.x = x / scalar;
    returnVec.y = y / scalar;

    return returnVec;
}

double Vector2d::abs(){

    return sqrt(x*x + y*y);

}


std::ostream& operator<<(std::ostream &out, const Vector2d& v){

    return out << "velocity is: ("<<v.x << "," << v.y <<")";

}
        

Boids::Boids(){

    //Set the texture to NULL
    boidsTexture = NULL;

    //Set the indexes for present and future boids
    pastBoids = 0;
    presentBoids = 1;

    //Set the size of the boids array to 2 so that we have 
    // one array holding the presentBoids and the other array
    //to hold the future boids
    boidsArray.resize(2);

    boidsWidth = 100;
    boidsHeight = 100;

    minX = 0;
    minY = 0;
    maxX = 1280;
    maxY = 960;

}

Boids::~Boids(){

    free();
}

bool Boids::setTexture(SDL_Renderer* gRenderer,std::string path){

    bool success = true;

    SDL_Surface* loadedSurface;
    //Load the image into a surface    
    loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface == NULL){

        success = false;
        printf("Failed to load surface. Error: %s\n",IMG_GetError());

    //Create a texture from the surface
    }else{

        boidsTexture = SDL_CreateTextureFromSurface(gRenderer,loadedSurface);

        if(boidsTexture == NULL){

            success = false;
            printf("Failed to create texture from surfce. Error: %s\n",SDL_GetError());
        }

        SDL_FreeSurface(loadedSurface);
    }

    return success;
}

void Boids::setBoundary(int minimumX,int minimunY, int maximumX,int maximumY){

    minX = minimumX;
    minY = minimunY;
    maxX = maximumX;
    maxY = maximumY;
}


void Boids::setBoidsSize(int w,int h){

    boidsWidth = w;
    boidsHeight = h;
}



//Take n as the number of boids
void Boids::init(int n){
    
    numberOfBoids = n;

    boidsArray[pastBoids].resize(numberOfBoids);
    boidsArray[presentBoids].resize(numberOfBoids);

    // obtain a seed from the system clock:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator (seed);

    //Randomly set the initial postions and velocities of the boids
    for(int i=0;i<numberOfBoids;++i){

        srand(1);
        //Set the initial position of boid i
        boidsArray[presentBoids][i].posVec.x = generator()%maxX;
        boidsArray[presentBoids][i].posVec.y = generator()%maxY;
        
        /*debug*/
        //int posX = boidsArray[presentBoids][i].posVec.x -boidsWidth/2;
        //int posY =  boidsArray[presentBoids][i].posVec.y-boidsHeight/2;
        //printf("%d: (%d,%d)\n",i,posX,posY);

        /*debug end*/

    
        //Set the initial velocity of boids i
        boidsArray[presentBoids][i].velocityVec.x = (generator()%3) -1;
        boidsArray[presentBoids][i].velocityVec.y = (generator()%3) -1;
    }

}

void Boids::draw(SDL_Renderer* gRenderer){

    //The structures we need to use for rendering api
    SDL_Rect drawQuad;
    double angle;
    SDL_Point centre;

    //The x and y positions of boid i
    double posX,posY;

    //The x and y components of velocity
    double veloX,veloY;

    for(int i=0;i<numberOfBoids;++i){
        
        //Get the x and y postions
        posX = boidsArray[presentBoids][i].posVec.x;
        posY = boidsArray[presentBoids][i].posVec.y;
        //printf("boid i pos(x,y) = (%f,%f)\n",posX,posY);
        
        //Get the x and y of vector
        veloX = boidsArray[presentBoids][i].velocityVec.x;
        veloY =  boidsArray[presentBoids][i].velocityVec.y;
        //printf("boid i velo(x,y) = (%f,%f)\n",veloX,veloY);
        
        //printf("speed = %f\n",sqrt(veloX*veloX + veloY*veloY));
        drawQuad.x =  posX - boidsWidth/2;
        drawQuad.y =  posY - boidsHeight/2;
        drawQuad.w = boidsWidth;
        drawQuad.h = boidsHeight;

        centre.x = boidsWidth/2;
        centre.y = boidsHeight/2;

        angle = (atan2(veloY,veloX) * 180)/PI + 90;
        
        SDL_RenderCopyEx(gRenderer,boidsTexture,NULL,&drawQuad,angle,NULL,SDL_FLIP_NONE);

    }
}
void Boids::free(){

    //clears the boids in array
    boidsArray[pastBoids].clear();
    boidsArray[presentBoids].clear();

    //Set the number of boids to 0
    numberOfBoids = 0;
    
}

void Boids::update(){

    //pastBoidsArrray will now hold present Boids
    pastBoids = (pastBoids+1)%2;
    presentBoids = (presentBoids+1)%2;

    Vector2d v1,v2,v3,v4;
    int m1,m2,m3,m4;

    m1 = 1;
    m2 = 1;
    m3 = 1;
    m4 = 1;
    
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator (seed);
    
    if(generator()%20==0){

        m1 = -1;
    }

    if(generator()%40 == 0){

        m2 = -1;
    }
    
    for(int i=0;i<numberOfBoids;++i){
        
        //Calculate the velocity
        v1 = centreOfMass(i)*m1;
        //v2 = centreOfMassOfNeighbours(i)*m2; 
        v3 = preventCollide(i)*m3;
        v4 = averageVelo(i)*m4;

        boidsArray[presentBoids][i].velocityVec = boidsArray[pastBoids][i].velocityVec + v1 + v2 + v3 + v4; 
        
        //limit the speed and the area
        boundPostion(i);
        limitSpeed(i);

        //update the positions of the boids
        boidsArray[presentBoids][i].posVec = boidsArray[pastBoids][i].posVec + boidsArray[presentBoids][i].velocityVec/2.0;

    }
}


//Move towards centre of mass of neighbours
Vector2d Boids::centreOfMass(int i){
    
    //The vector we will be returning
    Vector2d returnVec;

    //The position vector of the ith boid
    Vector2d boidIPos = boidsArray[pastBoids][i].posVec;

    //The centre of mass of the neighbouring boids
    Vector2d centreOfMass(0,0);

    //Find the centre of mass of neighbouring boids

    //Add the position vectors of all the neighbouring boids
    for (int j=0;j<numberOfBoids;++j){

        if(j!=i){

            centreOfMass = centreOfMass + boidsArray[pastBoids][j].posVec;
        }
    }

    //Take the average of the sum of the position vectors of the neighbouring boids

    centreOfMass = centreOfMass/(numberOfBoids-1);

    returnVec =  (centreOfMass - boidIPos)/100;

    return returnVec;

}


//Move towards centre of mass of neighbours
Vector2d Boids::centreOfMassOfNeighbours(int i){
    
    //The vector we will be returning
    Vector2d returnVec;

    //The position vector of the ith boid
    Vector2d boidIPos = boidsArray[pastBoids][i].posVec;

    
    //The centre of mass of the neighbouring boids
    Vector2d centreOfMass(0,0);

    //number of neighbours
    int numberOfNeighbours;

    //Find the centre of mass of neighbouring boids

    //Add the position vectors of all the neighbouring boids
    for (int j=0;j<numberOfBoids;++j){
        
        Vector2d boidJPos = boidsArray[pastBoids][j].posVec;
        Vector2d diff = boidIPos - boidJPos;
        if(diff.abs()<20){

            centreOfMass = centreOfMass + boidsArray[pastBoids][j].posVec;
        }
    }

    //Take the average of the sum of the position vectors of the neighbouring boids

    centreOfMass = centreOfMass/(numberOfBoids);

    returnVec =  (centreOfMass - boidIPos)/400;

    return returnVec;

}

//Prevent boids from colliding
Vector2d Boids::preventCollide(int i){

    //The vector we will be returning
    Vector2d returnVec(0,0);

    //The position of the ith boid
    Vector2d boidsIPos = boidsArray[pastBoids][i].posVec;

    //The position of the jth boid
    Vector2d boidsJPos;

    for(int j=0;j<numberOfBoids;++j){

        boidsJPos = boidsArray[pastBoids][j].posVec;

        if(j!=i){

            Vector2d diff = (boidsJPos - boidsIPos);

            if(diff.abs()<10){

                returnVec = returnVec - (boidsJPos - boidsIPos);
            } 
        }
    }


    return returnVec;
}

//Try and match velocity of neighbouring boids
Vector2d Boids::averageVelo(int i){

    Vector2d averageVelo(0.0f,0.0f);

    Vector2d boidsIVelo = boidsArray[pastBoids][i].velocityVec;
    Vector2d boidsIPos = boidsArray[pastBoids][i].posVec;
    
    Vector2d boidsJVelo;
    Vector2d boidsJPos;
    Vector2d diff;

    int numberOfNeighbours = 0;

    for(int j=0;j<numberOfBoids;++j){

        boidsJVelo = boidsArray[pastBoids][j].velocityVec;
        boidsJPos = boidsArray[pastBoids][j].posVec;

        diff = boidsJPos - boidsIPos;

        if(diff.abs()<30){

            averageVelo = averageVelo + boidsJVelo;
            numberOfNeighbours++;
        }
    }

    averageVelo = averageVelo/(numberOfNeighbours);

    return  (averageVelo)/8;
        
}

//limit the speed of the boids
void Boids::limitSpeed(int i){

    double limitSpeed = 30;

    Vector2d v;
    Vector2d boidsIVelo = boidsArray[presentBoids][i].velocityVec;
    if(boidsIVelo.abs() > limitSpeed){

        boidsIVelo = (boidsIVelo/boidsIVelo.abs()) * limitSpeed; 
    }
    
    boidsArray[presentBoids][i].velocityVec = boidsIVelo;
}

//limit the area in which the boids can move
void Boids::boundPostion(int i){

    Vector2d boidsIPos = boidsArray[presentBoids][i].posVec;
    Vector2d boidsIVelo = boidsArray[presentBoids][i].velocityVec;
    
    if(boidsIPos.x < minX){

        boidsIVelo.x +=5 ;
    
    }else if(boidsIPos.x > maxX){

        boidsIVelo.x -= 5 ;
    }

    if(boidsIPos.y < minY){

        boidsIVelo.y +=5;
    
    }else if(boidsIPos.y > maxY){

        boidsIVelo.y -=5;
    }

    boidsArray[presentBoids][i].velocityVec = boidsIVelo;

}







