//============================================================
// STUDENT NAME: Nicholas Sun
// NUS User ID.: E0543645
// COMMENTS TO GRADER:
//
// ============================================================

#include <cmath>
#include "Sphere.h"

using namespace std;

bool Sphere::hit( const Ray &r, double tmin, double tmax, SurfaceHitRecord &rec ) const 
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************
    
    // shift the ray to the frame of the sphere as the sphere isn't centered at the origin
    Vector3d newRayOrigin = r.origin() - center;
    /*
    It is a quadratic equation in the form at^2 + bt + c = 0
         a = Rd(dot)Rd = 1 (since |Rd| = 1)
         b = 2 Rd(dot)Ro
         c = Ro(dot)Ro − r2
    */
    double a = dot(r.direction(), r.direction());
    double b = 2 * dot(r.direction(), newRayOrigin);
    double c = dot(newRayOrigin, newRayOrigin) - radius * radius;
    // Discriminant, d = b2 − 4ac
    double d = b * b - 4*(a * c);
    //Case 1: d < 0, Case 2: d == 0, Case 3, d > 0
    if (d < 0) { // no intersect
        return false;
    } else { // there is an intersection
        double t_pos = (-b + sqrt(d)) / (2 * a);
        double t_neg = (-b - sqrt(d)) / (2 * a);
        double t;
        //check whether it lies in the threshold
        if (t_pos >= tmin && t_neg <= tmin) {
            t = t_pos;
        }
        else if (t_neg >= tmin && t_pos <= tmin) {
            t = t_neg;
        }
        else {
            t = min(t_pos, t_neg);
        }
        if (t < tmin || t > tmax) {
            return false;
        }

        rec.t = t;
        rec.p = r.pointAtParam(t);
        Vector3d temp = rec.p - center;
        rec.normal = temp / temp.length();
        rec.material = material;
        return true;
    }
}

bool Sphere::shadowHit( const Ray &r, double tmin, double tmax ) const 
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************


    // shift the ray to the frame of the sphere as the sphere isn't centered at the origin
    Vector3d newRayOrigin = r.origin() - center;
    /*
    It is a quadratic equation in the form at^2 + bt + c = 0
         a = Rd(dot)Rd = 1 (since |Rd| = 1)
         b = 2 Rd(dot)Ro
         c = Ro(dot)Ro − r2
    */
    double a = dot(r.direction(), r.direction());
    double b = 2 * dot(r.direction(), newRayOrigin);
    double c = dot(newRayOrigin, newRayOrigin) - radius * radius;
    // Discriminant, d = b2 − 4ac
    double d = b * b - 4 * (a * c);
    //Case 1: d < 0, Case 2: d == 0, Case 3, d > 0
    if (d < 0) { // no intersect
        return false;
    }
    else { // there is an intersection
        double t_pos = (-b + sqrt(d)) / (2 * a);
        double t_neg = (-b - sqrt(d)) / (2 * a);
        double t;
        //check whether it lies in the threshold
        if (t_pos >= tmin && t_neg <= tmin) {
            t = t_pos;
        }
        else if (t_neg >= tmin && t_pos <= tmin) {
            t = t_neg;
        }
        else {
            t = min(t_pos, t_neg);
        }
        if (t < tmin || t > tmax) {
            return false;
        }
        return true;
    }
}
