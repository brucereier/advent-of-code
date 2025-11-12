#include <fstream>
#include <string>
#include <vector>
#include <iostream>

bool hasAdjacentSymbol(const std::vector<std::string>& lines, int i, int j){
    for(int di = -1; di <= 1; di++){
	for(int dj = -1; dj <= 1; dj++){
	    int new_i = i + di;
	    int new_j = j + dj;
	    if((di == 0 && dj == 0) || new_i < 0 || new_j < 0 || new_i >= lines.size() || new_j >= lines[new_i].size()){
		continue;
	    }

	    if (lines[new_i][new_j] != '.' && !std::isdigit(lines[new_i][new_j])){
		return true;
	    }
	}
    }
    return false;
}

void partOne(const std::vector<std::string> &lines){
    int solution = 0;
    for (int i = 0; i < lines.size(); i++){
	bool is_part = false;
	std::string cur = "";

	for(int j = 0; j < lines[i].length(); j++){
	    if (!std::isdigit(lines[i][j])){
		if (is_part && cur.length() > 0){
		    solution += std::stoi(cur);
		}

		cur = "";
		is_part = false;

		continue;
	    }

	    cur += lines[i][j];

	    if (hasAdjacentSymbol(lines, i, j)){
		is_part = true;
	    }
	}
	if(is_part){
	    solution += std::stoi(cur);
	}
    }
    std::cout << "P1: " << solution << "\n";
}

void partTwo(std::vector<std::string> &lines){

}


int main(){
    std::ifstream file ("../inputs/day3.txt");
    std::string line;

    std::vector<std::string> lines;

    while (std::getline(file, line)){
	lines.push_back(line);
	std::cout << line << std::endl;
    }

    partOne(lines);
    partTwo(lines);
}
