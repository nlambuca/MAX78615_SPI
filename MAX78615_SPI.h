#ifndef _MAX78615_LMU
#define _MAX78615_LMU

typedef unsigned char u8;
typedef unsigned long u32;

class MAX78615_LMU
{
   public:
      MAX78615_LMU(void);
      MAX78615_LMU(int);      
      
      void write_registers(u8 word_addr, u8 words_to_write, u32 words[]);
      void write_register(u8 word_addr, u32 a_word);
      void read_registers(u8 word_addr, u8 words_to_read, u32 words[]);
      u32 read_register(u8 word_addr);
      
      //simply reconfigures the Arduino's SPI settings to
      //-MSBFIRST
      //-CLK_DIV16
      //-MODE 3
      //Call after another device uses SPI and changes its settings
      void configure_spi();
   private:
      int cs;
      void init(int cs);
};

/*REGISTER ADDRESSES*/
#define COMMAND 0x0 //INT  Y Command Register (see Command Register section)
#define FWDATE 0x1 //INT  Firmware release date in hex format (0x00YMDD)
#define MASK0 0x2 //INT  Y Status bit mask for MP0 pin
#define MASK4 0x3 //INT  Y Status bit mask for MP4 pin
#define MASK6 0x4 //INT  Y Status bit mask for MP6 pin
#define MASK7 0x5 //INT  Y Status bit mask for MP7 pin
#define STICKY 0x7 //INT  Y Status bits to hold until cleared by host
#define SAMPLES 0x8 //INT  Y High-Rate Samples per Low Rate (default 400)
#define CALCYCS 0x9 //INT  Y Number of Calibration Cycles to Average
#define PHASECOMP1 0xA //S.21  Y Phase compensation (+/-4 samples) for S1 input
#define PHASECOMP3 0xB //S.21  Y Phase compensation (+/- 4 samples) for S3 input
#define S1_GAIN 0xC //S.21  Y Input S1 Gain Calibration. Positive values only
#define S0_GAIN 0xD //S.21  Y Input S0 Gain Calibration. Positive values only
#define S3_GAIN 0xE //S.21  Y Input S3 Gain Calibration. Positive values only
#define S2_GAIN 0xF //S.21  Y Input S2 Gain Calibration. Positive values only
#define S1_OFFS 0x10 //S.23  Y Input S0 Offset Calibration
#define S0_OFFS 0x11 //S.23  Y Input S1 Offset Calibration
#define S3_OFFS 0x12 //S.23  Y Input S3 Offset Calibration
#define S2_OFFS 0x13 //S.23  Y Input S2 Offset Calibration
#define T_GAIN 0x14 //S.10  Y Temperature Slope Calibration
#define T_OFFS1 0x15 //S.10  Y Temperature1 Offset Calibration
#define HPF_COEF_I 0x16 //S.23  Y Current Input HPF Coefficient. Positive values only
#define HPF_COEF_V 0x17 //S.23  Y Voltage Input HPF Coefficient. Positive values only
#define VSURG_INT 0x18 //INT  Y Voltage Surge Detect Interval
#define VSAG_INT 0x19 //INT  Y Voltage Sag Detect Interval
#define STATUS 0x1A //INT  Alarm and Device Status Bits
#define STATUS_SET 0x1B //INT  Used to Set Status bits
#define STATUS_RESET 0x1C //INT  Used to Reset Status bits
#define DIO_STATE 0x1D //INT  State of DIO pins
#define CYCLE 0x1E //INT  High-Rate Sample Counter
#define FRAME 0x1F //INT  48 bit Low-Rate Sample Number – Low word
#define FRAME 0x20 //INT  48 bit Low-Rate Sample Number – High word
#define DIVISOR 0x21 //INT  Actual samples in previous low-rate period
#define HARM 0x22 //INT  Harmonic Selector, default: 1 (fundamental)
#define DEVADDR 0x23 //INT  Y High order address bits for I2C and UART interfaces
#define CONTROL 0x24 //INT  Control (see text)
#define CONFIG 0x25 //INT  Y Input Source M (gain) selectors and more
#define VTARGET 0x26 //S.23  Y Voltage Calibration Target. Positive values only
#define VSURG_VAL 0x27 //S.23  Y Voltage Surge Threshold. Positive values only
#define VSAG_VAL 0x28 //S.23  Y Voltage Sag Threshold. Positive values only
#define VRMS_MIN 0x29 //S.23  Y Voltage lower alarm limit. Positive values only
#define VRMS_MAX 0x2A //S.23  Y Voltage upper alarm limit. Positive values only
#define VA_RMS 0x2B //S.23  RMS Voltage for VA source
#define VB_RMS 0x2C //S.23  RMS Voltage for VB source
#define VA_FUND 0x2D //S.23  Fundamental Voltage for VA source
#define VB_FUND 0x2E //S.23  Fundamental Voltage for VB source
#define VA_HARM 0x2F //S.23  Harmonic Voltage for VA source
#define VB_HARM 0x30 //S.23  Harmonic Voltage for VB source
#define VC_RMS 0x31 //S.23  RMS Voltage for VC source
#define VA 0x33 //S.23  Instantaneous Voltage for VA source
#define VB 0x34 //S.23  Instantaneous Voltage for VB source
#define VQA 0x35 //S.23  Instantaneous Quadrature Voltage for VA source
#define VQB 0x36 //S.23  Instantaneous Quadrature Voltage for VB source
#define VC 0x37 //S.23  Instantaneous Voltage for VC source
#define SINE 0x38 //S.23  Reference Sine
#define COSINE 0x39 //S.23  Reference Cosine
#define VA_PEAK 0x3A //S.23  Peak recorded voltage
#define VB_PEAK 0x3B //S.23  Peak recorded voltage
#define ITARGET 0x3C //S.23  Y Current Calibration Target. Positive values only
#define IRMS_MIN 0x3D //S.23  Y RMS Current to squelch as zero. Positive values only
#define IA_RMS 0x3E //S.23  RMS Current for IA source
#define IB_RMS 0x3F //S.23  RMS Current for IB source
#define IA_FUND 0x40 //S.23  Fundamental Current for IA source
#define IB_FUND 0x41 //S.23  Fundamental Current for IB source
#define IA_HARM 0x42 //S.23  Harmonic Current for IA source
#define IB_HARM 0x43 //S.23  Harmonic Current for IB source
#define IA 0x44 //S.23  Instantaneous Current for IA source
#define IB 0x45 //S.23  Instantaneous Current for IB source
#define IA_PEAK 0x46 //S.23  Peak recorded current
#define IB_PEAK 0x47 //S.23  Peak recorded current
#define IRMS_MAX 0x48 //S.23  Y Over Current alarm limit. Positive values only
#define IARMS_OFFS 0x49 //S.23  Y RMS Current offset for IA. Positive values only
#define IBRMS_OFFS 0x4A //S.23  Y RMS Current offset for IB. Positive values only
#define WATT_A 0x4B //S.23  Active Power for source A
#define WATT_B 0x4C //S.23  Active Power for source B
#define WATT_C 0x4D //S.23  Total Active Power
#define VA_A 0x4E //S.23  Volt-Amperes for source A
#define VA_B 0x4F //S.23  Volt-Amperes for source B
#define VA_C 0x50 //S.23  Total Volt-Amperes
#define VAR_A 0x51 //S.23  Reactive Power for source A
#define VAR_B 0x52 //S.23  Reactive Power for source B
#define VAR_C 0x53 //S.23  Total Reactive Power
#define PFUND_A 0x54 //S.23  Fundamental Active Power for source A
#define PFUND_B 0x55 //S.23  Fundamental Active Power for source B
#define PHARM_A 0x56 //S.23  Harmonic Active Power for source A
#define PHARM_B 0x57 //S.23  Harmonic Active Power for source B
#define QFUND_A 0x58 //S.23  Fundamental Reactive Power for source A
#define QFUND_B 0x59 //S.23  Fundamental Reactive Power for source B
#define QHARM_A 0x5A //S.23  Harmonic Reactive Power for source A
#define QHARM_B 0x5B //S.23  Harmonic Reactive Power for source B
#define PA 0x5C //S.23  Instantaneous Active Power for source A
#define PB 0x5D //S.23  Instantaneous Active Power for source B
#define PQA 0x5E //S.23  Instantaneous Reactive Power for source A
#define PQB 0x5F //S.23  Instantaneous Reactive Power for source B
#define WATT_MAX 0x60 //S.23  Y Power alarm limit
#define PA_OFFS 0x61 //S.23  Y Active Power Offset for PA. Positive values only
#define QA_OFFS 0x62 //S.23  Y Reactive Power Offset for PQA. Positive values only
#define PB_OFFS 0x63 //S.23  Y Active Power Offset for PB. Positive values only
#define QB_OFFS 0x64 //S.23  Y Reactive Power Offset for PQB. Positive values only
#define PFA 0x65 //S.22  Source A Power Factor
#define PFB 0x66 //S.22  Source B Power Factor
#define PFC 0x67 //S.22  Total Power Factor
#define TEMPC1 0x68 //S.10  Chip Temperature – Channel 1
#define TEMPC2 0x69 //S.10  Chip Temperature – Channel 2
#define T_TARGET 0x6A //S.10  Y Temperature Calibration Target
#define T_MIN 0x6B //S.10  Y Temperature lower alarm limit
#define T_MAX 0x6C //S.10  Y Temperature upper alarm limit
#define FREQ 0x6D //S.16  Line Frequency
#define F_MIN 0x6E //S.16  Y Line Frequency lower alarm limit
#define F_MAX 0x6F //S.16  Y Line Frequency upper alarm limit
#define MIN1 0x71 //Minimum  Recorded Value 1
#define MIN2 0x72 //Minimum  Recorded Value 2
#define MIN3 0x73 //Minimum  Recorded Value 3
#define MIN4 0x74 //Minimum  Recorded Value 4
#define MIN5 0x75 //Minimum  Recorded Value 5
#define MIN6 0x76 //Minimum  Recorded Value 6
#define MAX1 0x77 //Maximum  Recorded Value 1
#define MAX2 0x78 //Maximum  Recorded Value 2
#define MAX3 0x79 //Maximum  Recorded Value 3
#define MAX4 0x7A //Maximum  Recorded Value 4
#define MAX5 0x7B //Maximum  Recorded Value 5
#define MAX6 0x7C //Maximum  Recorded Value 6
#define MM_ADDR1 0x7D //INT  Y Min/Max Monitor - Word Address 1
#define MM_ADDR2 0x7E //INT  Y Min/Max Monitor - Word Address 2
#define MM_ADDR3 0x7F //INT  Y Min/Max Monitor - Word Address 3
#define MM_ADDR4 0x80 //INT  Y Min/Max Monitor - Word Address 4
#define MM_ADDR5 0x81 //INT  Y Min/Max Monitor - Word Address 5
#define MM_ADDR6 0x82 //INT  Y Min/Max Monitor - Word Address 6
#define VFSCALE 0x83 //INT  Y (see Scaling Registers section)
#define IFSCALE 0x84 //INT  Y (see Scaling Registers section)
#define SCRATCH1 0x85 //INT  Y Extra Register for storing user info
#define SCRATCH2 0x86 //INT  Y Extra Register for storing user info
#define SCRATCH3 0x87 //INT  Y Extra Register for storing user info
#define SCRATCH4 0x88 //INT  Y Extra Register for storing user info
#define BUCKET 0x89 //INT  Y Energy Bucket Size – Low word
#define BUCKET 0x8A //INT  Y Energy Bucket Size – High word
#define IA_CREST 0x8B //S.16  Crest Factor for IA (positive values only)
#define IB_CREST 0x8C //S.16  Crest Factor for IB (positive values only)
#define PA_POS_CNT 0x8F //INT  Positive Active Energy Counter
#define PA_NEG_CNT 0x92 //INT  Negative Active Energy Counter
#define PB_POS_CNT 0x95 //INT  Positive Active Energy Counter
#define PB_NEG_CNT 0x98 //INT  Negative Active Energy Counter
#define PQA_POS_CNT 0x9B //INT  Leading Reactive Energy Counter
#define PQA_NEG_CNT 0x9E //INT  Lagging Reactive Energy Counter
#define PQB_POS_CNT 0xA1 //INT  Leading Reactive Energy Counter
#define PQB_NEG_CNT 0xA4 //INT  Lagging Reactive Energy Counter
#define SA_CNT 0xA7 //INT  Apparent Energy Counter
#define SB_CNT 0xAA //I24  Apparent Energy Counter
#define RYA_TON 0xAB //I24  Y Relay #1 turn-on delay
#define RYB_TON 0xAC //I24  Y Relay #2 turn-on delay
#define RYA_TOFF 0xAD //INT  Y Relay #1 turn-off delay
#define RYB_TOFF 0xAE //INT  Y Relay #2 turn-off delay
#define BAUD 0xB1 //INT  Y Baud rate for UART interface
#define DIO_POL 0xB2 //INT  Y Polarity of DIO pins. 1 = Active High ; 0 = Active Low
#define DIO_DIR 0xB3 //INT  Y Direction of DIO pins. 1 = Input ; 0 = Output
#define TEMPC 0xB5
#define T_OFFS2 0xB6 //S.10  Y Temperature2 Offset Calibration

/*STATUS REGISTER BITS*/
#define DRDY (1 << 23) //Sticky:No  New low-rate results (data) ready
#define MMUPD (1 << 22) //Sticky:Yes  Min/Max Update occurred
#define VA_SAG (1 << 21) //Sticky:Yes  Voltage A Sag Condition Detected
#define VB_SAG (1 << 20) //Sticky:Yes  Voltage B Sag Condition Detected
#define SIGN_VA (1 << 19) //Sticky:No  Sign of VA
#define SIGN_VB (1 << 18) //Sticky:No  Sign of VB
#define OV_TEMP (1 << 17) //Sticky:Yes  Temperature over High Limit
#define UN_TEMP (1 << 16) //Sticky:Yes  Under Low Temperature Limit
#define OV_FREQ (1 << 15) //Sticky:Yes  Frequency over High Limit
#define UN_FREQ (1 << 14) //Sticky:Yes  Under Low Frequency Limit
#define OV_VRMSA (1 << 13) //Sticky:Yes  RMS Voltage A Over Limit
#define UN_VRMSA (1 << 12) //Sticky:Yes  RMS Voltage A Under Limit
#define OV_VRMSB (1 << 11) //Sticky:Yes  RMS Voltage B Over Limit
#define UN_VRMSB (1 << 10) //Sticky:Yes  RMS Voltage B Under Limit
#define VA_SURGE (1 << 9) //Sticky:Yes  Voltage A Surge Condition Detected
#define VB_SURGE (1 << 8) //Sticky:Yes  Voltage B Surge Condition Detected
#define OV_WATT1 (1 << 7) //Sticky:Yes  Power 1 Over Limit
#define OV_WATT2 (1 << 6) //Sticky:Yes  Power 2 Over Limit
#define OV_AMP1 (1 << 5) //Sticky:Yes  Current 1 Over Limit
#define OV_AMP2 (1 << 4) //Sticky:Yes  Current 2 Over Limit
#define XSTATE (1 << 3) //Sticky:No  Crystal status
#define RELAY1 (1 << 2) //Sticky:Always  Relay 1 ON
#define RELAY2 (1 << 1) //Sticky:Always  Relay 2 ON
#define RESET (1 << 0) //Sticky:Always  Set by device after any type of reset

#endif

