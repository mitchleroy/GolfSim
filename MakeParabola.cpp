#include <iostream>
#include <cmath> 
using namespace std;

// #define PitchingWedge = 47.0
// #define SevenIron = 30
// #define ThreeWood = 20
// #define Driver = 12

const double g = 9.81;
const double m = 0.0459;
double Vf, Vi, Acc, ballForce, angleOfClub, deltaX, xSpan, clubLoft;

enum ClubAngles {PitchingWedge = 47, SevenIron = 30, ThreeWood = 20, Driver = 12};
enum ClubTimes {PitchingWedgeT = 2, SevenIronT = 3, ThreeWoodT = 5, DriverT = 8};

//deltaX = (v^2f - v^2i)/2a
double deltaXnoT (double Vf, double Vi, double Acc);
//forceOnBall = m * [(vf - vi) / contact time]
//^Leave contact time at 0.005
double forceOnBall (double Vf, double Vi, double m, double contactTime, double g);
//acc = forceOnBall / m
double acc (double forceOnBall, double m, double g);
//Hmax = (Vi * sin(angleOfClub)^2 / 2g
double Hmax (double angleOfClub, double Vi, double g);
/*
Parabola equation: y = a(x-h)^2 + k
 ^^ a = +; k = 0; h = 0;
 Pretend origin is in the middle of parabola curve, thus start point
 would be 0 - (dX/2) 
*/
double yOfParabola (double x);

void addYVals (double * ptr, double deltaX);

//TODO: find way to return all information in an array,
// should call all functions to get correct information. 
// dX - fOB - acc - maybe parabola generator 
int main () {

    //Pick club
    ClubAngles angleOFClub;
    angleOfClub = PitchingWedge;
    ClubTimes timeOfLoft;
    timeOfLoft = DriverT;
    clubLoft = timeOfLoft;

    //Assign final velocity ***Will be gathered from accelerometer***
    // ^^Velocity at end of club hitting ball
    Vi = 55;
    Vf = Vi * g;

    //Force
    ballForce = forceOnBall(Vf, Vi, m, clubLoft, g);

    //Acceleration
    //Acc = acc(ballForce, m, g);
    Acc = g;

    deltaX = deltaXnoT(Vf, Vi, Acc);
    int frameSize = 50;
    double xIncrement = deltaX/frameSize;
    //Plug Y values ino yValues array
    double yValues[frameSize];
        cout << "****debug****" << endl;
        cout << "Gravity: " << g << endl;
        cout << "Accelleration: " << Acc << endl;
        cout << "Ball force: " << ballForce << endl;
        cout << "Delta X: " << deltaX << endl;
        cout << "xIncrement: " << xIncrement << endl;
        cout << "****debug****" << endl;
    for (double i = 0; i < frameSize; i += xIncrement) {
        int place = 0;
        yValues[place] = yOfParabola(i);
        place++;  
    }

    for (int i = 0; i < frameSize; i++) {
        cout << yValues[i] << endl;
    }

    return 0;
}
//deltaX = (v^2f - v^2i)/2a
//Calculates displacement given Vi and Acc
double deltaXnoT (double Vf, double Vi, double Acc) {
    return ((pow(Vf,2))-(pow(Vi,2)))/(2 * Acc);
}
//forceOnBall = m * [(vf - vi) / contact time]
//^Leave contact time at 0.005
double forceOnBall (double Vf, double Vi, double m, double contactTime, double g) {
    return (((Vf)-(Vi))/contactTime) * (m * g);
}
//acc = forceOnBall / m
double acc (double forceOnBall, double m, double g) {
    return forceOnBall / (m * g);
}
//Hmax = (Vi * sin(angleOfClub)^2 / 2g
double Hmax (double angleOfClub, double Vi, double g, double m) {
    return ((sin(angleOfClub * (180/3.14))) * Vi) / (2 * g * m);
}
//yOfParabola
double yOfParabola (double x) {
    return pow(x,2);
}

// void addYVals (double * ptr, double deltaX) {
//     for (double i = 0; i < deltaX; i++) {
//         ptr = 1.0;
//         ptr += (2* i);
//     }
// }