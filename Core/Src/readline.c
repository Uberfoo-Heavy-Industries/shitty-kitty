/*
 * readline.c
 *
 *  Created on: Jul 17, 2021
 *      Author: james
 */

#include <stdio.h>
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stream_buffer.h"

#include "readline.h"

char readlineBuffer[READLINE_BUFF_LEN];
StreamBufferHandle_t stdinBufferHandle;

void init_input() {
    stdinBufferHandle = xStreamBufferCreate(256, 1);
}

int handleInput(char *ptr, int len) {
    size_t returnLength = 0;
    if (xTaskGetSchedulerState() == taskSCHEDULER_RUNNING) {
        returnLength = xStreamBufferSendFromISR(stdinBufferHandle, ptr, len, NULL);
    }
    return returnLength;
}

char *readline(char *prompt) {
    memchr(readlineBuffer, '\0', READLINE_BUFF_LEN);
    printf(prompt);
    int i = 0;
    for (;;) {
        size_t len;
        char *data = readlineBuffer + i;
        // Read up to READLINE_BUFF_LEN bytes from the buffer
        if ((len = xStreamBufferReceive(stdinBufferHandle, data, READLINE_BUFF_LEN - i, portMAX_DELAY)) > 0)
        {
            // TODO: Handle backspaces
            i += len;
            if (data[len - 1] == '\r' || i >= READLINE_BUFF_LEN) {
                data[len - 1] = '\0';
                return readlineBuffer;
            }
        } else {
            taskYIELD();
        }
    }
}

