#pragma once

#include <string>

namespace scandium{
	class World{
		public:
			World();
			~World();
			
			/*! @brief Returns seed of selected World object.
			 *
			 *  This function returns the world seed of the selected world, 
			 * 	which is private by default.
			 *
			 *  @returns std::string of 20 characters (digits)
			*/
		 	std::string& getWorldSeed();

			/*! @brief Generates a world seed from a given string.
			 *
			 *  This pseudo hash generator function takes any string and returns 
			 * 	a modified hash code to the variable @sa @ref worldSeed.
			 *	
			 *  @param[in] seedInput The input string. Can be empty or any length
			 *  as it will be padded and truncated to fit only 16 characters and padded.
			*/
			void generateWorldSeed(const std::string& seedInput);
		
		private:
			std::string worldSeed;
	};
}