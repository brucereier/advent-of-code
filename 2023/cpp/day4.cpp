#include <fstream>
#include <string>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <cmath>



std::vector<std::string> tokenize(std::string s, std::string del)
{
    std::vector<std::string> strings;
    int start, end = -1*del.size();
    do {
        start = end + del.size();
        end = s.find(del, start);
	strings.push_back(s.substr(start, end - start));
    } while (end != -1);
    return strings;
}

void partOne(const std::vector<std::string> &lines){
    int solution = 0;
    for(int i = 0; i < lines.size(); i++){
	int winning_num_count = 0;
	std::vector<std::string> split_game = tokenize(lines[i], ":");
	std::vector<std::string> nums_split = tokenize(split_game[1], "|");
	std::vector<std::string> winning_nums = tokenize(nums_split[0], " ");
	std::vector<std::string> my_nums = tokenize(nums_split[1], " ");
	
	std::unordered_set<std::string> win_set(winning_nums.begin(), winning_nums.end());

	for(const std::string num : my_nums){
	    if(win_set.count(num) && num != " " && num != "" && num != "\r"){
		winning_num_count += 1; 
	    }
	}
	if(winning_num_count > 0){
	    solution += pow(2, winning_num_count - 1);
	}
    }
    std::cout << solution << std::endl;
}

void partTwo(const std::vector<std::string> &lines){
    int solution = 0;
    std::unordered_map<int, int> copies;
    for(int j = 1; j <= 219; j++){
	copies[j] = 1;
    }
    for(int i = 0; i < lines.size(); i++){
	int winning_num_count = 0;
	int current_game = i + 1;
	std::vector<std::string> split_game = tokenize(lines[i], ":");
	std::vector<std::string> nums_split = tokenize(split_game[1], "|");
	std::vector<std::string> winning_nums = tokenize(nums_split[0], " ");
	std::vector<std::string> my_nums = tokenize(nums_split[1], " ");
		
	std::unordered_set<std::string> win_set(winning_nums.begin(), winning_nums.end());

	for(const std::string num : my_nums){
	    if(win_set.count(num) && num != " " && num != "" && num != "\r"){
		winning_num_count += 1; 
	    }
	}
	if(winning_num_count > 0){
	    for(int new_game = 1; new_game <= winning_num_count; new_game++){
		copies[current_game + new_game] += copies[current_game];
	    }
	}
    }

    for(int k = 1; k <= 219; k++){
	solution += copies[k];
    }

    std::cout << solution << std::endl;
}

int main(){
    std::ifstream file ("../inputs/day4.txt");
    std::string line;

    std::vector<std::string> lines;

    while (std::getline(file, line)){
	lines.push_back(line);
    }

    partOne(lines);
    //P1 Ans: 32609.
    partTwo(lines);
    //P2 Ans: 14624680.
}

