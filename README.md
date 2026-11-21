# **NEXYS A7 SSEG ANIMATOR**
This Projects consists of a bare bones animation software for a 8 digit 7 segment display.
It also includes the necessary systemverilog code to play that animation on a 7 segment
display.

The animation software consists of a GUI interface powered by RAYLIB.
It was used because it provided a simple library to design a functional GUI.

To build the animation software, all you really need is cmake.
run the command: "cmake -B build && cmake --build build"

The executable will be store in the "build directory".

For the systemverilog, just load it into whatever software your prefer. You may have to change the constraint file. For my case, my contraint file is for a Nexys A7 FPGA, XC7A100T-1CSG324C. It just loads the ROM file and plays the animation. You could change the frame rate by editing the MAX time counter on the FPS mod_counter.

# **GUI**
<img width="40" height="40" alt="image" src="https://github.com/user-attachments/assets/cac1be00-af28-4aee-9a96-f70440931016" />
