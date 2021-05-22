#include<iostream>
#include <iomanip>
#include<string>
using namespace std;

char arr[5][5] = { { 'A','S','E','M','B' },{ 'L','Y','F','U','N' },{ 'C','D','G','H','I' },{ 'K','O','P','Q','R' },{ 'T','V','W','X','Z' } };

int secondCharacterRowIndex = 0;
int secondCharacterColIndex = 0;
void printArray()
{
	cout << "Encode Pattern" << endl;
	cout << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << setw(10);
		for (int j = 0; j < 5; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}
bool isSecondCharacterInSameRow(int row, char character){
	for(int i = 0; i < 5; i++)
	{
		if(arr[row][i] == character){
			secondCharacterColIndex = i; 		// global variable
			return true;
		}
	}
	return false;
}
bool isSecondCharacterInSameColumn(int col, char character){
	for(int i = 0; i < 5; i++)
	{
		if(arr[i][col] == character){
			secondCharacterRowIndex = i;		// global variable
			return true;
		}
	}
	return false;
}
void replaceWithNextMost(int i, int j, string & str, int key){
	if(j < 4){
		str[key] = arr[i][j+1];
	}
	if(secondCharacterColIndex < 4){
		str[key+1] = arr[i][secondCharacterColIndex+1];
	}
	if(j == 4){
		str[key] = arr[i][0];
	}
	if(secondCharacterColIndex == 4){
		str[key+1] = arr[i][0];
	}
}
void replaceWithDownMost(int i, int j, string & str, int key){
	if(i < 4){
		str[key] = arr[i+1][j];
	}
	if(i == 4){
		str[key] = arr[0][j];
	}
	if(secondCharacterRowIndex < 4){
		str[key+1] = arr[secondCharacterRowIndex+1][j];
	}
	if(secondCharacterRowIndex == 4){
		str[key+1] = arr[0][j];
	}
}
void findSecondCharacterInSystem(char character){
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; j++){
			if(arr[i][j] == character){
				secondCharacterRowIndex = i;
				secondCharacterColIndex = j;
				return;
			}
		}
	}
}
void replaceRowColumnPattern(int i, int j, string & str, int key){
	//first character:
	str[key] = arr[i][secondCharacterColIndex];
	//second character:
	str[key+1] = arr[secondCharacterRowIndex][j];
}

void EncodeMessage( string & str)
{
	int key = 0;
	while(key < str.length()){
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if(arr[i][j] == str[key]){

					if(isSecondCharacterInSameRow(i,str[key + 1])){
						replaceWithNextMost(i, j, str, key);
            //break;
					}
					else if(isSecondCharacterInSameColumn(j, str[key + 1])){
						replaceWithDownMost(i, j, str, key);
						//cout << str << endl;
						//break;
					}else{
						findSecondCharacterInSystem(str[key+1]);
						replaceRowColumnPattern(i, j, str, key);
					}
					key += 2;
					i = 0;
				}
			}
		}
	}
}
void messageRules(){
	cout << "RULES TO TYPE A MESSAGE" << endl;
	cout << "1-	Message should be of even Length." << endl;
	cout << "2-	Message should'nt have repeting characters."<< endl << endl;
	cout << "Type a Message ...  " ;
}
void replacingIwithJ(string & str){
	for (int i = 0; i < str.length(); ++i)
	{
		if(str[i] == 'j'){
			str[i] = 'i';
			return;
		}
		if(str[i] == 'J'){
			str[i] = 'I';
			return;
		}
	}
}
void shiftToIUpperCaseLAtter(string & str){
	for(int i = 0; i < str.length(); i++){
		if(str[i] >= 'a' && str[i] <= 'z'){
			str[i] -= 32;
		}
	}
}
void validate(string & str){
	replacingIwithJ(str);
	shiftToIUpperCaseLAtter(str);
}
bool isValid(string & str){
	if(str.length() % 2 == 0){
		validate(str);
		return true;
	}
	return false;
}
int main()
{
	messageRules();
	string str ;
	getline(cin,str);
	if(isValid(str)){
		EncodeMessage(str);
	}
	else{
		cout << "Invalid" << endl;
	}
	cout << "Encoded Message ..  " << str << endl;

	return 0;
}
