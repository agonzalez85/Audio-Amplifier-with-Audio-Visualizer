# Audio-Amplifier-with-Audio-Visualizer

## Description
This project is an Audio amplifier with an integrated 7-band Audio Visualizer using an Arduino Nano, MSGEQ7 frequency analyzer chip, and an OLED display. This project is part of a custom PCB audio amplifier project that includes stereo sound output and user controls in volume, amplifier gain, and bass boost. The visualizer reads audio frequency data from the MSGEQ7 chip, processes it, and displays a bar graph of the 7 bands on the OLED screen. The frequency bands displayed are 63 Hz, 160 Hz, 400 Hz, 1 kHz, 2.5 kHz, 6.3 kHz, and 16 kHz.

## Features
- Real-time 7-band audio visualization
- Stereo audio output
- User-controllable volume, gain, and bass boost

## Hardware
- MSGEQ7 frequency analyzer chip
- Arduino Nano
- SSD1306 OLED Display (128x64)
- LM386N-4 amplifiers for stereo output
- NE5532P buffer for audio stability

## Software
- MSGEQ7 library
- U8g2lib library


## Schematic
The schematic for the audio amplifier with an integrated 7-band visualizer can be found here (./docs/Audio_Amplifier_Schematic.pdf).

## 3D Model
The 3D model is available in STEP and WRL format here (./docs/Audio Amplifier.step).
To view:
1. Download the files
2. Open it using 3D CAD software
 
A screenshot of the 3D model is available here (./docs/Audio_Amplifier_3D_Model.png)

## Project Structure
- `Audio_Visualizer_Amplifier.ino`: Main Arduino code
- `docs/`: Contains schematic, 3D model, and other documentation
