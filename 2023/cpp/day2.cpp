#include <fstream>
#include <string>
#include <iostream>

const std::unordered_map<std::string_view, int> color_to_limit {
  {"red" , 12}, {"green", 13}, {"blue", 14}
};

//Helper function to return array of token derived from delimeter.
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

int main()
{
    std::ifstream file("../inputs/day2.txt");
    std::string line;

    int sum;
    int index = 1;
    while (std::getline(file, line)){
	int min_red, min_blue, min_green;
	min_red = min_blue = min_green = 0;
	std::string games = line.substr(line.find(":") + 1);
	std::vector<std::string> full_games = tokenize(games, ";");
	for (const std::string game : full_games){
	    std::vector<std::string> pairs = tokenize(game, ",");
	    for (const std::string pair : pairs){
		std::vector<std::string> split = tokenize(pair.substr(1), " ");
		if(split[1] == "red"){
		    min_red = std::max(min_red, stoi(split[0]));
		} else if(split[1] == "blue"){
		    min_blue = std::max(min_blue, stoi(split[0]));
		} else if(split[1] == "green"){
		    min_green = std::max(min_green, stoi(split[0]));
		}

	    }
	}
	sum += (min_red * min_green * min_blue);
	index += 1;
    }
    std::cout << sum << std::endl;
    //P1 Ans: 2632.
    //P2 Ans: 69629.
}

