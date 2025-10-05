/**
******************************************************************************
* @file           : cdrv_ws2812.h
* @brief          : Header file for WS2812 LED driver
* @note           :
* @copyright      : COPYRIGHT© 2025 DiodeGroup
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright© 2025 DiodeGroup.
* All rights reserved.</center></h2>
*
* This software is licensed under terms that can be found in the LICENSE file
* in the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*
******************************************************************************
* @verbatim
* @endverbatim
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CDRV_WS2812_H
#define CDRV_WS2812_H

/* Includes ------------------------------------------------------------------*/
#include <FastLED.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Exported defines ----------------------------------------------------------*/
/**
 * @brief Return codes for WS2812 operations
 * 
 */
typedef uint8_t ws2812_res_t;

#define WS2812_RES_OK                           ((uint8_t)0)
#define WS2812_RES_ERROR_INIT_FAIL              ((uint8_t)1)

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
 * @brief WS2812 effect types
 * 
 */
typedef enum {

    FillColor = 0,

    LinearFill,

    LinearFillWithErase,

    Blink,

    BlinkSmooth,

    Fancy    

} eWs2812;

/**
 * @brief WS2812 configuration structure
 * 
 */
typedef struct {

    uint8_t LedNum;                // Number of LEDs

    eWs2812 Effect;                // Effect to apply

    uint32_t BetweanEffectDelayMs;  // Delay between effects (ms)

    uint8_t Brightness;            // Brightness level (0-255)

    CRGB *_pLeds;                  // Pointer to LED array

    CRGB Color;

    bool Init;                     // Initialization status

    uint8_t DataPin;  

} sWs2812;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
ws2812_res_t fWs2812_Init(sWs2812 * const me);
void fWs2812_Run(sWs2812 * const me);
void fWs2812_SetBrightness(sWs2812 * const me);


/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* CDRV_WS2812_H */

/************************ © COPYRIGHT DiodeGroup *****END OF FILE****/