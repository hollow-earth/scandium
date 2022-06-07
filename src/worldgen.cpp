#include "worldgen.hpp"

#include <iostream>
#include <string>
#include <array>


namespace scandium{
	
	void World::generateWorldSeed(const std::string& seedInput){				// This is a pseudo hash function
		enum DIGITS {THREE_DIGITS = 100, TWO_DIGITS = 10, ONE_DIGIT = 1};
		std::array<int, 32> seedPreHashInt;
		std::string seedInputTrimmed = seedInput.substr(0, 16);
		seedInputTrimmed.insert(seedInputTrimmed.length(), 16 - seedInputTrimmed.length(), ' ');
		
		int i = 0;
		for (const char &c: seedInputTrimmed){
			if (c >= THREE_DIGITS && c <= 127){									// <= 127 because we only want ASCII characters
				seedPreHashInt[i] = static_cast<int>((c % 100) / 10);			// We discard the leftmost digit
				seedPreHashInt[i+1] = c % 10;
			}
			else if (c >= TWO_DIGITS){
				seedPreHashInt[i] = static_cast<int>(c / 10);					// We add the digits to each array index
				seedPreHashInt[i+1] = c % 10;
			}
			else if (c >= ONE_DIGIT){
				seedPreHashInt[i] = 0;											// 0 because we have one digit
				seedPreHashInt[i+1] = c;
			}
			else{																// Guard for illegal characters
				seedPreHashInt[i] = 3;											// 3 and 8 are random numbers with no significance
				seedPreHashInt[i+1] = 8;
			}
			i += 2;
		}
		std::string seedPreHashString = "";
		for (const int &c: seedPreHashInt){
			seedPreHashString += std::to_string(c);
		}
		uint64_t seedHashInt = std::hash<std::string>{}(seedPreHashString);
		std::string seedHash = std::to_string(seedHashInt);
		seedHash.insert(seedHash.length(), 20 - seedHash.length(), '0');		// Pad to get 20 digits
		this->worldSeed = seedHash;
	}

	std::string& World::getWorldSeed(){
		return this->worldSeed;
	}

	World::World(){}

	World::~World(){}
}