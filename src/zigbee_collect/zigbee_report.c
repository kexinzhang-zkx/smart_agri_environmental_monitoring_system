// 数据上报总入口
static void zclSampleSw_Report_Datas(void)
{
#if EndDevice1
  halDHT11Data_t dht_data;
  Read_DHT11(&dht_data);
  if (!dht_data.ok) return;
  zclSampleSw_SendSingleReport(ATTRID_TEMPERATURE_DATA, dht_data.temp, seqNum++);
  zclSampleSw_SendSingleReport(ATTRID_HUMIDITY_DATA, dht_data.humi, seqNum++);
#endif

#if EndDevice2
  uint8 adcVal = HalAdcRead(HAL_ADC_CHANNEL_5, HAL_ADC_RESOLUTION_8);
  zclSampleSw_SendSingleReport(ATTRID_LIGHT_DATA, adcVal, seqNum++);
#endif
}

// 单属性上报
static void zclSampleSw_SendSingleReport(uint16 attrID, uint8 value, uint8 seqNum)
{
  zclReportCmd_t *reportCmd;
  afAddrType_t destAddr;
  destAddr.addrMode = afAddr16Bit;
  destAddr.endPoint = SAMPLESW_ENDPOINT;
  destAddr.addr.shortAddr = 0x0000;

  reportCmd = osal_mem_alloc(sizeof(zclReportCmd_t) + sizeof(zclReport_t));
  reportCmd->numAttr = 1;
  reportCmd->attrList[0].attrID = attrID;
  reportCmd->attrList[0].dataType = ZCL_DATATYPE_UINT8;
  *((uint8 *)(reportCmd->attrList[0].attrData)) = value;

  zcl_SendReportCmd(SAMPLESW_ENDPOINT, &destAddr, ZCL_CLUSTER_ID_GEN_ON_OFF_SWITCH_CONFIG,
                    reportCmd, ZCL_FRAME_CLIENT_SERVER_DIR, TRUE, seqNum);
  osal_mem_free(reportCmd);
}

// 协调器解析上报
#ifdef ZCL_REPORT
static uint8 zclSampleSw_ProcessInReportCmd( zclIncomingMsg_t *pInMsg )
{
  zclReportCmd_t *reportCmd = (zclReportCmd_t *)pInMsg->attrCmd;
  for ( uint8 i = 0; i < reportCmd->numAttr; i++ )
  {
    if( reportCmd->attrList[i].attrID == ATTRID_TEMPERATURE_DATA) {
      uint8 tempValue = *(reportCmd->attrList[i].attrData);
      sprintf((char *)zclSampleSw_UartBuf,"Tem:%d\n", tempValue );
      HalUARTWrite(HAL_UART_PORT_0 , zclSampleSw_UartBuf , strlen((char *)zclSampleSw_UartBuf));
    }
    else if( reportCmd->attrList[i].attrID == ATTRID_HUMIDITY_DATA) {
      uint8 humValue = *(reportCmd->attrList[i].attrData);
      sprintf((char *)zclSampleSw_UartBuf,"Hum:%d%%\n", humValue );
      HalUARTWrite(HAL_UART_PORT_0 , zclSampleSw_UartBuf , strlen((char *)zclSampleSw_UartBuf));
    }
    else if( reportCmd->attrList[i].attrID == ATTRID_LIGHT_DATA) {
      uint8 Light_data = *(reportCmd->attrList[i].attrData);
      sprintf((char *)zclSampleSw_UartBuf,"Light:%d\n", Light_data );
      HalUARTWrite(HAL_UART_PORT_0 , zclSampleSw_UartBuf , strlen((char *)zclSampleSw_UartBuf));
    }
  }
  return TRUE;
}
#endif
