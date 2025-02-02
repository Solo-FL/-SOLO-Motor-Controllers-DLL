// Copyright: (c) 2021-2023, SOLO motor controllers project
// GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)

/*
*    Title: SOLO Motor Controllers DLL
*    Author: SOLOMotorControllers
*    Date: 2023
*    Code version: 1.0.0
*    Availability: https://github.com/Solo-FL/SOLO-Motor-Controllers-DLL
This Library is made by SOLOMotorControllers.com
To learn more please visit:  https://www.SOLOMotorControllers.com/
*/

#pragma once

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>

#include "SOLOMotorControllersUtils.h"

//DLL BLOCK
#ifdef SOLOLIBRARY_EXPORTS
#define SOLOLIBRARY_API __declspec(dllexport)
#else
#define SOLOLIBRARY_API __declspec(dllimport)
#endif
//DLL need SOLOLIBRARY_API in the definitions too

#ifdef __cplusplus
extern "C"
{
#endif

	class SOLOMotorControllersSerial {

	private:
		UINT8 addr = 0;
		char* portName;
		bool isConnected = false;
		HANDLE hComm;
		UINT32 uartBaudrate;
		UINT32 timeout;
		UINT32 trialCount;

		char   ComPortName[10];
		BOOL   Status;
		DWORD  dNoOFBytestoWrite;              // No of bytes to write into the port
		DWORD  dNoOfBytesWritten = 0;          // No of bytes written to the port

		char  SerialBuffer[256];               // Buffer Containing Rxed Data
		DWORD NoBytesRecieved;
		char  TempChar;

		//javad
		SOLOMotorControllersUtils* soloUtils;

	public:

		enum Error
		{
			noErrorDetected = 0,
			generalError = 1,
			noProcessedCommand = 2,
			outOfRengeSetting = 3,
			packetFailureTrialAttemptsOverflow = 4,
			recieveTimeOutError = 5,
			Abort_Object = 6,
			Abort_Value = 7,
			MCP2515_Transmit_ArbitrationLost = 8,
			MCP2515_Transmit_Error = 9,
			objectNotInitialize = 10
		};

		enum CommandMode
		{
			analogue = 0,
			digital = 1
		};
		enum Direction
		{
			clockwise = 0,
			counterclockwise = 1
		};
		enum FeedbackControlMode
		{
			sensorLess = 0,
			encoders = 1,
			hallSensors = 2
		};
		enum ControlMode
		{
			speedMode = 0,
			torqueMode = 1,
			positionMode = 2
		};
		enum MotorType
		{
			dc = 0,
			bldcPmsm = 1,
			acim = 2,
			bldcPmsmUltrafast = 3
		};
		enum UartBaudrate
		{
			rate937500 = 0,
			rate115200 = 1
		};
		enum CanbusBaudrate
		{
			rate1000 = 0,
			rate500 = 1,
			rate250 = 2,
			rate125 = 3,
			rate100 = 4
		};
		enum Action
		{
			stop = 0,
			start = 1
		};
		enum PositionSensorCalibrationAction
		{
			stopCalibration = 0,
			incrementalEncoderStartCalibration = 1,
			hallSensorStartCalibration = 2
		};

		SOLOLIBRARY_API SOLOMotorControllersSerial(char* COMPortName, unsigned char deviceAddress = 0,
 				SOLOMotorControllersSerial::UartBaudrate baudrate = SOLOMotorControllersSerial::UartBaudrate::rate115200,
 				long millisecondsTimeout = 50, int packetFailureTrialAttempts = 3, bool autoConnect = true);

		SOLOLIBRARY_API ~SOLOMotorControllersSerial();

	private:

		SOLOLIBRARY_API bool ExeCMD(unsigned char* cmd, int& error);

		SOLOLIBRARY_API float ConvertToFloat(unsigned char* data);

		SOLOLIBRARY_API void ConvertToData(float f, unsigned char* data);

		SOLOLIBRARY_API long ConvertToLong(unsigned char* data);

		SOLOLIBRARY_API void ConvertToData(long l, unsigned char* data);

		SOLOLIBRARY_API void SplitData(unsigned char* data, unsigned char* cmd);

	public:

		SOLOLIBRARY_API bool Connect(char* COMPortName, unsigned char deviceAddress = 0,
 				SOLOMotorControllersSerial::UartBaudrate baudrate = SOLOMotorControllersSerial::UartBaudrate::rate115200,
 				long millisecondsTimeout = 50, int packetFailureTrialAttempts = 3);

		SOLOLIBRARY_API bool Connect();

		SOLOLIBRARY_API void Disconnect();

		SOLOLIBRARY_API bool Test();

		//----------Write----------

		SOLOLIBRARY_API bool SetDeviceAddress(unsigned char deviceAddress, int& error);

		SOLOLIBRARY_API bool SetDeviceAddress(unsigned char deviceAddress);

		SOLOLIBRARY_API bool SetCommandMode(CommandMode mode, int& error);

		SOLOLIBRARY_API bool SetCommandMode(CommandMode mode);

		SOLOLIBRARY_API bool SetCurrentLimit(float currentLimit, int& error);

		SOLOLIBRARY_API bool SetCurrentLimit(float currentLimit);

		SOLOLIBRARY_API bool SetTorqueReferenceIq(float torqueReferenceIq, int& error);

		SOLOLIBRARY_API bool SetTorqueReferenceIq(float torqueReferenceIq);

		SOLOLIBRARY_API bool SetSpeedReference(long speedReference, int& error);

		SOLOLIBRARY_API bool SetSpeedReference(long speedReference);

		SOLOLIBRARY_API bool SetPowerReference(float powerReference, int& error);

		SOLOLIBRARY_API bool SetPowerReference(float powerReference);

		SOLOLIBRARY_API bool MotorParametersIdentification(Action identification, int& error);

		SOLOLIBRARY_API bool MotorParametersIdentification(Action identification);

		SOLOLIBRARY_API bool EmergencyStop(int& error);

		SOLOLIBRARY_API bool EmergencyStop();

		SOLOLIBRARY_API bool SetOutputPwmFrequencyKhz(long outputPwmFrequencyKhz, int& error);

		SOLOLIBRARY_API bool SetOutputPwmFrequencyKhz(long outputPwmFrequencyKhz);

		SOLOLIBRARY_API bool SetSpeedControllerKp(float speedControllerKp, int& error);

		SOLOLIBRARY_API bool SetSpeedControllerKp(float speedControllerKp);

		SOLOLIBRARY_API bool SetSpeedControllerKi(float speedControllerKi, int& error);

		SOLOLIBRARY_API bool SetSpeedControllerKi(float speedControllerKi);

		SOLOLIBRARY_API bool SetMotorDirection(Direction motorDirection, int& error);

		SOLOLIBRARY_API bool SetMotorDirection(Direction motorDirection);

		SOLOLIBRARY_API bool SetMotorResistance(float motorResistance, int& error);

		SOLOLIBRARY_API bool SetMotorResistance(float motorResistance);

		SOLOLIBRARY_API bool SetMotorInductance(float motorInductance, int& error);

		SOLOLIBRARY_API bool SetMotorInductance(float motorInductance);

		SOLOLIBRARY_API bool SetMotorPolesCounts(long motorPolesCounts, int& error);

		SOLOLIBRARY_API bool SetMotorPolesCounts(long motorPolesCounts);

		SOLOLIBRARY_API bool SetIncrementalEncoderLines(long incrementalEncoderLines, int& error);

		SOLOLIBRARY_API bool SetIncrementalEncoderLines(long incrementalEncoderLines);

		SOLOLIBRARY_API bool SetSpeedLimit(long speedLimit, int& error);

		SOLOLIBRARY_API bool SetSpeedLimit(long speedLimit);

		SOLOLIBRARY_API bool ResetDeviceAddress(int& error);

		SOLOLIBRARY_API bool ResetDeviceAddress();

		SOLOLIBRARY_API bool SetFeedbackControlMode(FeedbackControlMode mode, int& error);

		SOLOLIBRARY_API bool SetFeedbackControlMode(FeedbackControlMode mode);

		SOLOLIBRARY_API bool ResetFactory(int& error);

		SOLOLIBRARY_API bool ResetFactory();

		SOLOLIBRARY_API bool SetMotorType(MotorType motorType, int& error);

		SOLOLIBRARY_API bool SetMotorType(MotorType motorType);

		SOLOLIBRARY_API bool SetControlMode(ControlMode controlMode, int& error);

		SOLOLIBRARY_API bool SetControlMode(ControlMode controlMode);

		SOLOLIBRARY_API bool SetCurrentControllerKp(float currentControllerKp, int& error);

		SOLOLIBRARY_API bool SetCurrentControllerKp(float currentControllerKp);

		SOLOLIBRARY_API bool SetCurrentControllerKi(float currentControllerKi, int& error);

		SOLOLIBRARY_API bool SetCurrentControllerKi(float currentControllerKi);

		SOLOLIBRARY_API bool SetMonitoringMode(bool mode, int& error);

		SOLOLIBRARY_API bool SetMonitoringMode(bool mode);

		SOLOLIBRARY_API bool SetMagnetizingCurrentIdReference(float magnetizingCurrentIdReference, int& error);

		SOLOLIBRARY_API bool SetMagnetizingCurrentIdReference(float magnetizingCurrentIdReference);

		SOLOLIBRARY_API bool SetPositionReference(long positionReference, int& error);

		SOLOLIBRARY_API bool SetPositionReference(long positionReference);

		SOLOLIBRARY_API bool SetPositionControllerKp(float positionControllerKp, int& error);

		SOLOLIBRARY_API bool SetPositionControllerKp(float positionControllerKp);

		SOLOLIBRARY_API bool SetPositionControllerKi(float positionControllerKi, int& error);

		SOLOLIBRARY_API bool SetPositionControllerKi(float positionControllerKi);

		SOLOLIBRARY_API bool ResetPositionToZero(int& error); //Home

		SOLOLIBRARY_API bool ResetPositionToZero();

		SOLOLIBRARY_API bool OverwriteErrorRegister(int& error);

		SOLOLIBRARY_API bool OverwriteErrorRegister();

		SOLOLIBRARY_API bool SetObserverGainBldcPmsm(float observerGain, int& error);

		SOLOLIBRARY_API bool SetObserverGainBldcPmsm(float observerGain);

		SOLOLIBRARY_API bool SetObserverGainBldcPmsmUltrafast(float observerGain, int& error);

		SOLOLIBRARY_API bool SetObserverGainBldcPmsmUltrafast(float observerGain);

		SOLOLIBRARY_API bool SetObserverGainDc(float observerGain, int& error);

		SOLOLIBRARY_API bool SetObserverGainDc(float observerGain);

		SOLOLIBRARY_API bool SetFilterGainBldcPmsm(float filterGain, int& error);

		SOLOLIBRARY_API bool SetFilterGainBldcPmsm(float filterGain);

		SOLOLIBRARY_API bool SetFilterGainBldcPmsmUltrafast(float filterGain, int& error);

		SOLOLIBRARY_API bool SetFilterGainBldcPmsmUltrafast(float filterGain);

		SOLOLIBRARY_API bool SetUartBaudrate(UartBaudrate baudrate, int& error);

		SOLOLIBRARY_API bool SetUartBaudrate(UartBaudrate baudrate);

		SOLOLIBRARY_API bool SensorCalibration(PositionSensorCalibrationAction calibrationAction, int& error);

		SOLOLIBRARY_API bool SensorCalibration(PositionSensorCalibrationAction calibrationAction);

		SOLOLIBRARY_API bool SetEncoderHallCcwOffset(float encoderHallOffset, int& error);

		SOLOLIBRARY_API bool SetEncoderHallCcwOffset(float encoderHallOffset);

		SOLOLIBRARY_API bool SetEncoderHallCwOffset(float encoderHallOffset, int& error);

		SOLOLIBRARY_API bool SetEncoderHallCwOffset(float encoderHallOffset);

		SOLOLIBRARY_API bool SetSpeedAccelerationValue(float speedAccelerationValue, int& error);

		SOLOLIBRARY_API bool SetSpeedAccelerationValue(float speedAccelerationValue);

		SOLOLIBRARY_API bool SetSpeedDecelerationValue(float speedDecelerationValue, int& error);

		SOLOLIBRARY_API bool SetSpeedDecelerationValue(float speedDecelerationValue);

		SOLOLIBRARY_API bool SetCanbusBaudrate(CanbusBaudrate canbusBoudrate, int& error);

		SOLOLIBRARY_API bool SetCanbusBaudrate(CanbusBaudrate canbusBoudrate);

		////----------Read----------
		SOLOLIBRARY_API long  GetDeviceAddress(int& error);

		SOLOLIBRARY_API long  GetDeviceAddress();

		SOLOLIBRARY_API float GetPhaseAVoltage(int& error);

		SOLOLIBRARY_API float GetPhaseAVoltage();

		SOLOLIBRARY_API float GetPhaseBVoltage(int& error);

		SOLOLIBRARY_API float GetPhaseBVoltage();

		SOLOLIBRARY_API float GetPhaseACurrent(int& error);

		SOLOLIBRARY_API float GetPhaseACurrent();

		SOLOLIBRARY_API float GetPhaseBCurrent(int& error);

		SOLOLIBRARY_API float GetPhaseBCurrent();

		SOLOLIBRARY_API float GetBusVoltage(int& error); //Battery Voltage

		SOLOLIBRARY_API float GetBusVoltage();

		SOLOLIBRARY_API float GetDcMotorCurrentIm(int& error);

		SOLOLIBRARY_API float GetDcMotorCurrentIm();

		SOLOLIBRARY_API float GetDcMotorVoltageVm(int& error);

		SOLOLIBRARY_API float GetDcMotorVoltageVm();

		SOLOLIBRARY_API float GetSpeedControllerKp(int& error);

		SOLOLIBRARY_API float GetSpeedControllerKp();

		SOLOLIBRARY_API float GetSpeedControllerKi(int& error);

		SOLOLIBRARY_API float GetSpeedControllerKi();

		SOLOLIBRARY_API long  GetOutputPwmFrequencyKhz(int& error);

		SOLOLIBRARY_API long  GetOutputPwmFrequencyKhz();

		SOLOLIBRARY_API float GetCurrentLimit(int& error);

		SOLOLIBRARY_API float GetCurrentLimit();

		SOLOLIBRARY_API float GetQuadratureCurrentIqFeedback(int& error);

		SOLOLIBRARY_API float GetQuadratureCurrentIqFeedback();

		SOLOLIBRARY_API float GetMagnetizingCurrentIdFeedback(int& error); //Magnetizing

		SOLOLIBRARY_API float GetMagnetizingCurrentIdFeedback();

		SOLOLIBRARY_API long  GetMotorPolesCounts(int& error);

		SOLOLIBRARY_API long  GetMotorPolesCounts();

		SOLOLIBRARY_API long  GetIncrementalEncoderLines(int& error);

		SOLOLIBRARY_API long  GetIncrementalEncoderLines();

		SOLOLIBRARY_API float GetCurrentControllerKp(int& error);

		SOLOLIBRARY_API float GetCurrentControllerKp();

		SOLOLIBRARY_API float GetCurrentControllerKi(int& error);

		SOLOLIBRARY_API float GetCurrentControllerKi();

		SOLOLIBRARY_API float GetBoardTemperature(int& error);

		SOLOLIBRARY_API float GetBoardTemperature();

		SOLOLIBRARY_API float GetMotorResistance(int& error);

		SOLOLIBRARY_API float GetMotorResistance();

		SOLOLIBRARY_API float GetMotorInductance(int& error);

		SOLOLIBRARY_API float GetMotorInductance();

		SOLOLIBRARY_API long  GetSpeedFeedback(int& error);

		SOLOLIBRARY_API long  GetSpeedFeedback();

		SOLOLIBRARY_API long  GetMotorType(int& error);

		SOLOLIBRARY_API long  GetMotorType();

		SOLOLIBRARY_API long  GetFeedbackControlMode(int& error);

		SOLOLIBRARY_API long  GetFeedbackControlMode();

		SOLOLIBRARY_API long  GetCommandMode(int& error);

		SOLOLIBRARY_API long  GetCommandMode();

		SOLOLIBRARY_API long  GetControlMode(int& error);

		SOLOLIBRARY_API long  GetControlMode();

		SOLOLIBRARY_API long  GetSpeedLimit(int& error);

		SOLOLIBRARY_API long  GetSpeedLimit();

		SOLOLIBRARY_API float GetPositionControllerKp(int& error);

		SOLOLIBRARY_API float GetPositionControllerKp();

		SOLOLIBRARY_API float GetPositionControllerKi(int& error);

		SOLOLIBRARY_API float GetPositionControllerKi();

		SOLOLIBRARY_API long  GetPositionCountsFeedback(int& error);

		SOLOLIBRARY_API long  GetPositionCountsFeedback();

		SOLOLIBRARY_API long  GetErrorRegister(int& error);

		SOLOLIBRARY_API long  GetErrorRegister();

		SOLOLIBRARY_API long  GetDeviceFirmwareVersion(int& error);

		SOLOLIBRARY_API long  GetDeviceFirmwareVersion();

		SOLOLIBRARY_API long  GetDeviceHardwareVersion(int& error);

		SOLOLIBRARY_API long  GetDeviceHardwareVersion();

		SOLOLIBRARY_API float GetTorqueReferenceIq(int& error);

		SOLOLIBRARY_API float GetTorqueReferenceIq();

		SOLOLIBRARY_API long  GetSpeedReference(int& error);

		SOLOLIBRARY_API long  GetSpeedReference();

		SOLOLIBRARY_API float GetMagnetizingCurrentIdReference(int& error);

		SOLOLIBRARY_API float GetMagnetizingCurrentIdReference();

		SOLOLIBRARY_API long  GetPositionReference(int& error);

		SOLOLIBRARY_API long  GetPositionReference();

		SOLOLIBRARY_API float GetPowerReference(int& error);

		SOLOLIBRARY_API float GetPowerReference();

		SOLOLIBRARY_API long  GetMotorDirection(int& error);

		SOLOLIBRARY_API long  GetMotorDirection();

		SOLOLIBRARY_API float GetObserverGainBldcPmsm(int& error);

		SOLOLIBRARY_API float GetObserverGainBldcPmsm();

		SOLOLIBRARY_API float GetObserverGainBldcPmsmUltrafast(int& error);

		SOLOLIBRARY_API float GetObserverGainBldcPmsmUltrafast();

		SOLOLIBRARY_API float GetObserverGainDc(int& error);

		SOLOLIBRARY_API float GetObserverGainDc();

		SOLOLIBRARY_API float GetFilterGainBldcPmsm(int& error);

		SOLOLIBRARY_API float GetFilterGainBldcPmsm();

		SOLOLIBRARY_API float GetFilterGainBldcPmsmUltrafast(int& error);

		SOLOLIBRARY_API float GetFilterGainBldcPmsmUltrafast();

		SOLOLIBRARY_API float Get3PhaseMotorAngle(int& error); // Read Estimated or Measured Rotor Angle

		SOLOLIBRARY_API float Get3PhaseMotorAngle();

		SOLOLIBRARY_API float GetEncoderHallCcwOffset(int& error);

		SOLOLIBRARY_API float GetEncoderHallCcwOffset();

		SOLOLIBRARY_API float GetEncoderHallCwOffset(int& error);

		SOLOLIBRARY_API float GetEncoderHallCwOffset();

		SOLOLIBRARY_API long  GetUartBaudrate(int& error);

		SOLOLIBRARY_API long  GetUartBaudrate();

		SOLOLIBRARY_API float GetSpeedAccelerationValue(int& error);

		SOLOLIBRARY_API float GetSpeedAccelerationValue();

		SOLOLIBRARY_API float GetSpeedDecelerationValue(int& error);

		SOLOLIBRARY_API float GetSpeedDecelerationValue();

		SOLOLIBRARY_API long  GetEncoderIndexCounts(int& error);

		SOLOLIBRARY_API long  GetEncoderIndexCounts();

		SOLOLIBRARY_API bool CommunicationIsWorking(int& error);

		SOLOLIBRARY_API bool CommunicationIsWorking();

	};

#ifdef __cplusplus
} // __cplusplus defined.
#endif
