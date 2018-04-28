#ifndef ZYNQ_MIO_H__
#define ZYNQ_MIO_H__
#include <stdint.h>

typedef enum MioSpeed
{
	SPEED_SLOW = 0,
	SPEED_FAST = 1,
} MioSpeed;

typedef enum MioType
{
	RESERVED_000 = 0,
	LVCMOS18     = 1,
	LVCMOS25     = 2,
	LVCMOS33     = 3,
	HSTL         = 4,
	RESERVED_101 = 5,
	RESERVED_110 = 6,
	RESERVED_111 = 7,
} MioType;

typedef struct MioDescrition
{
	uint32_t    tri_state_enabled;
	MioSpeed    speed;
	MioType     type;
	uint32_t    pull_up;
	uint32_t    disable_hstl_input;
	const char* desc;
} MioDescrition;

/**
 * @brief      Describes the given MIO pin
 *
 * Example usage is follows
 * @code
 * void PrintMIO(uint32_t val, int mio)
 * {
 *    MioDescrition desc = DescribeZynqMio(val, mio);
 *
 *    printf("MIO%2d ",mio);
 * 	  printf("%s ", desc.disable_hstl_input?"disable":"enable ");
 * 	  printf("%s ", desc.pull_up?"pull up":"       ");
 * 	  switch(desc.type)
 * 	  {
 * 	  case LVCMOS18:  printf("1.8V "); break;
 * 	  case LVCMOS25:  printf("2.5V "); break;
 * 	  case LVCMOS33:  printf("3.3V "); break;
 * 	  case HSTL:      printf("HSTL "); break;
 * 	  case RESERVED_000:
 * 	  case RESERVED_101:
 * 	  case RESERVED_110:
 * 	  case RESERVED_111:
 * 	  default:
 * 		             printf("%4d ", desc.type);
 * 		             break;
 * 	  }
 * 	  printf("%s ", desc.speed==SPEED_FAST?"FAST ":"SLOW ");
 * 	  printf("%s ", desc.tri_state_enabled?"TRI":"   ");
 *
 * 	  printf("%08x %s\r\n", val, desc.desc);
 * }
 * ...
 * printf("PIN   HSTL    PULL UP TYPE SPEED TRI RAW      Description\r\n");
 * volatile uint32_t* pins = (volatile uint32_t*)0xF8000700;
 * for(int i=0;i<54;i++)
 * {
 *    PrintMIO(pins[i], i);
 * }
 * @endcode
 *
 * @param val  Value from SLCR register starting at 0xF8000700
 * @param mio  Which MIO pin does this represent
 *
 * @returns    Decoded value
 */
MioDescrition DescribeZynqMio(uint32_t val, int mio);

#endif /* ZYNQ_MIO_H__ */
