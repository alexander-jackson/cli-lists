# CLI Lists

CLI Lists is a project to allow list functionality on the command line, for easy updating and modifying lists.

## Getting Started

### Prerequisites

CLI Lists uses the C language, and is written using C99.

### Installing

To install, simply clone the git repository and enter the directory. Then do

`make`

which will result in the `list` executable.

### Usage

Creating a list:

`list new {name}`

Deleting a list:

`list delete {name}`

Adding an item to a list

`list append {name} {item_text}`

Displaying a list:

`list display {name}`

### File Structure

CLI Lists uses a single file to track your lists, stored within the `~/.local/share` directory
thanks to [this thread on Reddit](https://www.reddit.com/r/linux/comments/971m0z/im_tired_of_folders_littering_my_home_directory/).

The file structure takes inspiration from [TOML](https://github.com/toml-lang/toml) and is thus quite easy to read.
