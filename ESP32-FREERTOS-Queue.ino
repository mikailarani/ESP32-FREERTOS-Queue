
//Course Lecturer Mikail Arani
//C embedded programming 
//Concordia University Montreal, Canada 2020-2021
//FREERTOS ESP32 Queue sample code
//Use only core 1 for demo purposes    ****to use both cores and have more threads look at my git****
//Arduino IDE

#if CONFIGE_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

//Settings
static const uint8_t msg_queue_len = 5;

//Globals
static QueueHandle_t msg_queue;

//Task: wait for item on queue and print it
void printMessages(void *parameters) {
int item;

//Loop forever
while (1){
if(xQueueReceive(msg_queue, (void *)&item, 0) ==pdTRUE) {

//Serial.println(item);

}
Serial.println(item);
vTaskDelay(1000 / portTICK_PERIOD_MS);
}
}

//
//Main (runs as its own task with priority 1 on core 1)
void setup() {

//Confiqure Serial
Serial.begin(115200);

//Wait a moment to start (so we don't miss Serial output)
vTaskDelay(1000 / portTICK_PERIOD_MS);

//Configure Serial1
  Serial.println();
  Serial.println("FreeRTOS Queue Demo");

//Creat queue
msg_queue= xQueueCreate(msg_queue_len, sizeof(int));

//Start print task
  xTaskCreatePinnedToCore(printMessages,
  "Print Message",
  1024,
  NULL,
  1,
  NULL,
  app_cpu);

}

void loop() {

//Put your main code here, to run repeatedly:
static int num = 0;

//Try to add item to queue for 10 ticks, fail if queue is full
  if (xQueueSend(msg_queue, (void *)&num, 10) != pdTRUE) {
    Serial.println ("Queue full");
  }
num++;

//Wait before trying again
vTaskDelay(1000 / portTICK_PREIOD_MS);
}
