/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * main.c - This application uses modified sample code & math to produce a
 * 			simple "Gas Calculator" (Metric/Canada)
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <string.h>

/* Define the module info section */
PSP_MODULE_INFO("GASPSP", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int done = 0;

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	done = 1;
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

/* Create class to store variables in */
typedef struct {
	int station_rate;
	int km_travelling;
	int consumption;
} gas_cost_struct;

gas_cost_struct gas_cost;

/* Function to update the gas cost rate */
void update_gas_cost_rate(int rate){
	gas_cost.station_rate = rate;
}

/* Function to update the km travelling */
void update_km_travelling(int km){
	gas_cost.km_travelling = km;
}

/* Function to update the consumption */
void update_consumption(int consumption){
	gas_cost.consumption = consumption;
}

/* Function to calculate the cost */
double calculate_cost(){
	double cost = 0;
	
	double r = gas_cost.km_travelling / 100.0;
	double lft = gas_cost.consumption * r;
	cost = lft * (gas_cost.station_rate/100.0);

	return cost;
}

/* Function to calculate how many litres of gas are needed */
double calculate_litres(){
	return (gas_cost.km_travelling * gas_cost.consumption) / 100.0;
}

/* Function to print the gas cost */
void print_gas_cost(){
	pspDebugScreenPrintf("Gas Cost Rate: %d\n", gas_cost.station_rate);
	pspDebugScreenPrintf("KM Travelling: %d\n", gas_cost.km_travelling);
	pspDebugScreenPrintf("Consumption: %d\n", gas_cost.consumption);
	pspDebugScreenPrintf("Cost: %.2f\n", calculate_cost());
}

/* Main function */

int main(void)
{
	SceCtrlData pad;

	pspDebugScreenInit();
	SetupCallbacks();

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

	while(!done){
		pspDebugScreenSetXY(0, 2);

		sceCtrlReadBufferPositive(&pad, 1);
		
		// Update the gas cost rate
		if (pad.Buttons & PSP_CTRL_LEFT){
			update_gas_cost_rate(gas_cost.station_rate - 1);
		}
		if (pad.Buttons & PSP_CTRL_RIGHT){
			update_gas_cost_rate(gas_cost.station_rate + 1);
		}

		// Update the km travelling
		if (pad.Buttons & PSP_CTRL_UP){
			update_km_travelling(gas_cost.km_travelling + 1);
		}
		if (pad.Buttons & PSP_CTRL_DOWN){
			update_km_travelling(gas_cost.km_travelling - 1);
		}

		// Update the consumption
		if (pad.Buttons & PSP_CTRL_LTRIGGER){
			update_consumption(gas_cost.consumption - 1);
		}
		if (pad.Buttons & PSP_CTRL_RTRIGGER){
			update_consumption(gas_cost.consumption + 1);
		}

		// Reset the gas cost
		if (pad.Buttons & PSP_CTRL_SQUARE){
			update_gas_cost_rate(0);
			update_km_travelling(0);
			update_consumption(0);
		}

		if (pad.Buttons & PSP_CTRL_TRIANGLE) {
			update_gas_cost_rate(gas_cost.station_rate + 25);
		}

		if (pad.Buttons & PSP_CTRL_CROSS) {
			update_gas_cost_rate(gas_cost.station_rate - 25);
		}

		if (pad.Buttons & PSP_CTRL_START) {
			update_km_travelling(gas_cost.km_travelling + 25);
		}

		if (pad.Buttons & PSP_CTRL_SELECT) {
			update_km_travelling(gas_cost.km_travelling - 25);
		}

		// Print the gas cost to the screen
		print_gas_cost();

		pspDebugScreenPrintf("Litres Fuel: %.2f\n", calculate_litres());

		pspDebugScreenPrintf("\n");

		// print buttons to screen
		pspDebugScreenPrintf("Buttons: ");

		if (pad.Buttons & PSP_CTRL_LEFT) pspDebugScreenPrintf("Left (cost+)\n");
		if (pad.Buttons & PSP_CTRL_RIGHT) pspDebugScreenPrintf("Right (cost-)\n");
		if (pad.Buttons & PSP_CTRL_UP) pspDebugScreenPrintf("Up (km+)\n");
		if (pad.Buttons & PSP_CTRL_DOWN) pspDebugScreenPrintf("Down (km-)\n");
		if (pad.Buttons & PSP_CTRL_LTRIGGER) pspDebugScreenPrintf("L (litres/100km-)\n");
		if (pad.Buttons & PSP_CTRL_RTRIGGER) pspDebugScreenPrintf("R (litres/100km+)\n");
		if (pad.Buttons & PSP_CTRL_START) pspDebugScreenPrintf("Start (km+25)\n");
		if (pad.Buttons & PSP_CTRL_SELECT) pspDebugScreenPrintf("Select (km-25)\n");
		if (pad.Buttons & PSP_CTRL_CROSS) pspDebugScreenPrintf("Cross (cost-25)\n");
		if (pad.Buttons & PSP_CTRL_CIRCLE) pspDebugScreenPrintf("Circle\n");
		if (pad.Buttons & PSP_CTRL_SQUARE) pspDebugScreenPrintf("Square (reset)\n");
		if (pad.Buttons & PSP_CTRL_TRIANGLE) pspDebugScreenPrintf("Triangle (cost+25)\n");
		pspDebugScreenPrintf("\n");

		// Wait for a frame
		sceKernelDelayThread(100000);
	
	}

	sceKernelExitGame();
	return 0;
}
