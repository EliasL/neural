/*
 * 
 ger.h
 *
 * Created: 04.07.2019 08:52:51
 * Author: Elias Lundheim
 */ 


#ifndef TINYDEBUGGER_H_
#define TINYDEBUGGER_H_

void tinyDebugger_send_int(const char* name, int value);
void tinyDebugger_send_uint32(const char* name, uint32_t value);
void tinyDebugger_send_uint8(const char* name, uint8_t value);
void tinyDebugger_send_double(const char* name, double value);
void tinyDebugger_send_string(const char* name, char * value);
void tinyDebugger_end_line();




#endif /* TINYDEBUGGER_H_ */