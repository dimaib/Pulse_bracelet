#include <Si7021_driver.h>
#include <i2c.h>

static const uint16_t I2C_ADDR = (0x40<<1);           // Si7021 I2C address

static uint8_t user_register_1 = 0x3A;

static float process_temp_code(uint16_t temp_code);
static uint16_t convert_to_uint16(uint8_t bytes[]);
//static int8_t w_reg(uint8_t value, Si7021_registers_t reg);
static int8_t r_reg(Si7021_registers_t reg);

static float process_temp_code(uint16_t temp_code)
{
  return (float)(((175.72 * temp_code) / 65536.0) - 46.85);
}

static uint16_t convert_to_uint16(uint8_t bytes[])
{
  return (uint16_t)((bytes[0]<<8) | bytes[1]);
}

static int8_t r_reg(Si7021_registers_t reg)
{
  uint8_t cmd;
  uint8_t* data;

  if(reg == User_Register_1)
  {
    cmd = R_RHT_U_reg;
    data = &(user_register_1);
  }
  else
    return -1;

  if(HAL_OK != HAL_I2C_Mem_Read(&hi2c1, I2C_ADDR, cmd, 1, data, 1, 10000))
    return -1;
  else
    return 0;
}
/*
static int8_t w_reg(uint8_t value, Si7021_registers_t reg)
{
  uint16_t cmd;

  if(reg == User_Register_1)
  {
    cmd = W_RHT_U_reg;
  }
  else if(reg == Heater_Control_Register)
  {
    cmd = W_Heater_C_reg;
  }
  else
    return -1;

  if(HAL_OK != HAL_I2C_Mem_Write(&hi2c1, I2C_ADDR, cmd, 1, &value, 1, 10000))
    return -1;
  else
    return 0;
}
*/

float r_single_Si7021()
{
  uint8_t cmd;
  uint8_t buffer[2];
  uint16_t code;

  cmd = Temp_HM;

  if(HAL_OK != HAL_I2C_Master_Transmit(&hi2c1, I2C_ADDR, &cmd, 1, 10000))
    return -1.0f;

  if(HAL_OK != HAL_I2C_Master_Receive(&hi2c1, I2C_ADDR, buffer, 2, 10000))
    return -1.0f;

  code = convert_to_uint16(buffer);
  return process_temp_code(code);
}

int8_t r_firmware_rev_Si7021()
{
  uint16_t cmd = (R_Firm_rev2<<8) | R_Firm_rev1;
  uint8_t data;

  if(HAL_OK != HAL_I2C_Master_Transmit(&hi2c1, I2C_ADDR, (uint8_t*)(&cmd), 2, 10000))
    return -1;

  if(HAL_OK != HAL_I2C_Master_Receive(&hi2c1, I2C_ADDR, &data, 1, 10000))
    return -1;

  switch(data)
  {
    case 0xFF: return 1;
    case 0x20: return 2;
    default: return -1;
  }
}

int8_t rst_Si7021()
{
  uint8_t cmd = Si7021_Reset;

  if(HAL_OK != HAL_I2C_Master_Transmit(&hi2c1, I2C_ADDR, &cmd, 1, 10000))
    return -1;
  else
    return 0;
}

int8_t get_register(Si7021_registers_t reg, uint8_t* rv)
{
  if(r_reg(reg) < 0)
    return -1;

  if(reg == User_Register_1)
    *rv = user_register_1;

  return 0;
}
