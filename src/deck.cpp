
/* Game UNO - wikipedia
deck consists of 108 cards
	25 of each color ( red, green, blue, and yellow)
	each color having two of each rank except zero
	zero to nine
	"Skip"
	"Draw Two"
	"Reverse "
	"Wild "
	"Wild Draw Four"

*/


/*
zero - 4 cards (RGBY)
one till nine - 4 cards (RGBY) & 4 cards (RGBY)
ten "Skip" -  4 cards (RGBY) & 4 cards (RGBY)
eleven "Draw Two" -  4 cards (RGBY) & 4 cards (RGBY)
twelve "Reverse " -  4 cards (RGBY) & 4 cards (RGBY)
thirteen "Wild " -  4 cards (RGBY)
fourteen "Wild Draw Four" -  4 cards (RGBY)


01234 =  wild + RGBY
zero = wild
one = red
two = green
three = blue
four = yellow

*/

#define DECK_SIZE 108
#include "deck.h"
#include "card.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

deck::deck(){
	ptr_deck = new card[108];
	size = 0;


}

deck::~deck(){
    clear();
}

deck::deck(const deck & other){
	copy(other);
}

const deck & deck::operator= (const deck & other){
	if (this != &other){
		clear();
		copy(other);
	}
	return *this;
}

void deck::shuffle_deck(){
	// create a temp deck
	card * temp_deck = new card[size];

	int temp_size =size;
	int position;

	for (int i =0; i<size; i++){
		temp_deck[i] = ptr_deck[i];
	}

	for (int i = 0 ; i <size; i++ ){
		srand(time(NULL)); // constant randomise to find a random position in the deck
		position = rand() % temp_size;
		//assign random element to deck[i]
		ptr_deck[i] = temp_deck[position];
		temp_size--;

		for (int temp_position = position ; temp_position < temp_size ; temp_position++){
			temp_deck[temp_position] = temp_deck[temp_position+1];//"removing" the position of the card by shifiting it -1 units
		}
	}

	delete [] temp_deck; // remove it from memory
}

void deck::create_deck(){
	int num = 0 ;


	// card rank 0
	for (int col = 1 ; col <= 4  ; col++){
		ptr_deck[size].number = num;
		ptr_deck[size].color = static_cast<COLOR>(col);
		size++;
	}

	// card rank 1 till 9 , "draw-two", "skip", "reverse"
	for (num = 1; num <= 12; num++){
		for (int x = 0 ; x < 2 ; x++ )
		{
			for (int col = 1 ; col <= 4  ; col++)
			{
				ptr_deck[size].number = num;
				ptr_deck[size].color = static_cast<COLOR>(col);
				size++;
			}
		}

	}

	// card "wild", "wild-draw-four"
	for (num = 13 ; num <= 14 ; num++){
		for (int x = 0 ; x < 4 ; x++){
			ptr_deck[size].number = num;
			ptr_deck[size].color = wild;
			size++;
		}
	}


}

void deck::quick_shuffle_deck(){
	int position;
	int temp_size = size - 1;
	card temp_card;
	while(temp_size > 0 ){

		srand(time(NULL));
		position = rand() % temp_size;
		// swap elements
		temp_card = ptr_deck[temp_size];
		ptr_deck[temp_size] = ptr_deck[position];
		ptr_deck[position] = temp_card;
		temp_size--;
	}

}

void deck::print_deck(){
	for (int i= 0 ; i< size ; i++){
		cout << i << ": " << ptr_deck[i] << endl;
	}
}

void deck::copy(const deck & other){
	size = other.size;
	ptr_deck = new card[size];
	for (int i =0 ; i < size ; i++){
		ptr_deck[i] = other.ptr_deck[i];
	}
}

void deck::clear(){
	delete []ptr_deck;
	ptr_deck = NULL;
	size = 0;
}

card deck::draw(){
	if (size <= 0){
		return card();
	}

	card temp_card = ptr_deck[size-1];
	size--;

	return temp_card;
}


int deck::add_card_to_deck(card temp_card){
	// O(1) insert
	if(size < DECK_SIZE){
		ptr_deck[size] = temp_card;
		size++;
		return 0;
	}
	else
		return -1;
}

int deck::get_size(){
	return size;
}
