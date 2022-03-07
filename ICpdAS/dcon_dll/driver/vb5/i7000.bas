Attribute VB_Name = "i7000"
 Option Explicit
'------------------------ Error Message ------------------
Global Const NoError = 0
Global Const FunctionError = 1
Global Const PortError = 2
Global Const BaudRateError = 3
Global Const DataError = 4
Global Const StopError = 5
Global Const ParityError = 6
Global Const CheckSumError = 7
Global Const ComPortNotOpen = 8


Global Const SendThreadCreateError = 9
Global Const SendCmdError = 10
Global Const ReadComStatusError = 11
Global Const ResultStrCheckError = 12
Global Const CmdError = 13
Global Const TimeOut = 15
Global Const ModuleIdError = 17
Global Const AdChannelError = 18
Global Const UnderInputRange = 19
Global Const ExceedInputRange = 20
Global Const InvalidateCounterNo = 21
Global Const InvalidateCounterValue = 22

'----------------------  UART.DLL -----------------------------------------------
Declare Function Get_Uart_Version Lib "uart.dll" () As Integer

Declare Function Open_Com Lib "uart.dll" (ByVal Port As Integer, ByVal BaudRate As Long, ByVal cData As Byte, ByVal cParity As Byte, ByVal cStop As Byte) As Integer

Declare Function Change_Baudrate Lib "uart.dll" (ByVal Port As Integer, ByVal lBaudrate As Long) As Integer

Declare Function Change_Config Lib "uart.dll" (ByVal Port As Integer, ByVal BaudRate As Long, ByVal cData As Byte, ByVal cParity As Byte, ByVal cStop As Byte) As Integer

Declare Function Get_Com_Status Lib "uart.dll" (ByVal Port As Integer) As Integer

Declare Function Close_Com Lib "uart.dll" (ByVal Port As Integer) As Boolean

Declare Function Send_Binary Lib "uart.dll" (ByVal Port As Integer, ByRef szBuf As Byte, ByVal length As Integer) As Integer

Declare Function Receive_Binary Lib "uart.dll" (ByVal Port As Integer, ByRef szResult As Byte, ByVal TimeOut As Integer, ByVal length As Integer, wT As Integer) As Integer
        
'Receive_Binary(unsigned char cPort, char szResult[], WORD wTimeOut, WORD wLen, WORD *wT)

Declare Function Send_Cmd Lib "uart.dll" (ByVal Port As Integer, ByVal Cmd As String, ByVal wChkSum As Integer) As Integer

Declare Function Receive_Cmd Lib "uart.dll" (ByVal Port As Integer, ByVal szResult As String, ByVal TimeOut As Integer, ByVal Checksum As Integer, wT As Integer) As Integer


Declare Function Send_Receive_Cmd Lib "uart.dll" (ByVal Port As Integer, ByVal szCmd As String, ByVal szResult As String, ByVal TimeOut As Integer, ByVal Checksum As Integer, wT As Integer) As Integer
        
Declare Function Send_Receive_Binary Lib "uart.dll" (ByVal Port As Integer, ByRef CmdByte As Byte, ByVal in_Len As Integer, ByRef ResultByte As Byte, ByVal out_Len As Integer, ByVal wTimeOut As Integer) As Integer
                
Declare Function ModbusGetCRC16 Lib "uart.dll" (ByRef puchMsg As Byte, ByRef crc As Byte, ByVal DataLen As Integer) As Integer
                
'----------------------  I7000.DLL --------------------------------------------
Declare Function Get_Dll_Version Lib "I7000.dll" () As Integer
Declare Function GetChCount_FR Lib "I7000.dll" (ByVal bPort As Byte, ByVal bAdd As Byte, ByVal bcheck As Byte, ByVal wTimeOut As Integer, ByRef wDICh As Integer, ByRef wDOCh As Integer, ByRef wAICh As Integer, ByRef wAOCh As Integer) As Integer
Declare Function DigitalOutAll_FR Lib "I7000.dll" (ByVal bPort As Byte, ByVal bAdd As Byte, ByVal bcheck As Byte, ByVal wTimeOut As Integer, ByVal wGroupCount As Integer, ByRef wDO As Long) As Integer
Declare Function DigitalOutGroup_FR Lib "I7000.dll" (ByVal bPort As Byte, ByVal bAdd As Byte, ByVal bcheck As Byte, ByVal wTimeOut As Integer, ByVal wGroupIndex As Integer, ByVal wDO As Long) As Integer
Declare Function DigitalOutBit_FR Lib "I7000.dll" (ByVal bPort As Byte, ByVal bAdd As Byte, ByVal bcheck As Byte, ByVal wTimeOut As Integer, ByVal wBitIndex As Integer, ByVal wDO As Integer) As Integer
Declare Function DigitalIOReadBackAll_FR Lib "I7000.dll" (ByVal bPort As Byte, ByVal bAdd As Byte, ByVal bcheck As Byte, ByVal wTimeOut As Integer, ByRef wDO As Long, ByRef wDI As Long) As Integer
Declare Function DigitalIOReadBackGroup_FR Lib "I7000.dll" (ByVal bPort As Byte, ByVal bAdd As Byte, ByVal bcheck As Byte, ByVal wTimeOut As Integer, ByVal wType As Integer, ByVal wGroupIndex As Integer, ByRef wIOValue As Long) As Integer
Declare Function DigitalIOReadBackBit_FR Lib "I7000.dll" (ByVal bPort As Byte, ByVal bAdd As Byte, ByVal bcheck As Byte, ByVal wTimeOut As Integer, ByVal wType As Integer, ByVal wBitIndex As Integer, ByRef wIOBit As Integer) As Integer
Declare Function DigitalOnLineStatus_FR Lib "I7000.dll" (ByVal bPort As Byte, ByVal bAdd As Byte, ByVal bcheck As Byte, ByVal wTimeOut As Integer, ByVal wType As Integer, ByRef wDIOStatus As Integer) As Integer

Declare Function ReadConfigStatus Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function Test Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function AnalogIn Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function AnalogInFsr Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function AnalogInHex Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function AnalogIn8 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function AnalogInAll Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
                                                               
Declare Function In8_7017 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
                                                               
Declare Function AnalogOut Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

Declare Function AnalogOutReadBack Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

Declare Function DigitalOut Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
                
Declare Function DigitalOut_7016 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
                
Declare Function DigitalOutReadBack Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

Declare Function DigitalIn Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function DigitalInCounterRead Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ClearDigitalInCounter Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function DigitalInLatch Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ClearDigitalInLatch Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

Declare Function ThermocoupleOpen_7011 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

Declare Function EnableAlarm Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function DisableAlarm Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ClearLatchAlarm Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function SetAlarmLimitValue Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadAlarmLimitValue Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadOutputAlarmState Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadEventCounter Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

Declare Function ClearEventCounter Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

Declare Function SetLedDisplay_7033 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function GetLedDisplay_7033 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

Declare Function SetLedDisplay Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function GetLedDisplay Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

Declare Function SetupLinearMapping Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function DisableLinearMapping Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function EnableLinearMapping Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadLinearMappingStatus Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadSourceValueOfLM Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadTargetValueOfLM Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

Declare Function CounterIn_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadCounterMaxValue_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function SetCounterMaxValue_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String, ByVal MaxValue As Double) As Integer
Declare Function ReadAlarmLimitValue_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function SetAlarmLimitValue_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String, ByVal AlarmValue As Double) As Integer
Declare Function ReadCounterStatus_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ClearCounter_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadOutputAlarmState_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function EnableCounterAlarm_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function DisableCounterAlarm_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function EnableCounterAlarm_7080D Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function DisableCounterAlarm_7080D Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function SetInputSignalMode_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadInputSignalMode_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadPresetCounterValue_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function PresetCounterValue_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String, ByVal PresetValue As Double) As Integer
Declare Function StartCounting_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadModuleMode_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function SetModuleMode_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadLevelVolt_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadMinSignalWidth_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function SetMinSignalWidth_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String, ByVal MinWidth As Long) As Integer
Declare Function SetGateMode_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadGateMode_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function DataToLED_7080 Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer


'----------------------for7082, 87082, 8080----------------------------------------------------------
Declare Function ReadCounter Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
                
Declare Function ReadUpDownDirPulse Lib "I7000.dll" (dwBuf As Long, IBuf As Integer, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

Declare Function ReadCounter_All Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadFreq Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadFreq_All Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

Declare Function ClearCounter Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String, ByVal MaxValue As Double) As Integer
Declare Function SetCounterStatus Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadCounterStatus Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String, ByVal AlarmValue As Double) As Integer

'--------------------- for 8K series -------------------------------------------
Declare Function AnalogIn_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function AnalogInFsr_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function AnalogInHex_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function AnalogInAll_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function SetAlarmConnect_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function SetAlarmLimitValue_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadAlarmLimitValue_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ClearLatchAlarm_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadAlarmMode_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function SetAlarmMode_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function AnalogOut_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function AnalogOutReadBack_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadAlarmStatus_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function SetConfigurationStatus_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadConfigurationStatus_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function SetStartUpValue_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadStartUpValue_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

Declare Function DigitalOut_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo8000 As String, ByVal ReceiveFrom8000 As String) As Integer
Declare Function DigitalOutReadBack_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo8000 As String, ByVal ReceiveFrom8000 As String) As Integer
Declare Function DigitalIn_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo8000 As String, ByVal ReceiveFrom8000 As String) As Integer
Declare Function DigitalBitOut_8K Lib "I7000.dll" (w7000 As Long, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

Declare Function DigitalInCounterRead_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo8000 As String, ByVal ReceiveFrom8000 As String) As Integer
Declare Function ClearDigitalInCounter_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo8000 As String, ByVal ReceiveFrom8000 As String) As Integer
Declare Function DigitalInLatch_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo8000 As String, ByVal ReceiveFrom8000 As String) As Integer
Declare Function ClearDigitalInLatch_8K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo8000 As String, ByVal ReceiveFrom8000 As String) As Integer



'--------------------- for 87K series -------------------------------------------
Declare Function AnalogIn_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function AnalogInFsr_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function AnalogInHex_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function AnalogInAll_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
                
Declare Function AnalogOut_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function AnalogOutReadBack_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
                
Declare Function AnalogOutFsr_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function AnalogOutReadBackFsr_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
                
Declare Function AnalogOutHex_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function AnalogOutReadBackHex_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

Declare Function SetConfigurationStatus_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadConfigurationStatus_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function SetStartUpValue_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadStartUpValue_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

Declare Function DigitalInCounterRead_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo8000 As String, ByVal ReceiveFrom8000 As String) As Integer
Declare Function ClearDigitalInCounter_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo8000 As String, ByVal ReceiveFrom8000 As String) As Integer
Declare Function DigitalInLatch_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo8000 As String, ByVal ReceiveFrom8000 As String) As Integer
Declare Function ClearDigitalInLatch_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo8000 As String, ByVal ReceiveFrom8000 As String) As Integer
Declare Function DigitalOut_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo8000 As String, ByVal ReceiveFrom8000 As String) As Integer
Declare Function DigitalOutReadBack_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo8000 As String, ByVal ReceiveFrom8000 As String) As Integer
Declare Function DigitalIn_87K Lib "I7000.dll" (dwBuf As Long, fBuf As Single, ByVal SendTo8000 As String, ByVal ReceiveFrom8000 As String) As Integer
Declare Function DigitalBitOut_87K Lib "I7000.dll" (w7000 As Long, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadOutputAlarmState_87K Lib "I7000.dll" (dwBuf As Long, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function SetAlarmLimitValue_87K Lib "I7000.dll" (dwBuf As Long, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadAlarmLimitValue_87K Lib "I7000.dll" (dwBuf As Long, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadEventCounter_87K Lib "I7000.dll" (dwBuf As Long, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ClearEventCounter_87K Lib "I7000.dll" (dwBuf As Long, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function EnableAlarm_87K Lib "I7000.dll" (dwBuf As Long, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function DisableAlarm_87K Lib "I7000.dll" (dwBuf As Long, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ClearLatchAlarm_87K Lib "I7000.dll" (dwBuf As Long, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

Declare Function SetupLinearMapping_87K Lib "I7000.dll" (dwBuf As Long, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function DisableLinearMapping_87K Lib "I7000.dll" (dwBuf As Long, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function EnableLinearMapping_87K Lib "I7000.dll" (dwBuf As Long, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadLinearMappingStatus_87K Lib "I7000.dll" (dwBuf As Long, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadSourceValueOfLM_87K Lib "I7000.dll" (dwBuf As Long, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function ReadTargetValueOfLM_87K Lib "I7000.dll" (dwBuf As Long, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function DigitalOut_87016 Lib "I7000.dll" (dwBuf As Long, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

Declare Function FloatToHex Lib "I7000.dll" (ByVal fv As Single) As Long


' function for WDT
Declare Function HostIsOK Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

'--- Read the module reset status, $AA5 --------*/
Declare Function ReadModuleResetStatus Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer


'--- To setup host watchdog, ~AA3ETT --------*/
Declare Function ToSetupHostWatchdog Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer


'--- To read host watchdog setup value, ~AA2 --------*/
Declare Function ToReadHostWatchdog Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer





'--- Read the module status about the host watchdog, ~AA0 --------*/
Declare Function ReadModuleHostWatchdogStatus Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer


'--- Reset the module status about the host watchdog, ~AA1 --------*/
Declare Function ResetModuleHostWatchdogStatus Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

'function for 7000 AO
Declare Function SetPowerOnValueForAo Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer
Declare Function SetSafeValueForAo Lib "I7000.dll" (w7000 As Integer, f7000 As Single, ByVal SendTo7000 As String, ByVal ReceiveFrom7000 As String) As Integer

