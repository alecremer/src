#define TESTING


#include <unity.h>
#include <iostream>
#include <sstream>
#include "laracna_pose/vector3.hpp"

using namespace std;

void setUp(void) {

}

void tearDown(void) {

}

void assign_float(){
    
    Vector3<float> v;
    v.x = 1;
    v.y = 2;
    v.z = 3;
    float sum = v.x + v.y + v.z;
    TEST_ASSERT_EQUAL(sum, 6);
    
    // message example
    // stringstream data;
    // data << "assign_float";
    // TEST_MESSAGE(data.str().c_str()) 
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST([]{assign_float();});
    return UNITY_END();
}