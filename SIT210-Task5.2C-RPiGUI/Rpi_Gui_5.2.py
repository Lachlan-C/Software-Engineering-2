from tkinter import *
import tkinter.font
from gpiozero import LED
import RPi.GPIO
RPi.GPIO.setmode(RPi.GPIO.BCM)

ledGreen=LED(14)
ledBlue=LED(15)
ledRed=LED(10)

win = Tk()
win.title("LED Toggler")
myFont = tkinter.font.Font(family = 'Helvetica', size = 12, weight = "bold")


def ledRedToggle():
    ledRed.on()
    ledGreen.off()
    ledBlue.off()

def ledGreenToggle():
    ledGreen.on()
    ledBlue.off()
    ledRed.off()
        
def ledBlueToggle():
    ledBlue.on()
    ledGreen.off()
    ledRed.off()
        
def close():
    RPi.GPIO.cleanup()
    win.destroy()


ledRedButton = Button(win, text='RED', font=myFont, command=ledRedToggle, bg='red', height=1, width=24)
ledRedButton.grid(row=0,column=1)
ledGreenButton = Button(win, text='GREEN', font=myFont, command=ledGreenToggle, bg='green', height=1, width=24)
ledGreenButton.grid(row=4,column=1)
ledBlueButton = Button(win, text='BLUE', font=myFont, command=ledBlueToggle, bg='blue', height=1, width=24)
ledBlueButton.grid(row=2,column=1)

exitButton = Button(win, text='Exit', font=myFont, command=close, bg='red', height=1, width=6)
exitButton.grid(row=6, column=1)

win.protocol("WM_DELETE_WINDOW", close) 

win.mainloop() 
