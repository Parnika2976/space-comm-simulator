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
  int status;  // Lost = -1, Waiting = 0, Sent = 1
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
  newpacket.id = ++packet_id;
  printf("Enter packet type (E.g. Telemetry, Command, Image): \n");
  scanf("%s", &newpacket.type);
  printf("Enter packet data: \n");
  getchar();
  fgets(newpacket.data, sizeof(newpacket.data), stdin);
  newpacket.status = 0; //waiting

  if(front == -1)
    front = 0;
  else
    rear = (rear+1)%SIZE;
  queue[rear] = newpacket;
  printf("Packet is created and added to queue.\n");
}

void sendpacket()
{
  if(front == -1)
    {
      printf("Queue is empty. No packet to send.\n");
      return;
    }
  struct packet current = queue[front];
  //Simulate transmission...assuming 80% success
  int chance = rand()%100;
  if (chance<80)
  {
    current.status = 1; //sent
    printf("Packet ID %d is sent successfully.\n", current.id);
  } 
  else
  {
    current.status = -1; //lost
    printf("Packet ID %d is lost.\n", current.id);
  }
  FILE *fp = fopen("spacelog.txt", "a");
  if(fp == NULL)
    printf("Sorry! Error occured while opening the log file.\n");
  else
  {
    fprintf(fp, "Packet ID: %d | Type: %s | Status: %s | Data: %s\n", current.id, current.type, (current.status==1)?"SENT":"LOST", current.data);
    fclose(fp);
  }
  if(front == rear)  front = rear = -1;
  else  front = (front+1)%SIZE;
}

void viewqueue()
{
  int i;
  if(front == -1)
  {
    printf("The queue is empty. No packets to display.\n");
    return;
  }
  printf("Current queue\n");
  for(i = front; i < rear; i = (i+1)%SIZE)
      printf("Packet ID: %d | Type: %s | Status: %s | Data: %s\n", queue[i].id, queue[i].type, queue[i].status, queue[i].data);
  printf("Packet ID: %d | Type: %s | Status: %s | Data: %s\n", queue[i].id, queue[i].type, queue[i].status, queue[i].data);
  printf("End of queue\n");
}

void viewlog()
{
  char c;
  FILE *fp = fopen("spacelog.txt", "r");
  if(fp == NULL)
  {
    printf("Log file not found!\n");
    return;
  }
  else
  {
    printf("SPACE COMMUNICATION LOG\n");
    while((c=fgetc(fp))!=EOF)
      printf("%c", c);
    fclose(fp);
  }
}

  int main()
{
  srand(time(0));  //seed for random numbers
  int choice;
  while(1)
    {
      printf("*** Space Communication Packet Simulator ***\n");
      printf("1. Create Packet\n");
      printf("2. Send Packet\n");
      printf("3. View Queue\n");
      printf("4. View Log\n");
      printf("5. Exit\n");
      printf("Enter your choice: ");
      scanf("%d", &choice);
      switch(choice)
        {
          case 1: createpacket();  break;
          case 2: sendpacket();  break;
          case 3: viewqueue();  break;
          case 4: viewlog();  break;
          case 5: printf("Exiting...\n");  return 0;
          default: printf("Invalid choice!\n");
        }
    }
}
