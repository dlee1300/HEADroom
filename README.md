# HEADroom

At its core, HEADroom is a gain utility plugin, although its primary purpose is to be used as a means of adding headroom to a mix before a mastering session.

## Run Locally

This project can be opened and edited locally in JUCE.

Clone the repository using:

```
git clone https://github.com/dlee1300/HEADroom.git
```
cd HEADroom

If you do not have JUCE, download it on your local computer. Once downloaded, can open HEADroom.jucer to view and edit the project file.

## Using the Plugin

HEADroom can be used on your local computer after you build the necessary files within HEADroom.jucer. 

To use it in a DAW:
- Open HEADroom.jucer and launch the project in your local IDE.
- Set the build target to "HEADroom - AU" or "HEADroom - VST3", depending on the requirements of your DAW.
- Run the Build command.
- If the .component .vst .vst3 files are not automatically added to the folder your DAW plugin folder, manually copy them from within the "Builds" folder to your computer's Plugin folder.
- Launch your DAW and allow it to scan for new plugins.

To use it as a standalone:
- Open HEADroom.jucer and launch the project in your local IDE.
- Set the build target to "HEADroom - Standalone Plugin"
- Use the Build and Run command, and wait for the plugin to launch as a standalone. Note that the plugin may not work if it is not taking in any input as a standalone.
