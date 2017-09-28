/**
 *  File:       bowling.cpp
 *
 *  Author:     Kevin Mendoza <kmendoza8@mail.csuchico.edu>
 *
 *  Purpose:    Simple scorekeeping for bowling
 *
 *  Version:    0.0.0
 **/

/**
 * Included libraries, definitions, and function declarations
 **/

#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include <vector>
#include <string>

using namespace std;

void playerInit(int&, vector<string>&);
void game(int, int&, vector<string>, vector< vector<int> >&,
    vector< vector<string> >&);
void printBoard(int, vector<string>, vector< vector<string> >,
    vector< vector<int> >);

int main(void)
{
    int numPlayers;
    int round = 1;
    vector< vector<int> > score;
    vector<string> names;
    vector< vector<string> > rolls;

    playerInit(numPlayers, names);

    score.resize(numPlayers);
    rolls.resize(numPlayers);

    game(numPlayers, round, names, score, rolls);

    return 0;
}

void playerInit(int &numPlayers, vector<string> &names)
{
    string nameInput;

    do
    {
        cout << "\nPlease enter number of players (1-4): " << endl;
        cin >> numPlayers;

        if ( isdigit(numPlayers) && numPlayers >= 1 && numPlayers <= 4 )
        {
            cout << "Invalid number of players." << endl;
        }

    } while ( isdigit(numPlayers) && numPlayers >= 1 && numPlayers <= 4 );

    for (int i = 0; i < numPlayers; i++)
    {
        cout << "Please enter Player " << i + 1 << "'s name: " << endl;
        cin >> nameInput;
        names.push_back(nameInput);
    }

    cout << endl;
}

void game(int numPlayers, int &round, vector<string> names,
    vector< vector<int> > &score, vector< vector<string> > &rolls)
{
    int roll = 0;
    vector<bool> strike(numPlayers, false);

    for (; round <= 10; round++)
    {
        cout << "\n\nRound " << round << endl;

        for (int i = 0; i < numPlayers; i++)
        {
            do
            {
                cout << "Enter " << names.at(i) << "'s first roll (0-10): " <<
                    endl;

                cin >> roll;

                if ( isdigit(roll) && roll >= 0 && roll <= 10 )
                {
                    cout << "Invalid score input." << endl;
                }

            } while ( isdigit(roll) && roll >= 0 && roll <= 10 );

            if ( roll == 10 )
            {
                rolls[i].push_back(" ");
                strike[i] = true;
            }
            else
            {
                rolls[i].push_back(to_string(roll));
            }
        }

        for (int i = 0; i < numPlayers; i++)
        {
            do
            {
                if ( strike[i] == true )
                {
                    break;
                }

                cout << "Enter " << names.at(i) << "'s second roll (0-10): " <<
                    endl;

                cin >> roll;

                if ( isdigit(roll) && roll >= 0 && roll <= 10 )
                {
                    cout << "Invalid score input." << endl;
                }

            } while ( isdigit(roll) && roll >= 0 && roll <= 10 );

            if ( strike[i] == true )
            {
                rolls[i].push_back("X");
            }
            else if ( stoi( rolls[i].back() ) + roll >= 10)
            {
                rolls[i].push_back("/");
            }
            else
            {
                rolls[i].push_back(to_string(roll));
            }
        }

        for (int i = 0; i < numPlayers; i++)
        {
            if ( rolls[i].back() == "X" )
            {
                score[i].push_back(99);
            }
            else if ( rolls[i].back() == "/" )
            {
                score[i].push_back(10);
            }
            else
            {
                score[i].push_back( stoi(rolls[i].back()) +
                    stoi( rolls[i].at( rolls[i].size() - 2 ) ) );
            }
        }

        printBoard(numPlayers, names, rolls, score);
    }
}

void printBoard(int numPlayers, vector<string> names,
    vector< vector<string> > rolls, vector< vector<int> > score)
{
    cout << endl;

    for (int i = 0; i < 80; i++)
    {
        cout << "=";
    }

    cout << endl;

    cout << "Players:\tRound:\t";

    for (int i = 0; i < 11; i++)
    {
        if ( i != 10 )
        {
            cout << i + 1 << "    ";
        }
        else
        {
            cout << "Total:" << endl;
        }
    }

    for (int i = 0; i < numPlayers; i++)
    {
        cout << names[i] << "\t\t\t";

        for (int j = 0; j < rolls[i].size(); j++)
        {
            cout << rolls[i].at(j) << "  ";
        }

        cout << "\n\t\tScore:\t";

        for (int j = 0; j < score[i].size(); j++)
        {
            cout << score[i].at(j) << "  ";
        }

        cout << endl;
    }

    for (int i = 0; i < 80; i++)
    {
        cout << "=";
    }
}
