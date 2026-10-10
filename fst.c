#include <stdio.h>

unsigned int utf8char_encode(unsigned int n){
   if(n<0x007f){
      return n;
   }
   else if(n<=0x07ff){
      unsigned int fst_byte3=0b110<<13; //0x5
      unsigned int snd_byte2=0b10<<6;
      unsigned int fst_byte5=(n>>6)<<8;
      unsigned int snd_byte6=n&0x3f; //0x3f=63=0b11_1111
      return fst_byte3|fst_byte5|snd_byte2|snd_byte6;
   }
   else if(n<=0xffff){
      unsigned int fst_byte4=0b1110<<20; //0xe
      unsigned int snd_byte2=0b10<<14;
      unsigned int trd_byte2=0b10<<6;
      unsigned int fst_byte_4=(n>>12)<<16;
      unsigned int snd_byte6=((n>>6)&0x3f)<<8;
      unsigned int trd_byte6=n&0x3f;
      return fst_byte4|fst_byte_4|snd_byte2|snd_byte6|trd_byte2|trd_byte6;
   }
   else if(n<=0x10ffff){
      unsigned int fst_byte5=0b11110<<27; //0xf0
      unsigned int snd_byte2=0b10<<22;
      unsigned int trd_byte2=0b10<<14;
      unsigned int four_byte2=0b10<<6;
      unsigned int fst_byte3=n>>18;
      unsigned int snd_byte6=((n>>12)&0x3f)<<16;
      unsigned int trd_byte6=((n>>6)&0x3f)<<8;
      unsigned int four_byte6=n&0x3f;
      return fst_byte5|fst_byte3|snd_byte2|snd_byte6|trd_byte2|trd_byte6|four_byte2|four_byte6;
   }
   return 0;
}

unsigned int utf8char_decode(unsigned int n){
   if(n<=0x7f) return n;
   else if(n<=0x7ff){
      unsigned int byte=(((n>>8)&0x1f)<<6)|(n&0x3f);
      return byte;
   }
   else if(n<=0xffff){
      unsigned int byte=(((n>>16)&15)<<12)|(((n>>8)&0x3f)<<6)|(n&0x3f);
      return  byte;
   }
   else if(n<=0x10ffff){
      unsigned int byte=(((n>>24)&0x07)<<18)|(((n>>16)&0x3f)<<12)|(((n>>8)&0x3f)<<6)|(n&0x3f);
      return byte;
   }
   return 0;
}

void print_decoded_utf8char(unsigned int n);

void print_decoded_utf8char(unsigned int n){
   if(n<=0xff) putchar(n);
   else if(n<=0xffff){
      putchar(((n>>8)&0xff));
      putchar((n&0xff));
   }
   else if(n<=0xffffff){
      putchar((n>>16)&0xff);
      putchar((n>>8)&0xff);
      putchar(n&0xff);
   }
   else{
      putchar(((n>>24)&0xff));
      putchar(((n>>16)&0xff));
      putchar(((n>>8)&0xff));
      putchar(n&0xff);
   }
}

int main(){
  unsigned int encoded = 0xc4ad;
  unsigned int decoded = utf8char_decode(encoded);
  unsigned int encoded_str[]={0xc4ad,0xc49d,0xc4b5,0xea9fbe,0xeaa080,0xeaa7bb,0x00};
  print_decoded_utf8char(utf8char_encode(decoded));
  putchar('\n');
  for(int i=0;i<sizeof(encoded_str)/sizeof(unsigned int);i++){
     print_decoded_utf8char(utf8char_encode(utf8char_decode(encoded_str[i])));
  }
  putchar('\n');
  return 0;

}
