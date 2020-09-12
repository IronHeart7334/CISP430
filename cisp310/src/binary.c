#include "base.h"
#include "binary.h"
#include "baseConverter.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const char BIN_ALPHABET[] = {'0', '1'};
const int BIN_ALPHABET_SIZE = sizeof(BIN_ALPHABET) / sizeof(char);

int testBinary(){
    int ip1;
    int ip2;
    char* binStr1 = 0;
    char* binStr2 = 0;
    char* result = 0;

    printf("%s", "Enter a decimal integer: ");
    scanf("%d", &ip1);
    printf("%s", "Now enter another: ");
    scanf("%d", &ip2);
    printf("%d + %d = %d (in decimal)\n", ip1, ip2, ip1 + ip2);

    binStr1 = intToBinStr(ip1);//decimalIntToBase(ip1, 2);
    binStr2 = intToBinStr(ip2);//decimalIntToBase(ip2, 2);
    result = binaryAdd(binStr1, binStr2);
    printf("%s + %s = %s (in binary)\n", binStr1, binStr2, result);

    if(binStr1){
        free(binStr1);
        binStr1 = 0;
    }
    if(binStr2){
        free(binStr2);
        binStr2 = 0;
    }
    if(result){
        free(result);
        result = 0;
    }
    return 0;
}

int binCharToInt(char binChar){
    return charToInt(binChar, BIN_ALPHABET, BIN_ALPHABET_SIZE);
}
char intToBinChar(int i){
    return intToChar(i, BIN_ALPHABET, BIN_ALPHABET_SIZE);
}

char* newBinStr(){
    return newStr(SYS_ARCH, BIN_ALPHABET[0]);
}
int deleteBinStr(char** binStr){
    return delStr(binStr);
}

char* toBinStr(char* cString){
    return parseStr(cString, &newBinStr, &binCharToInt, &intToBinChar);
}

int binStrToInt(char* binStr){
    return strToInt(binStr, BIN_ALPHABET_SIZE, &binCharToInt);
}




char* intToBinStr(int val){
    char* ret = newBinStr();
    int maxDigitValue = 1;
    for(int i = 0; i < SYS_ARCH; i++){
        maxDigitValue *= 2;
    }
    maxDigitValue /= 2; // The value of the lefternmost bit is either 0 or 2^(SYS_ARCH - 1)
    int count;
    while(maxDigitValue > 0){
        break; // not done
    }
    return ret;
}



char* binaryAdd(char* binString1, char* binString2){
    char* ret = newBinStr();

    int sumBit = 0;
    int carryBit = 0;
    int val1;
    int val2;
    int sum;
    for(int i = SYS_ARCH - 1; i >= 0; i--){
        val1 = (binString1[i] == '0') ? 0 : 1;
        val2 = (binString2[i] == '0') ? 0 : 1;
        sum = val1 + val2 + carryBit;
        sumBit = sum % 2;
        carryBit = sum / 2;
        //printf("%c + %c + %d = sum %d, carry %d\n", binString1[i], binString2[i], carryBit, sumBit, carryBit);
        ret[i] = BIN_ALPHABET[sumBit];
    }

    if(carryBit == 1){
        printf("%s\n", "Carry bit is 1, so the sum is incorrect: not enough room!");
    }

    return ret;
}
