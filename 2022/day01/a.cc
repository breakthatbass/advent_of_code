// day 1
// g++ -std=c++11 a.cc

#include <iostream>
#include <string>
#include <vector>

using namespace std;


int main(void)
{
	string line;
	uint32_t current_elf = 0;
	vector<uint32_t> elf_calories;

	while (getline(std::cin, line))
	{
		if (line.empty()) {
			elf_calories.push_back(current_elf);
			current_elf = 0;
		}
		else {
			current_elf += stoi(line);
		}
	}
	elf_calories.push_back(current_elf);

	sort(elf_calories.begin(), elf_calories.end(), greater<int>());
	
	uint32_t top_three_elves = elf_calories[0] + elf_calories[1] + elf_calories[2];
	cout << "part 1: " << elf_calories[0] << "\n";
	cout << "part 2: " << top_three_elves << "\n";
	return 0;
}
