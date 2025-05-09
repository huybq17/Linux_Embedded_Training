#include "topic.h"
#include <stdio.h>
#include <stdlib.h>


int main(void) {
    topic_init();
    topic_print();
    topic_deinit();

    return 0;
}