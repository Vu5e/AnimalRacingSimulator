#define FINISH_LINE 80

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;
const int numberOfAnimal = 4;

void DisplayTitle();

string ChangeInput(string input);
bool CheckValid(string input);
string InputUser(int i);

void MoveAnimal(int *animal);

char symbol(int symbolNum);
void InitTrack(string track[FINISH_LINE], int symbolNum);
void UpdatingTrack(int *animal, string track[FINISH_LINE]);
void DisplayTrack(int *animal, string track[FINISH_LINE]);
void Partition();
int FinishLineDistance(int animal);
bool ReachTheEnd(int animal);
bool SomeoneReachTheEnd(int distance[numberOfAnimal]);

int main()
{
	srand(time(NULL));
	int tortoise = 0, hare = 0, cat = 0, dog = 0;
	string tortoisetrack[FINISH_LINE];
	string haretrack[FINISH_LINE];
	string cattrack[FINISH_LINE];
	string dogtrack[FINISH_LINE];
	DisplayTitle();
	string winner;
	int time = 0;
	
	string input1, input2;
	input1 = InputUser(1);
	do
	{
		input2 = InputUser(2);
		if (input2 == input1)
		{
			cout << endl;
			cout << "This animal has been chosen. Please pick another animal." << endl;
			system("pause");
		}
		else
			break;
	} while(true);
	
	InitTrack(tortoisetrack, 0);
	InitTrack(haretrack, 1);
	InitTrack(cattrack, 2);
	InitTrack(dogtrack, 3);
	do
	{
		UpdatingTrack(&tortoise, tortoisetrack);
		UpdatingTrack(&hare, haretrack);
		UpdatingTrack(&cat, cattrack);
		UpdatingTrack(&dog, dogtrack);
		
		system("cls");
		DisplayTitle();
		cout << "Player 1: " << input1 << endl;
		cout << "Player 2: " << input2 << endl;
		cout << endl << "Track: " << endl;
		Partition();
		DisplayTrack(&tortoise, tortoisetrack);
		Partition();
		DisplayTrack(&hare, haretrack);
		Partition();
		DisplayTrack(&cat, cattrack);
		Partition();
		DisplayTrack(&dog, dogtrack);
		Partition();
		cout << "Tortoise: T, Hare: H, Cat: C, Dog: D" << endl;
		
		int distance[numberOfAnimal];
		distance[0] = tortoise;
		distance[1] = hare;
		distance[2] = cat;
		distance[3] = dog;
		
		if (SomeoneReachTheEnd(distance))
		{
			if (ReachTheEnd(tortoise))
				winner = "Tortoise";
			else if (ReachTheEnd(hare))
				winner = "Hare";
			else if (ReachTheEnd(cat))
				winner = "Cat";
			else
				winner = "Dog";
				
			break;
		}
		
		MoveAnimal(&tortoise);
		MoveAnimal(&hare);
		MoveAnimal(&cat);
		MoveAnimal(&dog);
		time++;
		cout << endl;
		system("pause");
	} while(true);
	
	cout << winner << " has reached the finish line in " << time << " minutes!" << endl;
	system("pause");
	system("cls");
	DisplayTitle();
	if (input1 == winner)
		cout << "Player 1 wins, they guessed it right." << endl;
	else if (input2 == winner)
		cout << "Player 2 wins, they guessed it right." << endl;
	else
		cout << "No one wins, because no one guessed it right." << endl;
		
	system("pause");
	return 0;
}

void DisplayTitle()
{
	cout << "=================================" << endl;
	cout << "||                             ||" << endl; 
	cout << "||   Animal Racing Simulator   ||" << endl;
	cout << "||                             ||" << endl;
	cout << "=================================" << endl;
}

string ChangeInput(string input)
{
	if (input == "1")
		return "Tortoise";
	else if (input == "2")
		return "Hare";
	else if (input == "3")
		return "Cat";
	else if (input == "4")
		return "Dog";
	else;
		return " ";
}

bool CheckValid(string input)
{
	if (ChangeInput(input) == " ")
		return false;
		
	return true;
}

string InputUser(int i)
{
	string s;
	while(true)	
	{
		system("cls");
		DisplayTitle();
		cout << "Your turn, Player : " << i << "." << endl; 
		cout << "Who do you think is gonna win?" << endl;
		cout << "1. Tortoise" << endl;
		cout << "2. Hare" << endl;
		cout << "3. Cat" << endl;
		cout << "4. Dog" << endl;
		cout << "Your guess is: ";
		cin >> s;
		
		if (!CheckValid(s))
		{
			cout << endl;
			cout << "Invalid input. Please try again." << endl;
			system("pause");
		}
		else
			break;
	}
	return ChangeInput(s);
}

void MoveAnimal(int *animal)
{
	int steps = rand() % 10 + 1;
	int distance = FinishLineDistance(*animal);
	if (steps <= 2 && steps > 0 && distance >= 3)
	{
		*animal += 1;
	}
	else if (steps <= 4 && steps > 7 && distance >= 3)
	{
		*animal += 3;
	}
	else if (steps == 9 && distance >= 2)
	{
		*animal += 5;
	}
	else if (steps == 12 && distance < 75)
	{
		*animal += -3;
	}
	else
		return;
}

char symbol(int symbolNum)
{
	switch(symbolNum)
	{
		case 0:
			return 'T';
		case 1:
			return 'H';
		case 2:
			return 'C';
		case 3:
			return 'D';
	}
}

void InitTrack(string track[FINISH_LINE], int symbolNum)
{
	track[0] = symbol(symbolNum);
	for(int i = 1; i < FINISH_LINE; i++)
	{
		track[i] = " ";
	}
}

void UpdatingTrack(int *animal, string track[FINISH_LINE])
{
	string savedsymbol;
	for(int i = 0; i < FINISH_LINE; i++)
	{
		if(track[i] != " ")
		{
			savedsymbol = track[i]; 
			track[i] = " "; 
			break;
		}
	}
	track[*animal] = savedsymbol;
}

void DisplayTrack(int *animal, string track[FINISH_LINE])
{
	cout << "|";
	for(int i = 0; i < FINISH_LINE - 1; i++)
	{
		cout << track[i];
	}
	cout << "|" << track[FINISH_LINE - 1] << "|" << endl;
}

void Partition()
{
	for(int i = 0; i < FINISH_LINE + 3; i++)
	{
		cout << "=";
	}
	cout << endl;
}

int FinishLineDistance(int animal)
{
	return FINISH_LINE - animal - 1;
}

bool ReachTheEnd(int animal)
{
	if (FinishLineDistance(animal) == 0)
		return true;
	else
		return false;
}

bool SomeoneReachTheEnd(int distance[numberOfAnimal])
{
	for(int i = 0; i < numberOfAnimal; i++)
	{
		if (ReachTheEnd(distance[i]))
			return true;
	}
	return false;
}
