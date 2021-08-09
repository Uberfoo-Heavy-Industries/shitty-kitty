# The Shitty Kitty

Welcome to the home of the Shitty Kitty firmware, a.k.a Shitty OS.

# How to Update the Firmware

The Shitty Kitty is easily reprogrammable via the USB port. To do this you will need the STM32CubeProgrammer.  You can find that here: https://www.st.com/en/development-tools/stm32cubeprog.html

After installing STM32CubeProgrammer, turn off the Shitty Kitty with the switch on the upper left side.  Plug in a USB cable from your computer to the Shitty Kitty.  Then, while holding down the BOOT0 button on the lower right side, turn the Shitty Kitty back on.  After turning on the Shitty Kitty you can release the BOOT0 button.
The Shitty Kitty should now be connected in DFU mode allowing it to be updated.

Open STM32CubeProgrammer. 

Select USB from the drop down menu on the upper right next to the connect button.  Then press the connect button.  The programmer should establish a connection with the Shitty Kitty.

![image](https://user-images.githubusercontent.com/13969279/128648523-ea3c69be-16fe-4336-a402-77bf11ec2e87.png)

Press the Downloads button on the left side of the window. Then press the browse button and select the firmware file you wish to install.

![image](https://user-images.githubusercontent.com/13969279/128648561-e911db22-04f1-4485-a6f2-4acf5a287e8e.png)

Next. press the Start Programming button. The programmer should now erase the flash and install the new flash. When it has completed, click the disconnect button.  Then turn you Shitty Kitty off and on to boot to the new firmware.

# Serail Port Controls

When connected normaly to a computer's USB port, the Shitty Kitty badge will appear as a serial port. The badge can be controlled over the USB serial port using typical terminal software like PuTTY or screen.

## Windows

### Finding the Serial Port

On Windows platforms, to find the Shitty Kitty's serial port you can use the device manager.  You can find the device manager by searching for it with WindowsKey+S.

In the device manager, look under the "Ports (COM & LTP)" for "USB Derial Device".  It should have a COM port number next to it.

![image](https://user-images.githubusercontent.com/13969279/128649122-33ad053d-1e94-488c-a1dc-78b04c270730.png)

### Opening With PuTTY

On Windows platforms, you can use PuTTY to connect to the Shitty Kitty. Just click the Serial option under Connection Type and enter the COM port identifier.

![image](https://user-images.githubusercontent.com/13969279/128649953-f6506a52-f82f-4e62-8431-7cc47cb587f9.png)

Press Open and a terminal window should open. Enjoy!
