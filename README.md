# ltc2308-axi

This is a Quartus project that makes use of the LTC2308 ADC on the DE10-Nano development board. It samples a 12-bit value from channel 0 of the ADC every 0.86 seconds and:
- Writes the 7 most significant bits of the result to the LED array;
- Allows the result of the current conversion to be polled over the Avalon memory map interface using a sample C program ```readadc.c``` with the 12-bit result written to stdout.

The LSB of the LED array blinks if the FPGA has been programmed after booting using U-Boot.

The ADC code is based on a helpful code from [truhy](https://github.com/truhy/adc_f2h_uart_de10nano), while the Avalon MM was setup based on a useful tutorial from [zangman](https://github.com/zangman/de10-nano).
