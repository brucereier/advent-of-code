#include <unordered_map>
#include <iostream>

bool checkBeatsRecord(long long time, long long distance, long long held_down){
    return ((held_down * (time - held_down)) > distance);
}

void partOne(std::unordered_map<int, int> races){
    int solution = 1;
    for (const auto& pair : races){
	int first_time = 0;
	int last_time = pair.first;
	while(!checkBeatsRecord(pair.first, pair.second, first_time)){
	    first_time += 1;
	}

	while(!checkBeatsRecord(pair.first, pair.second, last_time)){
	    last_time -= 1;
	}


	solution *= (last_time - first_time + 1);

    }
    std::cout << solution << std::endl;
}

void partTwo(std::unordered_map<long long, long long> races){
    int solution = 1;
    for (const auto& pair : races){
	long long first_time = 0;
	long long last_time = pair.first;
	while(!checkBeatsRecord(pair.first, pair.second, first_time)){
	    first_time += 1;
	}

	while(!checkBeatsRecord(pair.first, pair.second, last_time)){
	    last_time -= 1;
	}


	solution *= (last_time - first_time + 1);
    }
    std::cout << solution << std::endl;
}


int main(){
    std::unordered_map<int, int> races{
	{55, 401}, {99, 1485}, {97, 2274}, {93, 1405}
    };
    std::unordered_map<long long, long long> races2{
	{55999793, 401148522741405}
    };
    partOne(races);
    //P1 Ans 2374848.
    partTwo(races2);
}
