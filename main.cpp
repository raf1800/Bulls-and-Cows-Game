/*
This is the console executable , that makes use of the BullCow Class.
This acts as the view in a MVC pattern, and is responsible for all
user interactions. For game logic, please refer to the BullCow Class.
*/

#pragma once

#include <iostream>
#include <string>
#include <stdlib.h>
#include "FBCGame.h"

//To make syntax Unreal friendly.
using FText = std::string;
using int32 = int;

void PrintIntro();
FText GetValidGuess();
void PlayGame();
void PrintGameSummary();
bool AskAgain();

FBCGame BCGame;	//Instantiate a new game which is re-used across all plays.

//The entry point for the application
int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskAgain());
	return 0;	//Exit the application
}

void PrintIntro()
{
	system("CLS");
	std::cout << "Welcome to Bulls and Cows!\n" << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "\nCan you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
}

//Checks whether entered guess is valid or not.
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid;
	FText Guess = "";
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTries();
		std::cout << "\nTry " << CurrentTry << " of " <<BCGame.GetMaxTries()<< ".\nEnter your guess: ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuess(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an Isogram.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all letters in lowercase.\n";
			break;
		default:
			return Guess;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}


//Plays a single game to completion.
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	constexpr int32 NumberOfTurns = 5;
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTries() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		FBCCount Count = BCGame.SumbitGuess(Guess);	
		std::cout << "Bulls: " << Count.Bulls;
		std::cout << "\tCows: " << Count.Cows << std::endl;
	}
	PrintGameSummary();
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "\nWELL DONE. YOU FOUND THE WORD!!\n";
	}
	else
	{
		std::cout << "\nBetter luck next time\n";
	}
}

bool AskAgain()
{
	FText Response = "";
	std::cout << "\nDo you want to play again with the same hidden word? ";
	std::getline(std::cin, Response);
	if (Response[0] == 'y' || Response[0] == 'Y')
		return true;
	else
	{
		std::cout << "Good bye!\n";
		return false;
	}
}
