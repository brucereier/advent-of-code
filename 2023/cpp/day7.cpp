#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

struct Entry {
    std::string hand;
    int bid;
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

//Map to convert card to another character - used so we can use lexicographical comparison to break ties.
const std::unordered_map<char, char> lex_map{
    {'A', 'a'}, {'K', 'b'}, {'Q', 'c'}, {'J', 'd'}, {'T', 'e'}, {'9', 'f'}, {'8', 'g'}, {'7', 'h'}, {'6', 'i'}, {'5', 'j'}, {'4', 'k'}, {'3', 'l'}, {'2', 'm'}
};

const std::unordered_map<char, char> lex_map2{
    {'A', 'a'}, {'K', 'b'}, {'Q', 'c'}, {'J', 'o'}, {'T', 'e'}, {'9', 'f'}, {'8', 'g'}, {'7', 'h'}, {'6', 'i'}, {'5', 'j'}, {'4', 'k'}, {'3', 'l'}, {'2', 'm'}
};


std::string convertHandToLex(std::string hand){
   for(char& c: hand){
	c = lex_map.at(c);
    } 
    return hand;
}

std::string convertHandToLexTwo(std::string hand){
   for(char& c: hand){
	c = lex_map2.at(c);
    } 
    return hand;
}

std::unordered_map<char, int> createMapFromHand(std::string hand){
    std::unordered_map<char, int> handMap;
    for(const auto& pair: lex_map){
	handMap[pair.second] = 0;
    }
    for (char c : hand){
	handMap[c] += 1;	
    }

    //Joker check
    if(handMap['o'] > 0){
	if(handMap['o'] == 5){ //JJJJJ edgecase
	    handMap['a'] += 5;
	} else {
	    int biggest_group = 0;
	    char biggest_char = 'o';
	    for(const auto& pair: handMap){
		if(pair.second > biggest_group && pair.first != 'o'){
		    biggest_group = pair.second;
		    biggest_char = pair.first;
		}
	    }
	    handMap[biggest_char] += handMap['o'];
	}
	handMap['o'] = 0;
    }
    return handMap;
}

int compareHands(std::string hand1, std::string hand2){
    std::unordered_map<char, int> hand1map = createMapFromHand(hand1);
    std::unordered_map<char, int> hand2map = createMapFromHand(hand2);

    std::vector<int> hand1vec, hand2vec;
    for(const auto& pair: hand1map){
	if(pair.second > 1){
	    hand1vec.push_back(pair.second);
	}
    }

    for(const auto& pair: hand2map){
	if(pair.second > 1){
	    hand2vec.push_back(pair.second);
	}
    }

    std::sort(hand1vec.begin(), hand1vec.end(), std::greater<>());
    std::sort(hand2vec.begin(), hand2vec.end(), std::greater<>());

    while(hand1vec.size() > 0 && hand2vec.size() > 0){
	if(hand1vec[0] == hand2vec[0]){
	    hand1vec.erase(hand1vec.begin());
	    hand2vec.erase(hand2vec.begin());
	} else {
	    return (hand1vec[0] > hand2vec[0]) ? -1 : 1;
	}
    }

    
    if(hand1vec.size() + hand2vec.size() == 0){
	//Same hand type - compare lexicographically
	if(hand1 == hand2) return 0;
	return (hand1 > hand2) ? 1 : -1;
    }

    return (hand1vec.size() > hand2vec.size()) ? -1 : 1;
}

void addToRanked(Entry entry, std::vector<Entry>& ranked){
    if(ranked.size() == 0){
	ranked.emplace_back(entry);
	return;
    }
    int low = 0;
    int high = ranked.size();

    while (low < high){
	int mid = (low + high) / 2;
	int comp = compareHands(entry.hand, ranked[mid].hand);
	if (comp > 0){
	    high = mid;
	} else {
	    low = mid + 1;
	}
    }

    ranked.insert(ranked.begin() + low, entry);
}

void partOne(std::vector<std::string> lines){
    std::vector<Entry> rankedHands;
    int solution = 0;
    for(std::string line: lines){
        std::vector<std::string> line_split = tokenize(line, " ");
	Entry entry{convertHandToLex(line_split[0]), std::stoi(line_split[1])};
	addToRanked(entry, rankedHands);
    }
    
    for(int i = 0; i < rankedHands.size(); i++){
	solution += (rankedHands[i].bid * (i + 1));
    }
    std::cout << solution << std::endl;
}

void partTwo(std::vector<std::string> lines){
    std::vector<Entry> rankedHands;
    int solution = 0;
    for(std::string line: lines){
        std::vector<std::string> line_split = tokenize(line, " ");
	Entry entry{convertHandToLexTwo(line_split[0]), std::stoi(line_split[1])};
	addToRanked(entry, rankedHands);
    }
    
    for(int i = 0; i < rankedHands.size(); i++){
	solution += (rankedHands[i].bid * (i + 1));
    }
    std::cout << solution << std::endl;
}

int main(){
    std::ifstream file("../inputs/day7.txt");
    std::string line;

    std::vector<std::string> lines;

    while(std::getline(file, line)){
	lines.push_back(line);
    }

    partOne(lines);
    //P1 Ans: 250120186.
    partTwo(lines);
}

