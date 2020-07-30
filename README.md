# Sipeed Longan Nano Timer
Using the device's display to create a kitchen timer that can be reset by pressing a button.

## Sipeed documentation
It may be hard to find documentation for this device, if you need it check it's datasheet found in the docs directory if you follow [this link.](https://dl.sipeed.com/LONGAN/Nano) there is a section that links to various helpful locations including the directory linked with all it's reference manuals and datasheets for the technologies involved.

## LCD Reference project
This project uses the lcd library by github user [slmisc](https://github.com/slmisc/gd32v-lcd). The main pull is the support for dma between the screen and the board, allowing faster refresh rates and other cool stuff.

This project used to use code from [Kevin Sangeelee's git repo](https://github.com/Kevin-Sangeelee/gd32v_test.git) which helped the project get to a workable state. I would recommend it as a good example project using alot of the Sipeed Longan Nano's features.
