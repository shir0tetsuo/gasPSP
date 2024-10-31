# gasPSP
An introduction to programming on the PlayStation Portable

# The Program
![20241030_142532](https://github.com/user-attachments/assets/ce1565ba-bb61-497d-ae67-e92b7749dd08)
![20241030_200205](https://github.com/user-attachments/assets/767a8848-d532-4b0b-b064-c67f7f50d662)

📜 In a nutshell:
```c
		if (pad.Buttons & PSP_CTRL_LEFT)     pspDebugScreenPrintf("Left (cost+)\n");
		if (pad.Buttons & PSP_CTRL_RIGHT)    pspDebugScreenPrintf("Right (cost-)\n");
		if (pad.Buttons & PSP_CTRL_UP)       pspDebugScreenPrintf("Up (km+)\n");
		if (pad.Buttons & PSP_CTRL_DOWN)     pspDebugScreenPrintf("Down (km-)\n");
		if (pad.Buttons & PSP_CTRL_LTRIGGER) pspDebugScreenPrintf("L (litres/100km-)\n");
		if (pad.Buttons & PSP_CTRL_RTRIGGER) pspDebugScreenPrintf("R (litres/100km+)\n");
		if (pad.Buttons & PSP_CTRL_START)    pspDebugScreenPrintf("Start (km+25)\n");
		if (pad.Buttons & PSP_CTRL_SELECT)   pspDebugScreenPrintf("Select (km-25)\n");
		if (pad.Buttons & PSP_CTRL_CROSS)    pspDebugScreenPrintf("Cross (cost-25)\n");
		if (pad.Buttons & PSP_CTRL_CIRCLE)   pspDebugScreenPrintf("Circle\n");
		if (pad.Buttons & PSP_CTRL_SQUARE)   pspDebugScreenPrintf("Square (reset)\n");
		if (pad.Buttons & PSP_CTRL_TRIANGLE) pspDebugScreenPrintf("Triangle (cost+25)\n");
```

# Building
Make sure you have pspdev installed, see https://github.com/pspdev

See `build.sh` for example.

# Usage
Works fine on Ark-4 6.61 cIPL.

| Value Area | Description |
|------------|-------------|
| Cost | If you see "1.379" at a Gas Station use value "137" or "138" |
| KM Travelling | Pretty straight forward, how far are you going? |
| Consumption | How many litres of fuel does your vehicle consume per 100km, roughly? |
