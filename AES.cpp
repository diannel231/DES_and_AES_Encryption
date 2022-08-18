#include "AES.h"

/**
 * Sets the key to use
 * @param key - the first byte of this represents whether
 * to encrypt or to decrypt. 00 means encrypt and any other
 * value to decrypt.  Then come the bytes of the 128-bit key
 * (should be 16 of them).
 * @return - True if the key is valid and False otherwise
 */
bool AES::setKey(const unsigned char* keyArray)
{

	unsigned char key[16];
	for (int i = 0; i < 16; i++)
	{
		key[i] = keyArray[i + 1];
	}

	//const static unsigned char key[]={0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF};
	if (keyArray[0] == 0)
	{
		//Set encryption key
		if(AES_set_encrypt_key(key, 128, &enc_key) !=0)
		{
			fprintf(stderr, "AES_set_encrypt_key() failed!\n");
			return false;
		}
	}
	else if(keyArray[0] == 1)
	{
		//set decryption key
		if(AES_set_decrypt_key(key, 128, &dec_key) != 0)
		{
			fprintf(stderr, "AES_set_decrypt_key() failed!\n");
			return false;
		}
	}
	else
	{
		fprintf(stderr, "Error: key formatted improperly");
		return false;
	}
	return true;
}

/**
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
unsigned char* AES::encrypt(const unsigned char* plaintext)
{
	// allocate block for ciphertext
	unsigned char* output = (unsigned char*)malloc(16 * sizeof(char));

	//encrypt here
	AES_ecb_encrypt(plaintext, output, &enc_key, AES_ENCRYPT);
	return output;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
unsigned char* AES::decrypt(const unsigned char* ciphertext)
{
	// allocate block for ciphertext
	unsigned char* output = (unsigned char*)malloc(16 * sizeof(char));

	//decrypt here
	AES_ecb_encrypt(ciphertext, output, &dec_key, AES_DECRYPT);

	return output;
}
