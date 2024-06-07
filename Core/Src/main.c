/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_hid.h"
#include "usb_key_define.h"
#include "key.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define key_number ROW_NUM *COL_NUM
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern USBD_HandleTypeDef hUsbDeviceFS;

typedef struct
{
  uint8_t MODIFIER;
  uint8_t RESERVED;
  uint8_t KEYCODE1;
  uint8_t KEYCODE2;
  uint8_t KEYCODE3;
  uint8_t KEYCODE4;
  uint8_t KEYCODE5;
  uint8_t KEYCODE6;
} keyboardHID_t;

keyboardHID_t keyboardHID = {0, 0, 0, 0, 0, 0, 0, 0};
KEY_typedef key[key_number];
FN_KEY_typedef fn_key;

uint8_t modify_bit = 0x00;

KEY_MAP key_map_1[key_number] =
    {
        {key_grave},
        {key_1},
        {key_2},
        {key_3},
        {key_4},
        {key_5},
        {key_6},
        {key_7},
        {key_8},
        {key_9},
        {key_0},
        {key_minus},
        {key_equal},
        {key_backspace},
        {key_tab},
        {key_q},
        {key_w},
        {key_e},
        {key_r},
        {key_t},
        {key_y},
        {key_u},
        {key_i},
        {key_o},
        {key_p},
        {key_left_bracket},
        {key_right_bracket},
        {key_backslash},
        {key_caps_lock},
        {key_a},
        {key_s},
        {key_d},
        {key_f},
        {key_g},
        {key_h},
        {key_j},
        {key_k},
        {key_l},
        {key_semicolon},
        {key_quote},
        {key_return},
        {None_key},
        {LEFT_SHIFT_KEY},
        {key_z},
        {key_x},
        {key_c},
        {key_v},
        {key_b},
        {key_n},
        {key_m},
        {key_comma},
        {key_dot},
        {key_slash},
        {RIGHT_SHIFT_KEY},
        {None_key},
        {None_key},
        {LEFT_CTRL_KEY},
        {LEFT_ALT_KEY},
        {key_space},
        {GUI_KEY},
        {None_key},
        {None_key},
        {None_key},
        {None_key},
        {None_key},
        {None_key},
        {None_key},
        {None_key},
        {None_key},
        {None_key},

};
KEY_MAP key_map_2[key_number] =
    {
        {key_esc},
        {key_f1},
        {key_f2},
        {key_f3},
        {key_f4},
        {key_f5},
        {key_f6},
        {key_f7},
        {key_f8},
        {key_f9},
        {key_f10},
        {key_f11},
        {key_f12},
        {keypad_Delete},
        {key_tab},
        {key_q},
        {key_up_arrow},
        {key_e},
        {key_r},
        {key_t},
        {key_y},
        {key_u},
        {key_i},
        {key_o},
        {key_p},
        {key_left_bracket},
        {key_right_bracket},
        {key_backslash},
        {key_caps_lock},
        {key_left_arrow},
        {key_down_arrow},
        {key_right_arrow},
        {key_f},
        {key_g},
        {key_h},
        {key_j},
        {key_k},
        {key_l},
        {key_semicolon},
        {key_quote},
        {key_return},
        {None_key},
        {LEFT_SHIFT_KEY},
        {key_z},
        {key_x},
        {key_c},
        {key_v},
        {key_b},
        {key_n},
        {key_m},
        {key_comma},
        {key_dot},
        {key_slash},
        {RIGHT_SHIFT_KEY},
        {None_key},
        {None_key},
        {LEFT_CTRL_KEY},
        {LEFT_ALT_KEY},
        {key_space},
        {GUI_KEY},
        {None_key},
        {None_key},
        {None_key},
        {None_key},
        {None_key},
        {None_key},
        {None_key},
        {None_key},
        {None_key},
        {None_key},

};

void key_handler(int i)
{
  key[i].buffer_index = find_buff_emtpy_index(&keyboardHID, 8);
  if (i == 42 || i == 53)
  {
    // modify_bit = 0x02;
    keyboardHID.MODIFIER |= 0x02;
  }
  else if(i == 56 )
  {
    // modify_bit = 0x01;
    keyboardHID.MODIFIER |= 0x01;
  }
  else if(i == 57)
  {
    // modify_bit = 0x04;alt
    keyboardHID.MODIFIER |= 0x04;
  }
  else if(i == 59)
  {
    // gui
    keyboardHID.MODIFIER |= 0x08;
  }
  else
  {
    if (fn_key.layer == 0)
    {
      if (key[i].buffer_index != -1)
      {
        key_buffer_insert(key[i].buffer_index, i, key_map_1, &keyboardHID);
      }
    }
    else if (fn_key.layer == 1 )
    {

      if (key[i].buffer_index != -1)
      {
        key_buffer_insert(key[i].buffer_index, i, key_map_2, &keyboardHID);
      }
    }
  }
}

void key_handler_release(int i)
{ 
  if (i == 42 || i == 53)
  {
    // modify_bit = 0x02;shift
    keyboardHID.MODIFIER &= 0xFD;
  }
  else if(i == 56 )
  {
    // modify_bit = 0x01;ctrl
    keyboardHID.MODIFIER &= 0xFE;

  }
  else if(i == 57)
  {
    // modify_bit = 0x04;alt
    keyboardHID.MODIFIER &= 0xFB;
  }
  else if(i == 59)
  {
    // gui
    keyboardHID.MODIFIER &= 0xF7;
  }
  else
  {
  remove_buff(key[i].buffer_index, &keyboardHID);
  key[i].buffer_index = -1;
  }
}

void fn_key_handler()
{
  fn_key.layer = 1;
}
void fn_key_handler_release()
{
  fn_key.layer = 0;
  for(int i = 0; i < 8; i++)
  {
    remove_buff(i, &keyboardHID);
  }
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
  KEY_INIT(key_number, key, key_map_1);
  FN_KEY_INIT(&fn_key);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&keyboardHID, sizeof(keyboardHID));
    FN_KEY_SCAN(&fn_key);
    FN_KEY_PROCESS(&fn_key);
    key_scan(&key);
    // HAL_Delay(10);
  }
  /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
