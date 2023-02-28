/*
VIKRANT KUMAR - 101195442

This program encrypts plaintext to ciphertext and decrypts ciphertext to plaintext using a secret key. It will help in perventing eneimes from easily cracking encrypted messages.
*/

#include <stdio.h>
#include <string.h>

#define MAX_BUF  256
#define IV 0b11001011

void encode(unsigned char*pt, unsigned char*ct, unsigned char k);
void decode(unsigned char*ct, unsigned char*pt, unsigned char k, int numBytes);

unsigned char computeKey(unsigned char partial);
unsigned char encryptByte(unsigned char src, unsigned char);
unsigned char decryptByte(unsigned char ct, unsigned char k);
unsigned char setTextByte(unsigned char Byte, unsigned char k);
unsigned char byteShift(unsigned char byte, unsigned char shift, unsigned char dir);

unsigned char getBit(unsigned char, int);
unsigned char setBit(unsigned char, int);
unsigned char clearBit(unsigned char, int);

int main(){

  char str[8];
  int  choice;
  int findValue;
  unsigned char arraySize = 0;
  unsigned char key;
  unsigned char pt[MAX_BUF];
  unsigned char ct[MAX_BUF];

  printf("\nYou may:\n");
  printf("  (1) Encrypt a message \n");
  printf("  (2) Decrypt a message \n");
  printf("\n  what is your selection: ");
  fgets(str, sizeof(str), stdin);
  sscanf(str, "%d", &choice);

  switch (choice) {

    case 1: 
      //Get user input for key
      printf("Enter the partial key(1-15):");
      fgets(str, sizeof(str), stdin);
      sscanf(str, "%hhd", &key);
      if(key>=16|key<=0){
         printf("\nInvalid Key\n");
         break;
      }
      else{
         key = computeKey(key); 
      }
        
      //Get user input for plaintext
      printf("\nEnter plaintext: \n");
      fgets((char*)pt, sizeof(pt), stdin);
    	
      //Print out the ciphertext
      printf("\nCiphertext: \n");
      encode(pt,ct,key);
      for(int i=0; i<strlen(pt);++i){
        printf("%03d ",ct[i]); 
      }
        printf("\n");
      break;

    case 2:
      //Get user input for key
      printf("Enter the partial key(1-15):");
      fgets(str, sizeof(str), stdin);
      sscanf(str, "%hhd", &key);
      if(key>=16|key<=0){
         printf("\nInvalid Key\n");
         break;
      }
      else{
         key = computeKey(key); 
      }
        
      //Get user input for ciphertext
      printf("\nEnter ciphertext: \n");
      while(findValue != -1){
        scanf("%d",&findValue);
        ct[arraySize]=findValue;
        arraySize++;
      }  
	   
      //Print out the plaintext 
      printf("\nPlaintext: \n");
      arraySize = arraySize-1;
      decode(ct,pt,key,arraySize);
      for(int i=0; i<arraySize;++i){
        printf("%c",pt[i]); 
      }
      printf("\n");
      break;
      
    default:
      printf("\nInput is invalid. \n\n");
      break;
  }
  return 0;
}

/*
  Function:  computeKey
  Purpose:   to compute for the key
       in:   partial key entered by user
   return:   the computed key
*/
unsigned char computeKey(unsigned char partial){
  int index;

  for(int i=0;i<4;++i){
     index = 7;
     if(getBit(partial,i)==1){
        partial = setBit(partial,index-i);
     }
     else{
        partial = clearBit(partial,index-i);
     }
  }
  return partial;
}
	
/*
  Function:  encode
  Purpose:   using a key it encrypts a plaintext byte
       in:   plaintext array that needs to be encrypted
       in:   ciphertext array that stores the encrypted bytes
       in:   key to encrypt byte
      out:   array of ciphertext byte that was encrpyted by key
*/	
void encode(unsigned char*pt, unsigned char*ct, unsigned char k){
  unsigned char src;
  unsigned char encrypted;
  int index = 0;

  for(int i=0;i<strlen(pt); ++i){    	    
     if(i == 0 ){
       src = pt[i]^IV;
     }
     else{
       src = pt[i]^ct[index];
       index++;
     }
     encrypted = encryptByte(src,k);
     ct[i] = encrypted;
  }
}

/*
  Function:  decode
  Purpose:   using a key it decrypts a ciphertext byte
       in:   ciphertext array that needs to be decrypted
       in:   plaintext array that stores the decrypted bytes
       in:   key to decrypt byte
      out:   array of plaintext byte that was decrpyted by key
*/
void decode(unsigned char*ct, unsigned char*pt, unsigned char k, int numBytes){
  unsigned char src;
  unsigned char decrypted;
  int index = 0;
   
  for(int i=0;i<numBytes; ++i){ 
    src = ct[i];  	    
    decrypted = decryptByte(src,k);
    pt[i] = decrypted;
     
    if(i == 0){
      pt[i] = pt[i]^IV;
    }
    else{
      pt[i] = pt[i]^ct[index];
      index++;
    }
  }
}

/*
  Function:  encryptByte
  Purpose:   using a key it encrypts a byte
       in:   character in which byte will be encrypted
       in:   key to encrypt byte
   return:   ciphertext byte that was encrpyted
*/
unsigned char encryptByte(unsigned char src, unsigned char k){
  unsigned char cipherByte = 0;
  unsigned char byte;
 
  unsigned char bitOne = getBit(src,7);
  unsigned char bitTwo = getBit(src,6);
   
  byte = byteShift(src,2,'l');
   
  if(bitOne == 1){
    byte = setBit(byte,1);
  }
  if(bitTwo == 1){
    byte = setBit(byte,0);
  }
   
  cipherByte = setTextByte(byte,k); 
 
  return cipherByte;
}	
	
/*
  Function:  decryptByte
  Purpose:   using a key it decrypts a byte
       in:   character in which byte will be decrypted
       in:   key to decrypt byte
   return:   plaintext byte that was decrpyted
*/	
unsigned char decryptByte(unsigned char ct, unsigned char k){
  unsigned char plainByte = 0;

  plainByte = setTextByte(ct,k);
 
  unsigned char bitOne = getBit(plainByte,0);
  unsigned char bitTwo = getBit(plainByte,1);
   
  plainByte = byteShift(plainByte,2,'r');
   
  if(bitOne == 1){
     plainByte = setBit(plainByte,6);
  }
  if(bitTwo == 1){
     plainByte = setBit(plainByte,7);
  }
  return plainByte;
}	

/*
  Function:  byteShift
  Purpose:   shifts right or left
       in:   byte to shift 
       in:   number to shift by
       in:   direction to shift
      out:   shifted byte
*/
unsigned char byteShift(unsigned char byte, unsigned char shift, unsigned char dir){
  if(dir == 'r'| dir=='R'){
     byte = (byte >> shift);
  }
  if(dir == 'l'| dir=='L'){
     byte = (byte << shift);
  }
  return byte;
}
	
/*
  Function:  setTextByte
  Purpose:   set plain or cipher text byte from performing XOR operation
       in:   character in which byte will be set too
       in:   key perform XOR operation with
   return:   plain or cipher text byte
*/
unsigned char setTextByte(unsigned char Byte, unsigned char k){
  unsigned char computedBit;
  int index = 7;

  for(int x=0; x<8;++x){
    computedBit = getBit(Byte,x)^getBit(k,index);
    if(computedBit == 1){
       Byte = setBit(Byte,x);
    }
    else{
       Byte = clearBit(Byte,x);
    }
    index--; 
  }
  return Byte;
}

/*
  Function:  getBit
  Purpose:   retrieve value of bit at specified position
       in:   character from which a bit will be returned
       in:   position of bit to be returned
   return:   value of bit n in character c (0 or 1)
*/
unsigned char getBit(unsigned char c, int n){ 
  return ((c &(1<<n))>>n);
}

/*
  Function:  setBit
  Purpose:   set specified bit to 1
       in:   character in which a bit will be set to 1
       in:   position of bit to be set to 1
   return:   new value of character c with bit n set to 1
*/
unsigned char setBit(unsigned char c, int n){ 
  return c | (1<<n);
}

/*
  Function:  clearBit
  Purpose:   set specified bit to 0
       in:   character in which a bit will be set to 0
       in:   position of bit to be set to 0
   return:   new value of character c with bit n set to 0
*/
unsigned char clearBit(unsigned char c, int n){ 
  return c & (~(1<<n));
}

//DONE//
