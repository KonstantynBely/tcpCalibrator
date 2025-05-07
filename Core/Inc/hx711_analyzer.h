/*
 * hx711_analyzer.h
 *
 *  Created on: Apr 13, 2025
 *      Author: konst
 */

#ifndef INC_HX711_ANALYZER_H_
#define INC_HX711_ANALYZER_H_

#include <stdint.h>
#include <main.h>
#include <stdio.h>

#define HX711_BUFFER_SIZE 32  // ilość próbek do średniej

void HX711_Analyzer_Init(int32_t offset);
void HX711_Analyzer_Push(int32_t sample);
int32_t HX711_Analyzer_GetAverage(void);
int32_t HX711_Analyzer_GetDeviation(void);

void HX711_Init();

#endif /* INC_HX711_ANALYZER_H_ */
