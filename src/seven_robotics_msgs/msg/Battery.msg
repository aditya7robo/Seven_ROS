#Reports the current status of the battery
#Battery Type
#Battery Health 
#Charging
#Discharging
#Time to Discharge in Seconds
#Design Capacity in mAh
#Full Capacity - in mAh
#Remaining Capacity in mAh
#no of cells in series

#Battery Voltage in mV
#Average Current in mA
#Temperature in degree Celsius - temperature of the battery environment

Header header

BatteryType type
BatteryHealth health

bool 		 Charging

uint32_t CapacityDesigned	#BQ34Z100 Design Capacity
uint32_t CapacityFull			#Gas-gauging algorithm takes into account battery age and condition to adjust full capacity
uint32_t RemainingCapacity	#mAh remaining capacity of the battery

uint8_t  nCells	#no of series cells in the pack

uint32_t Volts	#Current Battery Voltage
int32_t  Amps		#Average current discharge
int32_t  TempC	#Battery pack environment temperature in degree celsius
