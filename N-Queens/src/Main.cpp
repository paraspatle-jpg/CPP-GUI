#include "Main.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;	  // nanoseconds, system_clock, seconds

vector<vector<int>> Queens = {
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 }
};

bool isSafe(vector<vector<int>> board, int row, int col)
{
	int i, j;
	int N = board.size();
	for (i = 0; i < col; i++)
		if (board[row][i])
			return false;
	for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
		if (board[i][j])
			return false;
	for (i = row, j = col; j >= 0 && i < N; i++, j--)
		if (board[i][j])
			return false;
	return true;
}

bool solveNQUtil(vector<vector<int>>& board, int col)
{
	int N = board.size();
	if (col == N)
	{
		vector<int> v;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (board[i][j] == 1)
					v.push_back(j + 1);
			}
		}
		sleep_for(nanoseconds(10));
		sleep_until(system_clock::now() + seconds(1));
		return true;
	}

	bool res = false;
	for (int i = 0; i < N; i++)
	{

		if (isSafe(board, i, col))
		{
			board[i][col] = 1;
			res = solveNQUtil(board, col + 1) || res;
			board[i][col] = 0;
		}
	}
	return res;
}

void nQueen()
{
	solveNQUtil(Queens, 0);
}
int main()
{
	sf::Thread thread(&nQueen);
	thread.launch();
	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 800), "My window");

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}


		window.clear(sf::Color::Black);

		sf::Texture B_Queen;
		B_Queen.loadFromFile("content/White.png");

		char Chess_Board[8][8] = {
			{ '0', '1', '0', '1', '0', '1', '0', '1' },
			{ '1', '0', '1', '0', '1', '0', '1', '0' },
			{ '0', '1', '0', '1', '0', '1', '0', '1' },
			{ '1', '0', '1', '0', '1', '0', '1', '0' },
			{ '0', '1', '0', '1', '0', '1', '0', '1' },
			{ '1', '0', '1', '0', '1', '0', '1', '0' },
			{ '0', '1', '0', '1', '0', '1', '0', '1' },
			{ '1', '0', '1', '0', '1', '0', '1', '0' }
		};

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				sf::RectangleShape square(sf::Vector2f(100.f, 100.f));
				if (Chess_Board[i][j] == '0')
				{

					if (Queens[i][j] == 1)
					{
						square.setTexture(&B_Queen);
					}
					else
					{
						square.setFillColor(sf::Color(0, 0, 0));
					}
				}
				else if (Chess_Board[i][j] == '1')
				{
					square.setFillColor(sf::Color(255, 255, 255));
					if (Queens[i][j] == 1)
					{
						square.setTexture(&B_Queen);
					}
				}
				square.setPosition(i * 100, j * 100);
				window.draw(square);
			}
		}
		// end the current frame
		window.display();
	}

	return 0;
}