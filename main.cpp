#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <random>
#include <string>

using std::cout, std::cin, std::string, std::vector, std::to_string, std::stoi;

/*
* written by chapel1337
* started on 11/24/2022
* finished on 11/25/2022
* 
* not much to say about this, it's just your traditional war game
* probably could've finished this yesterday, but i had family over that left today
* i'm not surprised this reached 1,000 lines; the war function is, as the comment says, literal hell
* i couldn't get a better icon; i know it looks bad
*/

vector<vector<int>> cards{ {}, {}, }; // player1 = vector0, player2 = vector1
int cardAmount{ 20 };

vector<vector<char>> presetMap
{
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  },
};
vector<vector<char>> map{ presetMap };

void refresh();

bool currentPlayer{ true }; // player1 = true, player2 = false
bool starting{ true };

int battleWinner{};
bool viewRules{ true };

void start();
void menu(const int position);

void clear()
{
	system("cls");
}

int getRandom(const int minimum, const int maximum)
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution random{ minimum, maximum };

	return random(mt);
}

void title(const string& title)
{
	SetConsoleTitleA(("war card game - " + title).c_str());
}

void title()
{
	SetConsoleTitleA("war card game");
}

void title(const string& title, const int i)
{
	SetConsoleTitleA(("war card game - " + title + to_string(i)).c_str());
}

void setTextColor(const int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetTextColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void playerWin(const bool player, const int position) // player1 = true, player2 = false
{
	clear();

	if (player)
	{
		title("player 1 wins!");

		cout << "  player 1 wins!\n\n";
	}
	else
	{
		title("player 2 wins!");

		cout << "  player 2 wins!\n\n";
	}

	cout << "  would you like to play again?\n\n";

	if (position == 1)
	{
		cout << "  > yes <\n";
	}
	else
	{
		cout << "  yes\n";
	}

	if (position == 2)
	{
		cout << "  > no <\n";
	}
	else
	{
		cout << "  no\n";
	}

	int keyInput{ _getch() };

	if (keyInput == 'W' && position != 1 || keyInput == 'w' && position != 1)
	{
		playerWin(player, position - 1);
	}
	else if (keyInput == 'S' && position != 2 || keyInput == 's' && position != 2)
	{
		playerWin(player, position + 1);
	}
	else if (keyInput == 13)
	{
		switch (position)
		{
		case 1:
			start();
			break;

		case 2:
			menu(1);
			break;
		}
	}
	else
	{
		playerWin(player, position);
	}
}

void displayStats()
{
	cout << "  total card amount: " << cardAmount << "\n\n";

	/*
	cout << "  player 1 card amount: " << cards[0].size() << '\n';
	cout << "  player 1 cards: ";
	for (unsigned int i{}; i < cards[0].size(); ++i)
	{
		cout << cards[0][i] << ' ';
	}
	cout << "\n\n";

	cout << "  player 2 card amount: " << cards[1].size() << "\n\n";
	cout << "  player 2 cards: ";
	for (unsigned int i{}; i < cards[1].size(); ++i)
	{
		cout << cards[1][i] << ' ';
	}
	cout << "\n\n";
	*/

	cout << "  current player: " << currentPlayer << "\n\n";

	if (battleWinner == 1)
	{
		cout << "  player 1 wins battle\n\n";
	}
	else if (battleWinner == 2)
	{
		cout << "  player 2 wins battle\n\n";
	}
}

void refresh()
{
	clear();
	displayStats();

	for (int i{}; i < 5; ++i)
	{
		cout << '\n';
	}

	for (unsigned int i{}; i < map.size(); ++i)
	{
		for (int i{}; i < 42; ++i)
		{
			cout << ' ';
		}

		for (unsigned int o{}; o < map[i].size(); ++o)
		{
			cout << map[i][o];
		}

		cout << '\n';
	}
}

void help(const int position)
{
	title("help");
	clear();

	cout << "  if you are confused or unfamiliar with the rules of this game, select \"yes\"\n";
	cout << "  the variant of this game is automatic war\n\n";

	cout << "  press h to return to the help menu\n";
	cout << "  press s to the current player's shuffle cards\n\n";

	if (viewRules)
	{
		if (position == 1)
		{
			cout << "  > yes <\n";
		}
		else
		{
			cout << "  yes\n";
		}

		if (position == 2)
		{
			cout << "  > no <\n";
		}
		else
		{
			cout << "  no\n";
		}

		int keyInput{ _getch() };

		if (keyInput == 'W' && position != 1 || keyInput == 'w' && position != 1)
		{
			help(position - 1);
		}
		else if (keyInput == 'S' && position != 2 || keyInput == 's' && position != 2)
		{
			help(position + 1);
		}
		else if (keyInput == 13)
		{
			viewRules = false;
			
			switch (position)
			{
			case 1:
				system("start https://en.wikipedia.org/wiki/War_(card_game)");
				break;

			case 2:
				return;
				break;
			}
		}
		else
		{
			help(position);
		}
	}
	else
	{
		cin.get();
	}
}

void generateCards()
{
	cards[0].push_back(5);
	cards[1].push_back(5);

	if (cardAmount % 2 == 0)
	{
		cards[getRandom(0, 1)].push_back(getRandom(1, 13));
	}

	for (unsigned int i{}; i < floor(cardAmount / 2); ++i)
	{
		cards[0].push_back(getRandom(1, 13));
	}

	for (unsigned int i{}; i < floor(cardAmount / 2); ++i)
	{
		cards[1].push_back(getRandom(1, 13));
	}
}

void shuffleCards()
{
	int currentCard{};

	if (currentPlayer)
	{
		for (unsigned int i{}; i < cards[0].size(); ++i)
		{
			currentCard = cards[0][i]; // spent the last half an hour trying to figure out why this wouldn't work, turns out i was settings cards[1][i] to currentCard instead of vice versa :coffin:

			cards[0].erase(cards[0].begin() + i);
			cards[0].insert(cards[0].begin() + getRandom(0, cards[0].size()), currentCard); // scary
		}
	}
	else
	{
		for (unsigned int i{}; i < cards[1].size(); ++i)
		{
			currentCard = cards[1][i];

			cards[1].erase(cards[1].begin() + i);
			cards[1].insert(cards[1].begin() + getRandom(0, cards[1].size()), currentCard);
		}
	}
}

// hell
void war(const int cardsPosition)
{
	title("war!");

	refresh();
	Sleep(1000);

	// top
	map[0][8] = '#';
	map[0][9] = '#';
	map[0][10] = '#';
	map[0][11] = '#';
	map[0][12] = '#';
	map[0][13] = '#';
	map[0][14] = '#';

	map[4][8] = '#';
	map[4][9] = '#';
	map[4][10] = '#';
	map[4][11] = '#';
	map[4][12] = '#';
	map[4][13] = '#';
	map[4][14] = '#';

	map[0][8] = '#';
	map[1][8] = '#';
	map[2][8] = '#';
	map[3][8] = '#';

	map[0][14] = '#';
	map[1][14] = '#';
	map[2][14] = '#';
	map[3][14] = '#';

	// bottom
	map[9][8] = '#';
	map[9][9] = '#';
	map[9][10] = '#';
	map[9][11] = '#';
	map[9][12] = '#';
	map[9][13] = '#';
	map[9][14] = '#';

	map[13][8] = '#';
	map[13][9] = '#';
	map[13][10] = '#';
	map[13][11] = '#';
	map[13][12] = '#';
	map[13][13] = '#';
	map[13][14] = '#';

	map[9][8] = '#';
	map[10][8] = '#';
	map[11][8] = '#';
	map[12][8] = '#';

	map[9][14] = '#';
	map[10][14] = '#';
	map[11][14] = '#';
	map[12][14] = '#';

	switch (cards[0][0])
	{
	case 10:
		map[2][11] = '1';
		map[2][12] = '0';
		break;

	case 11:
		map[2][11] = 'J';
		break;

	case 12:
		map[2][11] = 'Q';
		break;

	case 13:
		map[2][11] = 'K';
		break;

	default:
		map[2][11] = '0' + cards[0][0];
		break;
	}

	switch (cards[1][0])
	{
	case 10:
		map[11][11] = '1';
		map[11][12] = '0';
		break;

	case 11:
		map[11][11] = 'J';
		break;

	case 12:
		map[11][11] = 'Q';
		break;

	case 13:
		map[11][11] = 'K';
		break;

	default:
		map[11][11] = '0' + cards[1][0];
		break;
	}

	refresh();
	Sleep(1000);
	refresh();

	// top
	map[0][21] = '#';
	map[0][22] = '#';
	map[0][23] = '#';
	map[0][24] = '#';
	map[0][25] = '#';
	map[0][26] = '#';
	map[0][27] = '#';

	map[4][21] = '#';
	map[4][22] = '#';
	map[4][23] = '#';
	map[4][24] = '#';
	map[4][25] = '#';
	map[4][26] = '#';
	map[4][27] = '#';

	map[0][27] = '#';
	map[1][27] = '#';
	map[2][27] = '#';
	map[3][27] = '#';

	map[0][21] = '#';
	map[1][21] = '#';
	map[2][21] = '#';
	map[3][21] = '#';

	// bottom
	map[9][21] = '#';
	map[9][22] = '#';
	map[9][23] = '#';
	map[9][24] = '#';
	map[9][25] = '#';
	map[9][26] = '#';
	map[9][27] = '#';

	map[13][21] = '#';
	map[13][22] = '#';
	map[13][23] = '#';
	map[13][24] = '#';
	map[13][25] = '#';
	map[13][26] = '#';
	map[13][27] = '#';

	map[9][27] = '#';
	map[10][27] = '#';
	map[11][27] = '#';
	map[12][27] = '#';

	map[10][21] = '#';
	map[11][21] = '#';
	map[12][21] = '#';
	map[13][21] = '#';

	refresh();
	Sleep(1000);

	// top
	map[0][34] = '#';
	map[0][35] = '#';
	map[0][36] = '#';
	map[0][37] = '#';
	map[0][38] = '#';
	map[0][39] = '#';
	map[0][40] = '#';

	map[4][34] = '#';
	map[4][35] = '#';
	map[4][36] = '#';
	map[4][37] = '#';
	map[4][38] = '#';
	map[4][39] = '#';
	map[4][40] = '#';

	map[0][40] = '#';
	map[1][40] = '#';
	map[2][40] = '#';
	map[3][40] = '#';

	map[0][34] = '#';
	map[1][34] = '#';
	map[2][34] = '#';
	map[3][34] = '#';

	// bottom
	map[9][34] = '#';
	map[9][35] = '#';
	map[9][36] = '#';
	map[9][37] = '#';
	map[9][38] = '#';
	map[9][39] = '#';
	map[9][40] = '#';

	map[13][34] = '#';
	map[13][35] = '#';
	map[13][36] = '#';
	map[13][37] = '#';
	map[13][38] = '#';
	map[13][39] = '#';
	map[13][40] = '#';

	map[9][40] = '#';
	map[10][40] = '#';
	map[11][40] = '#';
	map[12][40] = '#';

	map[10][34] = '#';
	map[11][34] = '#';
	map[12][34] = '#';
	map[13][34] = '#';

	switch (cards[0][2])
	{
	case 10:
		map[2][37] = '1';
		map[2][38] = '0';
		break;

	case 11:
		map[2][37] = 'J';
		break;

	case 12:
		map[2][37] = 'Q';
		break;

	case 13:
		map[2][37] = 'K';
		break;

	default:
		map[2][37] = '0' + cards[0][2];
		break;
	}

	switch (cards[1][2])
	{
	case 10:
		map[11][37] = '1';
		map[11][38] = '0';
		break;

	case 11:
		map[11][37] = 'J';
		break;

	case 12:
		map[11][37] = 'Q';
		break;

	case 13:
		map[11][37] = 'K';
		break;

	default:
		map[11][37] = '0' + cards[1][2];
		break;
	}

	refresh();
	Sleep(1000);

	if (cards[0][cardsPosition] > cards[1][cardsPosition])
	{
		for (int i{}; i < cardsPosition; ++i)
		{
			cards[0].push_back(cards[1][i]);
			cards[1].erase(cards[1].begin() + i);
		}

		battleWinner = 1;
	}
	else if (cards[0][cardsPosition] < cards[1][cardsPosition])
	{
		for (int i{}; i < cardsPosition; ++i)
		{
			cards[1].push_back(cards[0][i]);
			cards[0].erase(cards[0].begin() + i);
		}

		battleWinner = 2;
	}
	else if (cards[0][cardsPosition] == cards[0][cardsPosition])
	{
		map = presetMap;

		war(cardsPosition + 2);
	}

	map = presetMap;
	title();
}

void placeCard()
{
	if (cards[0].size() == 0)
	{
		playerWin(false, 1);
	}
	else if (cards[1].size() == 0)
	{
		playerWin(true, 1);
	}

	if (currentPlayer)
	{	
		currentPlayer = false;

		map[0][8] = '#';
		map[0][9] = '#';
		map[0][10] = '#';
		map[0][11] = '#';
		map[0][12] = '#';
		map[0][13] = '#';
		map[0][14] = '#';

		map[4][8] = '#';
		map[4][9] = '#';
		map[4][10] = '#';
		map[4][11] = '#';
		map[4][12] = '#';
		map[4][13] = '#';
		map[4][14] = '#';

		map[0][8] = '#';
		map[1][8] = '#';
		map[2][8] = '#';
		map[3][8] = '#';

		map[0][14] = '#';
		map[1][14] = '#';
		map[2][14] = '#';
		map[3][14] = '#';

		refresh();
		Sleep(1000);
	}
	else 
	{
		if (starting)
		{
			starting = false;
		}

		currentPlayer = true;

		map[9][8] = '#';
		map[9][9] = '#';
		map[9][10] = '#';
		map[9][11] = '#';
		map[9][12] = '#';
		map[9][13] = '#';
		map[9][14] = '#';

		map[13][8] = '#';
		map[13][9] = '#';
		map[13][10] = '#';
		map[13][11] = '#';
		map[13][12] = '#';
		map[13][13] = '#';
		map[13][14] = '#';

		map[9][8] = '#';
		map[10][8] = '#';
		map[11][8] = '#';
		map[12][8] = '#';

		map[9][14] = '#';
		map[10][14] = '#';
		map[11][14] = '#';
		map[12][14] = '#';

		refresh();
		Sleep(1250);

		switch (cards[0][0])
		{
		case 10:
			map[2][11] = '1';
			map[2][12] = '0';
			break;

		case 11:
			map[2][11] = 'J';
			break;

		case 12:
			map[2][11] = 'Q';
			break;

		case 13:
			map[2][11] = 'K';
			break;

		default:
			map[2][11] = '0' + cards[0][0];
			break;
		}

		switch (cards[1][0])
		{
		case 10:
			map[11][11] = '1';
			map[11][12] = '0';
			break;

		case 11:
			map[11][11] = 'J';
			break;

		case 12:
			map[11][11] = 'Q';
			break;

		case 13:
			map[11][11] = 'K';
			break;

		default:
			map[11][11] = '0' + cards[1][0];
			break;
		}

		refresh();
		Sleep(1000);

		if (cards[0][0] > cards[1][0])
		{
			cards[0].push_back(cards[1][0]);
			cards[1].erase(cards[1].begin() + 0);

			cards[0].push_back(cards[1][0]);
			cards[0].erase(cards[0].begin() + 0);

			battleWinner = 1;
		}
		else if (cards[0][0] < cards[1][0])
		{
			cards[1].push_back(cards[0][0]);
			cards[0].erase(cards[0].begin() + 0);

			cards[1].push_back(cards[1][0]);
			cards[1].erase(cards[1].begin() + 0);

			battleWinner = 2;
		}
		else if (cards[0][0] == cards[1][0])
		{
			map = presetMap;

			if (cards[0].size() >= 3 && cards[1].size() >= 3)
			{
				war(2);
			}
			else
			{
				int random{ getRandom(0, 1) };

				if (!random)
				{
					cards[0].push_back(cards[1][0]);
					cards[1].erase(cards[1].begin() + 0);

					cards[0].push_back(cards[1][0]);
					cards[0].erase(cards[0].begin() + 0);

					battleWinner = 1;
				}
				else
				{
					cards[1].push_back(cards[0][0]);
					cards[0].erase(cards[0].begin() + 0);

					cards[1].push_back(cards[1][0]);
					cards[1].erase(cards[1].begin() + 0);

					battleWinner = 2;
				}
			}
		}

		map = presetMap;
	}
}

string cardAmountString{ to_string(cardAmount) };
void setCardAmountConfirmation(const int position)
{
	clear();

	cout << "  card amount: " << cardAmountString << "\n\n";

	cout << "  are you satisfied with this amount?\n\n";

	if (position == 1)
	{
		cout << "  > yes <\n";
	}
	else
	{
		cout << "  yes\n";
	}

	if (position == 2)
	{
		cout << "  > no <\n";
	}
	else
	{
		cout << "  no\n";
	}

	int keyInput{ _getch() };

	if (keyInput == 'W' && position != 1 || keyInput == 'w' && position != 1)
	{
		setCardAmountConfirmation(position - 1);
	}
	else if (keyInput == 'S' && position != 2 || keyInput == 's' && position != 2)
	{
		setCardAmountConfirmation(position + 1);
	}
	else if (keyInput == 13)
	{
		switch (position)
		{
		case 1:
			clear();

			cardAmount = stoi(cardAmountString);

			cout << "  successfully set card amount to " << cardAmount << "\n\n";
			cout << " > okay <\n";

			_getch();
			menu(1);
			break;

		case 2:
			menu(1);
			break;
		}
	}
	else
	{
		setCardAmountConfirmation(position);
	}
}

void setCardAmount()
{
	clear();
	title("set card amount");

	cout << "  set card amount\n\n";

	cout << "  input an amount: " << cardAmountString;

	int keyInput{ _getch() };

	if (keyInput == '1' || keyInput == '2' || keyInput == '3' || keyInput == '4' || keyInput == '5' || keyInput == '6' || keyInput == '7' || keyInput == '8' || keyInput == '9' || keyInput == '0')
	{
		cardAmountString.push_back(keyInput);
	}
	else if (keyInput == 8)
	{
		cardAmountString.pop_back();
	}
	else if (keyInput == 13)
	{
		setCardAmountConfirmation(1);
	}

	setCardAmount();
}

void quit()
{
	clear();

	for (int i{ 3 }; i > 0; --i)
	{
		title("exiting in ", i);

		cout << "  okay, exiting in " << i;

		Sleep(1000);
		clear();
	}

	exit(1);
}

void menu(const int position)
{
	clear();
	title("menu");

	cout << "  war card game\n\n";

	if (position == 1)
	{
		cout << "  > start <\n";
	}
	else
	{
		cout << "  start\n";
	}

	if (position == 2)
	{
		cout << "  > set card amount <\n";
	}
	else
	{
		cout << "  set card amount\n";
	}

	if (position == 3)
	{
		cout << "  > quit <\n";
	}
	else
	{
		cout << "  quit\n";
	}

	int keyInput{ _getch() };

	if (keyInput == 'W' && position != 1 || keyInput == 'w' && position != 1)
	{
		menu(position - 1);
	}
	else if (keyInput == 'S' && position != 3 || keyInput == 's' && position != 3)
	{
		menu(position + 1);
	}
	else if (keyInput == 13)
	{
		switch (position)
		{
		case 1:
			start();
			break;

		case 2:
			setCardAmount();
			break;
			
		case 3:
			quit();
			break;
		}
	}
	else
	{
		menu(position);
	}
}

void getInput()
{
	int keyInput{ _getch() };

	switch (keyInput)
	{
	case ' ':
	case 13:
		placeCard();
		break;

	case 'H':
	case 'h':
		help(1);
		break;

	case 'S':
	case 's':
		shuffleCards();
		break;
	}

	refresh();
	getInput();
}

void start()
{
	title();

	generateCards();
	refresh();
	getInput();
}

int main()
{
	title("credits");

	setTextColor(6);
	cout << "written by chapel1337\n\n";

	cout << "started on 11/24/2022\n";
	cout << "finished on 11/25/2022\n\n";
	resetTextColor();

	cout << "press h for help\n\n";

	Sleep(2000);
	menu(1);
}