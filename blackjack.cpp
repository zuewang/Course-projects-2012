/*
 * blackjack.cpp
 *
 *  Created on: 2015Äê9ÔÂ16ÈÕ
 *      Author: ThinkPad
 */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

// the number of cards held by each hands
int num_card_dealer=0, num_card_player=0,num_card_split1=0,num_card_split2=0,num_card_split3=0;
// the total points of each hands
int sum_dealer=0, sum_player=0, sum_split1=0, sum_split2=0, sum_split3=0;
// the current number (the index drew from the array containing the total 52 cards)
int current_num = 4;
// if it's the dealer's turn to draw, draw_dealer=1
int draw_dealer = 1;
// if the player get 21 points for the first 2 cards, win_begin = 1
int win_begin = 0;
// if the user wants to draw, if_draw = 'Y' or 'y'
char if_draw;
// add_num is a temporary variable to add the point of the card drew to the total points
int add_num = 0; // converted from temp
// the first two cards of each hand which the dealer can see
int first2_player=0, first2_1=0, first2_2=0, first2_3=0;
//create an array of all cards which will be operated afterwards
char all_cards[52][3]={"4H","5H","6H","7H","8H","9H","TH","JH","QH","KH",
		"1H","TC","1D","2H","3H","1C","1S","3D","3C","3S",
		"2D","4D","5D","6D","7D","8D","9D","TD","JD","QD","KD",
		"2C","4C","5C","6C","7C","8C","9C","JC","QC","KC",
		"2S","4S","5S","6S","7S","8S","9S","TS","JS","QS","KS"};;//T ===> 10

//create the potential card lists
char dealer[12][3], player[12][3], split1[12][3], split2[12][3], split3[12][3];
// the wager of the player
double pay_this;
// the number of the total cards
int num_of_cards = 52;
// the current money player holds
double current_money = 100;
char test_case;
char play_again = 'y';

// check whether the input wager is a double or not
void check(){
	bool input_right = false; // a temporary variable to check whether the form of the input is right
	    while (!input_right){
	        cin >> pay_this;

	        if(!cin.fail() && (cin.peek()==EOF || cin.peek()=='\n'))
	        {input_right = true;}
	        else{
	            cin.clear();
	            cin.ignore(256,'\n');
	            cout << "The form of your input is not correct, "
	            		"please enter another number: " << endl;
	        }
	    }
}
// whenever the game starts another time, run this function
void start(){
	//initialize these variables
	num_card_dealer=0; num_card_player=0;num_card_split1=0;num_card_split2=0;num_card_split3=0;current_num=4;
	sum_dealer=0; sum_player=0; sum_split1=0; sum_split2=0; sum_split3=0;
	first2_player=0; first2_1=0; first2_2=0; first2_3=0;
	add_num=0;  win_begin = 0; draw_dealer =1;
	//output the current money
	cout<<"Player: $"<<current_money<<endl;

	cout<<"Pay for this round : "<<endl;
	//check the input form
	check();
	//check the input range
	while (pay_this > current_money || pay_this <= 0){
		if(pay_this != 0){
			cout<<"You don't have such amount of money. Please enter another amount of money: "<<endl;
			check();
		}
		if(pay_this == 0){
			cout<<"You can't play for free. Please enter another amount of money: "<<endl;
			check();
		}
	}
	// substract the money paid
	current_money -= pay_this;
}
char temp; // store the character temporarily
int num_of_1 =0;  //the number of Aces in the cards
// calculate the total points of each hand
void calculatePoints(){// similar for each hand
	//if the hand doesn't bust, Ace will be calculated as 11.
	if (sum_player <= 11){
		for (int xxx=0; xxx<num_card_player; xxx++){
			if(player[xxx][0]=='1'){
				num_of_1=1;
			}
		}
		if(num_of_1 == 1){
			sum_player +=10;
		}
		num_of_1=0;
	}

	if (sum_split1 <= 11){
			for (int xxx=0; xxx<num_card_split1; xxx++){
				if(split1[xxx][0]=='1'){
					num_of_1=1;
				}
			}
			if(num_of_1 == 1){
				sum_split1 +=10;
			}
			num_of_1=0;
		}
	if (sum_split2 <= 11){
			for (int xxx=0; xxx<num_card_split2; xxx++){
				if(split2[xxx][0]=='1'){
					num_of_1=1;
				}
			}
			if(num_of_1 == 1){
				sum_split2 +=10;
			}
			num_of_1=0;
		}
	if (sum_split3 <= 11){
			for (int xxx=0; xxx<num_card_split3; xxx++){
				if(split3[xxx][0]=='1'){
					num_of_1=1;
				}
			}
			if(num_of_1 == 1){
				sum_split3 +=10;
			}
			num_of_1=0;
		}
	if (sum_dealer <= 11){
			for (int xxx=0; xxx<num_card_dealer; xxx++){
				if(dealer[xxx][0]=='1'){
					num_of_1=1;
				}
			}
			if(num_of_1 == 1){
				sum_dealer +=10;
			}
			num_of_1=0;
		}
}

void charToNum(){ 		// convert the charcater stored in the cards into the point it represents
	if (temp == '2' || temp == '3' || temp == '4'|| temp == '5'||temp == '6'||
			temp == '7'||temp == '8'||temp == '9')
	{add_num = temp-'0';}
	if(temp=='1')
	{add_num = 1;} //when adding numbers, use the smaller value
	if(temp=='T'||temp=='J'||temp=='Q'||temp=='K')
	{add_num = 10;}
}

void dealerDraw(){		//the function of the dealer drawing its cards
	// smart dealer
	while( ( (sum_dealer< first2_player)&&
			(!num_card_split1 || sum_dealer < first2_1) &&
			(!num_card_split2 || sum_dealer < first2_2 )&&
			(!num_card_split3 || sum_dealer < first2_3) &&
			!((player[0][0]=='1' && sum_player == 11)|| (sum_player == 11 && player[1][0]=='1')) ) || //doesn't equal 21
			sum_dealer < 14){ // smaller than the smallest one  (two face-up cards) of all the hands
		//dealer draws the cards
		dealer[num_card_dealer][0]=all_cards[current_num][0];
		dealer[num_card_dealer][1]=all_cards[current_num][1];
		temp = dealer[num_card_dealer][0];
		charToNum();
		sum_dealer += add_num;
		num_card_dealer++;
		current_num++;
	}
	draw_dealer=0;
}

void reward(){		//calculate the reward and the result of this round
					// the form of the codes is similar among each hand
		// for player
		if(!(sum_player > 21) && sum_player >= sum_dealer){
			// if same points and both don't bust
			if (sum_player == sum_dealer){
				current_money +=pay_this;
				cout<<"Player: tie!"<<endl;
			}
			else{
				current_money += 2*pay_this;
				cout<<"Player: win!"<<endl;
			}

		}
		//if not bust and player's points more than dealer's
		else if(!(sum_player > 21)&& sum_player > 0 && sum_dealer>21){
					current_money += 2*pay_this;
					cout<<"Player: win!"<<endl;
				}
		else{
			if(sum_player>21 && sum_dealer>21){//if both bust
				current_money += pay_this;
				cout<<"Player: tie!"<<endl;
			}
			else{// only player bust
			cout<<"Player: lose!"<<endl;
			}
		}

		//for split1
		if(!(sum_split1 > 21) && sum_split1 >= sum_dealer){
			if(sum_split1==sum_dealer){
				current_money+=pay_this;
				cout<<"Split: tie!"<<endl;
			}
			else{
				current_money += 2*pay_this;
				cout<<"Split: win!"<<endl;
			}

		}
		else if(!(sum_split1 > 21)&& sum_split1>0 && sum_dealer>21){
							current_money += 2*pay_this;
							cout<<"Split: win!"<<endl;
						}
		else{
			if(num_card_split1){ // if there is a second split
				if(sum_split1>21 && sum_dealer>21){
							current_money += pay_this;
							cout<<"Split: tie!"<<endl;
						}
				else{
					cout<<"Split: lose!"<<endl;
				}
			}
		}
		//for split2
		if(!(sum_split2 > 21 )&& sum_split2 >= sum_dealer){
			if(sum_split2==sum_dealer){
				current_money+=pay_this;
				cout<<"Split2: tie!"<<endl;
			}
			else{
				current_money += 2*pay_this;
				cout<<"Split2: win!"<<endl;
			}

		}
		else if(!(sum_split2 > 21)&& sum_split2>0 && sum_dealer>21){
							current_money += 2*pay_this;
							cout<<"Split2: win!"<<endl;
						}
		else{
			if(num_card_split2){
				if(sum_split2>21 && sum_dealer>21){
					current_money += pay_this;
					cout<<"Split2: tie!"<<endl;
				}
				else{
					cout<<"Split2: lose!"<<endl;
				}
			}
		}

		//for split3
		if(!(sum_split3 > 21 )&& sum_split3 >= sum_dealer){
			if(sum_split3 == sum_dealer){
				current_money+=pay_this;
				cout<<"Split3: tie!"<<endl;
			}
			else{
				current_money += 2*pay_this;
				cout<<"Split3: win!"<<endl;
			}

		}
		else if(!(sum_split3 > 21)&& sum_split3>0 &&  sum_dealer>21){
							current_money += 2*pay_this;
							cout<<"Split3: win!"<<endl;
						}
		else{
			if(num_card_split3){
				if(sum_split3>21 && sum_dealer>21){
					current_money += pay_this;
					cout<<"Split3: tie!"<<endl;
				}
				else{
				cout<<"Split3: lose!"<<endl;
				}
			}
		}
}

//the function for output the points of each hand
void coutFunction(){ // the steps are similar among each hand
	cout<<"> Dealer : ";
	// when the player doesn't stop drawing
	if( draw_dealer == 1 &&		//win_begin ==0
			(!((sum_player>21 && !num_card_split1) ||
			(sum_player>21 && sum_split1>21 && !num_card_split2) ||
			(sum_player>21 && sum_split1>21 && sum_split2>21 && !num_card_split3) ||
			(sum_player>21 && sum_split1>21 && sum_split2>21 && sum_split3>21)))){
		cout<<" * ";
	}
	//if all the hands of the player bust, the dealer doesn't draw (smart dealer)
	if((sum_player>21 && !num_card_split1) ||
			(sum_player>21 && sum_split1>21 && !num_card_split2) ||
			(sum_player>21 && sum_split1>21 && sum_split2>21 && !num_card_split3) ||
			(sum_player>21 && sum_split1>21 && sum_split2>21 && sum_split3>21)){
		draw_dealer = 0;
	}

	for (int dealer_num = draw_dealer; dealer_num<num_card_dealer; dealer_num++){	//<12 ?
		// output corresponding points of the cards
		if (dealer[dealer_num][0] == 'T'){
			cout<<"10"<<dealer[dealer_num][1]<<" ";
		}
		else if (dealer[dealer_num][0] == 'J'){
			cout<<"11"<<dealer[dealer_num][1]<<" ";
		}
		else if (dealer[dealer_num][0] == 'Q'){
			cout<<"12"<<dealer[dealer_num][1]<<" ";
		}
		else if (dealer[dealer_num][0] == 'K'){
			cout<<"13"<<dealer[dealer_num][1]<<" ";
		}
		else{
			cout<<dealer[dealer_num]<<" ";
		}
	}

	cout<<endl;
	cout<<"> Player : ";
	for (int player_num=0; player_num<num_card_player; player_num++){	//<12 ?

		if (player[player_num][0] == 'T'){
			cout<<"10"<<player[player_num][1]<<" ";
		}
		else if (player[player_num][0] == 'J'){
			cout<<"11"<<player[player_num][1]<<" ";
		}
		else if (player[player_num][0] == 'Q'){
			cout<<"12"<<player[player_num][1]<<" ";
		}
		else if (player[player_num][0] == 'K'){
			cout<<"13"<<player[player_num][1]<<" ";
		}
		else{
			cout<<player[player_num]<<" ";
		}
	}
	cout<<endl;

	if(num_card_split1){
		cout<<"> Split : ";
	}

	for (int num1=0; num1<num_card_split1; num1++){	//<12 ?

			if (split1[num1][0] == 'T'){
				cout<<"10"<<split1[num1][1]<<" ";
			}
			else if (split1[num1][0] == 'J'){
				cout<<"11"<<split1[num1][1]<<" ";
			}
			else if (split1[num1][0] == 'Q'){
				cout<<"12"<<split1[num1][1]<<" ";
			}
			else if (split1[num1][0] == 'K'){
				cout<<"13"<<split1[num1][1]<<" ";
			}
			else{
				cout<<split1[num1]<<" ";
			}

		}
	if (num_card_split1){
		cout<<endl;
	}
		if(num_card_split2){
		cout<<"> Split2 : ";
	}

	for (int num2=0; num2<num_card_split2; num2++){	//<12 ?

		if (split2[num2][0] == 'T'){
			cout<<"10"<<split2[num2][1]<<" ";
		}
		else if (split2[num2][0] == 'J'){
			cout<<"11"<<split2[num2][1]<<" ";
		}
		else if (split2[num2][0] == 'Q'){
			cout<<"12"<<split2[num2][1]<<" ";
		}
		else if (split2[num2][0] == 'K'){
			cout<<"13"<<split2[num2][1]<<" ";
		}
		else{
			cout<<split2[num2]<<" ";
		}

	}
	if(num_card_split2){
		cout<<endl;
	}
	if(num_card_split3){
			cout<<"> Split3 : ";
		}

	for (int num3=0; num3<num_card_split3; num3++){	//<12 ?

		if (split3[num3][0] == 'T'){
			cout<<"10"<<split3[num3][1]<<" ";
		}
		else if (split3[num3][0] == 'J'){
			cout<<"11"<<split3[num3][1]<<" ";
		}
		else if (split3[num3][0] == 'Q'){
			cout<<"12"<<split3[num3][1]<<" ";
		}
		else if (split3[num3][0] == 'K'){
			cout<<"13"<<split3[num3][1]<<" ";
		}
		else{
			cout<<split3[num3]<<" ";
		}

	}
	if(num_card_split3){
		cout<<endl;
	}
}
// if_same : whether it satisfies the requirement of splitting
int if_same = 0,  current_card = 4;
//if_split: whether the user wants to split
char if_split = 'n';
// the function to operate splitting
void split(){
	// 1- split
	//if the first o cards have the same points and the player has enough money for splitting (same for the other hands)
	if (player[0][0] == player[1][0] && current_money >= pay_this){
		cout<<"Split? (Y/N): "<<endl;
		cin>>if_split;
		if (if_split == 'y' || if_split == 'Y'){
			current_money -= pay_this;
			//seperate the same card into a split ,same as the other hands
			split1[0][0]=player[1][0];
			split1[0][1]=player[1][1];
			//add the points
			temp = split1[0][0];
			charToNum();
			sum_split1 += add_num;
			temp = player[1][0];
			charToNum();
			sum_player -= add_num;
			// draw cards automatically
			player[1][0]=all_cards[current_num][0];
			player[1][1]=all_cards[current_num][1];
			temp = player[1][0];
			charToNum();
			sum_player += add_num;
			current_num++;
			split1[1][0]=all_cards[current_num][0];
			split1[1][1]=all_cards[current_num][1];
			temp = split1[1][0];
			charToNum();
			sum_split1 += add_num;
			current_num++;
			num_card_split1 = 2;
			coutFunction();
			//2 - split
			if(player[0][0] == player[1][0] && (if_split == 'y'|| if_split == 'Y') && current_money >= pay_this){
				cout<<"Split? (Y/N): "<<endl;
				cin>>if_split;
				if (if_split == 'y' || if_split == 'Y'){
					current_money -= pay_this;
					//split
					split2[0][0]=player[1][0];
					split2[0][1]=player[1][1];
					temp = split2[0][0];
					charToNum();
					sum_split2 += add_num;
					temp = player[1][0];
					charToNum();
					sum_player -= add_num;
					//draw cards automatically
					player[1][0]=all_cards[current_num][0];
					player[1][1]=all_cards[current_num][1];
					temp = player[1][0];
					charToNum();
					sum_player += add_num;
					current_num++;
					split2[1][0]=all_cards[current_num][0];
					split2[1][1]=all_cards[current_num][1];
					temp = split2[1][0];
					charToNum();
					sum_split2 += add_num;
					current_num++;
					num_card_split2 =2;
					coutFunction();
					//3 - split
					if(player[0][0] == player[1][0]&& (if_split == 'y'|| if_split == 'Y')&& current_money >= pay_this){
						cout<<"Split? (Y/N): "<<endl;
						cin>>if_split;
						if (if_split == 'y' || if_split == 'Y'){
							current_money -= pay_this;
							//cout<<current_money<<endl;
							//split
							split3[0][0]=player[1][0];
							split3[0][1]=player[1][1];
							temp = split3[0][0];
							charToNum();
							sum_split3 += add_num;
							temp = player[1][0];
							charToNum();
							sum_player -= add_num;
							//draw cards auto
							player[1][0]=all_cards[current_num][0];
							player[1][1]=all_cards[current_num][1];
							temp = player[1][0];
							charToNum();
							sum_player += add_num;
							current_num++;
							split3[1][0]=all_cards[current_num][0];
							split3[1][1]=all_cards[current_num][1];
							temp = split3[1][0];
							charToNum();
							sum_split3 += add_num;
							current_num++;
							num_card_split3=2;
							coutFunction();
						}
					}
					if(split1[0][0] == split1[1][0]&& (if_split == 'y'|| if_split == 'Y')&& current_money >= pay_this){
						cout<<"Split? (Y/N): "<<endl;
						cin>>if_split;
						if (if_split == 'y' || if_split == 'Y'){
							current_money -= pay_this;
							//split
							split3[0][0]=split1[1][0];
							split3[0][1]=split1[1][1];
							temp = split3[0][0];
							charToNum();
							sum_split3 += add_num;
							temp = split1[1][0];
							charToNum();
							sum_split1 -= add_num;
							//draw cards automatically
							split1[1][0]=all_cards[current_num][0];
							split1[1][1]=all_cards[current_num][1];
							temp = split1[1][0];
							charToNum();
							sum_split1 += add_num;
							current_num++;
							split3[1][0]=all_cards[current_num][0];
							split3[1][1]=all_cards[current_num][1];
							temp = split3[1][0];
							charToNum();
							sum_split3 += add_num;
							current_num++;
							num_card_split3=2;
							coutFunction();
						}
					}
					if(split2[0][0] == split2[1][0]&& (if_split == 'y'|| if_split == 'Y')&& current_money >= pay_this){
						cout<<"Split? (Y/N): "<<endl;
						cin>>if_split;
						if (if_split == 'y' || if_split == 'Y'){
							current_money -= pay_this;
							//split
							split3[0][0]=split2[1][0];
							split3[0][1]=split2[1][1];
							temp = split3[0][0];
							charToNum();
							sum_split3 += add_num;
							temp = split2[1][0];
							charToNum();
							sum_split2 -= add_num;
							//draw cards automatically
							split2[1][0]=all_cards[current_num][0];
							split2[1][1]=all_cards[current_num][1];
							temp = split2[1][0];
							charToNum();
							sum_split2 += add_num;
							current_num++;
							split3[1][0]=all_cards[current_num][0];
							split3[1][1]=all_cards[current_num][1];
							temp = split3[1][0];
							charToNum();
							sum_split3 += add_num;
							current_num++;

							num_card_split3=2;
							coutFunction();
						}
					}
				}
			}
			//2 - split
			if(split1[0][0] == split1[1][0]&& (if_split == 'y'|| if_split == 'Y')&& current_money >= pay_this){
				cout<<"Split? (Y/N): "<<endl;
				cin>>if_split;
				if (if_split == 'y' || if_split == 'Y'){
					current_money -= pay_this;
					//split
					split2[0][0]=split1[1][0];
					split2[0][1]=split1[1][1];
					temp = split2[0][0];
					charToNum();
					sum_split2 += add_num;
					temp = split1[1][0];
					charToNum();
					sum_split1 -= add_num;
					//draw cards automatically
					split1[1][0]=all_cards[current_num][0];
					split1[1][1]=all_cards[current_num][1];
					temp = split1[1][0];
					charToNum();
					sum_split1 += add_num;
					current_num++;
					split2[1][0]=all_cards[current_num][0];
					split2[1][1]=all_cards[current_num][1];
					temp = split2[1][0];
					charToNum();
					sum_split2 += add_num;
					current_num++;
					num_card_split2=2;
					coutFunction();
					//3 - split
					if(player[0][0] == player[1][0]&& (if_split == 'y'|| if_split == 'Y')&& current_money >= pay_this){
						cout<<"Split? (Y/N): "<<endl;
						cin>>if_split;
						if (if_split == 'y' || if_split == 'Y'){
						current_money -= pay_this;
						//split
						split3[0][0]=player[1][0];
						split3[0][1]=player[1][1];
						temp = split3[0][0];
						charToNum();
						sum_split3 += add_num;
						temp = player[1][0];
						charToNum();
						sum_player -= add_num;
						//draw cards automatically
						player[1][0]=all_cards[current_num][0];
						player[1][1]=all_cards[current_num][1];
						temp = player[1][0];
						charToNum();
						sum_player += add_num;
						current_num++;
						split3[1][0]=all_cards[current_num][0];
						split3[1][1]=all_cards[current_num][1];
						temp = split3[1][0];
						charToNum();
						sum_split3 += add_num;
						current_num++;
						num_card_split3=2;
						coutFunction();
					}
			}
					if(split1[0][0] == split1[1][0]&& (if_split == 'y'|| if_split == 'Y')&& current_money >= pay_this){
						cout<<"Split? (Y/N): "<<endl;
						cin>>if_split;
						if (if_split == 'y' || if_split == 'Y'){
							current_money -= pay_this;
						//split
							split3[0][0]=split1[1][0];
							split3[0][1]=split1[1][1];
							temp = split3[0][0];
							charToNum();
							sum_split3 += add_num;
							temp = split1[1][0];
							charToNum();
							sum_split1 -= add_num;
							//draw cards auto
							split1[1][0]=all_cards[current_num][0];
							split1[1][1]=all_cards[current_num][1];
							temp = split1[1][0];
							charToNum();
							sum_split1 += add_num;
							current_num++;
							split3[1][0]=all_cards[current_num][0];
							split3[1][1]=all_cards[current_num][1];
							temp = split3[1][0];
							charToNum();
							sum_split3 += add_num;
							current_num++;

							num_card_split3=2;
							coutFunction();
						}
					}
						if(split2[0][0] == split2[1][0]&& (if_split == 'y'|| if_split == 'Y')&& current_money >= pay_this){
							cout<<"Split? (Y/N): "<<endl;
							cin>>if_split;
							if (if_split == 'y' || if_split == 'Y'){
								current_money -= pay_this;
								//split
								split3[0][0]=split2[1][0];
								split3[0][1]=split2[1][1];
								temp = split3[0][0];
								charToNum();
								sum_split3 += add_num;
								temp = split2[1][0];
								charToNum();
								sum_split2 -= add_num;
								//draw cards automatically
								split2[1][0]=all_cards[current_num][0];
								split2[1][1]=all_cards[current_num][1];
								temp = split2[1][0];
								charToNum();
								sum_split2 += add_num;
								current_num++;
								split3[1][0]=all_cards[current_num][0];
								split3[1][1]=all_cards[current_num][1];
								temp = split3[1][0];
								charToNum();
								sum_split3 += add_num;
								current_num++;

								num_card_split3=2;
								coutFunction();
							}
						}
				}
			}
		}
		if(if_split != 'Y' && if_split !='y'){
			coutFunction();
		}

	}


}

int main(){

	// random
	srand(time(0));

	start();

	while (play_again == 'y' || play_again == 'Y'){

		cout<<"Test case?(Y/N): "<<endl;
		cin>>test_case;
		//if not the test case, do the following so as to shuffle the cards
		if(test_case !='y' && test_case !='Y'){
			for (int time=0; time <52; time++){
				int random;
				random = (double) rand() /RAND_MAX *(num_of_cards);
				swap(all_cards[time],all_cards[random]);
			}
		}
		// TEST CASE
		else{
			// for test case, use the test sequence of cards
			char new_all_cards[52][4]={"2D","2H","3C","7D","5C","9D","TH","2C","4D","3S","4H","JD",
									"1H","1C","3D","TC","1S","1D","QC","KC","JH","QH","JC","6H",
									"7H","8H","9H","KH","TS","JS","QS","KS","3H","5H","5D","6D",
									"8D","TD","QD","KD","4C","6C","7C","8C","9C","2S","4S","5S",
									"6S","7S","8S","9S"};
			for (int row=0; row<52; row++){
				for (int col=0;col<4;col++){
					all_cards[row][col]=new_all_cards[row][col];
				}
			}
		}
		// draw the initial 4 cards

		player[0][0]=all_cards[0][0];
		player[0][1]=all_cards[0][1];
		temp = player[0][0];
		charToNum();
		sum_player += add_num;
		player[1][0]=all_cards[1][0];
		player[1][1]=all_cards[1][1];
		temp = player[1][0];
		charToNum();
		sum_player += add_num;
		num_card_player=2;
		// check whether 21 points at first or not
		if ((player[0][0]=='1' && sum_player == 11)
				|| (sum_player == 11 && player[1][0]=='1')){
			win_begin = 1;
			sum_player = 21;
		}

			dealer[0][0]=all_cards[2][0];
			dealer[0][1]=all_cards[2][1];
			num_card_dealer=2;
			temp = dealer[0][0];
			charToNum();
			sum_dealer += add_num;
			dealer[1][0]=all_cards[3][0];
			dealer[1][1]=all_cards[3][1];
			temp = dealer[1][0];
			charToNum();
			sum_dealer += add_num;
			coutFunction();

			split();
			// store the first two items of the players into these variables
			first2_player=sum_player;
			first2_1=sum_split1;
			first2_2=sum_split2;
			first2_3=sum_split3;
			// each round
			if (!(sum_player >= 21 || sum_split1 >=21 || sum_split2>=21 || sum_split3>=21)){
				cout<<"> Draw? (Y/N): "<<endl;
				cin>>if_draw;
			}
			while (if_draw == 'Y' || if_draw == 'y' ){


				player[num_card_player][0]=all_cards[current_num][0];
				player[num_card_player][1]=all_cards[current_num][1];

				temp = player[num_card_player][0];
				charToNum();
				sum_player += add_num;

				num_card_player++;
				current_num++;
				coutFunction();
				//bust case
				if(sum_player > 21 ){
					cout<<"Player busted!"<<endl;
					break;
				}
				// when the number of cards equals to 5(max number of cards) or total points equal 21, stop drawing
				// same as the other hands
				else if(num_card_player>4 || sum_player == 21){
					break;
				}
				cout<<"> Draw? (Y/N): "<<endl;
				cin>>if_draw;
			}

			if(num_card_split1){// if this hand (split1) exist
				coutFunction();
				cout<<"> Draw for split? (Y/N): "<<endl;
				cin>>if_draw;
				while (if_draw == 'Y' || if_draw == 'y'){

					split1[num_card_split1][0]=all_cards[current_num][0];
					split1[num_card_split1][1]=all_cards[current_num][1];
					temp = split1[num_card_split1][0];
					charToNum();
					sum_split1 += add_num;
					num_card_split1++;
					current_num++;
					coutFunction();
					if(sum_split1 >21){
						cout<<"Split busted!"<<endl;
						break;
					}
					else if(num_card_split1>4 || sum_split1 == 21){
						break;
					}
					cout<<"> Draw for split? (Y/N): "<<endl;
					cin>>if_draw;
				}
			}

			if(num_card_split2){
				coutFunction();
					cout<<"> Draw for split2? (Y/N): "<<endl;
					cin>>if_draw;
					while (if_draw == 'Y' || if_draw == 'y'){

						split2[num_card_split2][0]=all_cards[current_num][0];
						split2[num_card_split2][1]=all_cards[current_num][1];
						temp = split2[num_card_split2][0];
						charToNum();
						sum_split2 += add_num;
						num_card_split2++;
						current_num++;
						coutFunction();
						if(sum_split2 > 21 ){
							cout<<"Split2 busted!"<<endl;
							break;
						}
						else if(num_card_split2>4 || sum_split2 == 21){
							break;
						}
						cout<<"> Draw for split2? (Y/N): "<<endl;
						cin>>if_draw;
					}
			}

			if(num_card_split3){
				coutFunction();
				cout<<"> Draw for split3? (Y/N): "<<endl;
				cin>>if_draw;
				while (if_draw == 'Y' || if_draw == 'y'){

					split3[num_card_split3][0]=all_cards[current_num][0];
					split3[num_card_split3][1]=all_cards[current_num][1];
					temp = split3[num_card_split3][0];
					charToNum();
					sum_split3 += add_num;
					num_card_split3++;
					current_num++;
					coutFunction();
					if(sum_split3 > 21 ){
						cout<<"Split3 busted!"<<endl;
						break;
					}
					else if(num_card_split3>4 || sum_split3 == 21){
						break;
					}
					cout<<"> Draw for split3? (Y/N): "<<endl;
					cin>>if_draw;
				}
			}


			if (win_begin == 1){
				dealerDraw();
				coutFunction();
				calculatePoints();
				cout<<"> Dealer "<<sum_dealer<<" points, Player 21 points"<<endl;
				if(sum_dealer != 21){
					cout<<"Player win!!!"<<endl;
					current_money += pay_this*2.5;
				}
				if(sum_dealer == 21){
					cout<<"Tie!"<<endl;
					current_money +=pay_this;
				}
			}



			if (win_begin == 0 ){// if the first 2 cards of the player reach 21 points, the dealer begins drawing
				if(!((sum_player>21 && !num_card_split1) ||
						(sum_player>21 && sum_split1>21 && !num_card_split2) ||
						(sum_player>21 && sum_split1>21 && sum_split2>21 && !num_card_split3) ||
						(sum_player>21 && sum_split1>21 && sum_split2>21 && sum_split3>21))){
					dealerDraw();
				}
				coutFunction();

				calculatePoints();
				//output the final points of each hand and the dealer
				cout<<"> Dealer "<<sum_dealer<<" points, Player "<<sum_player<<" points";

				if(num_card_split1){
					cout<<"; Split "<<sum_split1<<" points";
				}
				if(num_card_split2){
					cout<<"; Split2 "<<sum_split2<<" points";
				}
				if(num_card_split3){
					cout<<"; Split3 "<<sum_split3<<" points";
				}
				cout<<endl;
				reward();
			}
			//if the player still has money left, ask the user whether play again or not
			if(current_money > 0){
				cout<<"> Again? (Y/N): "<<endl;
				cin>>play_again;
				if(play_again != 'n' && play_again!='N'){
					start();
				}
			}
			// if the player has run out of money, stop the game
			if(current_money <= 0){
				cout<<"You have run out of your money! Game over!"<<endl;
				play_again = 'n';
			}
	}
	return 0;
}



