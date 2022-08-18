#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"

using namespace std;

int main(int argc, char** argv)
{
	if (argc < 6)
	{
		cerr << "ERROR: not enough arguments";
		return -1;
	}
	// Open input file for read
	FILE * in;
	in = fopen(argv[4], "rb");
	if (in == NULL)
	{
		cerr << "ERROR: unable to open in file";
		return -1;
	}

	// Open output file for write
	FILE * out;
	out = fopen(argv[5], "a");
	if (in == NULL)
	{
		cerr << "ERROR: unable to open out file";
		fclose(in);
		return -1;
	}


	CipherInterface* cipher;
	string ciphername = argv[1];
	string encdec = argv[3];
	unsigned char* output;

	if (ciphername == "DES")
	{

		// Create cipher object
		cipher = new DES();
		if(!cipher)
		{
			fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",
			__FILE__, __FUNCTION__, __LINE__);
			fclose(in);
			fclose(out);
			exit(-1);
		}

		// Assign DES key
		cipher->setKey((unsigned char*)argv[2]);

		// Perform encryption
		if (encdec == "ENC")
		{
			int i = 0;
			int read = 0;
			unsigned char buffer[8]; // 8 byte blocks
			// read into buffer 8 bytes until read 0 bytes
			while ((read = fread(buffer, 1, 8, in)) > 0)
			{
				// if read less than 8 bytes, pad buffer
				for (i = read; i < 8; i++)
				{
					buffer[i] = ' ';
				}

				// encrypt here
				const unsigned char* input = buffer;

				unsigned char* plaintext = cipher->encrypt(input);

				//write to file
				fwrite(plaintext, 1, 8, out);

			}
		}

		else if (encdec == "DEC")
		{
			int i = 0;
			int read = 0;
			unsigned char buffer[8]; // 8 byte blocks

			// read into buffer 8 bytes until read 0 bytes
			while ((read = fread(buffer, 1, 8, in)) > 0)
			{
				// if read less than 8 bytes, pad buffer
				for (i = read; i < 8; i++)
				{
					buffer[i] = ' ';
				}

				// decrypt here
				const unsigned char* input = buffer;

				unsigned char* ciphertext = cipher->decrypt(input);

				//write to file
				fwrite(ciphertext, 1, 8, out);
			}
		}

		else
		{
			cerr << "ERROR: Invalid ENC/DEC input" << endl;
			fclose(in);
			fclose(out);
			return -1;
		}
	}

	else if (ciphername == "AES")
	{
		// Create cipher object
		cipher = new AES();
		if(!cipher)
		{
			fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",
			__FILE__, __FUNCTION__, __LINE__);
			fclose(in);
			fclose(out);
			exit(-1);
		}

		// Perform encoding or decoding
		if (encdec == "ENC")
		{
			// Assign AES key for encryption
			unsigned char key[17];
			key[0] = 0;
			for (int i = 0; i < 16; i++)
			{
				key[i + 1] = (unsigned char)argv[2][i];
			}
			cipher->setKey(key);

			// begin file read
			int i = 0;
			int read = 0;
			unsigned char buffer[16]; // 16 byte blocks
			// read into buffer 16 bytes until read 0 bytes
			while ((read = fread(buffer, 1, 16, in)) > 0)
			{
				// if read less than 16 bytes, pad buffer
				for (i = read; i < 16; i++)
				{
					buffer[i] = ' ';
				}

				// encrypt here
				unsigned char* plaintext = cipher->encrypt(buffer);

				//write to file
				fwrite(plaintext, 1, 16, out);
			}
		}
		else if (encdec == "DEC")
		{
			// Assign AES key for decryption
			unsigned char key[17];
			key[0] = 1;
			for (int i = 0; i < 16; i++)
			{
				key[i + 1] = (unsigned char)argv[2][i];
			}
			cipher->setKey(key);

			// begin file read
			int i = 0;
			int read = 0;
			unsigned char buffer[16]; // 16 byte blocks
			// read into buffer 16 bytes until read 0 bytes
			while ((read = fread(buffer, 1, 16, in)) > 0)
			{
				// if read less than 16 bytes, pad buffer
				for (i = read; i < 16; i++)
				{

					buffer[i] = ' ';
				}

				// decrypt here
				unsigned char* ciphertext = cipher->decrypt(buffer);

				//write to file
				fwrite(ciphertext, 1, 16, out);
			}
		}
		else
		{
			cerr << "ERROR: Invalid ENC/DEC input" << endl;
			fclose(in);
			fclose(out);
			return -1;
		}
	}
	else
	{
				cerr << "ERROR: Invalid cipher name" << endl;
				fclose(in);
				fclose(out);
				return -1;
	}

	// close files after successful run
	fclose(in);
	fclose(out);
	return 0;
}
