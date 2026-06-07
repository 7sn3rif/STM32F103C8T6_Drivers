/* USER CODE BEGIN Header */
/**
  Author: Hassan Arif
  Project : Closed-Loop Control of a Robotic Vehicle
  */
/* USER CODE END Header */

#include "main.h"
#include <math.h>

void ControlLoop();

volatile uint32_t msTicks = 0;

PID_TypeDef motor_pid;
PID_TypeDef speed_pid;        // new: closed-loop wheel speed PID

int main(void) {
    MPU6050_Init();
    UART_Init(UART_CHANNEL_2);
    DCmotor_Init();

    /* Encoder Init */
    ENCODER_EXTI_Init(ENCODER_1);
    ENCODER_EXTI_Init(ENCODER_2);


    /* Balance PID */
    PID_Init(&motor_pid, 1.0f, 0.5f, 0.1f, 0, 100);
    PID_SetIntegralLimit(&motor_pid, 50.0f);

    /* Speed PID — corrects wheel speed error */
    PID_Init(&speed_pid, 0.8f, 0.3f, 0.05f, -50, 50);
    PID_SetIntegralLimit(&speed_pid, 30.0f);

    while (1) {
        ControlLoop();
    }
}




void ControlLoop() {
    static float    dt            = 0.005f;   // 5ms loop
    static int32_t  prev_count1   = 0;
    static int32_t  prev_count2   = 0;
    static float    target_speed  = 0.0f;     // ticks/loop — set by command

    /* 1. Receive Bluetooth command */
    uint8_t cmd = UART_ReceiveData(UART_CHANNEL_2);

    /* 2. Read IMU */
    MPU_real_data sensor;
    MPU6050_ReadScaledVal(&sensor);

    float pitch    = atan2(sensor.Accel_y, sensor.Accel_z) * 180.0f / M_PI;
    float yaw_rate = sensor.Gyro_z;

    /* 3. Compute wheel speed (ticks per loop cycle) */
    int32_t count1 = ENCODER_GetCount(ENCODER_1);
    int32_t count2 = ENCODER_GetCount(ENCODER_2);

    float speed1 = (float)(count1 - prev_count1);   // ticks since last loop
    float speed2 = (float)(count2 - prev_count2);
    float avg_speed = (speed1 + speed2) / 2.0f;     // average both wheels

    prev_count1 = count1;
    prev_count2 = count2;

    /* 4. Set target speed and turn duty based on command */
    float turn_duty = constrain((fabsf(yaw_rate) / 250.0f) * 100.0f, 0, 100);

    switch (cmd) {
        case 'F': target_speed =  5.0f;  break;   // ~5 ticks/loop forward
        case 'B': target_speed = -5.0f;  break;   // ~5 ticks/loop backward
        case 'R': target_speed =  0.0f;  break;   // turning — no fwd speed
        case 'L': target_speed =  0.0f;  break;
        default:  target_speed =  0.0f;  break;   // stop
    }

    /* 5. Balance PID — corrects pitch angle → base duty */
    float balance_correction = PID_Compute(&motor_pid, 0.0f, pitch, dt);

    /* 6. Speed PID — corrects actual vs target wheel speed */
    float speed_correction = PID_Compute(&speed_pid, target_speed, avg_speed, dt);

    /* 7. Fuse both corrections */
    float f_b_duty = constrain(balance_correction + speed_correction + 50.0f, 0, 100);

    /* 8. Drive motors */
    switch (cmd) {
        case 'F': DCmotor_forward ((uint8_t)f_b_duty);  break;
        case 'B': DCmotor_Backward((uint8_t)f_b_duty);  break;
        case 'R': DCmotor_Right   ((uint8_t)turn_duty); break;
        case 'L': DCmotor_left    ((uint8_t)turn_duty); break;
        default:  DCmotor_forward (0);                  break;
    }
}
