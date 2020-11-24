#!/bin/sh
TELINK_SDK_ROOT=../../../board/tlsr825x_smesh/sdk/telink_sig_mesh_sdk
OPTION=$1
PARAM1=$2
APP_DIR=..

PACKAGE=../$PARAM1
fjq(){
    uname=`uname | tr '[A-Z]' '[a-z]'`
    jq="jq-win64.exe"
    if [ "$uname" = "linux" ]; then
        jq="jq"
    fi
    echo $(cat $PACKAGE | $jq $1 | sed 's/^\"\(.*\)\"$/\1/g')
}

F_WRITE_PATH="null"
f_write(){
	echo "$1" >> "$F_WRITE_PATH"
}

f_isnull(){
    while [ "$#" -ge "1"  ];do
        if [ "$1" != "null" ]; then
            return 0;
        fi
        shift
    done
    return 1;
}


function build(){
	echo " "
	echo "> [build-step1]-------------------------------------------"
	echo "package is: "$PACKAGE
	#cat $PACKAGE
	{
        #json-common
		NAME=$(fjq .name)
		DESCRIPTION=$(fjq .description)
		VERSION=$(fjq .version)
		VERSION_HEX=$(echo $VERSION | od -An -tx | sed 's/ 0a\(..\)2e\(..\)/0x\1\2/g') #0.0~f.f
		IC_KIND=$(fjq .ic)
		HARDWARE=$(fjq .hardware)
        
        #json-build
		BUILD_LOG_CONFIG=$(fjq .build.log)
        BUILD_OEM_CONFIG=$(fjq .build.oem)
        BUILD_JSON_CONFIG=$(fjq .build.json_config)

        #json-project
		PRODUCT_KIND=$(fjq .product.kind)
		PRODUCT_PID=$(fjq .product.pid)
		PRODUCT_VENDORID=$(fjq .product.vendorid)
        PRODUCT_POWER_RESET_CNT=$(fjq .product.power_reset_cnt)
        PRODUCT_POWER_RESET_TIME=$(fjq .product.power_reset_time)
        PRODUCT_POWER_RESET_RECOVER_TIME=$(fjq .product.power_reset_recover_time)
        BUILD_LOCAL_CONTROL_CONFIG=$(fjq .product.local_control)
        
		if [ "$NAME" = "null" ] || [ "$VERSION" = "null" ] || [ "$IC_KIND" = "null" ] ||
			[ "$PRODUCT_KIND" = "null" ] || [ "$PRODUCT_PID" = "null" ] || [ "$PRODUCT_VENDORID" = "null" ]; then
			echo "read last line error!!!"
			exit 1
		fi
        
        if [ "$PRODUCT_POWER_RESET_CNT" = "null" ];then
			PRODUCT_POWER_RESET_CNT=0
		fi
        
        if [ "$PRODUCT_POWER_RESET_TIME" = "null" ];then
			PRODUCT_POWER_RESET_TIME=5
		fi
        
        if [ "$PRODUCT_POWER_RESET_RECOVER_TIME" = "null" ];then
			PRODUCT_POWER_RESET_RECOVER_TIME=600
		fi

		if [ "$HARDWARE" = "null" ];then
			HARDWARE="OTHER"
		fi

		if [ "$BUILD_LOG_CONFIG" != 1 ];then
			BUILD_LOG_CONFIG=0
		fi
	    
        if [ "$BUILD_OEM_CONFIG" != 1 ];then
			BUILD_OEM_CONFIG=0
        fi
        
        if [ "$BUILD_JSON_CONFIG" != 1 ];then
			BUILD_JSON_CONFIG=0
        fi

        if [ "$BUILD_LOCAL_CONTROL_CONFIG" != 1 ];then
			BUILD_LOCAL_CONTROL_CONFIG=0
        fi
		
        #module light
		{
			MODULE_LIGHT=$(fjq .modules.light)
			MODULE_LIGHT_JSONVER=$(fjq .modules.light.Jsonver)
			MODULE_LIGHT_CATEGORY=$(fjq .modules.light.category)
			MODULE_LIGHT_MODULE=$(fjq .modules.light.module)
			MODULE_LIGHT_CMOD=$(fjq .modules.light.cmod)
			MODULE_LIGHT_DMOD=$(fjq .modules.light.dmod)
			MODULE_LIGHT_CWTYPE=$(fjq .modules.light.cwtype)
            
            MODULE_LIGHT_ONOFFMODE=$(fjq .modules.light.onoffmode)
            MODULE_LIGHT_PMEMORY=$(fjq .modules.light.pmemory)
            MODULE_LIGHT_DEFCOLOR=$(fjq .modules.light.defcolor)
            MODULE_LIGHT_DEFBRIGHT=$(fjq .modules.light.defbright)
            MODULE_LIGHT_DEFTEMP=$(fjq .modules.light.deftemp)
            MODULE_LIGHT_CWMAXP=$(fjq .modules.light.cwmaxp)
            MODULE_LIGHT_BRIGHTMIN=$(fjq .modules.light.brightmin)
            MODULE_LIGHT_BRINGTMAX=$(fjq .modules.light.brightmax)
            MODULE_LIGHT_COLORMIN=$(fjq .modules.light.colormin)
            MODULE_LIGHT_COLORMAX=$(fjq .modules.light.colormax)
            MODULE_LIGHT_WFCFG=$(fjq .modules.light.wfcfg)
            MODULE_LIGHT_RSTMODE=$(fjq .modules.light.rstmode)
            MODULE_LIGHT_RSTNUM=$(fjq .modules.light.rstnum)
            MODULE_LIGHT_RSTCOR=$(fjq .modules.light.rstcor)
            MODULE_LIGHT_RSTBR=$(fjq .modules.light.rstbr)
            MODULE_LIGHT_RSTTEMP=$(fjq .modules.light.rsttemp)
            MODULE_LIGHT_PWMHZ=$(fjq .modules.light.pmwhz)
			MODULE_LIGHT_PAIRT=$(fjq .modules.light.pairt)
			MODULE_LIGHT_NOTDISTURB=$(fjq .modules.light.notdisturb)
            	
			MODULE_LIGHT_R_PIN=$(fjq .modules.light.r_pin)
			MODULE_LIGHT_R_LV=$(fjq .modules.light.r_lv)
			MODULE_LIGHT_G_PIN=$(fjq .modules.light.g_pin)
			MODULE_LIGHT_G_LV=$(fjq .modules.light.g_lv)
			MODULE_LIGHT_B_PIN=$(fjq .modules.light.b_pin)
			MODULE_LIGHT_B_LV=$(fjq .modules.light.b_lv)
			MODULE_LIGHT_C_PIN=$(fjq .modules.light.c_pin)
			MODULE_LIGHT_C_LV=$(fjq .modules.light.c_lv)
			MODULE_LIGHT_W_PIN=$(fjq .modules.light.w_pin)
			MODULE_LIGHT_W_LV=$(fjq .modules.light.w_lv)

            MODULE_LIGHT_IIC_R=$(fjq .modules.light.iicr)
            MODULE_LIGHT_IIC_G=$(fjq .modules.light.iicg)
            MODULE_LIGHT_IIC_B=$(fjq .modules.light.iicb)
            MODULE_LIGHT_IIC_C=$(fjq .modules.light.iicc)
            MODULE_LIGHT_IIC_W=$(fjq .modules.light.iicw)
            MODULE_LIGHT_IIC_SCL=$(fjq .modules.light.iicscl)
            MODULE_LIGHT_IIC_SDA=$(fjq .modules.light.iicsda)
            MODULE_LIGHT_CTRL_PIN=$(fjq .modules.light.ctrl_pin)
			MODULE_LIGHT_CTRL_LV=$(fjq .modules.light.ctrl_lv)
			MODULE_LIGHT_IIC_CAMPERE=$(fjq .modules.light.campere)
			MODULE_LIGHT_IIC_WAMPERE=$(fjq .modules.light.wampere)
			
			MODULE_LIGHTL_WR=$(fjq .modules.light.wr)
			MODULE_LIGHTL_WG=$(fjq .modules.light.wg)
			MODULE_LIGHTL_WB=$(fjq .modules.light.wb)
			MODULE_LIGHTL_GR=$(fjq .modules.light.gr)
			MODULE_LIGHTL_GG=$(fjq .modules.light.gg)
			MODULE_LIGHTL_GB=$(fjq .modules.light.gb)
			MODULE_LIGHTL_CRC=$(fjq .modules.light.crc)
		}

        #module switch
		{
			MODULE_SWITCH=$(fjq .modules.switch)
			MODULE_SWITCH_NUM=$(fjq .modules.switch.key_num)	
			PROVISION_TIMEOUT=$(fjq .modules.switch.provision_timeout_s)			
			RELAY_HIGH_ACTIVE=$(fjq .modules.switch.relay_high_active)
            MODULE_SWITCH_KEY1_PIN=$(fjq .modules.switch.key1_pin)
			MODULE_SWITCH_KEY2_PIN=$(fjq .modules.switch.key2_pin)	
            MODULE_SWITCH_KEY3_PIN=$(fjq .modules.switch.key3_pin)

            MODULE_SWITCH_RELAY1_PIN=$(fjq .modules.switch.relay1_pin)
			MODULE_SWITCH_RELAY2_PIN=$(fjq .modules.switch.relay2_pin)	
            MODULE_SWITCH_RELAY3_PIN=$(fjq .modules.switch.relay3_pin)

            MODULE_SWITCH_BLINK1_PIN=$(fjq .modules.switch.blink1_pin)
			MODULE_SWITCH_BLINK2_PIN=$(fjq .modules.switch.blink2_pin)	
            MODULE_SWITCH_BLINK3_PIN=$(fjq .modules.switch.blink3_pin)
		}
	}
	
	echo " "
	echo "> [build-step2]-------------------------------------------"
	{
		export TIME_NOW=`date +%Y-%m-%d-%H:%M:%S`
		GETVER_FILE=getver.sh
		F_WRITE_PATH=$GETVER_FILE
		echo 'VER_FILE=version.in' > $GETVER_FILE
		f_write 'echo -n " .equ BUILD_VERSION, " > $VER_FILE'
		f_write 'echo '$VERSION_HEX' >> $VER_FILE'
		f_write ' '
		
		f_write 'CONFIG_FILE=base_oem_config.h'
		f_write 'echo "//-------------------------------------------"> $CONFIG_FILE'
		f_write 'echo "//common define">> $CONFIG_FILE'
		f_write 'echo "//-------------------------------------------">> $CONFIG_FILE'
		f_write 'echo "#define     FW_VERSION                \"'$VERSION'\"" >> $CONFIG_FILE'
        f_write 'echo "#define     FW_VERSION_HEX            '$VERSION_HEX'" >> $CONFIG_FILE'
		f_write 'echo "#define     BUILD_TIME                \"'$TIME_NOW'\"" >> $CONFIG_FILE'
		f_write 'echo "#define     BUILD_FIRMNAME            \"'$NAME'\"" >> $CONFIG_FILE'
		f_write 'echo "#define     MESH_PID                  \"'$PRODUCT_PID'\"" >> $CONFIG_FILE'
		f_write 'echo "#define     CONFIG_LOG_ON             '$BUILD_LOG_CONFIG'" >> $CONFIG_FILE'
		f_write 'echo "#define     CONFIG_OEM_ON             '$BUILD_OEM_CONFIG'" >> $CONFIG_FILE'
        f_write 'echo "#define     JSON_CONFIG_ON            '$BUILD_JSON_CONFIG'" >> $CONFIG_FILE'
        f_write 'echo "#define     LOCAL_CONTROL_ON          '$BUILD_LOCAL_CONTROL_CONFIG'" >> $CONFIG_FILE'
        f_write 'echo "#define     KIND_ID                   0x'$PRODUCT_VENDORID'" >> $CONFIG_FILE'      
        f_write 'echo "#define     POWER_RESET_CNT           '$PRODUCT_POWER_RESET_CNT'" >> $CONFIG_FILE' 
        f_write 'echo "#define     POWER_RESET_TIME          '$PRODUCT_POWER_RESET_TIME'" >> $CONFIG_FILE' 
        f_write 'echo "#define     POWER_RESET_RECOVER_TIME  '$PRODUCT_POWER_RESET_RECOVER_TIME'" >> $CONFIG_FILE' 
		f_write 'echo "#define     TY_BT_MODULE              '$HARDWARE'" >> $CONFIG_FILE'
		f_write 'echo "            #define     TYBT3L        0" >> $CONFIG_FILE'
		f_write 'echo "            #define     TYBT8C        1" >> $CONFIG_FILE'


		if [ "$IC_KIND" == "tlsr8266" ]; then
			f_write 'echo "#define     IC_TLSR8266" >> $CONFIG_FILE'
		elif [ "$IC_KIND" == "tlsr8267" ]; then
			f_write 'echo "#define     IC_TLSR8267" >> $CONFIG_FILE'
        elif [ "$IC_KIND" == "tlsr825x" ]; then
		    f_write 'echo "#define     IC_TLSR825x" >> $CONFIG_FILE'
		else
			echo "json error!"
			exit 1
		fi
		
		f_write 'echo "" >> $CONFIG_FILE'
		
		if [ "$MODULE_LIGHT" != "null" ];then
			f_write 'echo "//-------------------------------------------">> $CONFIG_FILE' 
			f_write 'echo "//module light define">> $CONFIG_FILE'
			f_write 'echo "//-------------------------------------------">> $CONFIG_FILE'

            f_write 'echo "#define DEFAULT_CONFIG \"{Jsonver:'$MODULE_LIGHT_JSONVER',category:'$MODULE_LIGHT_CATEGORY',module:'$MODULE_LIGHT_MODULE',cmod:'$MODULE_LIGHT_CMOD',dmod:'$MODULE_LIGHT_DMOD',cwtype:'$MODULE_LIGHT_CWTYPE',onoffmode:'$MODULE_LIGHT_ONOFFMODE',pmemory:'$MODULE_LIGHT_PMEMORY',defcolor:'$MODULE_LIGHT_DEFCOLOR',defbright:'$MODULE_LIGHT_DEFBRIGHT',deftemp:'$MODULE_LIGHT_DEFTEMP',cwmaxp:'$MODULE_LIGHT_CWMAXP',brightmin:'$MODULE_LIGHT_BRIGHTMIN',brightmax:'$MODULE_LIGHT_BRINGTMAX',colormin:'$MODULE_LIGHT_COLORMIN',colormax:'$MODULE_LIGHT_COLORMAX',wfcfg:'$MODULE_LIGHT_WFCFG',rstmode:'$MODULE_LIGHT_RSTMODE',rstnum:'$MODULE_LIGHT_RSTNUM',rstcor:'$MODULE_LIGHT_RSTCOR',rstbr:'$MODULE_LIGHT_RSTBR',rsttemp:'$MODULE_LIGHT_RSTTEMP',pwmhz:'$MODULE_LIGHT_PWMHZ',pairt:'$MODULE_LIGHT_PAIRT',notdisturb:'$MODULE_LIGHT_NOTDISTURB',r_pin:'$MODULE_LIGHT_R_PIN',r_lv:'$MODULE_LIGHT_R_LV',g_pin:'$MODULE_LIGHT_G_PIN',g_lv:'$MODULE_LIGHT_G_LV',b_pin:'$MODULE_LIGHT_B_PIN',b_lv:'$MODULE_LIGHT_B_LV',c_pin:'$MODULE_LIGHT_C_PIN',c_lv:'$MODULE_LIGHT_C_LV',w_pin:'$MODULE_LIGHT_W_PIN',w_lv:'$MODULE_LIGHT_W_LV',iicr:'$MODULE_LIGHT_IIC_R',iicg:'$MODULE_LIGHT_IIC_G',iicb:'$MODULE_LIGHT_IIC_B',iicc:'$MODULE_LIGHT_IIC_C',iicw:'$MODULE_LIGHT_IIC_W',iicscl:'$MODULE_LIGHT_IIC_SCL',iicsda:'$MODULE_LIGHT_IIC_SDA',ctrl_pin:'$MODULE_LIGHT_CTRL_PIN',ctrl_lv:'$MODULE_LIGHT_CTRL_LV',campere:'$MODULE_LIGHT_IIC_CAMPERE',wampere:'$MODULE_LIGHT_IIC_WAMPERE',wr:'$MODULE_LIGHTL_WR',wg:'$MODULE_LIGHTL_WG',wb:'$MODULE_LIGHTL_WB',gr:'$MODULE_LIGHTL_GR',gg:'$MODULE_LIGHTL_GG',gb:'$MODULE_LIGHTL_GB',crc:'$MODULE_LIGHTL_CRC',}\" ">> $CONFIG_FILE'
            f_write 'echo "" >> $CONFIG_FILE'
        fi

		if [ "$MODULE_SWITCH" != "null" ];then
			f_write 'echo "//-------------------------------------------">> $CONFIG_FILE' 
			f_write 'echo "//module switch define">> $CONFIG_FILE'
			f_write 'echo "//-------------------------------------------">> $CONFIG_FILE'
			if [ "$MODULE_SWITCH_NUM" = "null" ] || 
				[ "$MODULE_SWITCH_KEY1_PIN" = "null" ] || 
				[ "$MODULE_SWITCH_RELAY1_PIN" = "null" ] || 
				[ "$MODULE_SWITCH_BLINK1_PIN" = "null" ] ;then
				echo "json error:module light config not complete!"
				exit 1
			else      
                f_write 'echo "" >> $CONFIG_FILE'
				f_write 'echo "#define     IS_SWITCH_PROJ           1 " >> $CONFIG_FILE'				
				f_write 'echo "#define     SWITCH_KEY_NUM           '$MODULE_SWITCH_NUM' " >> $CONFIG_FILE'
				f_write 'echo "#define     RELAY_HIGH_ACTIVE           '$RELAY_HIGH_ACTIVE' " >> $CONFIG_FILE'				
				f_write 'echo "#define     SWITCH_PROVISION_TIMEOUT_S           '$PROVISION_TIMEOUT' " >> $CONFIG_FILE'
				
				if [ "$MODULE_SWITCH_NUM" = "1" ]|| 
					[ "$MODULE_SWITCH_NUM" = "2" ]|| 
					[ "$MODULE_SWITCH_NUM" = "3" ];then
					f_write 'echo "#define     SWITCH_KEY1_PIN           '$MODULE_SWITCH_KEY1_PIN' " >> $CONFIG_FILE'
					f_write 'echo "#define     SWITCH_RELAY1_PIN           '$MODULE_SWITCH_RELAY1_PIN' " >> $CONFIG_FILE'
					f_write 'echo "#define     SWITCH_BLINK1_PIN           '$MODULE_SWITCH_BLINK1_PIN' " >> $CONFIG_FILE'
				fi
				
				if [ "$MODULE_SWITCH_NUM" = "2" ]|| 
					[ "$MODULE_SWITCH_NUM" = "3" ];then
					f_write 'echo "#define     SWITCH_KEY2_PIN           '$MODULE_SWITCH_KEY2_PIN' " >> $CONFIG_FILE'
					f_write 'echo "#define     SWITCH_RELAY2_PIN           '$MODULE_SWITCH_RELAY2_PIN' " >> $CONFIG_FILE'
					f_write 'echo "#define     SWITCH_BLINK2_PIN           '$MODULE_SWITCH_BLINK2_PIN' " >> $CONFIG_FILE'
				fi
				
				if [ "$MODULE_SWITCH_NUM" = "3" ];then	
					f_write 'echo "#define     SWITCH_KEY3_PIN           '$MODULE_SWITCH_KEY3_PIN' " >> $CONFIG_FILE'
					f_write 'echo "#define     SWITCH_RELAY3_PIN           '$MODULE_SWITCH_RELAY3_PIN' " >> $CONFIG_FILE'
					f_write 'echo "#define     SWITCH_BLINK3_PIN           '$MODULE_SWITCH_BLINK3_PIN' " >> $CONFIG_FILE'				
				fi		
			fi		
		fi

		echo "getver file is: "$GETVER_FILE
        chmod +x $GETVER_FILE 
		cat $GETVER_FILE
	}

    echo " "
	echo "> [build-step3]---subdir.mk--of--app----------------------"
	{
        MAKEFILE_DIR=./app
        MAKEFILE_FILE=$MAKEFILE_DIR/subdir.mk
        if [ -d "$MAKEFILE_DIR" ]; then
            rm $MAKEFILE_DIR/*.*
        else
            mkdir -p $MAKEFILE_DIR
        fi

		C_DIR=`find .. | grep ".*\.c$" | sed 's:/[a-z|A-Z|0-9|_]*\.c$::g' | sort | uniq`
        I_DIR=`find .. | grep ".*\.h$" | sed 's:/[a-z|A-Z|0-9|_]*\.h$::g' | sed 's:\(.*\):-I\1:g' | sort | uniq`
		O_DIR=./app
        
        C_FILES=$(find .. | grep "\.c$" | sed 's:^./:'$APP_DIR'/:g')
		O_FILES=$(find .. -type f -printf "%f\n" | grep ".c$" | sed 's:\.c:\.o:g' | sed 's:^:'$O_DIR'/:g')


        echo "C_SRC = "$C_FILES >> $MAKEFILE_FILE 
        echo "USER_OBJ = "$O_FILES >> $MAKEFILE_FILE
        echo "INC = "$I_DIR >> $MAKEFILE_FILE
        echo " " >> $MAKEFILE_FILE   

        echo 'C_SRCS += ${C_SRC}' >> $MAKEFILE_FILE
        echo 'OBJS += ${USER_OBJ}' >> $MAKEFILE_FILE
        echo 'INCS += ${INC}' >> $MAKEFILE_FILE
      
        for SRC_PATH in $C_DIR
        do
            echo " " >> $MAKEFILE_FILE
            echo './app/%.o: '$SRC_PATH'/%.c' >> $MAKEFILE_FILE
            echo "	@echo 'Building file: $<'" >> $MAKEFILE_FILE
            echo "	@echo 'Invoking: TC32 Compiler'" >> $MAKEFILE_FILE
            echo '	$(CC) $(CFLAGS) ${INCS} -o $@ -c $< ${CMACROS}' >> $MAKEFILE_FILE
            echo "	@echo 'Finished building: $<'" >> $MAKEFILE_FILE
            echo "	@echo ' '" >> $MAKEFILE_FILE
        done

		echo "makefile is: "$MAKEFILE_FILE
		cat $MAKEFILE_FILE

    }

    echo " "
	echo "> [build-step4]-------------------------------------------"
	{
		make -j4 clean PRODUCT_KIND=$PRODUCT_KIND 
		make -j4 pre-build main-build PRODUCT_KIND=$PRODUCT_KIND 
		cp 8258_mesh.bin $NAME'_'$VERSION'.bin'

        echo " "
        echo "> [build-end]-------------------------------------------"
        echo "> project name: "$NAME
        echo "> version: "$VERSION
        echo "> version hex: "$VERSION_HEX
        echo "> vendor id: "$PRODUCT_VENDORID
        echo "> pid: "$PRODUCT_PID
        echo "> build log: "$BUILD_LOG_CONFIG
        echo "> build oem: "$BUILD_OEM_CONFIG
        echo "> build json_config: "$BUILD_JSON_CONFIG
        echo "> build local_control: "$BUILD_LOCAL_CONTROL_CONFIG
        echo "> [build-end]-------------------------------------------"
	}
}

function flash_all(){
    tcdb rst
    tcdb wf 0 -s 512k -e
    tcdb -i 8258_mesh.bin -b
    tcdb wc 6f 20
}

function flash(){
    tcdb rst
    tcdb -i 8258_mesh.bin -b
    tcdb wc 6f 20
}

function clean(){
    make -j4 clean
    rm -rf app version.in getver.sh base_oem_config.h *.bin
}

echo "bash run.sh $option[build/clean/flash/flash_all] $param1[3rgb_h.json]"

if [ "$OPTION" == "build" ]; then
    build
elif [ "$OPTION" == "flash" ]; then
    flash
elif [ "$OPTION" == "flash_all" ]; then
    flash_all
elif [ "$OPTION" == "clean" ]; then
    clean
else
    echo "error, try bash run.sh help"
fi

#git_id: 3ba00b0b2f00060ce8d0b687b9efda51e25d83c4
#date: Tue 24 Nov 21:49:47 CST 2020
