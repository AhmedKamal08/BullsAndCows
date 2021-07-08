// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
	 
    Super::BeginPlay();
	
	Isograms = GetVaildWords(Words);
	InitGame();
	PrintLine(TEXT("Guess the %i letter word"), Hiddenword.Len());

	
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	if (bGameOver)
	{
		ClearScreen();
		InitGame();

	}
	else
	{
		ProcessGuess(Input);
	}
}
void UBullCowCartridge::InitGame()
{
	PrintLine(TEXT("welcome  !"));
	Hiddenword = Isograms[FMath::RandRange(0, Isograms.Num()-1)];
	Lives = Hiddenword.Len();
	bGameOver = false;
	
	PrintLine(TEXT("You have %i lives"), Lives );
	PrintLine(TEXT("The number of words is : %i"), Words.Num());
	//PrintLine(TEXT("The hidden words is : %s"), *Hiddenword);

}

void UBullCowCartridge::EndGame()
{
	ClearScreen();
	bGameOver = true;
	
	PrintLine(TEXT("\npress enter to play again!"));

}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
	if (Guess == Hiddenword)
	{
		PrintLine(TEXT("You have won!"));
		EndGame();
		return;
	}

	if (Guess.Len() != Hiddenword.Len())
	{
		PrintLine(TEXT("Try again, you have %i livs left "), Lives);
		PrintLine(TEXT("the hidden word is %i long "), Hiddenword.Len());
		return;
	}

	 if (!isIsogram(Guess))
	{
		 PrintLine(TEXT("no rpeated letters , try again "));
		 return;
	 } 

	--Lives;
	PrintLine(TEXT("You lost a life"));
	PrintLine(TEXT("%i"), Lives);
	

	if (Lives<= 0)
	{
		PrintLine(TEXT("the hidden word was %s "), *Hiddenword);
		PrintLine(TEXT("You have no lives"));
		EndGame();
		return;

	}

	int32  bulls = 0;
	int32  cows = 0;
	GetBullCows(Guess, bulls, cows);
	PrintLine(TEXT(" you have %i Bulls and %i Cows"), bulls ,cows);
	PrintLine(TEXT("Guess again, you have %i livs left "), Lives);

}

bool UBullCowCartridge::isIsogram(const FString& Guess)
{
	
	for (size_t i = 0; i < Guess.Len(); i++)
	{ 

		 
		for (size_t j = i+1; j < Guess.Len(); j++)
		{
			if (Guess[i] == Guess[j]) {
				return false;
			}
		}

	}

	return true;
}

TArray<FString> UBullCowCartridge::GetVaildWords(const TArray<FString>& WordList)
{
	TArray<FString> ValidWords;
	for (FString Word : WordList)
	{
		if (Word.Len() >=4 && Word.Len()<=8 && isIsogram(Word))
		{
			ValidWords.Emplace(Word);
		}
	}

	return ValidWords;
}

void UBullCowCartridge::GetBullCows(const FString& guess, int32& BullCount, int32& CowCount) const
{
	 
	for (int32 i = 0; i < guess.Len(); i++)
	{
		if (guess[i] == Hiddenword[i]) {
			BullCount++;
			continue;
		}
		for (int32 hiddenIndex = 0; hiddenIndex < Hiddenword.Len(); hiddenIndex++)
		{
			if (guess[i] == Hiddenword[hiddenIndex]) {
				CowCount++;
				break;
			}
		}
	}
}

 

 