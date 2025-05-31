#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <vector>
#include <stdexcept>

using namespace std;

template<typename T>
class Vector3 {
    
public:

    T x, y, z;
    Vector3(void){};

    
    Vector3(const vector<T>& v){
        
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

    
private:

};

#endif // VECTOR3_HPP