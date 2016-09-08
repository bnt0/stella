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

## Arch Linux
If you are using Arch Linux you should consider using the package I've uploaded
in the AUR [stella-typer-git](https://aur.archlinux.org/packages/stella-typer-git/)
this will do the compiling for you, and manage your package correctly.

If you use pacaur it will also install the other AUR dependencies

## Other

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

# Building unittests and documentation

You need to have [doxygen](http://www.stack.nl/~dimitri/doxygen/) installed to build the documentation. By default building documentation is disabled, to enable it, use `ccmake .` from the root of the repo and set the BuildDocs option to ON. Then use:
```
cmake .
make docs
```

Building unit tests is disabled by default. To enable it, set BuildTests to true in `ccmake .`. You need to have the [UnitTest++](https://github.com/unittest-cpp/unittest-cpp) library installed to build and run the unittests.
```
cmake .
make tests   # build and run all unit tests
```
