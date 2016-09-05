#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
using namespace std;

const int MAX_ELEMENTS = 10;	//the maximum size of the input string
char play_again='c';	//whether the player wants to play again
int size_of_string = 0;	//the size of the input string
int if_same=0;			//if_same = 1 when the selected two indices have the same value
void check(){			//check the form of user input for size
	bool ok = false;
	    while (!ok){
	        cin >> size_of_string;
	        if(!cin.fail() && (cin.peek()==EOF || cin.peek()=='\n'))
	        {ok = true;}
	        else{
	            cin.clear();
	            cin.ignore(256,'\n');
	            cout << "The form of your input is not correct, "
	            		"please enter another number: " << endl;
	        }
	    }
}
void permutation(char str[MAX_ELEMENTS], int num){	// str corresponds to the user input string
	char temp[10];		// a temporary string
	for (int k=0; k<size_of_string; k++){
		temp[k]=str[k];
	}
	if (num != size_of_string){
		for (int i=num; i<size_of_string; i++){
			for (int k=num; k<i; k++ ){	//  let the same items keep their relative sequence
				if (temp[k] == temp[i]){
					if_same = 1;
				}
			}
			if (if_same == 0){
				// This function is the same as selecting the
				//ith item to numth position and the items between 2 positions are pushed behind
				for(int j=0; j<i-num; j++){
					swap(temp[i-j],temp[i-j-1]);
				}
				permutation(temp, num+1);
			}
			// avoid repeated outputs
			else{
				if_same=0;
				continue;
			}
		}
	}
	//when the permutation has all results
	else{
			for (int i=0; i<size_of_string; i++){
				cout<<temp[i];
			}
			cout<<endl;
		}
}
int main(){
	while (play_again == 'C' || play_again == 'c'){
		char character;
		char string[MAX_ELEMENTS];
		cout<<"Please input array size (1-10): ";
		check();
		cout<<endl;
		while(size_of_string>MAX_ELEMENTS || size_of_string<1){
			cout<<"The number is not in the domain. Please enter another one:";
			check();
			cout<<endl;
		}
		cout<<"Please input array elements : ";

		for (int times = 0; times<size_of_string; times++){

			cin>>character;
			string[times]=character;
		}
		cout<<endl;
		cout<<"The permutation are:"<<endl;

		permutation(string,0);
		cout<<"Continue to use this program? (C / c to continue):";
		cin>>play_again;
		cout<<endl;
	}
	return 0;
}



