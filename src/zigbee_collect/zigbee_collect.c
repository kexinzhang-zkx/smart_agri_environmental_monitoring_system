// DHT11温湿度读取
static void Read_DHT11( halDHT11Data_t *dht_data )
{
  if (dht_data == NULL) {
      printf("dht_data is NULL!\n");
      return;
  }
  *dht_data = halDHT11GetData();
  if (dht_data->ok) {
      printf("Temperture:%d ,Hum:%d%%\n", dht_data->temp, dht_data->humi);
  } else {
      dht_data->temp = 0;
      dht_data->humi = 0;
  }
}

// 光照ADC采集
uint8 adcVal = HalAdcRead(HAL_ADC_CHANNEL_5, HAL_ADC_RESOLUTION_8);
