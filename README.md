# **NEXYS A7 SSEG ANIMATOR**
This Projects consists of a bare bones animation software for a 8 digit 7 segment display.
It also includes the necessary systemverilog code to play that animation on a 8 digit 7 segment display.

The animation software consists of a GUI interface powered by RAYLIB.
It was used because it provided a simple library to design a functional GUI.

To build the animation software, all you really need is cmake.
Run the command: "cmake -B build && cmake --build build".
It will download raylib .

The executable will be store in the "build directory".

All animations are saved in a "ASCII text" file and will be stored in the "SSEG ANIMATOR" directory.

If you are using Vivado, be sure to conver the file into a ".txt" or ".bin" file.

For the systemverilog, just load it into whatever software your prefer. You may have to change the constraint file. For my case, my constraint file is for a Nexys A7 FPGA, XC7A100T-1CSG324C. It just loads the ROM file and plays the animation. You could change the frame rate by editing the MAX time counter on the FPS mod_counter.

# **GUI**
<img width="808" height="488" alt="image" src="https://github.com/user-attachments/assets/3f93919a-37c4-458d-b7c4-593fbc5e2de1" />
<br/>
The "arrow and file" button are used to load an existing file used to edit an existing animation file.<br/>
The "trash bin" button unloads the existing animation, it will not affect the existing animation file.<br/>
The "plus" button adds a frame relative to where you are in the animation.<br/>
The "minus" button removes a frame relative to where you are in the animation.<br/>
The "cc/ac" button is a toggle that affects how the animation saves. It is based on if the LEDS are common anode or common cathode.<br/>
The "save" button saves the animation and if the animation is to be used for a common anode or common cathode LED.<br/>
The "export" button saves the animation and does not include a setting for common anode or common cathode display.<br/>
Red text below frame count is meant to give user feed back and letting the user know what they did in case they did not look at readme or open the program in a terminal.
