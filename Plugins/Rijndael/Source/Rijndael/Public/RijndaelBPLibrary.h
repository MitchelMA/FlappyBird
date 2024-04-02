// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "RijndaelBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class RIJNDAEL_API URijndaelBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	static uint8 PadByte;
	static int32 IvLength;
	static int32 KeyLength;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Rijndael")
	static int32 ObjectMemSize();

	UFUNCTION(BlueprintCallable, Category = "Rijndael")
	static void GenIv(TArray<uint8>& Iv);

	UFUNCTION(BlueprintCallable, Category = "Rijndael")
	static void GenKey(TArray<uint8>& Key);

	UFUNCTION(BlueprintCallable, Category = "Rijndael")
	static void Encrypt(const FString& PlainText, const FString& Key, bool& Success, TArray<uint8>& CipherBytes);

	UFUNCTION(BlueprintCallable, Category = "Rijndael")
	static void Decrypt(const TArray<uint8>& CipherBytes, const FString& Key, bool& Success, FString& PlainText);

private:
	static void PrependString(FString& Text, const uint8* Iv);
	static void RemovePrepend(FString& Text);
};
