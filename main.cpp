#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <ios>
#include <string_view>
#include <algorithm>
#include "HeapAlgo.h"
#include "main.h"

int main()
{
    heapAlgo HA;
    bool textOutput = false;
    bool specifiedOutputMethod = false;
    std::string temp1;
    while(!specifiedOutputMethod){
        std::cout << "Do you want the output to be in a text file format?" << std::endl;
        std::cin >> temp1;
        if(stringCompare(temp1, "true") || stringCompare(temp1, "yes") || stringCompare(temp1, "ok") || stringCompare(temp1, "y") || stringCompare(temp1, "t") || (temp1 == "1")){
            textOutput = true;
            specifiedOutputMethod = true;
        } else if(stringCompare(temp1, "false") || stringCompare(temp1, "no") || stringCompare(temp1, "n") || stringCompare(temp1, "f") || (temp1 == "0")){
            textOutput = false;
            specifiedOutputMethod = true;
        } else {
            std::cout << "Input cannot be resolved to yes or no. Try again." << std::endl;
        }
    }
    std::string outputPath = "-";
    if(textOutput){
        std::string configPath = "C:\\ProgramData\\HomemadePasswordRecoverySoftware\\config.txt";
        std::string defaultOutputPath = "C:\\ProgramData\\HomemadePasswordRecoverySoftware\\";
        std::string defaultOutputFileName = "output.txt";
        std::string defaultFullPath = defaultOutputPath + defaultOutputFileName;
        std::fstream config(configPath,std::ios::in);
        if(!config.is_open()){
            config.open(configPath,std::ios::app);
            config << "Output Path = " << defaultFullPath;
            outputPath = defaultFullPath;
        } else {
            std::string line;
            std::string::size_type pos;
            while(std::getline(config, line)){
                pos = line.find("=");
                if(pos != std::string::npos){
                    outputPath = line.substr((pos+1));
                    break;
                }
            }
        }
        config.close();
    }

    bool permutationGenerationMode = false;
    /*
    bool hasSpecifiedProcessViewing = false;
    std::string passGenInput;
    while(!hasSpecifiedProcessViewing){
        std::cout << "Do you need to view the process of password generation?" << std::endl;
        std::cin >> passGenInput;
    }
    */
    std::string unusedLetter;
    std::cout << "Provide the letter that you believe is not used in the password." << std::endl;
    std::cin >> unusedLetter;
    bool stillInput = true;
    bool fragmentInput = true;
    bool passwordInsert = false;
    bool posSpec = false;
    bool passwordReplace = false;
    std::string input;
    std::string unusedStatement = "Unused letter used for finish inputting is ";
    unusedStatement.append(unusedLetter);
    std::vector<std::string> passFrag;
    passFrag.reserve(8);
    std::vector<std::string> staticPassFrag;
    staticPassFrag.reserve(4);
    std::vector<int> passPosStatic;
    passPosStatic.reserve(4);
    std::vector<std::string> passRepFrag;
    passRepFrag.reserve(2);
    std::vector<int> passRepPos;
    passRepPos.reserve(2);
    while(stillInput){
        std::string totalSizeStatement = "Total length of this password are: ";
        std::string totalSize =  std::to_string((passFrag.size() + staticPassFrag.size()));
        if(fragmentInput){
            std::cout << "Please provide password fragment." << std::endl<< unusedStatement << std::endl;
        } else if(passwordInsert){
            if(!posSpec){
                std::cout << "Please provide password fragment that needs to stay in place." << std::endl << unusedStatement << std::endl;
            } else {
                std::cout << "Please provide position in which fragment to be stayed." << std::endl << totalSizeStatement << totalSize << std::endl << unusedStatement << std::endl;
            }
        } else if(passwordReplace){
            if(!posSpec){
                std::cout << "Please provide password fragment that replace some fragment." << std::endl << unusedStatement << std::endl;
            } else {
                std::cout << "Please provide position in which fragment be replaced." << std::endl << totalSizeStatement << totalSize << std::endl << unusedStatement << std::endl;
            }
        }
        std::cin >> input;
        if(input != unusedLetter){
            int positionInt;
            if(fragmentInput){
                passFrag.push_back(input);
            } else if(passwordInsert && !posSpec){
                staticPassFrag.push_back(input);
            } else if(passwordInsert && posSpec){
                //Position here is not programming position, where the first position is specified as 0, but ordinary position, where the first position is specified as 1.
                try{
                    positionInt = std::stoi(input);
                } catch(...) {
                    std::cout << "This input can't be converted to a number." << std::endl;
                }
                passPosStatic.push_back(positionInt);
                if(staticPassFrag.size() == passPosStatic.size()){
                    goto forceEnd;
                }
            } else if(passwordReplace && !posSpec){
                passRepFrag.push_back(input);
            } else if(passwordReplace && posSpec){
                try{
                    positionInt = std::stoi(input);
                } catch(...) {
                    std::cout << "This input can't be converted to a number." << std::endl;
                }
                if(positionInt <= std::stoi(totalSize)){
                    passRepPos.push_back(positionInt);
                } else {
                    std::cout << "Position specified pointed outside of the password." << std::endl;
                    std::cout << "If you want to append the password, please use stay function." << std::endl;
                }
                if(passRepFrag.size() == passRepPos.size()){
                    goto forceEnd;
                }
            }
        } else if(input == unusedLetter){
            forceEnd:
            std::string notEnoughPos = "There is not enough position inputted.";
            size_t fragSize;
            size_t posSize;
            if(fragmentInput){
                fragmentInput = false;
                passwordInsert = true;
            } else if(passwordInsert && !posSpec){
                if(staticPassFrag.size() != 0){
                    fragSize = staticPassFrag.size();
                    posSpec = true;
                } else {
                    passwordInsert = false;
                    passwordReplace = true;
                }
            } else if(passwordInsert && posSpec){
                posSize = passPosStatic.size();
                if(posSize != fragSize){
                    std::cout << notEnoughPos << std::endl;
                    continue;
                }
                posSpec = false;
                passwordInsert = false;
                passwordReplace = true;
            } else if(passwordReplace && !posSpec){
                if(passRepFrag.size() != 0){
                    fragSize = passRepFrag.size();
                    posSpec = true;
                } else {
                    passwordReplace = false;
                    stillInput = false;
                }
            } else if(passwordReplace && posSpec){
                posSize = passRepPos.size();
                if(posSize != fragSize){
                    std::cout << notEnoughPos << std::endl;
                    continue;
                }
                posSpec = false;
                passwordReplace = false;
                stillInput = false;
            }
        }
    }
    int passFragSize = passFrag.size();
    std::vector<std::vector<std::string> > permPassFrag;
    HA.heapAlgorithm(passFragSize, passFrag);
    permPassFrag = HA.getPermArray();
    //vectorVectorPrint(permPassFrag, true);
    std::cout << "Total number of permutation: " << permPassFrag.size() << std::endl;
    std::vector<std::vector<std::string> > resultPass;
    if(!permutationGenerationMode){
        if((staticPassFrag.size() != passPosStatic.size()) || (passRepFrag.size() != passRepPos.size())){
            return 1;
        }
    } else {
        return 0;
    }
    bool calcStatic;
    bool calcReplace;
    for(size_t i = 0; i < permPassFrag.size(); i++){
        if(staticPassFrag.size() > 0){
            calcStatic = true;
        } else{
            calcStatic = false;
        }
        if(passRepFrag.size() > 0){
            calcReplace = true;
        } else {
            calcReplace = false;
        }
        if(calcStatic){
            for(size_t o = 0; o < staticPassFrag.size(); o++){
                permPassFrag[i].insert(permPassFrag[i].begin() + passPosStatic[o], staticPassFrag[o]);
            }
            calcStatic = false;
        }
        std::vector<std::string> tempVector = permPassFrag[i];
        if(!calcStatic && calcReplace){
            for(size_t u = 0; u < passRepFrag.size(); u++){
                tempVector[passRepPos[u]] = passRepFrag[u];
            }
        }
        resultPass.push_back(tempVector);
    }
    if(textOutput){
        std::fstream output(outputPath,std::ios::out);
        if(!output.is_open()){
            output.open(outputPath,std::ios::out);
        }
        for(size_t i = 0; i < resultPass.size(); i++){
            for(size_t o = 0; o < resultPass[i].size(); o++){
                output << resultPass[i][o];
            }
            output << "\n";
        }
        output.close();
    } else {
        vectorVectorPrint(resultPass, false);
    }
    return 0;
}

void vectorPrint(std::vector<std::string> inputVector){
    int vectorSize = inputVector.size();
    for(int i = 0; i < vectorSize; i++){
        std::cout << inputVector[i] << "|";
    }
}

void unsepVectorPrint(std::vector<std::string> inputVector){
    int vectorSize = inputVector.size();
    for(int i = 0; i < vectorSize; i++){
        std::cout << inputVector[i];
    }
}

void vectorVectorPrint(std::vector<std::vector<std::string> > inputVV, bool hasSep){
    int vVSize = inputVV.size();
    for(int i = 0; i < vVSize; i++){
        if(hasSep){
            vectorPrint(inputVV[i]);
        } else {
            unsepVectorPrint(inputVV[i]);
        }
        std::cout << std::endl;
    }
}

bool stringCompare(std::string_view input1, std::string_view input2){
    if(input1.length() != input2.length()){
        return false;
    } else {
        return std::equal(input1.begin(), input1.end(), input2.begin(),[](char a, char b) {
            return std::tolower(static_cast<unsigned char>(a)) == std::tolower(static_cast<unsigned char>(b));
        });
    }
}
