import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
GPIO_TRIGGER = 5
GPIO_ECHO = 6
GPIO_OUTPUT = 14
GPIO.setup(GPIO_TRIGGER,GPIO.OUT)
GPIO.setup(GPIO_ECHO,GPIO.IN)
GPIO.setup(GPIO_OUTPUT,GPIO.OUT)
GPIO.output(GPIO_TRIGGER, False)
pwm = GPIO.PWM(GPIO_OUTPUT, 100)
pwm.start(100)
time.sleep(0.5)

try:
    while True:
        GPIO.output(GPIO_TRIGGER, True)
        time.sleep(0.00001)
        GPIO.output(GPIO_TRIGGER, False)
        start = time.time()
        while GPIO.input(GPIO_ECHO)==0:
          start = time.time()
        while GPIO.input(GPIO_ECHO)==1:
          stop = time.time()
        elapsed = stop-start
        distance = elapsed * 34300
        distance = distance / 2
        if distance > 50:
            distance = 50
        elif distance < 0:
            distance = 0
        print(distance)
        pwm.ChangeDutyCycle(100-(distance*2))
        time.sleep(0.2)
except KeyboardInterrupt:  
    print("Exiting Program")
finally:  
    GPIO.cleanup()  

