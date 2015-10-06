#include <SPI.h>

#include "MAX78615_LMU.h"
#define READ 0
#define WRITE 1
#define MISO 12
#define MOSI 11
#define CLK  13

#define CS_LOW() digitalWrite(cs, LOW)
#define CS_HIGH() digitalWrite(cs, HIGH)
#define SPI_XMIT(byte) SPI.transfer(byte)
 
void send_control_byte(u8 additional_rw, u8 word_addr, u8 rw);
  u8 read_byte(void);
void write_byte(u8 byte);

MAX78615_LMU::MAX78615_LMU() 
{
   int default_chip_sel = 7;
   init(default_chip_sel); 
}  

MAX78615_LMU::MAX78615_LMU(int chip_sel) { init(chip_sel); }  
  
void MAX78615_LMU::init(int cs)
{
   this->cs = cs;
   pinMode(cs, OUTPUT);
   configure_spi();
   SPI.begin();
   CS_HIGH();   
}

void MAX78615_LMU::configure_spi()
{
   SPI.setBitOrder(MSBFIRST);
   SPI.setClockDivider(SPI_CLOCK_DIV16);
   SPI.setDataMode(SPI_MODE3);
}

void MAX78615_LMU::read_registers(u8 word_addr, u8 words_to_read, u32 words[])
{
   u8 additional_rw, i;
   u8 * parts_of_word;
     
   if (words_to_read < 1) return;
   
   CS_LOW();
   additional_rw = words_to_read - 1;
   send_control_byte(additional_rw, word_addr, READ);
   
   i = 0;
   while(words_to_read > 0)
   {
      parts_of_word = (u8 *) (words + i);
      parts_of_word[2] = read_byte();
      parts_of_word[1] = read_byte();
      parts_of_word[0] = read_byte();
      words_to_read--;
      i++;
   }
   CS_HIGH();
}

u32 MAX78615_LMU::read_register(u8 word_addr)
{
   u32 ret = 0;
   read_registers(word_addr, 1, &ret);
   return ret;
}

void MAX78615_LMU::write_registers(u8 word_addr, u8 words_to_write, u32 words[])
{
   u8 additional_rw, rw, i;
   u8 * parts_of_word;
   
   if (words_to_write < 1) return;
   
   CS_LOW();
   additional_rw = words_to_write - 1;
   send_control_byte(additional_rw, word_addr, WRITE);
   
   i = 0;
   while(words_to_write > 0)
   {
      parts_of_word = (u8 *)(words + i);
      //assume little endian
      //assume that the LSB starts at the lower offset
      write_byte(parts_of_word[2]);
      write_byte(parts_of_word[1]);
      write_byte(parts_of_word[0]);
      words_to_write--;
      i++;
   }
   CS_HIGH();
   return;
}

void MAX78615_LMU::write_register(u8 word_addr, u32 a_word)
{
   u8 words_to_write = 1;
   write_registers(word_addr, words_to_write, &a_word);
   return;
}

void send_control_byte(u8 additional_rw, u8 word_addr, u8 rw)
{
   //additional_rw means the number of additional reads or writes
   //you wish to perform after ONE mandatory read or write
   //after the control byte is sent
 
   u8 NBRACC, ADDR_7_8, cntrl_byte_1, cntrl_byte_2;
   
   //Format the first Control Byte, see pg 53 of the 
   //MAX78615+LMU Datasheet
   //http://datasheets.maximintegrated.com/en/ds/MAX78615+LMU.pdf
   
   NBRACC = (additional_rw << 4) & 0xf0;
   ADDR_7_8 = word_addr & ((1 << 7) | (1 << 6));
   ADDR_7_8 >>= 4;
   
   cntrl_byte_1 = NBRACC | ADDR_7_8 | (1 << 0);
   
   cntrl_byte_2 = (word_addr << 2) & ~0x03;
   
   if(rw) cntrl_byte_2 |= (1 << 1);
   
   write_byte(cntrl_byte_1);   
   write_byte(cntrl_byte_2);
   
   return;   
}
 
u8 read_byte() 
{
   u8 read = SPI_XMIT(0x00);
   return read;
}

void write_byte(u8 byte) 
{
   SPI_XMIT(byte);
}
