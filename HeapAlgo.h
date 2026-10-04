#ifndef HEAPALGO_H_INCLUDED
#define HEAPALGO_H_INCLUDED
#include <vector>
#include <string>

class heapAlgo{
private:
    inline static std::vector<std::vector<std::string>> collectionPermutatedArray;
public:
    void heapAlgorithm(int lng, std::vector<std::string> inputVector);
    static void appendPermArray (std::vector<std::string> input){
        collectionPermutatedArray.push_back(input);
    }
    void clearPermArray(){
        collectionPermutatedArray.clear();
        std::vector<std::vector<std::string>>().swap(collectionPermutatedArray);
    }
    std::vector<std::vector<std::string>> getPermArray(){
        return collectionPermutatedArray;
    }
};


#endif // HEAPALGO_H_INCLUDED
