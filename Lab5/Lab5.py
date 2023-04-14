import Jetson.GPIO as GPIO
import time

SPICLK = 11
SPIMISO = 9
SPIMOSI = 10
SPICS = 8
output_pin = 7
output_pin2 = 13
photo_ch = 0

def init():
    GPIO.setmode(GPIO.BOARD)
    #GPIO.setup(output_pin, GPIO.OUT)
    GPIO.setwarnings(False)
    GPIO.cleanup()
    GPIO.setmode(GPIO.BCM)
    #GPIO.setup(output_pin, GPIO.OUT)
    GPIO.setup(SPIMOSI, GPIO.OUT)
    GPIO.setup(SPIMISO, GPIO.IN)
    GPIO.setup(SPICLK, GPIO.OUT)
    GPIO.setup(SPICS, GPIO.OUT)

def readadc(adcnum, clockpin, mosipin, misopin, cspin):
    GPIO.setmode(GPIO.BCM)
    if ((adcnum > 7) or (adcnum < 0)):
        return -1
    GPIO.output(cspin, True)

    GPIO.output(clockpin, False)
    GPIO.output(cspin, False)

    commandout = adcnum
    commandout |= 0x18
    commandout <<= 3
    for i in range(5):
        if (commandout & 0x80):
            GPIO.output(mosipin, True)
        else:
            GPIO.output(mosipin, False)
        commandout <<= 1
        GPIO.output(clockpin, True)
        GPIO.output(clockpin, False)
    
    adcout = 0
    #print('fuck you')
    for i in range(12):
        GPIO.output(clockpin, True)
        GPIO.output(clockpin, False)
        adcout <<= 1
        if (GPIO.input(misopin)):
            adcout |= 0x1 
    
    GPIO.output(cspin, True)
    
    #print("fuck you chino")
    GPIO.cleanup()
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(output_pin, GPIO.OUT)
    GPIO.setup(output_pin2, GPIO.OUT)
    adcout >>= 1
    #print(output_pin,GPIO.LOW)
    print("Led1 {}".format(adcout>500))
    print("Led2 {}".format(adcout>150))
    GPIO.output(output_pin2, adcout>500)
    GPIO.output(output_pin, adcout>150)
    GPIO.cleanup()
    return adcout

def main():
    #init()
    while True:
        init()
        adc_value = readadc(photo_ch, SPICLK, SPIMOSI, SPIMISO, SPICS)
        print(adc_value)
        time.sleep(1)

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(e)
