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
    front = rear = 0;
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
  if (chance < 80)
    {
        queue[front].status = 1;
        printf("Packet ID %d is sent successfully.\n", queue[front].id);
    }
  else
    {
        queue[front].status = -1;
        printf("Packet ID %d is lost.\n", queue[front].id);
    }

  FILE *fp = fopen("spacelog.txt", "a");
  if(fp == NULL)
    printf("Sorry! Error occured while opening the log file.\n");
  else
  {
    fprintf(fp, "Packet ID: %d | Type: %s | Status: %s | Data: %s\n", queue[front].id, queue[front].type,
        (queue[front].status == 1) ? "SENT" : "LOST",
        queue[front].data);
    fclose(fp);
  }
  if(front == rear)  front = rear = -1;
  else  front = (front+1)%SIZE;
}

void viewqueue()
{
    if (front == -1)
    {
        printf("The queue is empty. No packets to display.\n");
        return;
    }
    printf("Current queue:\n");
    int i = front;
    while (1)
    {
        printf("Packet ID: %d | Type: %s | Status: %s | Data: %s\n",
               queue[i].id, queue[i].type,
               (queue[i].status == 1) ? "SENT" : (queue[i].status == -1) ? "LOST" : "WAITING",
               queue[i].data);
        if (i == rear)
            break;
        i = (i + 1) % SIZE;
    }
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
      if (scanf("%d", &choice) != 1) {
    printf("Invalid input. Please enter a number.\n");

    // Flush buffer completely
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    continue;
}

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
