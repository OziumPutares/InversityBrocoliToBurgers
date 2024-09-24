# Research
## Intro
### Key
1. In this file anything with Markdown quotes \` is a quote from the AI Chatbot unless it links to something
2. Square brackets in markdown qutoes represents and addition e.g `This is the quote[This is not the quote]`
## Problem Selection
Using the AI Chatbot I found out that a major problem in tackling obesity is `how food is promoted (advertising and placement)`.
So I decided to try to find out how this problem could be tackled and found out that `Personalized ad blockers could be a tech solution to limit exposure to unhealthy food ads.`
I saw that ads on social media `promote junk food` and using `sophisticated algorithms to target ads based on user behavior making it easy for junk food companies to reach their audience`,
and that the impact is signaificant due to ads increasing `cravings and consumption` of junk food which contributes to poor habits and diets.\
Also in my research I found that ["Children consumed 45% more when exposed to food advertising. Adults consumed more of both healthy and unhealthy snack foods following exposure to snack food advertising compared to the other conditions." and that "advertising [led] to prime automatic eating behaviors and thus influence far more than brand preference alone"](https://psycnet.apa.org/buy/2009-10284-004),
Further reasearch found that ["Food advertising focuses particularly on unhealthy and palatable food products" and that "Food advertising is considered to be a significant contributor to obesity."](https://www.sciencedirect.com/science/article/abs/pii/S2352154615001564) these results were found **repeatedly** across many different scientific studies,
looking at the affect of advertising on food consumption.
## Problem Definition
The problem is the high prevelance of online food advertising.
## Implementation Issues
Some Issues consist of:
1. MV2 is being depracted by chrome
2. The ad-blocker can't block server side mixed ads
3. A filtering list dedicated to blocking food ads would have to be curated
4. Web-kit on IOS prevents any ad-blocking
5. No CSS blocking
6. Can't block all food ads (due to google ads using one url for all ads) :(
Possible Solutions:
1. Use Machine Learning to filter ads
2. Partnerships with Advertisers to give people a choice in what ads they are shown e.g. like with gambling
## Implementation Process
Therefore to test this Idea I decied to make a "quick" C++ script to filter easylist,
tested how this would work by configuring uBlock Origin with the filtered version of EasyList.
This turned out to block around 90% of all the food ads an therefore I decided to continue with the basic idea.
While this solution may not be as optimal as a machine learning based detection scheme,
it took far less time than a neural network would take to implement.
I implemented the entire extension/add-on in Javascript.
