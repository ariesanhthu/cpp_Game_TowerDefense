#include "cgame.h"
#include <thread>

using namespace std;

void ThreadFunc2(cgame&);
void ThreadFunc1(cgame&);

int main() {
    
}

void ThreadFunc2(cgame& cg) {
    
    while (!cg.getIsExist1()) {
       
    }
    cg.setIsExist2(true);
}

void ThreadFunc1(cgame& cg) {
    
    while (!cg.getIsExist1()) {
       
    }
    cg.setIsExist1(true);
}