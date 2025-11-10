#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <string_view>

const std::unordered_map<std::string_view,int> word_to_int{
    {"one",1},{"two",2},{"three",3},{"four",4},{"five",5},
    {"six",6},{"seven",7},{"eight",8},{"nine",9}
};

int find_num(std::string str, int start){
    if (isdigit(str[start])){
	//Subtract 0 offset since int returns ascii code.
	return int(str[start] - '0');
    }
    for (int i = 0; i < 3; i++){
	try {
            int value = word_to_int.at(str.substr(start, 3 + i)); // This will throw an exception if not found.
	    return value;
        } catch (const std::out_of_range& e) {
	    
        }
    }
    return 0;
}

int main() 
{ 
    std::ifstream file("../inputs/day1.txt");
    std::string str; 
    int sum;

    while (std::getline(file, str))
    {
	int head = 0;
	int tail = str.length() - 1;

	while (find_num(str, head) == 0){
	    head += 1;
	}
	while (find_num(str, tail) == 0){
	    tail -= 1;
	}
	std::cout << str << std::endl;
	sum += (find_num(str, head)* 10);
	sum += find_num(str, tail);
	std::cout << sum << std::endl;
    }
    std::cout << sum << std::endl;
    //P1 Ans: 54239.
    //P2 Ans: 55343.
}
