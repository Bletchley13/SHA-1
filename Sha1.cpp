/*
* file: 9617049_2.c
* -----------------
* this file implement...
*/
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <iomanip>
using namespace std;
/* define the test strings */
#define TESTA "cry"
#define TESTB "artisaliethatmakesusrealizedthetruthbymarcusmauriceartis"
/* private function prototypes */
unsigned int M[100][80]={0};
int M_index=0;
static int SHA1(const unsigned char *testStr,
unsigned length);
void SHA1_PAD(const unsigned char *testStr,unsigned length);

unsigned int FT(unsigned int B,unsigned int C,unsigned int D,int t)
{
         //use different function depand on t
         if(t<20)return (B&C)|((~B)&D);
         if(t<40)return B^C^D;
         if(t<60)return (B&C)|(B&D)|(C&D);
         else return B^C^D;
}

unsigned int ROTL(unsigned int x,int y)//X rotate left y¦ì 
{
         //cout << x << endl; 
         //use 8 bit as example:
         // x =01234567 y=2
         // x<<y      x=23456700
         // x>>(8-y)  x=00000001
         //          x'=23456700
                     
         x=(x<<y)|(x>>(32-y));
         //cout << x << endl;
         return x;
} 


/* main program */
int main(void)
{
/* perform the test string A */
//cout  <<hex<< (0x000C ^ 0x000A)  << endl;
printf("(1) ");
SHA1((const unsigned char *) TESTA, strlen(TESTA));
/* output the 160-bit message digest in the hexadecimal format */
/* perform the test string B */
printf("(2) ");
SHA1((const unsigned char *) TESTB, strlen(TESTB));
/* output the 160-bit message digest in the hexadecimal format */
//system("pause");
return 0;
}
/*
* function: SHA1
* usage: SHA1(...);
* ----------------------------------
* this function implements the SHA-1 algorithm,...
*/
void SHA1_PAD(const unsigned char *testStr,unsigned length)
{
    
    
    //cout << length << endl;
    int index;//index of testStr
    
    //put all the input data in M
    for(index=0;M_index*16+index<=length/4;index++)
    {
            //4n char put into bit 31~24                                       
            if(4*index<length)M[M_index][index]=testStr[4*index]<<24;
            //4n+1 char put into bit 23~16
            if(4*index+1<length)M[M_index][index]=M[M_index][index]| testStr[4*index+1]<<16;
            //4n char put into bit 15~8
            if(4*index+2<length)M[M_index][index]=M[M_index][index]| testStr[4*index+2]<<8;
            //4n char put into bit 7~0
            if(4*index+3<length)M[M_index][index]=M[M_index][index]| testStr[4*index+3];
            //if index=16,means we uae all the m in this block
            //move to next block
            if(index==16){index=0;M_index++;}
    }
    index--;
    //pad 1 
    M[M_index][index]=M[M_index][index]| ((0x80) << (3-length%4)*8);
    
    long long int bitlen= length*8;
    //if we don't have two word left for d(string length)
    //we must to make new 512 bit block
    if(index%16>=14)
               M_index++;
   
   //set d into the last two word in block
   M[M_index][14]= bitlen>>32;
   M[M_index][15]= bitlen;
    
    //for(int j=0;j<=M_index;j++)
    //{
    //        for(int i=0;i<16;i++)
    //                cout <<hex<< M[j][i]<<" ";
    //        cout << endl;
    //}
    
}

void SHA1_HASH()
{
     
    //for(int j=0;j<=M_index;j++)
    //{
    //        for(int i=0;i<16;i++)
    //                cout <<hex<< M[j][i]<<" ";
    //        cout << endl;
    //} 
    //initial hash value 
    unsigned int H0=0x67452301;
    unsigned int H1=0xEFCDAB89;
    unsigned int H2=0x98BADCFE;
    unsigned int H3=0x10325476;
    unsigned int H4=0xC3D2E1F0;
    //set the keys
    unsigned int K[4]={0x5A827999,0x6ED9EBA1,0x8F1BBCDC,0xCA62C1D6};
    unsigned int A;
    unsigned int B;
    unsigned int C;
    unsigned int D;
    unsigned int E;
    for(int i=0;i<=M_index;i++)
    {
            for(int t=16;t<80;t++)
               M[i][t]=ROTL(M[i][t-3]^M[i][t-8]^M[i][t-14]^M[i][t-16],1);
            A=H0;
            B=H1;
            C=H2;
            D=H3;
            E=H4;
            
            for(int t=0;t<80;t++)
            {
               unsigned int temp=(ROTL(A,5)+FT(B,C,D,t)+E+M[i][t]+K[t/20]);
               E=D;
               D=C;
               C=ROTL(B,30);
               B=A;
               A=temp;
            }
            
            H0+=A;
            H1+=B;
            H2+=C;
            H3+=D;
            H4+=E;
                
    }
    //let output in hex and uppercase
    cout <<setiosflags (ios_base::uppercase);
    cout << hex << H0 << H1 << H2 << H3 << H4 << endl;
    //ROTL(0xf0000000,1);
}

void SHA_INIT()
{
     for(int i=0;i<100;i++)
        for(int j=0;j<80;j++)
          M[i][j]=0;
}

int SHA1( const unsigned char *testStr,
unsigned length)
{
/* please add your code here */
   
   SHA_INIT();
   SHA1_PAD(testStr,length);
   SHA1_HASH();
    
   
return 0;
}
