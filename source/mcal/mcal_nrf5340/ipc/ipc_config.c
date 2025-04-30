#include "ipc_config.h"

#include "nrf5340_network_peripherals.h"

const IpcConfig_t IpcConfig = {
	     .valid=true,
		 .config={
                .send_task_config[0]=1,     /* Configuration of the connection between signals and IPC channels.*/
                .send_task_config[1]=2,     /* Configuration of the connection between signals and IPC channels.*/
                .send_task_config[2]=3,     /* Configuration of the connection between signals and IPC channels.*/
                .send_task_config[3]=4,     /* Configuration of the connection between signals and IPC channels.*/
                .send_task_config[4]=0,     /* Configuration of the connection between signals and IPC channels.*/
                .send_task_config[5]=0,     /* Configuration of the connection between signals and IPC channels.*/
                .send_task_config[6]=0,     /* Configuration of the connection between signals and IPC channels.*/
                .send_task_config[7]=0,     /* Configuration of the connection between signals and IPC channels.*/
                .send_task_config[8]=0,     /* Configuration of the connection between signals and IPC channels.*/
                .send_task_config[9]=0,     /* Configuration of the connection between signals and IPC channels.*/
                .send_task_config[10]=0,     /* Configuration of the connection between signals and IPC channels.*/
                .send_task_config[11]=0,     /* Configuration of the connection between signals and IPC channels.*/
                .send_task_config[12]=0,     /* Configuration of the connection between signals and IPC channels.*/
                .send_task_config[13]=0,     /* Configuration of the connection between signals and IPC channels.*/
                .send_task_config[14]=0,     /* Configuration of the connection between signals and IPC channels.*/
                .send_task_config[15]=0,     /* Configuration of the connection between signals and IPC channels.*/

				.receive_event_config[0]=1 , /*Configuration of the connection between events and IPC channels*/
                .receive_event_config[1]=2 , /*Configuration of the connection between events and IPC channels*/
                .receive_event_config[2]=3 , /*Configuration of the connection between events and IPC channels*/
                .receive_event_config[3]=4 , /*Configuration of the connection between events and IPC channels*/
                .receive_event_config[4]=0 , /*Configuration of the connection between events and IPC channels*/
                .receive_event_config[5]=0 , /*Configuration of the connection between events and IPC channels*/
                .receive_event_config[6]=0 , /*Configuration of the connection between events and IPC channels*/
                .receive_event_config[7]=0 , /*Configuration of the connection between events and IPC channels*/
                .receive_event_config[8]=0 , /*Configuration of the connection between events and IPC channels*/
                .receive_event_config[9]=0 , /*Configuration of the connection between events and IPC channels*/
                .receive_event_config[10]=0, /*Configuration of the connection between events and IPC channels*/
                .receive_event_config[11]=0, /*Configuration of the connection between events and IPC channels*/
                .receive_event_config[12]=0, /*Configuration of the connection between events and IPC channels*/
                .receive_event_config[13]=0, /*Configuration of the connection between events and IPC channels*/
                .receive_event_config[14]=0, /*Configuration of the connection between events and IPC channels*/
                .receive_event_config[15]=0, /*Configuration of the connection between events and IPC channels*/
                .receive_events_enabled=0xFFFFFFFF, /* Bitmask with events to be enabled to generate interrupt*/
		 },
};


Ipc_t Ipc={
		.valid=true,
};
