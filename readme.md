### 1、环境搭建
#### 1.1、IDE安装

Telink官方论坛主页：http://wiki.telink-semi.cn/wiki/IDE-and-Tools/IDE-for-TLSR8-Chips/ ->  Telink IDE（集成开发环境）->  按指导进行安装

将 `doc\tools\jq-win64.exe` 放入 `C:\TelinkSDK\bin\`

将下面路径加入系统环境变量中：

```
C:\TelinkSDK\opt\Vim\vim73\;	
C:\TelinkSDK\opt\tc32\bin\;	
C:\TelinkSDK\bin\;	
C:\TelinkSDK\opt\tc32\tools\;	
```

<br>

#### 1.2、烧写调试助手安装

Telink官方论坛主页：http://wiki.telink-semi.cn/wiki/IDE-and-Tools/Burning-and-Debugging-Tools-for-all-Series/ -> Burning and Debugging Tools (BDT) -> 下载解压即可

<br>

#### 1.3、git安装

从 https://git-scm.com/download/win 下载 `git-for-win` 并安装（不熟悉的人建议全部采用默认安装,如果电脑上已经有git-bash之类的可以运行sh脚本的软件可以不用安装）

<br>

### 2、上手

#### 2.1 build

利用 `app/mesh_common/_build` 中的 `run.sh` 脚本，可以实现编译、烧录：

`bash run.sh build/flash [app_config.json]`

该脚本会将 `[app_config.json]` 转变为 `_build/base_oem_config.h`, 其中有大量的宏定义，用于让同一个应用代码，能生成不同的应用程序（如：只需要改动生成固件的名字、版本号、PID等信息时，不需要改动代码，只需要改动该 json 配置文件）。

凡是能通过修改 `[app_config.json]` 能满足客户需求，尽量不要修改APP代码，这样产出的固件风险性小；凡是不能通过修改 `[app_config.json]`满足客户需求的，建议采用复制一个相似的 `app_name` 进行改动开发。一般情况不建议产生大量做简单修改不同的 `app`，而推荐考虑加强 `[app_config.json]` 能力。


```
$ cd app/mesh_common/_build
$ bash run.sh build  package.json
```

<br>

#### 2.2 flash

1）将烧写器的SWM引脚与开发板的SWS引脚相连，烧写器通过 USB 连接到电脑上，开发板单独供电（保持共地）；

![][p1]

<br>

2）打开 Telink 烧写调试助手 (BTD)，选择 8258 芯片，点击 SWS 初始配置烧写器（让烧写器可以烧录 8258 型号芯片，往往只需要 SWS 一次即可）：

![][p2]


<br>

3）在 Git Bash 中输入：tcdb.exe rst看到下面的结果，表明待烧写板子已经成功连接到烧写板子上：

```
$ tcdb.exe rst
  Slave MCU Reset
```

<br>

上面准备工作做好后，可以直接利用 run.sh 将 bin 文件烧录到开发板：

```
$ bash run.sh flash  package.json
```

<br>

**附：一个典型的应用参数配置 json 介绍**

```
{
    "name": "tlsr_825x_sig_mesh_common",		//最终生成固件的名字
    "description": "mesh_base_test",			//无用
    "version": "1.0",					//最终生成固件的版本号（0.0~F.F)
    "ic":"tlsr825x",					//不要改动
    "hardware":"TYBT3L",				//不要改动
    "build":{
        "log":"0",					//调试时用来打印log
        "oem":"0",					//不用改动
        "json_config":"0"				//不用改动
    },
    "directories": {					//无用
        "bin": "../../sdk/DEBUG/light.bin",
        "doc": "../../doc/",
        "sdk": "../../sdk/",
        "tools": "../../tools/"
    },
    "product":{
        "kind":"sig_mesh_light",			 //不用改动
        "pid":"33lnzacq",				 /产品ID，PID
        "vendorid":"2000",				 //不用改动
        "local_control":"1"				 //不用改动
    }
    ...
}
```

<br>

### 3、代码架构

**tuya_mesh_sdk** 整个架构主要包括app（应用）、includes（头文件）、libs（SDK库）。

```
.
├── app
│   └── mesh_common
│       ├── app
│       ├── _build
│       ├── config.json
│       └── package.json
├── includes
│   ├── board
│   │   ├── bal
│   │   ├── board.h
│   │   ├── chip
│   │   └── hal
│   └── components
│       ├── ty_fifo.h
│       ├── ty_gpio_base_test.h
│       ├── ty_nv.h
│       ├── ty_rssi_base_test.h
│       ├── ty_string_op.h
│       ├── ty_timer_event.h
│       ├── ty_uart_cmd_server_for_factory_test.h
│       └── ty_uart_cmd_server_for_sig_mesh_uart_common.h
├── libs
│   └── libtuya_ble_os.a
└── readme.md
```

<br>

### 4、应用详解

#### 4.1、应用层文件介绍

```
➜  app git:(master) ✗ tree -L 1
.
├── app_common.c				//入口文件
├── app_factory_test.c				//烧录授权相关（不用改动）
├── app_mcu_protocol.c				//通用对接应用逻辑（将手机发来的命令通过串口转发给MCU，或将MCU发来的数据发送给手机）
├── app_rssi.c					//烧录授权相关（不用改动）
├── app_storage.c				//一个基于可用的 4K flash 做的简单的增量信息存储的demo (目前用来存一些标志位)
├── app_uart.c					//烧录授权相关（不用改动）
├── app_unprov_beacon.c				//mesh 广播包初始化相关（一般不用改动）
└── tuya_node_init.c				//mesh 各种参数初始化相关（一般不用改动）
```

<br>

#### 4.2、入口

入口文件：app_common.c 

勾连sdk层和app层，其中：

- void mesh_app_init(void)		
	- 用于应用层逻辑的初始化
- void mesh_main_run(void)
	- 用于应用层逻辑的周期性执行 	
- void mesh_factory_reset(void)
	- 设备被重置前会调用该函数，用于应用层在设备重置时清空一些应用层级别的 flash 数据
- void tuya_mdev_test(uint8_t is_Authorized, uint8_t rssi)
	- 烧录授权时的产测回调函数，一般不要改，不要动 
- void mesh_state_callback(mesh_state_t stat)
	- 各种mesh状态发生变化时，会调用该函数，通知给应用层（看 mesh_state_t 可知道有哪些信息会上报）
- void tuya_mesh_data_recv_callback(uint16_t src_addr, uint16_t dst_addr, uint32_t opcode, uint8_t *data, uint16_t data_len, uint8_t ttl)
	- 手机 -> 设备的数据回调函数（非常重要）

<br>

#### 4.2、串口数据流

主要文件：app_uart.c

- void app_uart_init(void)  			
	- 除了串口初始化，还有 FIFO 初始化、存储初始化、广播初始化、产测初始化、与mcu通信初始化 

- void app_uart_run(void)
	- 是一个 loop 函数，不断执行从串口读取数据，放入 fifo 中
	- 此外还有三个 loop 函数在这个总的 loop 中执行
		- app_mcu_protocol_run();
		- app_factory_test_run();
		- uart_server_run();//解析FIFO中的数据，并调用相应的处理函数 	
- static void uart_server_run(void)
	- 按照串口协议解析 FIFO 中的串口数据，获取有效的数据帧，根据数据帧类别，分别送到：
		- 产测数据处理接口 app_factory_test_cmd(cmd,&buf[F_DATA],len) 
		- 与 MCU 通信的串口对接数据处理接口 app_mcu_protocol_cmd(cmd,&buf[F_DATA],len)	 
	- 串口数据格式为： 
	
		HEAD | VERSION | CMD | lenght | datas | check-sum
		---|---|---|---|---|---
		2 | 1 | 1 | 2 | lenght | 1
		55 AA | 00 | 命令字 | 长度 (大端模式表示) | 数据 | 和校验
    
    **注：** HEAD 中是 55 AA 表示是 MCU 发来的数据；是 66 AA 表示是产测上位机发来的数据。

**注：** 该文件及产测授权相关文件（app_factory_test.c、app_rssi.c）一般不要动，否则会对产测授权造成影响。

<br>

#### 4.3、通用对接数据流

主要文件：app_mcu_protocol.c

- **MCU -> BT 串口数据流：** uart_server_run() -> app_mcu_protocol_cmd(cmd,&buf[F_DATA],len) -> ty_uart_cmd_server_for_sig_mesh_uart_common.receive_cmd(cmd,data,len);
	- 其中最后一个函数是封装在 SDK 内部的函数，会对串口数据进行解析，调用相关函数 （心跳交互、数据状态上报... 具体可以参考：[《BLE Mesh 通用串口协议》][#1]）
	- <font color="#FF000">  用户如果打算做 SOC 应用，可以将 ty_uart_cmd_server_for_sig_mesh_uart_common.receive_cmd(cmd,data,len) 去掉</font>

- **手机 -> BT -> MCU 数据流：** tuya_mesh_data_recv_callback(...) -> app_mesh_vendor_write 或 app_mesh_vendor_read -> ty_uart_cmd_server_for_sig_mesh_uart_common.send_cmd(...)
	- 其中最后一个函数是封装在 SDK 内部的函数，会对手机传过来的 DP 数据进行封装、通过串口发送给 MCU.
	- <font color="#FF000"> 用户如果打算做 SOC 应用，可以将 ty_uart_cmd_server_for_sig_mesh_uart_common.send_cmd(...) 去掉，自己在 SOC 中写对应逻辑，处理 DP 数据 </font>

- **BT -> 手机数据流：** 蓝牙模块给手机或其他设备发送命令，主要用： app_mesh_vendor_ad_tx(...) 函数
	
    函数名 | void app_mesh_vendor_ad_tx(u16 adr_src, u16 adr_dst, u8 *params, u8 len, u8 is_use_params_adr)
	---|---
    adr_src | 源地址（底层会自动填充该字段，因此可以默认填写 0x0000）
    adr_dst | 目的地址（命令投递的目的地址） <br> 特别地：<br> - 当 is_use_params_adr = 1 时，实际目的地址用 adr_dst （用于主动上报、主动推送，这个一般的应用使用较少，主要用于设备与设备之间相互发送命令） <br> - 当 is_use_params_adr = 0 时，实际目的地址用 ad_tx_adress （用于回复，如手机下发一个开关命令，设备执行了开关动作，需要回复最新的开关状态）
    params <br> len | 需要发送的数据，参考 [《DP格式说明》][#2] <br> params[0] = dp_id <br> params[1] = dp_type <br> params[2:3] = dp_len  <br> params[4:...] = dp_data <br><br>  支持多个 dp 一起上报，但是一般建议单条上报的 len ≤ 4，否则 mesh 底层就会采用分包的方式才能将数据发送出去 <br> 调用该函数不能太频繁，控制单包数据 340ms（即：如果发送的数据的 len = 8，建议至少间隔 680ms）
	

<br>

### 5、重要 API 介绍
#### 5.1、mesh 相关 API

tuya_mesh_node_init

| 函数名 | tuya_mesh_node_init |
| :- | :- |
| **函数原型** | void tuya_mesh_node_init(node_info_t *node_info) |
| **功能概述** | mesh 节点初始化，相关能力的配置 |
| **参数** | node_info[in]：节点能力设置 |
| **返回值** | 无 |
| **备注** | 设备初始化流程，必须调用 |

tuya_mesh_data_recv_callback

| 函数名 | tuya_mesh_data_recv_callback |
| :- | :- |
| **函数原型** | void tuya_mesh_data_recv_callback(uint16_t src_addr, uint16_t dst_addr, uint32_t opcode, uint8_t *data, uint16_t data_len, uint8_t ttl) |
| **功能概述** | mesh 应用数据接收 API |
| **参数** | src_addr[in]：数据源地址 <br> dst_addr[in]：数据目的地址 <br> opcode[in]：命令字 <br> data[in]：数据指针 <br> data_len[in]：数据长度 <br> ttl[in]：数据剩余转发次数 |
| **返回值** | 无 |
| **备注** | 无 |

tuya_mesh_data_send

| 函数名 | tuya_mesh_data_send |
| :- | :- |
| **函数原型** | void tuya_mesh_data_send(uint16_t src_addr, uint16_t dst_addr, uint32_t opcode, uint8_t *data, uint16_t data_len, uint16_t appkey_idx, uint8_t is_rsp) |
| **功能概述** | mesh 数据发送 API |
| **参数** | src_addr[in]：数据源地址 <br> dst_addr[in]：数据目的地址 <br> opcode[in]：命令字 <br> data[in]：数据指针 <br> data_len[in]：数据长度 <br> appkey_idx[in]：使用的app_key <br> is_rsp[in]：是否status回复 |
| **返回值** | 无 |
| **备注** | 无 |

tuya_primary_ele_addr_set

| 函数名 | tuya_primary_ele_addr_set |
| :- | :- |
| **函数原型** | void tuya_primary_ele_addr_set(uint16_t addr, int save) |
| **功能概述** | 设置设备的 unicast addr |
| **参数** | addr[in]：设备地址 <br> save[in]：是否flash记忆 |
| **返回值** | 无 |
| **备注** | 无 |

tuya_mesh_devkey_set

| 函数名 | tuya_mesh_devkey_set |
| :- | :- |
| **函数原型** | void tuya_mesh_devkey_set(uint8_t *key) |
| **功能概述** | 主动更新设备的devkey |
| **参数** | addr[in]：设备地址 <br> save[in]：是否flash记忆 |
| **返回值** | 无 |
| **备注** | 无 |

tuya_mesh_reset_network

| 函数名 | tuya_mesh_reset_network |
| :- | :- |
| **函数原型** | void tuya_mesh_reset_network(void) |
| **功能概述** | 将设备移除网络并恢复到配网状态 |
| **参数** | addr[in]：设备地址 <br> save[in]：是否flash记忆 |
| **返回值** | 无 |
| **备注** | 无 |

tuya_mesh_network_reset_with_restore

| 函数名 | tuya_mesh_network_reset_with_restore |
| :- | :- |
| **函数原型** | void tuya_mesh_network_reset_with_restore(uint16_t restore_time_s) |
| **功能概述** | 将设备移除网络并恢复到配网状态，且配置超时时间，超时后恢复到移除前的网络 |
| **参数** | addr[in]：设备地址 <br> save[in]：是否flash记忆 |
| **返回值** | 无 |
| **备注** | 无 |

tuya_mesh_rf_power_set

| 函数名 | tuya_mesh_rf_power_set |
| :- | :- |
| **函数原型** | void tuya_mesh_rf_power_set(TUYA_RF_Power level) |
| **功能概述** | 设置发射功率 |
| **参数** | level：发射功率的大小 |
| **返回值** | 无 |
| **备注** | 无 |

tuya_mesh_uuid_set

| 函数名 | tuya_mesh_uuid_set |
| :- | :- |
| **函数原型** | void tuya_mesh_uuid_set(uint8_t *uuid) |
| **功能概述** | uuid 更新接口 |
| **参数** | 16字节长度的 uuid |
| **返回值** | 无 |
| **备注** | 无 |

tuya_gatt_adv_beacon_enable

| 函数名 | tuya_gatt_adv_beacon_enable |
| :- | :- |
| **函数原型** | void tuya_gatt_adv_beacon_enable(uint8_t enable) |
| **功能概述** | 广播 beacon 使能 |
| **参数** | 是否开启 |
| **返回值** | 无 |
| **备注** | enable 为0时，设备将不再广播 mesh beacon，可用来关闭设备配网广播 |

get_primary_ele_addr

| 函数名 | get_primary_ele_addr |
| :- | :- |
| **函数原型** | uint16_t get_primary_ele_addr(void) |
| **功能概述** | 获取设备的 unicast addr |
| **参数** | 无 |
| **返回值** | 设备 mesh unicast addr |
| **备注** | 无 |

get_if_prov_success

| 函数名 | get_if_prov_success |
| :- | :- |
| **函数原型** | uint8_t get_if_prov_success(void) |
| **功能概述** | 获取设备配网状态 |
| **参数** | 无 |
| **返回值** | 0：设备未配网 <br> 1：设备配网成功 |
| **备注** | 无 |

<br>

#### 5.2、tuya 信息 API

设备的基本信息 SDK 在底层已经从授权信息或者编译配置中导出使用，但是应用上层可能有修改部分信息的需求。

tuya_pid_set

| 函数名 | tuya_pid_set |
| :- | :- |
| **函数原型** | void tuya_pid_set(uint8_t *pid) |
| **功能概述** | PID 更新接口，不调用则默认用授权的 PID |
| **参数** | 8字节长度的 PID 字符串 |
| **返回值** | 无 |
| **备注** | 无 |

tuya_mesh_category_set

| 函数名 | tuya_mesh_category_set |
| :- | :- |
| **函数原型** | void tuya_mesh_category_set(uint16_t mesh_category) |
| **功能概述** | mesh 设备能力值配置 |
| **参数** | 设备能力值 |
| **返回值** | 无 |
| **备注** | 无 |



[p1]:./doc/pics/telink_flash_tools.jpg
[p2]:./doc/pics/telink_btd.png
[#1]:https://developer.tuya.com/cn/docs/iot/device-development/access-mode-mcu/ble-mesh-general-solution/tuya-universal-serial-port-protocol?id=K9u2sraj6kmc8
[#2]:https://developer.tuya.com/cn/docs/iot/device-development/access-mode-mcu/ble-mesh-general-solution/tuya-universal-serial-port-protocol?id=K9u2sraj6kmc8#title-3-DP%E6%A0%BC%E5%BC%8F%E8%AF%B4%E6%98%8E


