#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define SIZE 100

struct packet
{
  int id;
  char type[30];
  char data[30];
  int status;
};

struct packet queue[SIZE];
int front = -1, rear = -1;
int packet_id = 0;

void createpacket()
{
    if(front == (rear+1)%SIZE)
    {
      printf("Queue is full. Packet cannot be created.\n");
      return;
    }
  struct packet newpacket;
  newpacket.id = packet_id++;
  printf("Enter packet type (E.g. Telemetry, Command, Image): \n");
  scanf("%s", &newpacket.type);
  printf("Enter packet data: \n");
  fgets(newpacket.data, )
}
