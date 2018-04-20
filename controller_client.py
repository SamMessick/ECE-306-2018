'''
 Xbox Controller server for driving MSP430 car
 with IoT-based serial commands. Developed for
 ECE 309. This software is compatible with Linux 
 distributions. 

 Use the Left and Right Xbox 360 joysticks to control
 the PWM values and direction for the left and right
 motors. Use the AXBY buttons to signal an emote.
 Use the back button to trigger the car to enter
 black line mode. Use the start button to trigger
 the car into menu mode.

 Author: Sam Messick
 Last Modified: April 2018
'''

import pygame
import time
import socket
import sys

# Indices in status list
LTHUMBSTICK_X = 0
LTHUMBSTICK_Y = 1
RTHUMBSTICK_X = 4
RTHUMBSTICK_Y = 3
BUTTON_X      = 7
BUTTON_A      = 5
BUTTON_B      = 6
BUTTON_Y      = 8
BUTTON_SELECT = 11
BUTTON_START  = 14

# Control variables
max_pwm    = 250.0
min_pwm    = 5
max_analog = 1
min_analog = 0
a_pressed  = False         #=============================================#
b_pressed  = False         # Maintain button pressed to one message sent #
x_pressed  = False         #                                             #
y_pressed  = False         #=============================================#
pwm_l      = 0
analog_l   = 0
pwm_r      = 0
analog_r   = 0
port       = 32000
remote_ip  = "10.153.58.190"

message = ""

#=====================================================================================================


# Format decimal to string format xxx
def fmtDec(n):
    return '{0:3g}'.format(n)
	
"""
Returns a vector of the following form:
[LThumbstickX, LThumbstickY, Unknown Coupled Axis???, 
RThumbstickX, RThumbstickY, 
Button 1/X, Button 2/A, Button 3/B, Button 4/Y, 
Left Bumper, Right Bumper, Left Trigger, Right Triller,
Select, Start, Left Thumb Press, Right Thumb Press]

Note:
No D-Pad.
Triggers are switches, not variable. 
Your controller may be different
"""
def getState():                    
    out = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    it = 0 #iterator
    pygame.event.pump()
    
    #Read input from the two joysticks       
    for i in range(0, gamepad.get_numaxes()):
        out[it] = gamepad.get_axis(i)
        it+=1
    #Read input from buttons
    for i in range(0, gamepad.get_numbuttons()):
        out[it] = gamepad.get_button(i)
        it+=1
    return out
	
def rangeMap(value):
    return (int) (value*(max_pwm-min_pwm)/(max_analog-min_analog))
#=====================================================================================================

# ------Set up Xbox controller------- #
pygame.init()
gamepad = pygame.joystick.Joystick(0)
gamepad.init()
print("Initialized Xbox controller: %s" %gamepad.get_name())

# ------Set up server socket------- #
try:
    spwIoTsock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    #spwIoTsock.bind(('', host_port))
    print("Socket creation successful")
except socket.error as err:
    print("Socket creation failed with error %s" %(err))
    sys.exit()

# ------Wait for client connect------- #
#print("Awaiting connection from SPW IoT Module")
#spwIoTsock.listen(1)
#client, addr = spwIoTsock.accept()
spwIoTsock.connect((remote_ip, port))
print("Connection established. Got connection at", remote_ip)

#=====================================================================================================
# ------Send commands until back button is pressed------ #
status = getState()

while not status[BUTTON_SELECT]:
    time.sleep(.050)

    # ---Attempt to send commands to client--- #
    try:
	
        status = getState()
        print status
		

        # ---Check for button presses--- #
        if status[BUTTON_A]:    
            if not a_pressed:
                spwIoTsock.sendall("*8657A0000\r\n")
                a_pressed = True
                print("A")
                continue
        else:
            print("A not pressed")
            a_pressed = False

        if status[BUTTON_B]:
            if not b_pressed:
                spwIoTsock.sendall("*8657B0000\r\n")
                b_pressed = True
                print("B")
                continue
        else:
            print("B not pressed")
            b_pressed = False

        if status[BUTTON_Y]:
            if not y_pressed:
                spwIoTsock.sendall("*8657Y0000\r\n")
                y_pressed = True
                print("Y")    
                continue
        else:
            y_pressed = False

        if status[BUTTON_X]:
            if not x_pressed:
                spwIoTsock.sendall("*8657X0000\r\n")
                x_pressed = True
                print("X")
                continue
        else:
            x_pressed = False	

        # ---if no button presses to handle, send wheel PWM adjustment--- #
        pwm_l = rangeMap(status[LTHUMBSTICK_Y])
        if abs(pwm_l) < (max_pwm/3):
            pwm_l = 0
        pwm_r = rangeMap(status[RTHUMBSTICK_Y])
        if abs(pwm_r) < (max_pwm/3):
		    pwm_r = 0
        if pwm_l < 0:
            if pwm_r < 0:
                message = "*8657KQ" + str(abs(pwm_l)).zfill(3) + str(abs(pwm_r)).zfill(3) + "0\r\n"
                spwIoTsock.sendall(message) 
            else:
                message = "*8657KS" + str(abs(pwm_l)).zfill(3) + str(abs(pwm_r)).zfill(3) + "0\r\n"
                spwIoTsock.sendall(message)
        else:
            if pwm_r < 0:
                message = "*8657MQ" + str(abs(pwm_l)).zfill(3) + str(abs(pwm_r)).zfill(3) + "0\r\n" 
                spwIoTsock.sendall(message)
            else:
                message = "*8657MS" + str(abs(pwm_l)).zfill(3) + str(abs(pwm_r)).zfill(3) + "0\r\n"
                spwIoTsock.sendall(message)

    # ------Wait for reconnect if connection fails------ #
    except socket.error:  
        print("Connection lost. Awaiting recconect from SPW IoT Module") 
        spwIoTsock.connect((remote_ip, port))
        print("Connection established. Got connection from", addr)
    
# ---Back button pressed: send command for black line detection and close--- #

spwIoTsock.sendall("*8657L0000\r\n");
sys.exit()
