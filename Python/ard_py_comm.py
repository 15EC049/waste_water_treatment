import blynklib
import serial

ser = serial.Serial('/dev/ttyUSB1')
BLYNK_AUTH = 'dcNjKdO7nfeIlRyZ8lMpceB6IJ5om5x7'

# initialize Blynk
blynk = blynklib.Blynk(BLYNK_AUTH)

WRITE_EVENT_PRINT_MSG = "[WRITE_VIRTUAL_PIN_EVENT] Pin: V{} Value: '{}'"


# register handler for virtual pin V4 write event
@blynk.handle_event('write V0')
def write_virtual_pin_handler(pin, value):
    #print(WRITE_EVENT_PRINT_MSG.format(pin, value))
    print('V0 Value')
    if ( str(value)==str("['1']")):
    	print (pin)
    	ser.write(b'1')



@blynk.handle_event('write V1')
def write_virtual_pin_handler(pin, value):
    #print(WRITE_EVENT_PRINT_MSG.format(pin, value))
    print('V1 Value')
    if ( str(value)==str("['1']")):
    	print (pin)
    	ser.write(b'2')

@blynk.handle_event('write V2')
def write_virtual_pin_handler(pin, value):
    #print(WRITE_EVENT_PRINT_MSG.format(pin, value))
    print('V2 Value')
    if ( str(value)==str("['1']")):
    	print (pin)
    	ser.write(b'3')

###########################################################
# infinite loop that waits for event
###########################################################
while True:
    #print(ser.name) 
    blynk.run()
    #ser.write(b'hello')
    
ser.close()
