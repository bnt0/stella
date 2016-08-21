# Stella
Text expander for Linux and X11

# Prereqs
- Linux with X11
- libxtst (libXtst.so)
- [libuiohook](https://github.com/kwhat/libuiohook)
- [protobuf](https://github.com/google/protobuf)
- [jsoncpp](https://github.com/open-source-parsers/jsoncpp)
- cmake

# Compiling & Install
```
./configure (or cmake .)
make
make install
```

# Running
Run `stellad` in the background use `stella-config` to alter the settings of the running `stellad`.

`stella-config --help` has extensive usage info

Consider using the `stella-config -I` option for iteractive console. `ctrl + c` to exit.

## Listing current shortcuts
`stella-config -s list` or interactive mode

## Adding shortcuts
### Easy mode
`stella-config -I`
### Hard mode
`stella-config -Sak <key> -v <value> -e "true"`
will add the `<key>` with resultant text `<value>`

`stella-config -Srk <key>` will remove it

`stella-config -Sm` will remove any keys that exist before readding.

## Saving
Configuration is not saved unless explicitly requested, use `stella-config -s save` to save

