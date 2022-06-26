#include "card.h"
#include "deck.h"
#include "player.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits>
#include <time.h>
#include <locale>
#include <vector>

using namespace std;

#define PRINT_ALL_PLAYERS 0
#define TEMP_DECK 1
#define TURN 2
#define TEST -1

//declaring class template
template<class T>
class Determine_Score{
private:
    T Score = 0;

public:
    Determine_Score(T Accumulator){
        Score = Score + Accumulator;
    }

    int getScore(){
        return Score;
    }
};

//declaring of struct to keep count of amount of players
struct Amt_of_players{

	int amount_players;
	bool correct_amt_players = false;
}play;

//declared template to display any type of file
template<typename Instructions>
    void Read(Instructions filename){
        string line;

        ifstream myfile (filename);

        if (myfile.is_open()){
            while(getline(myfile,line)){

                cout<<line<<'\n';
            }
            cout<<'\n'<<'\n'<<'\n'<<endl;
            myfile.close();
        }
        else{
            cout<<"File dont exist"<<endl;
        }
    }


void confirm_turn (int x)
{

	int temp = -4;
	while( temp != x + 1){
        cout << "Confirm Player " << x + 1<< " by typing " << "'" << x + 1<< "'" << " and pressing enter" << ": " ;
		cin >> temp;
	}
}

COLOR FromString (const string & str)
{
	if ( str == "red")
		return red;
	else if (str == "green")
		return green;
	else if (str == "blue")
		return blue;
	else if (str == "yellow")
		return yellow;
	else
		return wild;
}


int main()
{
	// display an introduction to the game in the beginning
	Read("Instructions.txt");

	// ask user for amount of players
	while (!play.correct_amt_players)
	{
		cout << "Please enter amount of players: ";
		cin >> play.amount_players;
		if (play.amount_players >= 2 && play.amount_players <= 5)
		{
			cout << play.amount_players << " players entering game .... " << endl;
			cout<<endl;
			play.correct_amt_players = true;
			break;
		}
		else
		{
			cout << "invalid amount of players" << endl;
		}
	}

	cout<<"Please enter the type of difficulty"<<endl;
	cout<<"Easy/Medium/Hard"<<endl;

	string difficulty = "";

	cin>>difficulty;

	//selection of difficulty
	bool selected = false;
	int amt_cards = 0;
	while (!false){
        if (difficulty == "Easy" || difficulty == "easy"){
            selected = true;
            amt_cards = 7;
            break;
        }
        if (difficulty == "Medium" ||difficulty == "medium"){
            selected = true;
            amt_cards = 10;
             break;
        }
        if (difficulty == "Hard" ||difficulty == "hard"){
            selected = true;
            amt_cards = 15;
             break;
        }
        else{
            cout<<"Invalid selection"<<endl;
            cout<<"Please enter the type of difficulty"<<endl;
            cout<<"Easy/Medium/Hard"<<endl;
            cin>>difficulty;
        }
	}


	// creating deck
	deck main_deck;
	main_deck.create_deck();
	main_deck.quick_shuffle_deck();

	// creating player array
	player * play_array;
	play_array = new player[play.amount_players];
	// 7 cards are given to each player
	for (int i = 0 ; i < play.amount_players ; i ++){
		for (int j = 0 ; j < amt_cards ; j++){
			card temp_card;
			temp_card = main_deck.draw();
			play_array[i].hand_add_to_player(temp_card);
		}
	}
	deck temp_deck;

	// drawing the first card out of the deck
	card played_card;
	card temp_card;
	bool flag_Wcard = false; // making sure the correct card is removed from the deck
	while (flag_Wcard == false){
		temp_card = main_deck.draw();
		// determine whether the first card is a wild card *NOT ALLOWED*
		if (temp_card.color != wild){
			flag_Wcard = true;
			played_card = temp_card;
		}
		else{
			temp_deck.add_card_to_deck(temp_card);
		}
	}

	for (int i =0; i < play.amount_players ; i++){
		cout << "player: " << i + 1 << endl;
		play_array[i].print();
		cout<<endl;
	}
	cout<<endl;

	// since in the rules the person on the right of the dealer plays first
	// however the cpu is the dealer so we randomise which player plays first
	srand(time(NULL));
	int player_turn = rand() % play.amount_players;
	cout << "PLAYER " << player_turn + 1 << " is randomly selected to play first" << endl;
	cout<<endl;
	confirm_turn(player_turn);

	bool force_draw_bool = false;
	int next_turn = 1;
	bool win = false;
	// keep playing until a player wins

    // a vector is used to keep count of all the cards that have been played

    vector<int> num;
	while (!win){
		#if TEST == TEMP_DECK
		temp_deck.print_deck();
		#endif

		player * curr_player = &play_array[player_turn%play.amount_players];


		// checked for forced draw cards
		cout << "PLAYER " << player_turn%play.amount_players << endl;

		if (force_draw_bool){
            // checked for Draw-2
            if (played_card.number == 10){
                cout << "Forced Draw-2" << endl;
                card draw_2;
                for (int i = 0 ; i < 2; i ++){
                    draw_2 = main_deck.draw();
                    curr_player->hand_add_to_player(draw_2);
                }
            }

            // check for Draw-4
            if (played_card.number == 14){
                cout << "Forced Draw-4" << endl;
                card draw_4;
                for (int i = 0 ; i < 4; i ++){
                    draw_4 = main_deck.draw();
                    curr_player->hand_add_to_player(draw_4);
                }

            }
			force_draw_bool = false;
		}


		// print out the cards remaining for each player
		cout << "Cards remaining for each player: " << endl;
		for (int i= 0 ; i < play.amount_players; i ++ ){
			cout << "PLAYER " << i + 1 << ": " << play_array[i].get_size() << "   " ;
		}
		cout << endl;
		cout<<endl;
		cout << "Played Card: " << played_card << endl;
		cout<<endl;

		// print out cards in player's hand
		cout << "PLAYER " << player_turn%play.amount_players + 1 << endl;

		curr_player->print();
		cout<<endl;

		bool check = false;
		int index;
		int size = curr_player->get_size();
		// ask for which card to play into middle
		while (!check){
			cout << "which card do you want to play? " << endl;
			cout << "If you want to draw a card please enter '-1' " << endl;
			cout << "Type the index of the card and press enter: ";
			cin >> index;
			cout<<endl;
			//check if index is to draw a card
			if (index == -1){
				card draw_temp;
				draw_temp = main_deck.draw();
				cout << "DRAWN CARD: " << draw_temp << endl;
				cout<<endl;
				if (draw_temp == played_card && draw_temp.color != wild){
					bool play_draw_flag = false;
					while (!play_draw_flag){
                        string temp_play;

                        cout << "Do you want to play the drawn card [y/n] : " ;
                        cin >> temp_play;
                        if (temp_play == "y"){
                            played_card = draw_temp;
                            temp_deck.add_card_to_deck(draw_temp);
                            num.push_back(draw_temp.number);
                            if (played_card.number >= 10 && played_card.number <= 14){
                                force_draw_bool = true;
                            }
                            play_draw_flag = true;
                        }
                        if (temp_play == "n"){
                            curr_player->hand_add_to_player(draw_temp);
                            play_draw_flag = true;
                        }
					}

				}
				else{
					curr_player->hand_add_to_player(draw_temp);
				}
				check = true;

			}
			else{
                //check if index is valid
                if (index >= 0 && index < size){
                    // check if card is compatilbe with played card
                    card temp = curr_player->peek(index);
                    if (temp == played_card){
                        //remove from player's hand
                        curr_player->hand_remove_from_player(index);
                        // add to the discarded pile
                        temp_deck.add_card_to_deck(temp);
                        num.push_back(temp.number);
                        // change the played card
                        played_card = temp;
                        // check if card is a wild card
                        if(played_card.color == wild){
                            bool check_color = false;
                            COLOR temp_color;
                            string str_color;
                            while (!check_color){
                                // ask for new color
                                cout << "Please choose a color (red , green, blue, yellow) :";
                                cin >> str_color;
                                // change string to enum type COLOR
                                temp_color = FromString(str_color);
                                // check if valid color
                                if (temp_color != wild){
                                    played_card.color = temp_color;
                                    check_color = true;
                                }
                                else{
                                    cout << "invalid color" << endl;
                                }

                            }
                        }
                        if (played_card.number >= 10 && played_card.number <= 14){
                            force_draw_bool = true;
                        }
                        check = true;
                    }
                    else{
                        cout << "card cannot be played " << endl;
                    }
                }
                else{
                    cout<<"invalid index " << endl;
                }
            }

		}

        // if a player is on the last card and and its a wild card
        // then automatically a card is handed to them

        if (curr_player->get_size() == 1){
            if (curr_player->peek().color == wild){
                temp_card = main_deck.draw();
                while (temp_card.color == wild){
                    temp_card = main_deck.draw();
                }
                curr_player->hand_add_to_player(temp_card);
            }
        }

		// check if there is a winner, and break while loop
		if ( curr_player->get_size() == 0 ){
			win = true;
			cout << "PLAYER " << player_turn%play.amount_players + 1<< " has won the game." << endl;
            string name;

            cout<<"PLAYER " << player_turn%play.amount_players + 1<< " what is your name?" << endl;
            cin>> name;

            //Writing to scoreboard of the winner
			ofstream myFile("Scoreboard.txt");

			myFile << "PLAYER " << player_turn%play.amount_players + 1<< "-"<< name <<endl;
			myFile.close();

			//Read score board
			Read("Scoreboard.txt");

			break;
		}

		// check for action cards that influence the turn here
		// skip case
		if (played_card.number == 11 && force_draw_bool == true ){
			if (next_turn == 1)
				player_turn += 2;
			else
				player_turn -= 2;
		}
		// reverse case
		else if (played_card.number == 12 && force_draw_bool == true){
			// if only two players, behaves like a skip card
			if (play.amount_players== 2){
				player_turn += 2;
			}
			else{
				// changes the rotation of game
				if (next_turn == 1){
					next_turn = -1;
					player_turn--;
				}
				else{
					next_turn = 1;
					player_turn++;
				}

			}
		}
		// for other cards
		else{
			// depending on going Clockwise or CounterClockwise
			if (next_turn == 1)
				player_turn++;
			else
				player_turn--;
		}

		// print out the cards remaining for each player
		cout << "Cards remaining for each player: " << endl;
		for (int i= 0 ; i < play.amount_players; i ++ ){
			cout << "PLAYER " << i + 1 << ": " << play_array[i].get_size() << "   " ;
		}
		cout << endl;

		// print out the temporary card
		cout << "Played Card: " << played_card << endl;
		confirm_turn(player_turn%play.amount_players);

	}
	return 0;
}



