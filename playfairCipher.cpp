#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string stringPrep(string input);
string create_encoding(const string &key, string alphabet_minus_j);
void display_square(const string &comp);
string messageEncrypt(string message, string table);
string messageDecrypt(string message, string table);
string phrasePrep(string phrase);
////////////////////////////////////////////////////////////////////////////////////////
int main(){
	string alphabet_minus_j = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
	string message, keyword, keytable, postMessage;
	char mode;
	
	while(mode != 'Q'){
		cout << "\n[E]ncrypt, [D]ecrypt, [Q]uit: ";
		cin >> mode;
		mode = toupper(mode);
		cin.get();
		
		if(mode == 'Q') return 0;
		
		keyword = stringPrep("Keyword: ");
		keytable = create_encoding(keyword, alphabet_minus_j);
		display_square(keytable);
		
		switch (mode){
			case 'E':
				message = stringPrep("Message: ");
				postMessage = messageEncrypt(phrasePrep(message), keytable);	
				break;
				
			case 'D':
				message = stringPrep("Encrypted Message: ");
				postMessage = messageDecrypt(phrasePrep(message), keytable);
				break;
				
			default:
				cout <<"[Invalid Function]\n";	
		}
		
		
		
		for(int i = 0; i < message.length(); i++){
			cout << message[i];
			if(i != 0 && i % 2 == 1) cout << ' ';
		}
		cout << endl;
		
		for(int i = 0; i < postMessage.length(); i++){
			cout << postMessage[i];
			if(i != 0 && i % 2 == 1) cout << ' ';
		}
		cout << endl;
	}
}
///////////////////////////////////////////////////////////////////////////////////////
string phrasePrep(string phrase){
	string newPhrase = phrase;
	
	for(int i = 0; i < newPhrase.length(); i += 2){
		if(newPhrase[i] == newPhrase[i + 1]) newPhrase[i + 1] = 'X';      //replaces 2nd letter of pair with X is both are the same
	}
	
	if(newPhrase.length() % 2 != 0) newPhrase += 'X';                //adds X to the end of the string if the string is odd in length

	return newPhrase;
}
/////////////////////////////////////////////////////////////////////////////////////
string messageEncrypt(string message, string table){
	char keytable[5][5];
	string encMessage = message;
	int stringPos = 0;
	
	int pos1r, pos1c, pos2r, pos2c;
	
	for(int c = 0; c < 5; c++){
		for(int r = 0; r < 5; r++){
			keytable[r][c] = table[stringPos];   //converts the string keytable to a 2 dimensional array
			stringPos++;                         //will make it easier to reference character positions
		}
	}
	stringPos = 0;
	
	for(int i = 0; i < encMessage.length(); i += 2){
		
		for(int c = 0; c < 5; c++){
			for(int r = 0; r < 5; r++){
				if (encMessage[stringPos] == keytable[r][c]){
					pos1r = r;
					pos1c = c;
				}
				if (encMessage[stringPos + 1] == keytable[r][c]){
					pos2r = r;
					pos2c = c;
				}
			}
		}
		
		if(pos1r == pos2r){                                                             //same row
			if(pos1c + 1 == 5) encMessage[stringPos] = keytable[pos1r][0];
						  else encMessage[stringPos] = keytable[pos1r][pos1c + 1];
			
			if(pos2c + 1 == 5) encMessage[stringPos + 1] = keytable[pos2r][0];
						  else encMessage[stringPos + 1] = keytable[pos2r][pos2c + 1];
			
			stringPos += 2;
		}
		else if(pos1c == pos2c){                                                        //same column
			if(pos1r + 1 == 5) encMessage[stringPos] = keytable[0][pos1c];
						  else encMessage[stringPos] = keytable[pos1r + 1][pos1c];
			
			if(pos2r + 1 == 5) encMessage[stringPos + 1] = keytable[0][pos2c];
						  else encMessage[stringPos + 1] = keytable[pos2r + 1][pos2c];
			
			stringPos += 2;
		}                                                                               //rectangle
		else{
			encMessage[stringPos] = keytable[pos2r][pos1c];
			encMessage[stringPos + 1] = keytable[pos1r][pos2c];
			
			stringPos += 2;
		}	
	}
	
	return encMessage;
}
////////////////////////////////////////////////////////////////////////////////////////
string messageDecrypt(string message, string table){
	char keytable[5][5];
	string encMessage = message;
	int stringPos = 0;
	
	int pos1r, pos1c, pos2r, pos2c;
	
	for(int c = 0; c < 5; c++){
		for(int r = 0; r < 5; r++){
			keytable[r][c] = table[stringPos];   //converts the string keytable to a 2 dimensional array
			stringPos++;                         //will make it easier to reference character positions
		}
	}
	stringPos = 0;
	
	for(int i = 0; i < encMessage.length(); i += 2){
		
		for(int c = 0; c < 5; c++){
			for(int r = 0; r < 5; r++){
				if (encMessage[stringPos] == keytable[r][c]){
					pos1r = r;
					pos1c = c;
				}
				if (encMessage[stringPos + 1] == keytable[r][c]){
					pos2r = r;
					pos2c = c;
				}
			}
		}
		
		if(pos1r == pos2r){                                                             //same row
			if(pos1c - 1 == -1) encMessage[stringPos] = keytable[pos1r][4];
						  else encMessage[stringPos] = keytable[pos1r][pos1c - 1];
			
			if(pos2c - 1 == -1) encMessage[stringPos + 1] = keytable[pos1r][4];
						  else encMessage[stringPos + 1] = keytable[pos2r][pos2c - 1];
			
			stringPos += 2;
		}
		else if(pos1c == pos2c){                                                        //same column
			if(pos1r - 1 == -1) encMessage[stringPos] = keytable[4][pos1c];
						  else encMessage[stringPos] = keytable[pos1r - 1][pos1c];
			
			if(pos2r - 1 == -1) encMessage[stringPos + 1] = keytable[4][pos2c];
						  else encMessage[stringPos + 1] = keytable[pos2r - 1][pos2c];
			
			stringPos += 2;
		}                                                                               //rectangle
		else{
			encMessage[stringPos] = keytable[pos2r][pos1c];
			encMessage[stringPos + 1] = keytable[pos1r][pos2c];
			
			stringPos += 2;
		}	
	}
	
	return encMessage;
}
////////////////////////////////////////////////////////////////////////////////////////
string stringPrep(string input){
	bool iserased, valid_key;
	string str;
	
	//cin.get();                                                                                     //accepts only alphabetical characters, erases spaces for keyword and phrase
	do{
		cout << input;		
		getline(cin, str);
		
		for(int i = 0; i < str.length(); i++){
			char c = str[i];
			if (!((c >= 'a' && c <= 'z')||(c >= 'A' && c <= 'Z')||(c == ' '))) {
				valid_key = 0;
				break;
			}
			else 
				valid_key = 1;
		}
	}while(valid_key == 0);
	
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	replace(str.begin(), str.end(), 'J', 'I');
	
	for (int j = 0; j < str.length(); j++){
		do{
			if (str[j] == ' '){
				str.erase(str.begin() + j);
				iserased = true;
			}
			else iserased = false;			
		}while(iserased);
	}
	
	return str;
}
///////////////////////////////////////////////////////////////////////////////////////
string create_encoding(const string &key, string alphabet_minus_j){
	string temp = key + alphabet_minus_j;
	bool iserased;
	                                                                        //adds the keyword to the fron of the alphabet and deletes any duplicate chr
	for (int i = 0; i < temp.length(); i++){
		for (int j = i + 1; j < temp.length(); j++){
			do{
				if (temp[i] == temp[j]){
					temp.erase(temp.begin() + j);
					iserased = true;
				}
				else iserased = false;			
			}while(iserased);
		}
	}
	
	return temp;
}
////////////////////////////////////////////////////////////////////////////////////////
void display_square(const string &comp){
	
	for(int i = 0; i < comp.length(); i++){
		if (i%5 == 0 && i != 0) cout << endl;
		cout << comp.at(i) << " ";	
	}
	cout << endl;
}
