/*
The game logic (no direct user interaction).
The game is a simple guess the word game based
on the bull and cow count.
*/

#pragma once
#include <string>

//To make syntax Unreal friendly.
using FString = std::string;
using int32 = int;

struct FBCCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
};

class FBCGame
{
public:
	
	FBCGame();
	void Reset();
	int32 GetMaxTries() const;
	int32 GetCurrentTries() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuess(FString) const;
	FBCCount  SumbitGuess(FString);

private:
	int32 MyCurrentTries;
	FString MyHiddenWord;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
	bool bGameIsWon;
};