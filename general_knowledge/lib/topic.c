#include "topic.h"
#include <stdio.h>
#include <stdlib.h>

void topic_init(void) {
    printf("Initialized.\n");
}

void topic_deinit(void) {
    printf("Deinitialized.\n");
}

void topic_print(void) {
    printf("Topic: Shared and static libary.\n");
}
