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

void create_by_vector(){
    
    Vector3<float> v(vector<float>{1, 2, 3});
    float sum = v.x + v.y + v.z;
    TEST_ASSERT_EQUAL(sum, 6);
    
    // message example
    // stringstream data;
    // data << "assign_float";
    // TEST_MESSAGE(data.str().c_str()) 
}

void create_by_num(){
    
    Vector3<float> v(7);
    float sum = v.x + v.y + v.z;
    TEST_ASSERT_EQUAL(sum, 21);
    
    // message example
    // stringstream data;
    // data << "assign_float";
    // TEST_MESSAGE(data.str().c_str()) 
}

void test_magnitude(){
    Vector3<float> v(vector<float>{1, 2, 3});
    float mag = v.get_magnitude();
    TEST_ASSERT_FLOAT_WITHIN(0.001f, mag, 3.7416f);

}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST([]{assign_float();});
    RUN_TEST([]{create_by_vector();});
    RUN_TEST([]{create_by_num();});
    RUN_TEST([]{test_magnitude();});
    return UNITY_END();
}