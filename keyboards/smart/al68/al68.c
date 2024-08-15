// // /* Copyright 2022 Jacky
// //  *
// //  * This program is free software: you can redistribute it and/or modify
// //  * it under the terms of the GNU General Public License as published by
// //  * the Free Software Foundation, either version 2 of the License, or
// //  * (at your option) any later version.
// //  *
// //  * This program is distributed in the hope that it will be useful,
// //  * but WITHOUT ANY WARRANTY; without even the implied warranty of
// //  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// //  * GNU General Public License for more details.
// //  *
// //  * You should have received a copy of the GNU General Public License
// //  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
// //  */

#include "quantum.h"


void keyboard_pre_init_kb(void) {
    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk);
    AFIO->MAPR|= AFIO_MAPR_SWJ_CFG_DISABLE; //diable JTAG (GD32 different to STM32)
    setPinOutput(A8);
    writePinHigh(A8);  //ENABLE USB
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) 
{
    if (record->event.pressed){
        // if ((keycode>=KC_BLE1) && (keycode<=KC_24G))
        // {
        //     WIRELESS_START(keycode-KC_USB);
        //     return false;     
        // }
        // else if (keycode == KC_USB)
        // {
        //     WIRELESS_STOP();
        //     return false;
        // }
    }
    return process_record_user(keycode, record);   
}


