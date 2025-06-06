#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <vector>
#include <stdexcept>
#include <cmath>

using namespace std;

template<typename T>
class Vector3 {
    
public:

    T x, y, z;
    Vector3(void){};

    
    Vector3(vector<T> v){
        
        if(v.size() != 3){
            throw invalid_argument("vector must have 3 elements");
        }
        else {
            
            typename vector<T>::iterator it = v.begin();
            x = *it;
            y = *(it + 1);
            z = *(it + 2);
        }
    } 
    Vector3(const T& num){
        
        x = num;
        y = num;
        z = num;
        
    } 
    float get_magnitude(void){return sqrt(x*x + y*y + z*z);}
    
    Vector3<T> degrees(void){
        return Vector3(vector<T>{x*180.0f/M_PI, y*180.0f/M_PI, z*180.0f/M_PI});
    }

    Vector3<T> rad(void){
        return Vector3(vector<T>{x*M_PI/180.0f, y*M_PI/180.0f, z*M_PI/180.0f});
    }
    
private:

};

#endif // VECTOR3_HPP