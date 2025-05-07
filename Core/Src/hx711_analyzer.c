/*
 * hx711_analyzer.c
 *
 *  Created on: Apr 13, 2025
 *      Author: konst
 */

#include <hx711_analyzer.h>

static int32_t buffer[HX711_BUFFER_SIZE];
static int64_t sum = 0;
static uint8_t index = 0;
static int32_t latest = 0;

void HX711_Analyzer_Init(int32_t offset)
{
    for (uint8_t i = 0; i < HX711_BUFFER_SIZE; i++) {
        buffer[i] = -offset;
        sum += buffer[i];
    }
    index = 0;
}

void HX711_Analyzer_Push(int32_t sample)
{
    latest = sample;

    sum -= buffer[index];
    buffer[index] = sample;
    sum += sample;

    index = (index + 1) % HX711_BUFFER_SIZE;
}

int32_t HX711_Analyzer_GetAverage(void)
{
    return (int32_t)(sum / HX711_BUFFER_SIZE);
}

int32_t HX711_Analyzer_GetDeviation(void)
{
    return latest - HX711_Analyzer_GetAverage();
}

void HX711_Init()
{
	printf("Kalibracja HX711...\r\n");

	int32_t offset = 0;
	for (int i = 0; i < 100; i++) {
	    offset += HX711_Read();
	    HAL_Delay(10);
	}
	offset /= 100;

	HX711_Analyzer_Init(offset);

	HAL_Delay(1000);
	for (uint16_t i = 0; i < 100; i++)
	{
		int32_t sample = HX711_Read();
		HX711_Analyzer_Push(sample);
		HAL_Delay(10);
	}

	printf("Offset ustawiony: %ld\r\n", offset);
}
