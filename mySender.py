"""
This python script is used to configure the DW1000 chip as a sender and start sending message . It must be used in conjunction with the Receiver script. 
It sends the custom message with a specified delay (2 sec by default).
It requires the following modules: DW1000, DW1000Constants
"""


import DW1000
import DW1000Constants as C
import time

number = 1
sent = False
SEND_DELAY = 5
# [dataRate, pulseFrequency, preambleLength]
MODE_TEST = [C.TRX_RATE_6800KBPS, C.TX_PULSE_FREQ_16MHZ, C.TX_PREAMBLE_LEN_128]

def handleSent():
    """
    This is a callback called from the module's interrupt handler when a transmission was successful. 
    It sets the sent variable as True so the loop can continue.
    """
    global sent
    sent = True

def transmitter():
    """
    This function configures the chip to prepare for a transmission.
    It modifies the data that will be sent and start the transmission with the chosen delay.
    """
    global number
    DW1000.newTransmit()
    # msg = "Hello Raspi3, it's #" + str(number)
    # DW1000.setDataStr(msg)
    msg = [0x41, 0x88, 0, 0xCA, 0xDE, 0xFF, 0xFF, 0, 0, 0x80, 0, 0]
    msg[2] = number
    DW1000.setData(msg, 12)
    DW1000.setDelay(SEND_DELAY, C.MILLISECONDS)
    DW1000.startTransmit()
    number += 1
    print(msg[2])

try:
    PIN_IRQ = 19
    PIN_SS = 16
    DW1000.begin(PIN_IRQ)
    DW1000.setup(PIN_SS)
    print("DW1000 initialized ...")
    DW1000.generalConfiguration("7D:00:22:EA:82:60:3B:9C", MODE_TEST)
    DW1000.registerCallback("handleSent", handleSent)
    DW1000.setLeds(C.LEDS_ENABLE)
    transmitter()
    while 1:
        if sent:
            transmitter()
            sent = False
            time.sleep(1)
except KeyboardInterrupt:
    DW1000.close()
