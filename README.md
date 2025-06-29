# Pioneer: a space-themed fidget board! 🚀

First of all, thank you Meghana for the awesome YSWS https://pathfinder.hackclub.com/! We stan Meghana <3

This is a board I made for the Pathfinder YSWS by Hack Club. And now for a mini yap session
about the name and why I chose it:

## Inspiration ✨
I heard the word Pathfinder and my thoughts jumped to an explorer trying to find their way in an unknown world. Then, of course, I went to brainstorming name ideas, and Pioneer stuck. I thought about the different "eras" of exploration, and came up with four symbols (for the four buttons): a foot, a compass, a train, and a rocket. Each era, when activated, makes the LEDs do something new.

And then of course the empty space was kind of sad, so I thought, why not add stars and planets? The final design has three LEDs as planets, one as the sun, and a couple constellations and a LOT of stars. 💖✨

My final goal for making this project was to learn get more experience with PCBs on Kicad and microcontrollers! 

## Functions ⚙️
So, what do each of the buttons do? Read the table below to find out!
| Button     | Description |
|----------|-------------|
| 🦶 Foot   | Turns on the sun (LED1) with a soft pulse. Press again to turn it off. |
| 🧭 Compass | Starts a slow orbit animation around the sun. Press again to reverse direction! |
| 🚂 Train  | LEDs blink in rhythm—either to a steady beat or synced to music via USB. |
|  🚀 Rocket | Launch sequence: LEDs light up in order, then all flash and stay on. |

## Built With 🛠️ 

- Seeed Studio XIAO RP2040
- 4 tactile switches
- 4 LEDs
- A lot of trial and error

I used KiCad for the PCB and Arduino for the firmware part of it.

## Struggles and Learning 🌱

This project was a mix of “wow this is working!” and “why is nothing working.” A few things I wrestled with:

- **Pin naming confusion**: In the code, I used `D0`, `D1`, etc. at first, but the XIAO RP2040 doesn’t recognize those in code. Turns out you just use numbers like `0`, `1`, `2` instead. Simple fix, but it tripped me up for a while.
- **Red squiggles in GitHub Codespaces**: I thought my code was broken because everything was underlined. Spoiler: Codespaces doesn’t know Arduino syntax unless you set it up. The code was fine.
- **State machines and mode switching**: I didn’t want a million global variables, so I learned how to use enums and clean logic to manage modes. It made the code way easier to read and extend!
- **Timing without delay()**: I had to learn how to use `millis()` to time animations without freezing everything else. It felt weird at first, but now I get why it’s so useful.

## Images!
Here is my schematic: 

![pioneer schematic](images/schematic.png)

And here's my PCB:

![PCB front](images/pcb_front.png)
![PCB back](images/pcb_back.png)