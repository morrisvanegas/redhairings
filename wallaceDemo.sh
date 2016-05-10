#!/bin/bash

osascript -e 'quit app "Preview"'
open -a Preview "src/wallace_output/wallace_output.png" ; /usr/bin/osascript -e 'tell application "Preview"' -e "activate" -e 'tell application "System Events"' -e 'keystroke "f" using {control down, command down}' -e "end tell" -e "end tell"
