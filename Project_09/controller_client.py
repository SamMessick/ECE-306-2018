'''
 Name: controller_client.py
 
 
 Xbox 360 Controller client for driving MSP430 car
 with IoT-based serial commands. Developed for
 ECE 306. This software is compatible with Windows,
 MacOX and most Linux distributions.

 Use the Left and Right Xbox 360 joysticks to control
 the PWM values and direction for the left and right
 motors. Use the AXBY buttons to signal an emote.
 Use the back button to trigger the car to enter
 'no command' mode. Use the start button
 to reenter remote control.

 
 Author: Sam Messick
 Last Modified: April 2018
'''

import pygame
import time
import socket
import sys

# Indices in status list (Joystick elements)
LTHUMBSTICK_X = 0
LTHUMBSTICK_Y = 1
RTHUMBSTICK_X = 4
RTHUMBSTICK_Y = 3
BUTTON_A      = 5
BUTTON_B      = 6
BUTTON_X      = 7
BUTTON_Y      = 8
BUTTON_LTHUM  = 9
BUTTON_RTHUM  = 10
BUTTON_SELECT = 11
BUTTON_START  = 12

# Control variables
status_update_delay = .200             # delay time between commands
max_pwm        = 240.0                 # maximum pwm value (to transmit)
min_pwm        = 5                     # minimum pwm value (to transmit)
max_analog     = 1                     # maximum joystick reading
min_analog     = 0                     # minimum joystick reading
a_pressed      = False         #=============================================#
b_pressed      = False         # Maintain button pressed to one message sent #
x_pressed      = False         #                                             #
y_pressed      = False         #=============================================#
pwm_l          = 0                     # left wheel pwm value
analog_l       = 0                     # analog left joystick value
pwm_r          = 0                     # right wheel pwm value
analog_r       = 0                     # analog right joystick value
zero_threshold = (max_pwm/3)           # threshold for zeroing pwm value (allows for joystick dead zone)
port           = 32000                 # Port of car server socket
remote_ip      = ""                    # IP address of car server socket

# Command string parameters
message          = ""              # string for storing command
special_char     = "*"
password         = "8657"
forward_keyword  = "KQ"
reverse_keyword  = "MS"
right_keyword    = "KS"
left_keyword     = "MQ"
a_keyword        = "A000"
b_keyword        = "B000"
y_keyword        = "Y000"
x_keyword        = "X000"
blk_line_keyword = "L000"
exit_keyword     = "E000"
command_tag      = "0\r\n"

# Format decimal to string format xxx
def fmtDec(n):
    return '{0:3g}'.format(n)
	
"""
Returns a vector of the following form:
[LThumbstickX, LThumbstickY, R/L trigger status, 
RThumbstickX, RThumbstickY, 
Button 1/X, Button 2/A, Button 3/B, Button 4/Y, 
Left Bumper, Right Bumper, Left Trigger, Right Trigger,
Select, Start, Left Thumb Press, Right Thumb Press]

Note:
No D-Pad.
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
	
#=============================      Setup       ======================================================

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
remote_ip = raw_input("Please enter the IP address displayed on your car: ")
spwIoTsock.connect((remote_ip, port))
print("Connection established. Got connection at", remote_ip)

#===============================     Status Loop     =================================================

# ------Send commands until back button is pressed------ #
status = getState()
while True:
    while not status[BUTTON_SELECT]:
    
        message = special_char + password;
		
        # -------------------------------'remote control' mode-------------------------------------- #
        try:
            time.sleep(status_update_delay)
            status = getState()
            print status
		

            # ---Check for button presses--- #
            if status[BUTTON_A]:    
                if not a_pressed:
                    message += (a_keyword + command_tag)
                    spwIoTsock.sendall(message)
                    a_pressed = True
                    print("A")
                    continue
            else:
                print("A not pressed")
                a_pressed = False

            if status[BUTTON_B]:
                if not b_pressed:
                    message += (b_keyword + command_tag)
                    spwIoTsock.sendall(message)
                    b_pressed = True
                    print("B")
                    continue
            else:
                print("B not pressed")
                b_pressed = False

            if status[BUTTON_Y]:
                if not y_pressed:
                    message += (y_keyword + command_tag)
                    spwIoTsock.sendall(message)
                    y_pressed = True
                    print("Y")    
                    continue
            else:
                y_pressed = False

            if status[BUTTON_X]:
                if not x_pressed:
                    message += (x_keyword + command_tag)
                    spwIoTsock.sendall(message)
                    x_pressed = True
                    print("X")
                    continue
            else:
                x_pressed = False	

            # ---if no button presses to handle, send wheel PWM adjustment--- #
            pwm_l = rangeMap(status[LTHUMBSTICK_Y])
            pwm_r = rangeMap(status[RTHUMBSTICK_Y])
            if abs(pwm_l) < (zero_threshold):             # zero PWM if within joystick "dead-zone"
                pwm_l = 0
            if abs(pwm_r) < (zero_threshold):
		        pwm_r = 0
            if pwm_l < 0:
                if pwm_r < 0:
                    message += (forward_keyword + str(abs(pwm_l)).zfill(3) + str(abs(pwm_r)).zfill(3) + command_tag)
                    spwIoTsock.sendall(message) 
                else:
                    message += (right_keyword   + str(abs(pwm_l)).zfill(3) + str(abs(pwm_r)).zfill(3) + command_tag)
                    spwIoTsock.sendall(message)
            else:
                if pwm_r < 0:
                    message += (left_keyword    + str(abs(pwm_l)).zfill(3) + str(abs(pwm_r)).zfill(3) + command_tag)
                    spwIoTsock.sendall(message)
                else:
                    message += (reverse_keyword + str(abs(pwm_l)).zfill(3) + str(abs(pwm_r)).zfill(3) + command_tag)
                    spwIoTsock.sendall(message)

        # ------Wait for reconnect if connection fails------ #
        except socket.error:  
            print("socket.error: connection disrupted. Awaiting recconect from SPW IoT Module") 
            try:
                spwIoTsock.close()
                spwIoTsock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)      
                spwIoTsock.connect((remote_ip, port))                                 
                print("Connection established. Connected client socket to", remote_ip)
            except socket.error:
                print("socket.error: connection to IoT module lost. Please restart program.")
                sys.exit()
    
	# -------------------------------'no command' mode-------------------------------------- #
	
    # ---Back button pressed: send command for black line detection--- #
	message = special_char + password + blk_line_keyword + command_tag
    spwIoTsock.sendall(message)
    print("Controller client in 'no command' mode. Press START to reinitiate remote control.")
	
	# ---Disconnect from car--- #
    spwIoTsock.close()
	
	# ---Do not send commands until the start button is pressed--- #
    while not status[BUTTON_START]:
        time.sleep(status_update_delay)
        status = getState()
	
	# ---Reconnect to server socket after start button has been pressed--- #
    spwIoTsock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    spwIoTsock.connect((remote_ip, port))
	
	# ---Send command to leave black line--- #
    message = special_char + password + exit_keyword + command_tag
    spwIoTsock.sendall(message)
    print("Connection reestablished. Terminal command sent.")
    break
	
spwIoTsock.close();
sys.exit()
