#include "RijndaelBPLibrary.h"
#include "rijndael_exports.h"

uint8 URijndaelBPLibrary::PadByte = 1;
int32 URijndaelBPLibrary::IvLength = 16;
int32 URijndaelBPLibrary::KeyLength = 32;

int32
URijndaelBPLibrary::ObjectMemSize()
{
	return rijndael_get_mem_size();
}

void
URijndaelBPLibrary::GenIv(
	TArray<uint8>& Iv
)
{
	Iv.Init(0, IvLength);
	rijndael_gen_iv(Iv.GetData());
}

void
URijndaelBPLibrary::GenKey(
	TArray<uint8>& Key
)
{
	Key.Init(0, KeyLength);
	rijndael_gen_key(Key.GetData());
}

void
URijndaelBPLibrary::Encrypt(
	const FString& PlainText,
	const FString& Key,
	bool& Success,
	TArray<uint8>& CipherBytes
)
{
	FString PlainCopy = PlainText;

	FString KeyCopy = Key;
	while (KeyCopy.Len() < KeyLength)
		KeyCopy += '0';

	uint8 KeyBytes[32] = {0};
	uint8 IvBytes[16] = {0};

	StringToBytes(KeyCopy, KeyBytes, KeyLength);
	rijndael_gen_iv(IvBytes);

	PrependString(PlainCopy, IvBytes);

	int32 EncryptionLength = PlainCopy.Len();
	CipherBytes.Init(0, EncryptionLength);
	StringToBytes(PlainCopy, CipherBytes.GetData(), EncryptionLength);

	auto RHandle = rijndael_ctor();
	rijndael_encrypt(
		RHandle,
		CipherBytes.GetData(), &EncryptionLength,
		IvBytes,
		KeyBytes, 32,
		CipherBytes.GetData());
	rijndael_dtor(RHandle);
	Success = EncryptionLength >= 0;
}

void
URijndaelBPLibrary::Decrypt(
	const TArray<uint8>& CipherBytes,
	const FString& Key,
	bool& Success,
	FString& PlainText
)
{
	FString KeyCopy = Key;
	while(KeyCopy.Len() < KeyLength)
		KeyCopy += '0';

	uint8 KeyBytes[32] = {0};
	uint8 IvBytes[16] = {0};
	int32 CipherLength = CipherBytes.Num();

	StringToBytes(KeyCopy, KeyBytes, KeyLength);
	rijndael_gen_iv(IvBytes);

	TArray<uint8> PlainBytes;
	PlainBytes.Init(0, CipherLength);

	auto RHandle = rijndael_ctor();
	rijndael_decrypt(
		RHandle,
		CipherBytes.GetData(), &CipherLength,
		IvBytes,
		KeyBytes, 32,
		PlainBytes.GetData());
	rijndael_dtor(RHandle);

	if (CipherLength < 0)
	{
		Success = false;
		return;
	}

	PlainText = BytesToString(PlainBytes.GetData(), CipherLength);
	RemovePrepend(PlainText);
	Success = true;
}

void
URijndaelBPLibrary::PrependString(
	FString& Text,
	const uint8* Iv
)
{
	FString Prepend = BytesToString(Iv, IvLength);

	const int32 CurrentLength = Text.Len() + IvLength;
	const int32 IvMod = CurrentLength % IvLength;
	const int32 Addition = (IvMod != 0) * (IvLength - IvMod);

	for (int32 i = 0; i < Addition; i++)
		Prepend.AppendChar(PadByte);
		
	Prepend.Append(Text);
	Text = Prepend;
}

void
URijndaelBPLibrary::RemovePrepend(
	FString& Text
)
{
	int32 TotalSkip = IvLength;
	for (; Text[TotalSkip] == PadByte; TotalSkip++) {}

	Text.RemoveAt(0, TotalSkip);
}

