## 0x00 ManufacturerAccess() & 0x44 ManufacturerBlockAccess()

1. ManufacturerAccess()和ManufacturerBlockAccess()命令可以提供各种数据:
- ManufacturerAccess()通过智能电池数据集标准提供对数据的访问，包括在SEALED模式下，使用一个ManufacturerAccess()写字序列和一个ManufacturerData()读取数据块
- ManufacturerBlockAccess()是一个扩展命令，允许访问相同的数据，但是通过一个更简单的块对同一个命令进行写/读序列。
2. ManufacturerAccess()读取LifetimeDataBlock1()的示例:
- 通过 ManufacturerAccess()发送LifetimeDataBlock1()的cmd指令:也就是给command0x00写入0x0060
- 接着读去command0x23，返回块的前两个字节是数据长度
下一个字节是命令的数据。

## ManufacturerAccess() 的command列表
| command    | 功能   | 操作权限 | 备注  |
| ------ | ---------- | ---- | ---- |
| 0x0001 | DeviceType | R   | 设备类型  |
| 0x0002 | FirmwareVersion  | R      |固件版本      |
| 0x0003       | HardwareVersion|    R  |  硬件版本    |
|0x0004|IFChecksum|R | Instruction Flash Signature|
|0x0005|StaticDFSignature|R||
|0x0006|ChemID|R ||
|0x0008|StaticChemDFSignature|R||
|0x0009|AllDFSignature|R||
|0x0010|ShutdownMode|W||
|0x0011|SleepMode|W||
|0x0012|DeviceReset|W||
|0x001B|CellBalanceToggle|W||
|0x001C|AFEDelayDisable|W||
|0x001D|SAFEToggle|W||
|0x001E|PrechargeFET|W||
|0x001F|ChargeFET|W||
|0x0020|DischargeFET|W||
|0x0021|Gauging|W||
|0x0022|FETControl|W||
|0x0023|LifetimeDataCollection|W||
|0x0024|PermanentFailure|W||
|0x0025|BlackBoxRecorder|W||
|0x0026|SAFE|W||
|0x0027|LEDDisplayEnable|W||
|0x0028|LifetimeDataReset|W||
|0x0029|PermanentFailureDataReset|W||
|0x002A|BlackBoxRecorderReset|W||
|0x002B|LED Toggle|W||
|0x002C|LEDDisplayPress|W||
|0x002D|CalibrationMode|W||
|0x0030|SealDevice|W||
|0x0035|SecurityKeys|R/W||
|0x0037|AuthenticationKey|W||
|0x0041|DeviceReset|W||
|0x0050|SafetyAlert|W||
|0x0051|SafetyStatus|W||
|0x0052|PFAlert|W||
|0x0053|PFStatus|W||
|0x0054|OperationStatus|W||
|0x0055|ChargingStatus|W||
|0x0056|GaugingStatus|W||
|0x0057|ManufacturingStatus|W||




### 0X0001 DeviceType
设备可以检查IC零件号。当0x0001被写入到ManufacturerAccess()时BQ78350-R1在随后的ManufacturerBlockAccess()或读取时返回IC部件编号如下格式的ManufacturerData(): aaAA

| data   | 备注  |
| ------ | ---- |
| aaAA | DeviceType |

### 0x0002 FirmwareVersion
当写入0x0002时，设备可以检查IC的固件版本制造访问，BQ78350-R1返回的固件版本格式如下:ddDDvvVVbbBBTTzzZZRREE
其中：
| value   | 描述  |
| ------ | ---- |
| ddDD | 设备号 |
|vvVV|版本|
|bbBB|编译版本|
|ttTT|固件类型
|zzZZ|字符设备版本|
|RREE|保留|

### 0x0003 HardwareVersion

写入硬件版本
例如格式：aaAA

### 0x0004 Flash签名指令

设备可以返回指令flash签名。当将0x0004写入到ManufacturerAccess()时
BQ78350-R1返回后续读取ManufacturerBlockAccess()或时的IF签名
经过250毫秒的等待时间后的ManufacturerData()

### 睡眠模式

| 状态| 条件 |动作|
| -- | -- | ---|
|ENABLE|发送0x0011到ManufacturerAccess()|睡眠
|Activate| 电流小于睡眠电流|关闭充放电MOS，设备进睡眠|
|EXIT|电流大于睡眠电流|返回Normal模式
|EXIT|SafetyAlert() flag or PFAlert() flag set|返回Normal模式

### 0x001B CellBalanceToggle
关闭或激活内部平衡MOS  一般还是不动了把  一般用于内部测试用


### 0x001C AFEDelayDisable

### 0x001F CHG FET
该命令打开/关闭CHG FET驱动功能，当0x001F是当ManufacturingStatus()[FET_EN,CHG_TEST] = 0,0时，写入到ManufacturerAccess()，然后CHG
打开并将ManufacturingStatus()[CHG_TEST]设置为1。如果将0x001F写入ManufacturerAccess()再次，CHG关闭，ManufacturingStatus()[CHG_TEST]被清除为0

### 0x0020 DSG FET
该命令打开/关闭DSG FET驱动功能，以简化制造过程中的测试。当0x0020为
当ManufacturingStatus()[FET_EN, DSG_TEST] = 0,0时，写入到ManufacturerAccess()，然后DSG打开并将ManufacturingStatus()[DSG_TEST]设置为1。如果将0x0020写入ManufacturerAccess()再一次，DSG关闭并且ManufacturingStatus()[DSG_TEST]被清除到0。

### 0x0022 FET Control
该命令禁用/启用固件对CHG、DSG和PCHG FET的控制。当0x0022
当ManufacturingStatus()[FET_EN] = 0时，被写入到ManufacturerAccess()，那么fet由
firmware和ManufacturingStatus()[FET_EN]被设置为1。如果将0x0022写入ManufacturerAccess()
再次，然后CHG, DSG和PCHG关闭，并且ManufacturingStatus()[FET_EN]清除为0。