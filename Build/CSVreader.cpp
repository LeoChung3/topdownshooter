#include "CSVreader.h"

void CSVreader::readfile(string location)
{
    // Open an existing file 
    fin.open(location, ios::in);
    if (!fin.is_open()) {
        cout << "cannot open csv file" << endl;
    }


    //FIRST_NAME	LAST_NAME	LEVEL	SCORE	TAG	CHARACTER_CLASS	KILLS

    if (fin.is_open()){



        row.clear();

        stringstream s(line);

        // read every column data of a row and store it in a string variable, 'word' 
        while (getline(fin, line, ','))
        {
            row.push_back(line);
            //cout << line << endl;
        }
    }
    //std::this_thread::sleep_for(std::chrono::seconds(5));
    //cout << "loaded csv file" << endl;
}

int CSVreader::readfile2(string location)
{
    fin2.open(location, ios::in);
    if (!fin2.is_open()) {
        cout << "cannot open csv file" << endl;}

    if (fin2.is_open()) {
        row2.clear();
        stringstream s(line2);
        while (getline(fin2, line2, ','))
        {
            row2.push_back(line2);
        }
    }

    return 1;
    //std::this_thread::sleep_for(std::chrono::seconds(5));
    //cout << "loaded csv file" << endl;


}
