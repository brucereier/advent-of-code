#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

struct Node {
    std::string left;
    std::string right;
};

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

void buildGraph(std::unordered_map<std::string, Node>& graph, std::vector<std::string> lines){
    for(std::string line : lines){
	graph[line.substr(0, 3)] = Node{line.substr(7, 3), line.substr(12, 3)};
    }    
}

int traverseGraph(std::unordered_map<std::string, Node> graph, std::string input){
    std::string cur = "AAA";
    int steps = 0;
    while(cur != "ZZZ"){
	if(input[steps % input.length()] == 'L'){
	    cur = graph[cur].left;
	} else{
	    cur = graph[cur].right;
	}
	steps += 1;
    }
    return steps;
}

void partOne(std::string input, std::vector<std::string> lines){
    std::unordered_map<std::string, Node> graph;
    buildGraph(graph, lines);
    int solution = traverseGraph(graph, input);
    std::cout << solution << std::endl;
}

bool checkDone(std::vector<std::string> nodes){
    for(std::string node: nodes){
	if(node[2] != 'Z'){
	    return false;
	}
    }

    return true;
}

void updateNodes(std::vector<std::string>& nodes, std::unordered_map<std::string, Node>& graph, char dir){
    for(std::string& node: nodes){
	node = (dir == 'L') ? graph[node].left : graph[node].right;
    }
}
int traverseGhostGraph(std::unordered_map<std::string, Node> graph, std::vector<std::string> starts, std::string input){
    int steps = 0;
    while(!checkDone(starts)){
	if(input[steps % input.length()] == 'L'){
	    updateNodes(starts, graph, 'L');
	} else{
	    updateNodes(starts, graph, 'R');
	}
	steps += 1;
    }
    return steps;
 
}
void partTwo(std::string input, std::vector<std::string> lines){
    std::unordered_map<std::string, Node> graph;
    buildGraph(graph, lines);
    std::vector<std::string> starts;
    for(auto& pair: graph){
	if(pair.first[2] == 'A'){
	   starts.emplace_back(pair.first); 
	}
    }
    int solution = traverseGhostGraph(graph, starts, input);
    std::cout << solution << std::endl;
}

int main() {
    std::ifstream file("../inputs/day8.txt");    
    std::string line;

    std::vector<std::string> lines;
    std::string input;
    
    int i = 0;
    while(std::getline(file, line)){
	if (i == 0){
	    input = line;
	} else if(i > 1){
	    lines.push_back(line);
	}
	i += 1;
    }

    partOne(input, lines);
    //P1: 19951.
    partTwo(input, lines);
    //P2: hard.
}
