#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEST_STRING_LENGTH      100

#ifdef ENABLE_DEBUG_PRINT
#define PRINT printf
#else
#define PRINT
#endif

unsigned char charToHexChar(unsigned char ch)
{	
	if (ch <= 'F' && ch >= 'A')  {
		return (ch - 'A') + 10;
	} else if (ch <= 'f' && ch >= 'a') {
		return (ch - 'a') + 10;
	} else if (ch <= '9' && ch >= '0') {
		return  (ch - '0');
	} else {
		PRINT("unknow character 0x%x", ch);
		return 0xFF;
	}
}


char stringToHexString(unsigned char *pSrcStr, unsigned int len, unsigned char *pDestStr, unsigned int *pOutLen)
{
	if ((len <= 0) && (len % 2 != 0)) {
		return -1;
	}

	// check string to sure it is hex string
	for(int i = 0; i < len; i++) {
		if (0xFF == charToHexChar(pSrcStr[i])) {
			PRINT("input string not hex string, please check it!");
			return -1;
		}
	}

	//cover to hex
	for(int i = 0; i < len; i+=2) {

		pDestStr[i/2] = charToHexChar(pSrcStr[i]) * 16 + charToHexChar(pSrcStr[i+1]);
	}

	// output hex string
	printf("Dest Hex String : 0x");
	*pOutLen = len/2;
	for(int i = 0; i < *pOutLen; i++) {
		printf("%02X", pDestStr[i]);
	}

	return 0;
}


int main(int argc, char* argv[]) 
{
	unsigned char destStr[MAX_DEST_STRING_LENGTH] = {0xFF};
	unsigned int destStrLen = 0;

	if(argc < 1) {
		PRINT("Using as: 'C00100080000010000FF02'\n");
		return -1;
	} else {
		PRINT("argc %d, len %d: ", argc, strlen(argv[1]));
		for(int i = 0; i < strlen(argv[1]); i++) {
			PRINT("%C", argv[1][i]);
		}
		PRINT("\r\n");
	}

	if(-1 == stringToHexString((unsigned char *)argv[1], strlen(argv[1]), destStr, &destStrLen)) {
		PRINT("conveter failed!");
		return -1;
	}
	
}