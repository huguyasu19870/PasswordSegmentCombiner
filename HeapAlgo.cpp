#include "HeapAlgo.h"
#include <vector>
#include <string>
#include <algorithm>

void heapAlgo::heapAlgorithm(int lng, std::vector<std::string> inputArray){
    if(lng == 1){
        heapAlgo::appendPermArray(inputArray);
    } else {
        for(int i = 0; i < lng; i++){
            heapAlgo::heapAlgorithm(lng-1, inputArray);
            if(lng%2 == 0){
                std::swap(inputArray[i], inputArray[lng-1]);
            } else {
                std::swap(inputArray[0], inputArray[lng-1]);
            }
        }
    }
}
