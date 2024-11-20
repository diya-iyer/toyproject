import os
os.add_dll_directory(os.getcwd())
import vlc
import time
from serial import Serial

arduino = Serial(port='COM4', baudrate=9600, timeout=1)  


while True:
    push = vlc.MediaPlayer("audio_toyproject\ButtonAudio\PressThe.mp3")
    neg = vlc.MediaPlayer("audio_toyproject\ButtonAudio\\NegativeBeep.mp3")
    pos = vlc.MediaPlayer("audio_toyproject\ButtonAudio\PositiveBeep.mp3")
    heart = vlc.MediaPlayer("audio_toyproject\ButtonAudio\Shapes\Heart.mp3")
    squa = vlc.MediaPlayer("audio_toyproject\ButtonAudio\Shapes\Square.mp3")
    tri = vlc.MediaPlayer("audio_toyproject\ButtonAudio\Shapes\Triangle.mp3")
    data = arduino.readline().decode('utf-8').rstrip()  
    if "Task: Press the" in data:
        push.play()
        time.sleep(.75)
        if "heart" in data:
            heart.play()
        if "square" in data:
            squa.play()
        if "triangle" in data:
            tri.play()
    if "Correct" in data:
        pos.play()
        time.sleep(.5)
    if "Incorrect" in data:
        neg.play()
        time.sleep(.5)
    print(data)  