#ifndef _MAX78615
#define _MAX78615

class MAX78615
{
   public:
      MAX78615_LMU(uint8_t);      
      
      void write_registers(utin8_t addr, uint8_t to_write, uint32_t words[]);
      void write_register(uint8_t addr, uint32_t word);
      void read_registers(uint8_t addr, uint8_t to_read, uint32_t words[]);
      uint32_t read_register(uint8_t addr);
      
      //-MSBFIRST
      //-1MHZ max
      //-MODE 3
   private:
      uint8_t  SS;
      void init(uint8_t ss);
};
#endif

