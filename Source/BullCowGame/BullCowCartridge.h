// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void InitGame();
	void EndGame();
	void ProcessGuess(const FString& Guess);
	bool isIsogram(const FString& Guess);
	TArray<FString> GetVaildWords(const TArray<FString>&  ) ;
	void GetBullCows(const FString& guess, int32& BullCount, int32& CowCount) const;
	
	
	// Your declarations go below!
	private:
	FString Hiddenword;
	int32 Lives;
	bool bGameOver;
	TArray<FString> Isograms;
};
