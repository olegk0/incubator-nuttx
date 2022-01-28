/****************************************************************************
 * boards/arm/stm32h7/nucleo-h743zi/src/stm32_pwm.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <errno.h>
#include <debug.h>

#include <nuttx/timers/pwm.h>
#include <arch/board/board.h>

#include "chip.h"
#include "arm_arch.h"
#include "stm32_pwm.h"
#include "my-h743ii.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define OK 0

/* Configuration ************************************************************/

#define HAVE_PWM 1

#ifndef CONFIG_PWM
#  undef HAVE_PWM
#endif

#ifndef CONFIG_STM32H7_TIM12
#  undef HAVE_PWM
#endif

#ifndef CONFIG_STM32H7_TIM12_PWM
#  undef HAVE_PWM
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: stm32_pwm_setup
 *
 * Description:
 *   Initialize PWM and register the PWM device.
 *
 ****************************************************************************/

int stm32_pwm_setup(void)
{
#ifdef HAVE_PWM
  static bool initialized = false;
//  struct pwm_lowerhalf_s *pwm;
  struct stm32_pwm_dev_s *pwm;
  int ret;

  /* Have we already initialized? */

  if (!initialized)
    {
      /* Get an instance of the PWM interface */

      pwm = (FAR struct stm32_pwm_dev_s *) stm32_pwminitialize(LCD_PWMTIMER);
      if (!pwm)
        {
          tmrerr("ERROR: Failed to get the STM32 PWM lower half\n");
          return -ENODEV;
        }

  /* Setup PWM device */

	PWM_SETUP(pwm);

  /* Set timer frequency */
      ret = PWM_FREQ_UPDATE(pwm, 200);
      if (ret < 0)
        {
          tmrerr("ERROR: pwm_frequency_update failed: %d\n", ret);
//          return ret;
        } else
	{
  /* Set CCR1 */

	    ret = PWM_CCR_UPDATE(pwm, 1, 0x7a00);
	    if (ret < 0)
	    {
              tmrerr("ERROR: pwm_duty_update failed: %d\n", ret);
            }

//	    PWM_TIM_ENABLE(pwm, 1);
  /* Enable TIM1 OUT1 */

	    PWM_OUTPUTS_ENABLE(pwm, STM32_PWM_OUT1, true);
	    PWM_TIM_ENABLE(pwm, true);
	}

#ifdef CONFIG_DEBUG_PWM_INFO
  /* Print debug */

	PWM_DUMP_REGS(pwm, "after init");
#endif

      /* Register the PWM driver at "/dev/pwm0" */

      ret = pwm_register("/dev/pwm0", (struct pwm_lowerhalf_s *)pwm);
      if (ret < 0)
        {
          tmrerr("ERROR: pwm_register failed: %d\n", ret);
          return ret;
        }

      /* Now we are initialized */

      initialized = true;
    }

  return OK;
#else
  return -ENODEV;
#endif
}
