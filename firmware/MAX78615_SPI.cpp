#include "MAX78615_SPI.h"
//include register MAP
#include "MAX78615_LMU_MAP.h"
//include SPI driver
#include <SPI.h>

#define READ 0
#define WRITE 1

void send_control_byte(u8 additional_rw, u8 word_addr, u8 rw);
  u8 read_byte(void);
void write_byte(u8 byte);

MAX78615::MAX78615(uint8_t ss) 
{ 
  init(ss);
}  
  
void MAX78615::init(uint8_t ss)
{
   this->SS = ss;
   pinMode(ss, OUTPUT);
   configure_spi();
   SPI.begin();
   set_SS();
}

void MAX78615::set_SS()
{
 digitalWrite(SS,1);
}

void MAX78615::rst_SS()
{
 digitalWrite(SS,0);
}

void MAX78615::configure_spi()
{
   SPI.setBitOrder(MSBFIRST);
   SPI.setClockSpeed(1000000)); //1MHz max
   SPI.setDataMode(SPI_MODE3);
}

void MAX78615::read_registers(uint8_t addr, uint8_t to_read, uint32_t words[])
{
   uint8_t additional_rw, i;
   uint8_t * parts_of_word;
     
   if (!words_to_read) //nothing to do here...
    return;
   
   rst_SS(); //select IC
   additional_rw = words_to_read - 1;
   send_control_byte(additional_rw, word_addr, READ);
   
   i = 0;
   while(words_to_read > 0)
   {
      parts_of_word = (uint8_t *) (words + i);
      parts_of_word[2] = read_byte();
      parts_of_word[1] = read_byte();
      parts_of_word[0] = read_byte();
      words_to_read--;
      i++;
   }
   set_SS();
}

uint32_t MAX78615::read_register(uint8_t addr)
{
   uint32_t ret = 0;
   read_registers(addr, 1, &ret);
   return ret;
}

void MAX78615::write_registers(uint8_t addr, uint8_t to_write, uint32_t words[])
{
   uint8_t additional_rw, rw, i;
   uint8_t * parts_of_word;
   
   if (!words_to_write) return; //nothing to do here
   
   rst_SS();
   additional_rw = words_to_write - 1;
   send_control_byte(additional_rw, word_addr, WRITE);
   
   i = 0;
   while(words_to_write > 0)
   {
      parts_of_word = (uint8_t *)(words + i);
      //assume little endian
      //assume that the LSB starts at the lower offset
      write_byte(parts_of_word[2]);
      write_byte(parts_of_word[1]);
      write_byte(parts_of_word[0]);
      words_to_write--;
      i++;
   }
   set_SS();
   return;
}

void MAX78615::write_register(uint8_t addr, uint32_t a_word)
{
   write_registers(addr, 1, &a_word);
   return;
}

void void MAX78615::send_control_byte(uint8_t additional_rw, uint8_t word_addr, uint8_t rw)
{
   //additional_rw means the number of additional reads or writes
   //you wish to perform after ONE mandatory read or write
   //after the control byte is sent
 
   uint8_t NBRACC, ADDR_7_8, cntrl_byte_1, cntrl_byte_2;
   
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
 
uint8_t void MAX78615::read_byte() 
{
   uint8_t read = SPI.transfer(0x00);
   return read;
}

void MAX78615::write_byte(uint8_t byte) 
{
   SPI.transfer(byte);
}
