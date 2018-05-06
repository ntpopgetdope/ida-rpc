# ida-rpc

<p align="center"><img src ="https://i.imgur.com/OcrZ7Fp.png" /></p>

## About
ida-rpc was a quick test plugin to see what changed in the 7.0 sdk, subsequently it only supports IDA 7.x as of now, 
it allows for [discord rich presence](https://discordapp.com/rich-presence) to display information about the current IDA session

## Installation
To install ida-rpc simply copy the two binaries from the [latest release](https://github.com/offlineJ/ida-rpc/releases) to ```ida_install_location/plugins/``` ,
to change options within the plugin open the plugins menu and select IDA RPC ```Edit -> Plugins -> IDA RPC``` or use the default hotkey ```Ctrl-Alt-R```

## :flushed:
~~Didnt see any point in uploading source as its such a simple plugin, will upload if requested though~~

## Building
To build this solution you'll need to get a copy of the [IDA 7.x SDK](https://www.hex-rays.com/products/ida/support/download.shtml), compile in 64bit Release for 32bit ida and 64bit Release64 for 64bit ida
