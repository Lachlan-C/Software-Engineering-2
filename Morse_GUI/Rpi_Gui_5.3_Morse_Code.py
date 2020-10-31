from tkinter import *
import time
import tkinter.font
from gpiozero import LED
import RPi.GPIO
RPi.GPIO.setmode(RPi.GPIO.BCM)
led=LED(14)

MORSE_CODE_DICT = { 'A':'.-', 'B':'-...', 
                    'C':'-.-.', 'D':'-..', 'E':'.', 
                    'F':'..-.', 'G':'--.', 'H':'....', 
                    'I':'..', 'J':'.---', 'K':'-.-', 
                    'L':'.-..', 'M':'--', 'N':'-.', 
                    'O':'---', 'P':'.--.', 'Q':'--.-', 
                    'R':'.-.', 'S':'...', 'T':'-', 
                    'U':'..-', 'V':'...-', 'W':'.--', 
                    'X':'-..-', 'Y':'-.--', 'Z':'--..', 
                    '1':'.----', '2':'..---', '3':'...--', 
                    '4':'....-', '5':'.....', '6':'-....', 
                    '7':'--...', '8':'---..', '9':'----.', 
                    '0':'-----', ', ':'--..--', '.':'.-.-.-', 
                    '?':'..--..', '/':'-..-.', '-':'-....-', 
                    '(':'-.--.', ')':'-.--.-'}

win = Tk()
win.title("LED Morse Code")
myFont = tkinter.font.Font(family = 'Helvetica', size = 12, weight = "bold")


def morse_code():
    input = textBox.get("1.0",'end-1c')
    input = input.upper()
    morse = ''
    for letter in input:
        if letter != ' ':
            morse += MORSE_CODE_DICT[letter] + ' '
        else:
            morse += ' '
    for item in morse:
        if item == '.':
            led.on()
            time.sleep(.5)
            led.off()
            time.sleep(.5)
        elif item == '-':
            led.on()
            time.sleep(1.5)
            led.off()
            time.sleep(.5)
        elif item == ' ':
            time.sleep(2)
            
            
        
def close():
    RPi.GPIO.cleanup()
    win.destroy()

textBox = Text(win, height=1, width=42)
textBox.grid(row=0, column=1)

ledButton = Button(win, text='Submit', font=myFont, command=morse_code, bg='gray', height=1, width=6)
ledButton.grid(row=1,column=1)


exitButton = Button(win, text='Exit', font=myFont, command=close, bg='red', height=1, width=6)
exitButton.grid(row=2, column=1)

win.protocol("WM_DELETE_WINDOW", close) 

win.mainloop() 