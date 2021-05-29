/**
 * Copyright (c) 2015 - 2020, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "app_util_platform.h"
#include "boards.h"
#include "app_error.h"
#include <string.h>

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "card_emu.h"

#include "nrf_drv_clock.h"
#include "app_timer.h"
#include "bsp.h"

static void lfclk_config(void)
{
    ret_code_t err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);

    nrf_drv_clock_lfclk_request(NULL);
}

void bsp_evt_handler(bsp_event_t evt)
{
    uint32_t err_code;
		static uint8_t slot = 0;
    switch (evt)
    {
        case BSP_EVENT_KEY_0:
				
						NRF_LOG_INFO("KEY0");
						ntag215_card_change(++slot);
            break;

        case BSP_EVENT_KEY_1:
						NRF_LOG_INFO("KEY1");
						ntag215_card_change(--slot);
            break;
				
				case BSP_EVENT_KEY_2:
						NRF_LOG_INFO("KEY2");
						ntag215_current_slot_init();
            break;

        default:
					NRF_LOG_INFO("KEY?");
            return; // no implementation needed
    }
}

static void bsp_configuration()
{
    uint32_t err_code;
	
		err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);

    err_code = bsp_init(BSP_INIT_BUTTONS, bsp_evt_handler);
    APP_ERROR_CHECK(err_code);
}

int main(void)
{
	
		lfclk_config();
		bsp_configuration();

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    card_emu_begin();

    NRF_LOG_INFO("NFC Card emulation started.");

    while (1)
    {

				NRF_LOG_FLUSH();
        __SEV();
        __WFE();
        __WFE();
    }
		
}
