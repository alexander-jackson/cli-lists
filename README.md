# CLI Lists

CLI Lists is a project to allow list functionality on the command line, for easy updating and modifying lists.

## Getting Started

### Prerequisites

CLI Lists uses the C language, and is written using C99.

### Installing

To install, simply clone the git repository and enter the directory. Then do

`make`

which will result in the `lists` executable.

You can then do 

`make install`

to create the needed directories and move the `lists` binary to `/usr/local/bin/lists`

Alternatively, `make build install` will build and install the binary for you.

### Usage

Creating a list:

`lists create {list_name}`

Deleting a list:

`lists delete {list_name}`

Adding an item to a list

`lists append {list_name} {item_text}`

Removing an item from a list

`lists remove {list_name} {item_text}`

Displaying a list:

`lists display {list_name}`

Renaming a list:

`lists rename {old_name} {new_name}`

Clearing a list:

`lists clear {list_name}`

### File Structure

CLI Lists uses a single file to track your lists, stored within the `~/.local/share` directory
thanks to [this thread on Reddit](https://www.reddit.com/r/linux/comments/971m0z/im_tired_of_folders_littering_my_home_directory/).

The file structure takes inspiration from [TOML](https://github.com/toml-lang/toml) and is thus quite easy to read.
