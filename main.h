#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <vector>
#include <string>
#include <string_view>

int main();
void vectorPrint(std::vector<std::string> inputVector);
void unsepVectorPrint(std::vector<std::string> inputVector);
void vectorVectorPrint(std::vector<std::vector<std::string> > inputVV, bool hasSep);
bool stringCompare(std::string_view input1, std::string_view input2);

#endif // MAIN_H_INCLUDED
