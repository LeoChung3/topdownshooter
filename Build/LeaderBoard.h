#pragma once
#include <sstream>
#include <fstream>
#include <iostream>
#include <string> 
#include <map>
#include "GameObject.h"
class LeaderBoard
{
private:
	std::ifstream leaderBoardFile;
	std::string allscores;
	sf::Font myFont;

	std::multimap<std::string, int> highscores;
public:
	bool beingdrawn = false;
	LeaderBoard() {

		if (!myFont.loadFromFile("../Assets/topdown/Fonts/IHATCS__.TTF"))
		{
			std::cout << "not loading font" << std::endl;
		}
		std::string line;

		leaderBoardFile.open("LeaderBoard.txt");
		if (leaderBoardFile.is_open())
		{
			while (getline(leaderBoardFile, line)) {
				allscores.append(line + "\n");
			}
		}
	}
	void NewScore(std::string name, int score);
	void LoadScore();
	void showLeaderBoard(sf::RenderWindow&);
	std::string getasstring();
	std::multimap<std::string, int> getmultimap();
	void closeFile();
};