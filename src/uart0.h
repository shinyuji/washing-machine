/*
 * uart0.h
 *
 * Created: 2026-06-16 오전 9:57:41
 *  Author: kccistc
 */ 

#include "common.h"

#define QUEUE_SIZE 4
#define QUEUE_LENGTH 80
volatile int rear=0;  // interrupt에서 queue에 data를 저장하는 위치값
volatile int front=0;  // pc_command_processing에서 가져가는 위치값
volatile unsigned char rx_buff[QUEUE_SIZE][QUEUE_LENGTH];
