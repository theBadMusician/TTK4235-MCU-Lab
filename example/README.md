# nRF52DK Development Environment
Development environment for nRF52DK. This project can be used as a basic Makefile-based project or via VSCode with the *cortex-debug* extension on Linux or MacOS.

## Dependencies
Dependencies can be install with your preferred package manager (apt, homebrew, yay, pacman etc.) or via the provided links. 

- arm-none-eabi-gcc >=10.3.1
- arm-none-eabi-gdb
- J-Link Software Tools (https://www.segger.com/downloads/jlink)
-  [nRF Command Line Tools (for nrfjprog)](https://www.nordicsemi.com/Products/Development-tools/nrf-command-line-tools/download) 
- [Alternative installation for nRF Command Line Tools (AUR)](https://aur.archlinux.org/packages/nrf-command-line-tools)
- Python 3.8 for Cortex-Debug

## Ubuntu installation (not needed for lab PCs)

> This installation guide is not complete, and may vary depending on your specific release and/or architecture. See the installation script `install_tildat_microcontroller_deps.sh` for some hints.

Check for existing install:
```bash
arm-none-eabi-gcc --version
```
If not found download and install the ARM GNU toolchain from [this link](https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain) including libcurses5 (Check ![this link](https://askubuntu.com/questions/1243252/how-to-install-arm-none-eabi-gdb-on-ubuntu-20-04-lts-focal-fossa) for solving a common issue with the dependency libcurses5.). Install [nRF Command Line Tools (for nrfjprog)](https://www.nordicsemi.com/Products/Development-tools/nrf-command-line-tools/download) and Python 3.8. 

## MacOS installation
> This installation guide is not complete, and may vary depending on your specific release and/or architecture. See the installation script `install_tildat_microcontroller_deps.sh` for some hints.
> 
This installation process requires Homebrew package manager (https://brew.sh/).

1. Install ARM Toolchain
```bash
brew install arm-none-eabi-gcc
```
```bash
brew install arm-none-eabi-gdb
```
2. Download and install [nRF Command Line Tools](https://www.nordicsemi.com/Products/Development-tools/nrf-command-line-tools/download)
3. Install J-Link Software Tools (https://www.segger.com/downloads/jlink)
4. Install dependencies for Marus cortex debug (See install script for hints)
5. Clone repository and open repository with VSCode
6. Adjust Makefile to suit Homebrew installation paths

## VSCode debugging
To utilize the debugging features in VSCode you need to install the [*marus-cortex-debug*](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug) extension.

### Step 1: Click "Run and Debug"
<img width="507" alt="step1" src="https://github.com/ITK-TTK4235/nrf52-devenvironment/assets/48350530/db4e69e4-5f95-4c5f-86ac-e3fb619e0512">

### Step 2: Click: "Debug (jlink)"
<img width="538" alt="step2" src="https://github.com/ITK-TTK4235/nrf52-devenvironment/assets/48350530/5620c1f8-a286-4178-829b-4eee63a8741b">

## Step 3: Set break points and step through code
<img width="1512" alt="Screenshot 2024-02-06 at 15 20 23" src="https://github.com/ITK-TTK4235/nrf52-devenvironment/assets/48350530/749d3f9d-1e5e-4862-8660-b19346e589ff">

## Step 4: Change and read registers live
<img width="1319" alt="Screenshot 2024-02-06 at 15 21 12" src="https://github.com/ITK-TTK4235/nrf52-devenvironment/assets/48350530/337a8326-9546-4cf9-8693-133cf8be0896">

## Step 5: Read and decode memory layouts
![image](https://github.com/ITK-TTK4235/nrf52-devenvironment/assets/48350530/0fccf8d3-2b01-4b66-874b-7168a0260115)


## Sources
- Based on GH user [*tordnat*'s minimal nrf52dk environment](https://github.com/tordnat/nrf52-minimal-environment)
- Documentation for *marus-cortex-debug*: https://github.com/Marus/cortex-debug
