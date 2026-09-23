void setup(void) {
	stdio_init_all();
	cyw43_arch_init();
	adc_init();
	adc_set_temp_sensor_enabled();	
	adc_select_input(4);
}

int sense_and_light(void) {
	uint16_t raw = adc_read();
	float voltage = raw * 3.3f / 4095.0f;
	float temperature = 27.0f - (voltage - 0.706f) / 0.001721f;
	if 
	
}
