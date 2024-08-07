#include "LeaderBoard.h"

void LeaderBoard::NewScore(std::string name, int score)
{
    std::ofstream leaderBoardFile;    
    leaderBoardFile.open("LeaderBoard.txt");

    //std::string str = name + std::to_string(score);
    //leaderBoardFile << allscores << str << std::endl;
    highscores.insert(std::make_pair(name, score));

    for (auto it = highscores.rbegin(); it != highscores.rend(); it++)
    {
        leaderBoardFile << it->first << " " << it->second << endl;
    }

    leaderBoardFile.close();

}

void LeaderBoard::LoadScore()
{
    highscores.clear();
    std::ifstream leaderBoardFile;
    leaderBoardFile.open("LeaderBoard.txt");
    char mychar;
    std::string line;
    std::string a;
    int b;
    while (leaderBoardFile >> a >> b)
    {
        highscores.insert(std::make_pair(a, b));
    }


}

void LeaderBoard::showLeaderBoard(sf::RenderWindow& window)
{
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(500.f, 500.f));
    shape.setPosition((1920.f / 2) - 250, (1080.f / 2) - 250);
    shape.setFillColor(sf::Color::White);
    window.draw(shape);

    sf::Text nameandscore;

    nameandscore.setFont(myFont);
    nameandscore.setCharacterSize(30);
    nameandscore.setColor(sf::Color::Black);

    //std::ifstream leaderBoardFile;
    //leaderBoardFile.open("LeaderBoard.txt");
    float order = 0;
    for (auto it = highscores.rbegin(); it != highscores.rend(); it++)
    {
        nameandscore.setPosition(sf::Vector2f((1920.f / 2.f) - 250.f, (1080.f / 2.f) - (250.f - (order * 30.f))));
        order += 1;
        string killText = it->first + " : " + to_string(it->second);
        nameandscore.setString(killText);
        window.draw(nameandscore);

    }
    order = 0;
    /*if (leaderBoardFile.is_open())
    {
        char mychar;
        std::string line;
        while (getline(leaderBoardFile, line))
        {
            std::cout << line << '\n';
        }
    }
    leaderBoardFile.close();*/
}

std::string LeaderBoard::getasstring()
{
    std::ostringstream displaytext;
    displaytext << "scores" << std::endl;
    for (auto it = highscores.rbegin(); it != highscores.rend(); it++)
    {
        displaytext << it->first << ": " << it->second << std::endl;
    }

    return displaytext.str();
}

std::multimap<std::string, int> LeaderBoard::getmultimap()
{
    return highscores;
}

void LeaderBoard::closeFile()
{
	leaderBoardFile.close();
}
