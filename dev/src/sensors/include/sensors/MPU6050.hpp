/*---------------------------------------------------------------
 * Copyright (c) 2020 Space Engineering Research Center (SERC)
 * Project    : LEAPFROG 
 * Author     : Kunal Singla, Antariksh Narain
 * Description: 
 * 
----------------------------------------------------------------- */

#ifndef _MPU6050_h_
#define _MPU6050_h_

#include <vector>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "Kalman.hpp"

using namespace std;

#define SMPLRT_DIV 0x19
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define FIFO_EN 0x23
#define INT_ENABLE 0x38

#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3C
#define ACCEL_ZOUT_H 0x3D
#define TEMP_OUT_H 0x41
#define GYRO_XOUT_H 0x43
#define GYRO_YOUT_H 0x44
#define GYRO_ZOUT_H 0x45

#define PWR_MGMT_1 0x6B

class MPU6050
{
private:
    float Ax, Ay, Az;
    float Gx, Gy, Gz;
    float TempC;
    int id;

    float offsetA[3];
    float offsetG[3];

    Kalman filters[6];
    const double dt = 0.0001;

private:
    // Function to read raw register value
    short registerValue(int addr);
    void readValues();

protected:
    float roll, pitch;

public:
    // Function to Initialize with the selected device address
    MPU6050(int device_address);

    // Function to return RAW values from the sensor
    vector<float> RawValues();

    // Function to calculate Pitch and Roll
    vector<float> PrincipalAxisValues();

    // \brief Read values from sensor and return values
    // \return vector of values : linear_acc, angular_acc, roll, pitch and temperature.
    vector<float> GetValues();

    void Calibrate(int duration);
};

#endif