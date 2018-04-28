#include "zynq_mio.h"

/*
*  [0]  = Level 0 - 1
*  [1]  = Level 1 - 1
*  [2]  = Level 2 - 1
*  [3]  = Level 2 - 2
*  [4]  = Level 2 - 3
*  [5]  = Level 3 - 0
*  [6]  = Level 3 - 1
*  [7]  = Level 3 - 2
*  [8]  = Level 3 - 3
*  [9]  = Level 3 - 4
*  [10] = Level 3 - 5
*  [11] = Level 3 - 6
*  [12] = Level 3 - 7
*/
typedef struct mio_decode {
	const char* names[13];
} mio_decode;
mio_decode mio_pin_names[] = {
	{"QSPI 1 CS",      "reserved",
			"SRAM/NOR Chip Select 0", "NAND Flash Chip Select", "SDIO 0 Power Control",
			"GPIO 0 (bank 0)","reserved","reserved","reserved","reserved","reserved","reserved","reserved"},
	{"QSPI 0 CS",      "reserved",
			"SRAM Address Bit 25", "SRAM/NOR CS 1", "SDIO 1 Power Control",
			"GPIO 1 (bank 0)","reserved","reserved","reserved","reserved","reserved","reserved","reserved"},
	{"QSPI 0 IO Bit 0","Trace Port Data Bit 8",
			"reserved", "NAND Flash ALEn","SDIO 0 Power Control",
			"GPIO 2 (bank 0)","reserved","reserved","reserved","reserved","reserved","reserved","reserved"},
	{"QSPI 0 IO Bit 1","Trace Port Data Bit 9",
			"SRAM/NOR Data bit 0", "NAND WE_8","SDIO 1 Card Port",
			"GPIO 3 (bank 0)","reserved","reserved","reserved","reserved","reserved","reserved","reserved"},
    {"QSPI 0 IO Bit 2", "Trace Port Data Bit 10",
    		"SRAM/NOR Data Bit 1","NAND Flash IO Bit 2",
			"GPIO 4 (bank 0)","reserved","reserved","reserved","reserved","reserved","reserved","reserved"},
	{"QSPI 0 IO Bit 3", "Trace Port Data Bit 11",
			"SRAM/NOR Data Bit 2","NAND Flash IO Bit 0", "SDIO 1 Power Control",
			"GPIO 5 (bank 0)","reserved","reserved","reserved","reserved","reserved","reserved","reserved"},
	{"QSPI 0 Clk", "Trace Port Data Bit 12",
			"SRAM/NOR Data Bit 3","NAND Flash IO Bit 1","SDIO 0 Power Control",
			"GPIO 6 (bank 0)","reserved","reserved","reserved","reserved","reserved","reserved","reserved"},
	{"reserved", "Trace Port Data Bit 13",
			"SRAM/NOR OE_B","NAND Flash CLE_B","SDIO 1 Power Control",
			"GPIO 7 (bank 0)","reserved","reserved","reserved","reserved","reserved","reserved","reserved"},
	{"QSPI Feedback Clk", "Trace Port Data Bit 14",
			"reserved","NAND Flash RD_B","SDIO 0 Power Control",
			"GPIO 8 (bank 0)","CAN 1 Tx","SRAM/NOR BLS_B","reserved","reserved","reserved","reserved","Uart 1 Tx"},
	{"QSPI 1 Mem Clk", "Trace Port Data Bit 15",
			"SRAM/NOR Data Bit 6","NAND Flash IO Bit 4","SDIO 1 Power Control",
			"GPIO 9 (bank 0)","CAN 1 Rx","reserved","reserved","reserved","reserved","reserved","Uart 1 Rx"},
	{"QSPI 1 IO Bit 0", "Trace Port Data Bit 2",
			"SRAM/NOR Data Bit 7","NAND Flash IO Bit 5","SDIO 0 Power Control",
			"GPIO 10 (bank 0)","CAN 0 Rx","I2C 0 Clk","JTAG TDI","SDIO 1 IO Bit 0","SPI 1 MOSI","reserved","Uart 0 Rx"},
	{"QSPI 1 IO Bit 1", "Trace Port Data Bit 3",
			"SRAM/NOR Data Bit 4","NAND Flash IO Bit 6","SDIO 1 Power Control",
			"GPIO 11 (bank 0)","CAN 0 Tx","I2C 0 Data","JTAG TDO","SDIO 1 Cmd","SPI 1 MISO","reserved","Uart 0 Tx"},
	{"QSPI 1 IO Bit 2", "Trace Port Clk",
			"reserved","NAND Flash IO Bit 7","SDIO 0 Power Control",
			"GPIO 12 (bank 0)","CAN 1 Tx","I2C 1 Clk","JTAG TCK","SDIO 1 Clk","SPI 1 Clk","reserved","Uart 1 Tx"},
	{"QSPI 1 IO Bit 3", "Trace Port Control Signal",
			"SRAM/NOR Data Bit 5","NAND Flash IO Bit 3","SDIO 1 Power Control",
			"GPIO 13 (bank 0)","CAN 1 Rx","I2C 1 Data","JTAG TMS","SDIO 1 IO Bit 1","SPI 1 SS 0","reserved","Uart 1 Rx"},
	{"reserved", "Trace Port Data Bit 0",
			"reserved","NAND Flash Busy","SDIO 0 Power Control",
			"GPIO 14 (bank 0)","CAN 0 Rx","I2C 1 Clk","SWDT Clk","SDIO 1 IO Bit 2","SPI 1 SS 1","reserved","Uart 0 Rx"},
	{"reserved", "Trace Port Data Bit 1",
			"SRAM/NOR Address Bit 0","reserved","SDIO 1 Power Control",
			"GPIO 15 (bank 0)","CAN 0 Tx","I2C 0 Data","SWDT Reset","SDIO 1 IO Bit 3","SPI 1 SS 2","reserved","Uart 0 Tx"},
	{"Eth 0 RGMII Tx Clk", "Trace Port Data Bit 4",
			"SRAM/NOR Address Bit 1","NAND Flask IO Bit 8","SDIO 0 Power Control",
			"GPIO 16 (bank 0)","CAN 1 Tx","I2C 1 Clk","reserved","SDIO 0 Clk","SPI 0 Clk","TTC 1 Wave","Uart 1 Tx"},
	{"Eth 0 RGMII Tx Bit 0", "Trace Port Data Bit 5",
			"SRAM/NOR Address Bit 2","NAND Flask IO Bit 9","SDIO 1 Power Control",
			"GPIO 17 (bank 0)","CAN 1 Rx","I2C 1 Data","reserved","SDIO 0 Cmd","SPI 0 MISO","TTC 1 Clk","Uart 1 Rx"},
	{"Eth 0 RGMII Tx Bit 1", "Trace Port Data Bit 6",
			"SRAM/NOR Address Bit 3","NAND Flask IO Bit 10","SDIO 0 Power Control",
			"GPIO 18 (bank 0)","CAN 0 Rx","I2C 0 Clk","reserved","SDIO 0 IO Bit 0","SPI 0 SS 0","TTC 0 Wave","Uart 0 Rx"},
	{"Eth 0 RGMII Tx Bit 2", "Trace Port Data Bit 7",
			"SRAM/NOR Address Bit 4","NAND Flask IO Bit 11","SDIO 1 Power Control",
			"GPIO 19 (bank 0)","CAN 0 Tx","I2C 0 Data","reserved","SDIO 0 IO Bit 1","SPI 0 SS 1","TTC 0 Clk","Uart 0 Tx"},
	{"Eth 0 RGMII Tx Bit 3", "reserved",
			"SRAM/NOR Address Bit 5","NAND Flask IO Bit 12","SDIO 0 Power Control",
			"GPIO 20 (bank 0)","CAN 1 Tx","I2C 1 Clk","reserved","SDIO 0 IO Bit 2","SPI 0 SS 2","reserved","Uart 1 Tx"},
	{"Eth 0 RGMII Tx Ctrl", "reserved",
			"SRAM/NOR Address Bit 6","NAND Flask IO Bit 13","SDIO 1 Power Control",
			"GPIO 21 (bank 0)","CAN 1 Rx","I2C 1 Data","reserved","SDIO 0 IO Bit 3","SPI 0 MOSI","reserved","Uart 1 Rx"},
	{"Eth 0 RGMII Rx Clk", "Trace Port Data Bit 2",
			"SRAM/NOR Address Bit 7","NAND Flask IO Bit 14","SDIO 0 Power Control",
			"GPIO 22 (bank 0)","CAN 0 Rx","I2C 0 Clk","JTAG TDI","SDIO 1 IO Bit ","SPI 1 MOSI","reserved","Uart 0 Rx"},
	{"Eth 0 RGMII Rx 0", "Trace Port Data Bit 3",
			"SRAM/NOR Address Bit 8","NAND Flask IO Bit 15","SDIO 1 Power Control",
			"GPIO 23 (bank 0)","CAN 0 Tx","I2C 0 Data","JTAG TDO","SDIO 1 CMD ","SPI 1 MISO","reserved","Uart 0 Tx"},
	{"Eth 0 RGMII Rx 1", "Trace Port Clk",
			"SRAM/NOR Address Bit 9","reserved","SDIO 0 Power Control",
			"GPIO 24 (bank 0)","CAN 1 Tx","I2C 1 Clk","JTAG TCK","SDIO 1 CLK ","SPI 1 CLK","reserved","Uart 1 Tx"},
	{"Eth 0 RGMII Rx 2", "Trace Port Ctrl",
			"SRAM/NOR Address Bit 10","reserved","SDIO 1 Power Control",
			"GPIO 25 (bank 0)","CAN 1 Rx","I2C 1 Data","JTAG TMS","SDIO 1 IO Bit 1","SPI 1 SS 0","reserved","Uart 1 Rx"},
	{"Eth 0 RGMII Rx 3", "Trace Port Data Bit 0",
			"SRAM/NOR Address Bit 11","reserved","SDIO 0 Power Control",
			"GPIO 26 (bank 0)","CAN 0 Rx","I2C 0 Clk","SWDT Clk","SDIO 1 IO Bit 2","SPI 1 SS 1","reserved","Uart 0 Rx"},
	{"Eth 0 RGMII Rx Ctrl", "Trace Port Data Bit 1",
			"SRAM/NOR Address Bit 12","reserved","SDIO 1 Power Control",
			"GPIO 27 (bank 0)","CAN 0 Tx","I2C 0 Data","SWDT Reset","SDIO 1 IO Bit 3","SPI 1 SS 2","reserved","Uart 0 Tx"},
	{"Eth 0 RGMII Tx Clk", "USB 0 ULPI Data 4",
			"SRAM/NOR Address Bit 13","reserved","SDIO 0 Power Control",
			"GPIO 28 (bank 0)","CAN 1 Tx","I2C 1 Clk","reserved","SDIO 0 Clk","SPI 0 Clk","TTC 1 Wave","Uart 1 Tx"},
	{"Eth 1 RGMII Tx 0", "USB 0 ULPI Dir",
			"SRAM/NOR Address Bit 14","reserved","SDIO 1 Power Control",
			"GPIO 29 (bank 0)","CAN 1 Rx","I2C 1 Data","reserved","SDIO 0 Cmd","SPI 0 MISO","TTC 1 Clk","Uart 1 Rx"},
	{"Eth 1 RGMII Tx 1", "USB 0 ULPI Stop",
			"SRAM/NOR Address Bit 15","reserved","SDIO 0 Power Control",
			"GPIO 30 (bank 0)","CAN 0 Rx","I2C 0 Clk","reserved","SDIO 0 IO 0","SPI 0 SS 0","TTC 0 Wave","Uart 0 Rx"},
	{"Eth 1 RGMII Tx 2", "USB 0 ULPI Next",
			"SRAM/NOR Address Bit 16","reserved","SDIO 1 Power Control",
			"GPIO 31 (bank 0)","CAN 0 Tx","I2C 0 Clk","reserved","SDIO 0 IO 1","SPI 0 SS 1","TTC 0 Clk","Uart 0 Tx"},
	{"Eth 1 RGMII Tx 3", "USB 0 ULPI Data 0",
			"SRAM/NOR Address Bit 17","reserved","SDIO 0 Power Control",
			"GPIO 32 (bank 1)","CAN 1 Tx","I2C 1 Serial","reserved","SDIO 0 IO 2","SPI 0 SS 2","reserved","Uart 1 Tx"},
	{"Eth 1 RGMII Tx Ctrl", "USB 0 ULPI Data 1",
			"SRAM/NOR Address Bit 18","reserved","SDIO 1 Power Control",
			"GPIO 33 (bank 1)","CAN 1 Rx","I2C 1 Data","reserved","SDIO 0 IO 3","SPI 0 MOSI","reserved","Uart 1 Rx"},
	{"Eth 1 RGMII Rx Clk", "USB 0 ULPI Data 2",
			"SRAM/NOR Address Bit 19","reserved","SDIO 0 Power Control",
			"GPIO 34 (bank 1)","CAN 0 Rx","I2C 0 Clk","JTAG TDI","SDIO 1 IO 0","SPI 1 MOSI","reserved","Uart 0 Rx"},
	{"Eth 1 RGMII Rx Data 0", "USB 0 ULPI Data 3",
			"SRAM/NOR Address Bit 20","reserved","SDIO 1 Power Control",
			"GPIO 35 (bank 1)","CAN 0 Tx","I2C 0 Data","JTAG TDO","SDIO 1 Cmd","SPI 1 MISO","reserved","Uart 0 Tx"},
	{"Eth 1 RGMII Rx Data 1", "USB 0 ULPI Clk",
			"SRAM/NOR Address Bit 21","reserved","SDIO 0 Power Control",
			"GPIO 36 (bank 1)","CAN 1 Tx","I2C 1 Clk","JTAG TCK","SDIO 1 Clk","SPI 1 Clk","reserved","Uart 1 Tx"},
	{"Eth 1 RGMII Rx Data 2", "USB 0 ULPI Data 5",
			"SRAM/NOR Address Bit 22","reserved","SDIO 1 Power Control",
			"GPIO 37 (bank 1)","CAN 1 Rx","I2C 1 Data","JTAG TMS","SDIO 1 IO 1","SPI 1 SS 0","reserved","Uart 1 Rx"},
	{"Eth 1 RGMII Rx Data 3", "USB 0 ULPI Data 6",
			"SRAM/NOR Address Bit 23","reserved","SDIO 0 Power Control",
			"GPIO 38 (bank 1)","CAN 0 Rx","I2C 0 Clk","SWDT Clk","SDIO 1 IO 2","SPI 1 SS 1","reserved","Uart 0 Rx"},
	{"Eth 1 RGMII Rx Data Ctrl", "USB 0 ULPI Data 7",
			"SRAM/NOR Address Bit 24","reserved","SDIO 1 Power Control",
			"GPIO 39 (bank 1)","CAN 0 Tx","I2C 0 Data","SWDT Reset","SDIO 1 IO 3","SPI 1 SS 2","reserved","Uart 0 Tx"},
	{"reserved", "USB 1 ULPI Data 4",
			"reserved","reserved","SDIO 0 Power Control",
			"GPIO 40 (bank 1)","CAN 1 Tx","I2C 1 Clk","reserved","SDIO 0 Clk","SPI 0 Clk","TTC 1 Wave","Uart 1 Tx"},
	{"reserved", "USB 1 ULPI Dir",
			"reserved","reserved","SDIO 1 Power Control",
			"GPIO 41 (bank 1)","CAN 1 Rx","I2C 1 Data","reserved","SDIO 0 Cmd","SPI 0 MISO","TTC 1 Clk","Uart 1 Rx"},
	{"reserved", "USB 1 ULPI Stop",
			"reserved","reserved","SDIO 0 Power Control",
			"GPIO 42 (bank 1)","CAN 0 Rx","I2C 0 Clk","reserved","SDIO 0 IO 0","SPI 0 SS 0","TTC 0 Wave","Uart 0 Rx"},
	{"reserved", "USB 1 ULPI Next",
			"reserved","reserved","SDIO 1 Power Control",
			"GPIO 43 (bank 1)","CAN 0 Tx","I2C 0 Data","reserved","SDIO 0 IO 1","SPI 0 SS 1","TTC 0 Clk","Uart 0 Tx"},
	{"reserved", "USB 1 ULPI Data 0",
			"reserved","reserved","SDIO 0 Power Control",
			"GPIO 44 (bank 1)","CAN 1 Tx","I2C 1 Clk","reserved","SDIO 0 IO 2","SPI 0 SS 2","reserved","Uart 1 Tx"},
	{"reserved", "USB 1 ULPI Data 1",
			"reserved","reserved","SDIO 1 Power Control",
			"GPIO 45 (bank 1)","CAN 1 Rx","I2C 1 Data","reserved","SDIO 0 IO 3","SPI 0 MOSI","reserved","Uart 1 Rx"},
	{"reserved", "USB 1 ULPI Data 2",
			"reserved","reserved","SDIO 0 Power Control",
			"GPIO 46 (bank 1)","CAN 0 Rx","I2C 0 Clk","JTAG TDI","SDIO 1 IO 0","SPI 1 MOSI","reserved","Uart 0 Rx"},
	{"reserved", "USB 1 ULPI Data 3",
			"reserved","reserved","SDIO 1 Power Control",
			"GPIO 47 (bank 1)","CAN 0 Tx","I2C 0 Data","JTAG TDO","SDIO 1 Cmd","SPI 1 MISO","reserved","Uart 0 Tx"},
	{"reserved", "USB 1 ULPI Clk",
			"reserved","reserved","SDIO 0 Power Control",
			"GPIO 48 (bank 1)","CAN 1 Tx","I2C 1 Clk","JTAG TCK","SDIO 1 Clk","SPI 1 Clk","reserved","Uart 1 Tx"},
	{"reserved", "USB 1 ULPI Data 5",
			"reserved","reserved","SDIO 1 Power Control",
			"GPIO 49 (bank 1)","CAN 1 Rx","I2C 1 Data","JTAG TMS","SDIO 1 IO 1","SPI 1 SS 0","reserved","Uart 1 Rx"},
	{"reserved", "USB 1 ULPI Data 6",
			"reserved","reserved","SDIO 0 Power Control",
			"GPIO 50 (bank 1)","CAN 0 Rx","I2C 0 Clk","SWDT Clk","SDIO 1 IO 2","SPI 1 SS 1","reserved","Uart 0 Rx"},
	{"reserved", "USB 1 ULPI Data 7",
			"reserved","reserved","SDIO 1 Power Control",
			"GPIO 51 (bank 1)","CAN 0 Tx","I2C 0 Data","SWDT Reset","SDIO 1 IO 3","SPI 1 SS 2","reserved","Uart 0 Tx"},
	{"reserved", "reserved",
			"reserved","reserved","SDIO 0 Power Control",
			"GPIO 52 (bank 1)","CAN 1 Tx","I2C 1 Clk","SWDT Clk","MDIO 0 Clk","MDIO 1 Clk","reserved","Uart 1 Tx"},
	{"reserved", "reserved",
			"reserved","reserved","SDIO 1 Power Control",
			"GPIO 53 (bank 1)","CAN 1 Rx","I2C 1 Data","SWDT Reset","MDIO 0 Data","MDIO 1 Data","reserved","Uart 1 Rx"},
};

/**
 * @brief      Describes the given MIO pin
 *
 * @param val  Value from SLCR register starting at 0xF8000700
 * @param mio  Which MIO pin does this represent
 *
 * @returns    Decoded value
 */
MioDescrition DescribeZynqMio(uint32_t val, int mio)
{
	MioDescrition result;
	uint32_t l0  = (val>>1) & 1;
	uint32_t l1  = (val>>2) & 1;
	uint32_t l2  = (val>>3) & 3;
	uint32_t l3  = (val>>5) & 7;
	char** decode;

	// default to all 0 and invalid
	memset(&result,0,sizeof(result));
	result.desc = "invalid";
	if(mio < 0 || mio > 53) return result;

	decode = mio_pin_names[mio].names;

	result.tri_state_enabled  = val & 1;
	result.speed              = (val>>8) & 1;
	result.type               = (val>>9) & 7;
	result.pull_up            = (val>>12)&1;
	result.disable_hstl_input = (val>>13)&1;

	result.desc="unknown";
	if(l0)
	{
		result.desc = decode[0];
	}else if(l1)
	{
		result.desc = decode[l1];
	}else if(l2)
	{
		result.desc = decode[l2+1];
	}else //if(l3)
	{
		result.desc = decode[l3+5];
	}

	return result;
}
