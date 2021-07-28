/*
 * messages.h
 *
 *  Created on: Dec 27, 2020
 *      Author: james
 */

#ifndef INC_MESSAGES_H_
#define INC_MESSAGES_H_


#ifdef __cplusplus
extern "C" {
#endif

typedef struct console_msg_t {
	char *str;
	int len;
} ConsoleMsg;

#ifdef __cplusplus
}
#endif

#endif /* INC_MESSAGES_H_ */
