# InversityBrocoliToBurgers
## What is this project?
This Project is a Proof of concept for a junk food adblocker oriented in the interest of tackling obesity also made as part of my inversity submission for September 2024
## How do you configure the filtering script?
The general format for the configuration is using these simple rules:\
1. Start a line with text to search for e.g. `eat`
2. Then add an exclamation mark to symbolise a term to exclude e.g. `!feat`
3. Repeat the exclamation marks until all the terms are included
4. A commented line starts with `#Hello`
An example configuration could include
```
#This is my obesity tackling Filter file
#Include all lines that include eat but not feat
eat!feat
ads!google!amazon
ubereat
```
**N.B. if you start a line with an exclamtion(`!`) mark all the lines will be filtered for that term and backslashes can be used to include exclamation marks or hashtags in the line e.g. `\#` or `\!`**
# Building
For building see [building.md](https://github.com/OziumPutares/InversityBrocoliToBurgers/blob/main/building.md)
