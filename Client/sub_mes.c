#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"
#include "sub_pic.c"

#define ADDRESS     "203.146.252.179:1883"
#define CLIENTID    "ExampleClientSub"
#define TOPIC       "kjpie"
#define PAYLOAD     "Hello World!"
#define QOS         1
#define TIMEOUT     10000L

int is_connected;
char sub_text[25] ;
char topic_name[50] = "kjpie" ;
char server_name[50] = "203.146.252.179:1883" ;
char *top_en ;
char *ser_en ;

volatile MQTTClient_deliveryToken deliveredtoken;
void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{

    int i;
    char *payloadptr;
    //printf("Message arrived\n");
    //printf("     topic: %s\n", topicName);
    //printf("   message: ");
    payloadptr = message->payload;

    for(i=0; i < 24; i++)
    {
        sub_text[i] = payloadptr[i] ;
    }
    sub_text[24] = '\0' ;

    FILE *fp;
    fp = fopen("all_data.txt","a");
    fprintf(fp,"%s\n",sub_text);
    fclose(fp);

    sub_pic(sub_text);
    

    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}

void to_connect_mqtt (MQTTClient *client ,MQTTClient_connectOptions conn_opts) {
    
    int ch;
    MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);
    if ((is_connected = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", is_connected);
        exit(EXIT_FAILURE);
    }

    MQTTClient_subscribe(client, TOPIC, QOS);

}

void to_connect_topic(MQTTClient client,MQTTClient_connectOptions conn_opts ) {

    MQTTClient_unsubscribe(client,TOPIC);
    
    MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);
    if ((is_connected = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", is_connected);
        exit(EXIT_FAILURE);
    }

    MQTTClient_subscribe(client, topic_name, QOS);
    
}

void to_connect_server(MQTTClient client,MQTTClient_connectOptions conn_opts ) {

    MQTTClient_disconnect(client,10000);
    
    MQTTClient_create(&client, "localhost:1883", CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);
    if ((is_connected = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", is_connected);
        exit(EXIT_FAILURE);
    }

    MQTTClient_subscribe(client, topic_name, QOS);
    
}
