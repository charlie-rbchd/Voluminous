# Voluminous
An ennecessarily large volume control plug-in targetting both JUCE and Wwise.

## Building for JUCE
1. Install [JUCE](https://shop.juce.com/get-juce)
2. Open `Voluminous.jucer` in the Projucer
3. Export and build for your targets of choice

## Building for Wwise
1. Install the Wwise SDK (>=2018.1.3) using the [Wwise Launcher](https://www.audiokinetic.com/download)
2. Premake and build for your targets of choice using the plug-in development tools:
```
%WWISEROOT%\Scripts\Build\Plugins\wp.py premake Authoring
%WWISEROOT%\Scripts\Build\Plugins\wp.py premake Windows_vc140

%WWISEROOT%\Scripts\Build\Plugins\wp.py build Authoring Release
%WWISEROOT%\Scripts\Build\Plugins\wp.py build Windows_vc140 Release
```
