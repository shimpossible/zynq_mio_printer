# zynq_mio_printer
Allows user to print out MIO configurations

Given the MIO configuration value and which MIO pin, this will decode into a description of the pin.

Example usage
```c
  void PrintMIO(uint32_t val, int mio)
  {
     MioDescrition desc = DescribeZynqMio(val, mio);
 
      printf("MIO%2d ",mio);
  	  printf("%s ", desc.disable_hstl_input?"disable":"enable ");
  	  printf("%s ", desc.pull_up?"pull up":"       ");
  	  switch(desc.type)
  	  {
  	  case LVCMOS18:  printf("1.8V "); break;
  	  case LVCMOS25:  printf("2.5V "); break;
  	  case LVCMOS33:  printf("3.3V "); break;
  	  case HSTL:      printf("HSTL "); break;
  	  case RESERVED_000:
  	  case RESERVED_101:
  	  case RESERVED_110:
  	  case RESERVED_111:
  	  default:
  		             printf("%4d ", desc.type);
  		             break;
  	  }
  	  printf("%s ", desc.speed==SPEED_FAST?"FAST ":"SLOW ");
  	  printf("%s ", desc.tri_state_enabled?"TRI":"   ");
 
  	  printf("%08x %s\r\n", val, desc.desc);
  }
```

Run the PrintMIO with the following
```c
  printf("PIN   HSTL    PULL UP TYPE SPEED TRI RAW      Description\r\n");
  volatile uint32_t* pins = (volatile uint32_t*)0xF8000700;
  for(int i=0;i<54;i++)
  {
     PrintMIO(pins[i], i);
  }
```
