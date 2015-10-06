#ifndef _MAX78615
#define _MAX78615

class MAX78615
{
   public:
      MAX78615_LMU(uint8_t);      
      
      void write_registers(utin8_t, uint8_t , uint32_t words[]);
      void write_register(uint8_t, uint32_t );
      void read_registers(uint8_t, uint8_t to_read, uint32_t words[]);
      uint32_t read_register(uint8_t);
      
      //-MSBFIRST
      //-1MHZ max
      //-MODE 3
   private:
      uint8_t  SS;
      void init(uint8_t ss);
      void send_control_byte(uint8_t, uint8_t, uint8_t );
      void writebyte(uint8_t);
      uint8_t readbyte(uint8_t);
};
#endif

