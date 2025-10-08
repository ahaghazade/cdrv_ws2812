/**
 ******************************************************************************
 * @file           : ws2812_cdrv.c
 * @brief          :
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 DiodeGroup.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component
 *
 *
 ******************************************************************************
 * @verbatim
 * @endverbatim
 */

/* Includes ------------------------------------------------------------------*/
#include "ws2812_cdrv.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static CRGB* leds = nullptr;

/* Private function prototypes -----------------------------------------------*/
void fWs2813_FullColor(CRGB Color, int LedNums, CRGB leds[]);
void fWs2813_LinearColorFill(CRGB Color, int LedNums, CRGB leds[]);
void fWs2813_LinearColorWithErase(CRGB Color, int LedNums, bool CW, CRGB leds[]);
void fWs2813_BlinkColor(CRGB Color, int LedNums, uint32_t delay_ms, int replication, CRGB leds[]);
void fWs2813_BlinkColorSmooth(CRGB Color, int LedNums, int replication, int Smooth, CRGB leds[]);
void fWs2813_Fancy(CRGB Color, int LedNums, CRGB leds[]);

/* Variables -----------------------------------------------------------------*/

/*
╔═════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Exported Functions #####                         ║
╚═════════════════════════════════════════════════════════════════════════════════╝*/
/**
 * @brief 
 * 
 * @param me 
 * @return ws2812_res_t 
 */
ws2812_res_t fWs2812_Init(sWs2812 * const me) {

    me->Init = false;

    if (me == NULL || me->LedNum == 0) {
        return WS2812_RES_ERROR_INIT_FAIL;
    }

    // Allocate memory for LEDs using C-style malloc
    me->_pLeds = (CRGB *)malloc(me->LedNum * sizeof(CRGB));
    if (me->_pLeds == NULL) {
        return WS2812_RES_ERROR_INIT_FAIL;
    }

    // Initialize FastLED
    switch (me->DataPin) {

        case 16:
            FastLED.addLeds<WS2812, 16, GRB>(me->_pLeds, me->LedNum);
            break;
        
        case 17:
            FastLED.addLeds<WS2812, 17, GRB>(me->_pLeds, me->LedNum);
            break;

        case 18:
            FastLED.addLeds<WS2812, 18, GRB>(me->_pLeds, me->LedNum);
            break;

        case 19:
            FastLED.addLeds<WS2812, 19, GRB>(me->_pLeds, me->LedNum);
            break;

        default:
            return WS2812_RES_ERROR_INIT_FAIL;
    }
    FastLED.setBrightness(int(me->Brightness));

    me->Init = true;

    return WS2812_RES_OK;
}

void fWs2812_Run(sWs2812 * const me) {

    if (me == NULL || !me->Init || me->_pLeds == NULL) {
        return;
    }

    switch (me->Effect) {

        case FillColor:
            fWs2813_FullColor(me->Color, me->LedNum, me->_pLeds);
            break;
        
        case LinearFill:
            fWs2813_LinearColorFill(me->Color, me->LedNum, me->_pLeds);
            break;
        
        case LinearFillWithErase:
            fWs2813_LinearColorWithErase(me->Color, me->LedNum, true, me->_pLeds);
            break;
        
        case Blink:
            fWs2813_BlinkColor(me->Color, me->LedNum, me->BetweanEffectDelayMs, 3, me->_pLeds);
            break;
        
        case BlinkSmooth:
            fWs2813_BlinkColorSmooth(me->Color, me->LedNum, 3, 10, me->_pLeds);
            break;
        
        case Fancy:
            fWs2813_Fancy(me->Color, me->LedNum, me->_pLeds);
            break;
        
        default:
            break;
    }
}

/**
 * @brief 
 * 
 * @param me 
 */
void fWs2812_SetBrightness(sWs2812 * const me) {

    FastLED.setBrightness(int(me->Brightness));
    FastLED.show();
}

/*
╔═════════════════════════════════════════════════════════════════════════════════╗
║                            ##### Private Functions #####                        ║
╚═════════════════════════════════════════════════════════════════════════════════╝*/
/**
 * @brief 
 * 
 * @param Color 
 * @param LedNums 
 * @param leds 
 */
void fWs2813_FullColor(CRGB Color, int LedNums, CRGB leds[])
{
    for(int i = 0; i < LedNums; i++)
    {
        leds[i] = Color;
    }  
    FastLED.show();
}

/**
 * @brief 
 * 
 * @param Color 
 * @param LedNums 
 * @param leds 
 */
void fWs2813_LinearColorFill(CRGB Color, int LedNums, CRGB leds[])
{
    for(int i = -4; i < LedNums; i++)
    {
        if(i >= 0)
            leds[i] = Color;
        for(int j = i + 1; j < i + 5; j++)
        {
            if(j >= 0)
            {
                leds[j] =  Color;
                leds[j].r *=  (0.5- (j - i) * 0.125);
                leds[j].g *=  (0.5- (j - i) * 0.125);
                leds[j].b *=  (0.5- (j - i) * 0.125);
            }
        }
        FastLED.show();
        delay(35);
    }  
}

/**
 * @brief 
 * 
 * @param Color 
 * @param LedNums 
 * @param CW 
 * @param leds 
 */
void fWs2813_LinearColorWithErase(CRGB Color, int LedNums, bool CW, CRGB leds[])
{   
    fWs2813_LinearColorFill(Color, LedNums, leds);
    delay(1000);
    if(CW)
    {
        for(int i = LedNums - 1 ; i >= 0; i--) 
        {
            leds[i] = CRGB::Black;
            FastLED.show();
            delay(35);
        }
    }
    if(!CW)
    {
        for(int i = 0 ; i < LedNums; i++) 
        {
            leds[i] = CRGB::Black;
            FastLED.show();
            delay(35);
        }
    }

}

/**
 * @brief 
 * 
 * @param Color 
 * @param LedNums 
 * @param delay_ms 
 * @param replication 
 * @param leds 
 */
void fWs2813_BlinkColor(CRGB Color, int LedNums, uint32_t delay_ms, int replication, CRGB leds[])
{
    for(int rep = 0; rep < replication; rep++)
    {
        fWs2813_FullColor(Color, LedNums, leds);
        FastLED.show();
        delay(delay_ms);
        fWs2813_FullColor(CRGB::Black, LedNums, leds);
        FastLED.show();
        delay(delay_ms);
    }
}

/**
 * @brief 
 * 
 * @param Color 
 * @param LedNums 
 * @param replication 
 * @param Smooth 
 * @param leds 
 */
void fWs2813_BlinkColorSmooth(CRGB Color, int LedNums, int replication, int Smooth, CRGB leds[])
{
    float Percent = 1 / float(Smooth);
    for(int rep = 0; rep < replication; rep++)
    {
        for(int j = 0; j <= Smooth; j++)
        {
            for(int i = 0; i < LedNums; i++)
            {
                if(j == 0)
                {
                    leds[i].r = Color.r * 0;
                    leds[i].g = Color.g * 0;
                    leds[i].b = Color.b * 0;
                }
                else
                {
                    leds[i].r = Color.r * Percent * j;
                    leds[i].g = Color.g * Percent * j;
                    leds[i].b = Color.b * Percent * j;
                }
            }  
            FastLED.show();
            delay(400/Smooth);
        }
        delay(200);
        for(int j = Smooth; j >= 0; j--)
        {
            for(int i = 0; i < LedNums; i++)
            {
                if(j == 0)
                {
                    leds[i].r = Color.r * 0;
                    leds[i].g = Color.g * 0;
                    leds[i].b = Color.b * 0;
                }
                else
                {
                    leds[i].r = Color.r * Percent * j;
                    leds[i].g = Color.g * Percent * j;
                    leds[i].b = Color.b * Percent * j;
                }
            }  
            FastLED.show();
            delay(400/Smooth);
        }
    }
}

/**
 * @brief 
 * 
 * @param Color 
 * @param LedNums 
 * @param leds 
 */
void fWs2813_Fancy(CRGB Color, int LedNums, CRGB leds[])
{
    int LedPairs =  LedNums / 10;
    for(int i = 0; i < LedNums/2 - LedPairs / 2; i++)//leds from sides to center
    {
        fWs2813_FullColor(CRGB::Black, LedNums, leds);
        for(int j = 0; j < LedPairs; j++)
        {
            leds[i + j].r = Color.r * 1;
            leds[i + j].g = Color.g * 1;
            leds[i + j].b = Color.b * 1;

            leds[LedNums - j - i - 1].r = Color.r * 1;
            leds[LedNums - j - i - 1].g = Color.g * 1;
            leds[LedNums - j - i - 1].b = Color.b * 1;
        }
        FastLED.show();
        delay(35);
    }
    delay(80);
    for(int i = 0; i < LedNums/2 - LedPairs / 2; i++)//leds from center to sides
    {
        fWs2813_FullColor(CRGB::Black, LedNums, leds);
        for(int j = 0; j < LedPairs; j++)
        {
            leds[LedNums/2 - 1 - i - j].r = Color.r * 1;
            leds[LedNums/2 - 1 - i - j].g = Color.g * 1;
            leds[LedNums/2 - 1 - i - j].b = Color.b * 1;

            leds[LedNums/2 + i + j].r = Color.r * 1;
            leds[LedNums/2 + i + j].g = Color.g * 1;
            leds[LedNums/2 + i + j].b = Color.b * 1;
        }
        FastLED.show();
        delay(35);
    }
    delay(80);
    for(int i = 0; i < LedNums/2 - LedPairs / 2; i++)//leds from sides to center half
    {
        for(int j = 0; j < LedPairs; j++)
        {
            leds[i + j].r = Color.r * 0.3;
            leds[i + j].g = Color.g * 0.3;
            leds[i + j].b = Color.b * 0.3;

            leds[LedNums - j - i - 1].r = Color.r * 0.3;
            leds[LedNums - j - i - 1].g = Color.g * 0.3;
            leds[LedNums - j - i - 1].b = Color.b * 0.3;
        }
        FastLED.show();
        delay(40);
    }
    delay(100);
    for(int i = 0; i < LedNums/2 - LedPairs / 2; i++)//leds from center to sides full
    {
        for(int j = 0; j < LedPairs; j++)
        {
            leds[LedNums/2 - 1 - i - j].r = Color.r * 1;
            leds[LedNums/2 - 1 - i - j].g = Color.g * 1;
            leds[LedNums/2 - 1 - i - j].b = Color.b * 1;

            leds[LedNums/2 + i + j].r = Color.r * 1;
            leds[LedNums/2 + i + j].g = Color.g * 1;
            leds[LedNums/2 + i + j].b = Color.b * 1;
        }
        FastLED.show();
        delay(40);
    }
}


/**End of Group_Name
  * @}
  */
/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
