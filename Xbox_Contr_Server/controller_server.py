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

import xbox
import time
import socket
import sys

# Format decimal to string format xxx
def fmtDec(n):
    return '{:d}'.format(n)

#=====================================================================================================

joy = xbox.Joystick()
max_pwm    = 255
a_pressed  = False         #=============================================#
b_pressed  = False         # Maintain button pressed to one message sent #
x_pressed  = False         #                                             #
y_pressed  = False         #=============================================#
host_port  = 33333
pwm_l      = 0
pwm_r      = 0

# ------Set up server socket------- #
try:
    spwIoTsock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    spwIoTsock.bind(('', host_port))
    print("Socket creation successful")
except socket.error as err:
    print("Socket creation failed with error %s" %(err))
    sys.exit()

# ------Wait for client connect------- #
print("Awaiting connection from SPW IoT Module")
spwIoTsock.listen(1)
client, addr = spwIoTsock.accept()
print("Connection established. Got connection from", addr)

#=====================================================================================================
# ------Send commands until back button is pressed------ #
while not joy.Back():
    time.sleep(.050)

    # ---Attempt to send commands to client--- #
    try:
        if joy.connected():
        # ---Xbox 360 Controller Connected--- #
            print("Connected: Lx,Ly ",fmtDec(max_pwm*joy.leftX()),fmtDec(max_pwm*joy.leftY()))

            # ---Check for button presses--- #
            if joy.A():    
                if not a_pressed:
                    client.send("*8657A0000\r\n")
                    a_pressed = True
                    print("A")
                    continue
            else:
                a_pressed = False,

            if joy.B():
                if not b_pressed:
                    client.send("*8657B0000\r\n")
                    b_pressed = True
                    print("B")
                    continue
            else:
                b_pressed = False,

            if joy.Y():
                if not y_pressed:
                    client.send("*8657Y0000\r\n")
                    y_pressed = True
                    print("Y")    
                    continue
            else:
                y_pressed = False,

            if joy.X():
                if not x_pressed:
                    client.send("*8657X0000\r\n")
                    x_pressed = True
                    print("X")
                    continue
            else:
                x_pressed = False

            # ---if no button presses to handle, send wheel PWM adjustment--- #
            pwm_l = max_pwm*((int) joy.leftY())
            pwm_r = max_pwm*((int) joy.rightY())
            if pwm_l < 0:
                if pwm_r > 0:
                    client.send("*8657KQ" + str(abs(pwm_l)) + str(abs(pwm_r)) + "\r\n")
                else:
                    client.send("*8657KS" + str(abs(pwm_l)) + str(abs(pwm_r)) + "\r\n")
            else:
                if pwm_r > 0:
                    client.send("*8657MQ" + str(abs(pwm_l)) + str(abs(pwm_r)) + "\r\n")
                else:
                    client.send("*8657MS" + str(abs(pwm_l)) + str(abs(pwm_r)) + "\r\n")
        
        # ---Xbox 360 Controller disconnected--- #
        else:
            print("Disconnected")

    # ------Wait for reconnect if connection fails------ #
    except socket.error:  
        print("Connection lost. Awaiting recconect from SPW IoT Module") 
        client.remove(spwIoTsock)
        spwIoTsock.listen(1)
        client, addr = spwIoTsock.accept()
        print("Connection established. Got connection from", addr)
    
# ---Back button pressed: send command for black line detection and close--- #
client.send("*8657L0000\r\n");
joy.close()
