// /* Copyright 2024 Jacky
//  *
//  * This program is free software: you can redistribute it and/or modify
//  * it under the terms of the GNU General Public License as published by
//  * the Free Software Foundation, either version 2 of the License, or
//  * (at your option) any later version.
//  *
//  * This program is distributed in the hope that it will be useful,
//  * but WITHOUT ANY WARRANTY; without even the implied warranty of
//  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  * GNU General Public License for more details.
//  *
//  * You should have received a copy of the GNU General Public License
//  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
//  */
#include "bluetooth.h"
#include "uart.h"
#include "wait.h"
#include <string.h>
#include "report.h"

void bluetooth_init(void) {
    uint8_t ble_command[24];
    uart_init(460800);
    wait_ms(200);
    ble_command[0]=0x55;  
    ble_command[1]=20;   
    ble_command[2]=0;       
    ble_command[3]=1;    
    strcpy((char * restrict)(ble_command+4),PRODUCT);  //setup BLE name,length <16
    ble_command[strlen(PRODUCT)+4]=0;
    uart_transmit(ble_command,sizeof(ble_command));
}

void bluetooth_task(void) {}


void bluetooth_send_nkro(report_keyboard_t *report)
{
    uart_write(0x55);
    uart_write(0x09);
    uart_write(0x01);
    uart_transmit((uint8_t *)report,KEYBOARD_REPORT_SIZE);
}

void bluetooth_send_keyboard(report_keyboard_t *report)
{
    uart_write(0x55);
    uart_write(0x09);
    uart_write(0x01);
    uart_transmit((uint8_t *)report,KEYBOARD_REPORT_SIZE);
}

void bluetooth_send_mouse(report_mouse_t *report)
{
    static uint8_t last_report[sizeof(report_mouse_t)]={0};
    if (!has_mouse_report_changed((report_mouse_t *)last_report, report)) return;
    memcpy(last_report,report,sizeof(report_mouse_t));
    uart_write(0x55);
    uart_write(sizeof(report_mouse_t));
    uart_transmit(last_report,sizeof(report_mouse_t));
}

void bluetooth_send_consumer(uint16_t usage)
{
    report_extra_t report = {
        .report_id = REPORT_ID_CONSUMER,
        .usage     = usage,
    };
    uart_write(0x55);
    uart_write(sizeof(report_extra_t));
    uart_transmit((uint8_t *)&report,sizeof(report_extra_t));
}