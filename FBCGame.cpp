#pragma once

#include "FBCGame.h"
#include <map>
#define TMap std::map	//To make syntax Unreal friendly.

FBCGame::FBCGame()	//Default Constructor
{
	Reset();
}
	
void FBCGame::Reset()
{
	const FString HIDDEN_WORD = "tyres";	//This must be an Isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTries = 1;
	bGameIsWon = false;
	return;
}

int32 FBCGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,5}, {5,6}, {6,10}, {7,12}, {8,16} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBCGame::GetCurrentTries() const
{
	return MyCurrentTries;
}

int32 FBCGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBCGame::IsGameWon() const
{
	return bGameIsWon;
}

bool FBCGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1)
	{
		return true;
	}
	TMap<char, bool> LetterSeen;	//Creates a map to check whether a letter is repeated or not.
	for (auto Letter : Guess)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBCGame::IsLowerCase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter))
			return false;
	}
	return true;
}

EGuessStatus FBCGame::CheckGuess(FString Guess) const
{
	if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else
	{
		return EGuessStatus::OK;
	}
}
	
FBCCount FBCGame::SumbitGuess(FString Guess)
{
	MyCurrentTries++;
	FBCCount Count;
	int32 WordLength = MyHiddenWord.length();
	
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
					Count.Bulls++;
				else
					Count.Cows++;
			}
		}
	}
	if (Count.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return Count;
}