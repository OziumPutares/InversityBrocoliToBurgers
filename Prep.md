# Research
## Intro
### Key
1. In this file anything with Markdown quotes \` is a quiote from the AI Chatbot unless specified otherwise
## Problem Selection
Using the AI Chatbot I found out that a major problem in tackling obesity is `how food is promoted (advertising and placement)`.
So I decided to try to find out how this problem could be tackled and found out that `Personalized ad blockers could be a tech solution to limit exposure to unhealthy food ads.`
I saw that ads on social media `promote junk food` and using `sophisticated algorithms to target ads based on user behavior making it easy for junk food companies to reach their audience`,
and that the impact is signaificant due to ads increasing `cravings and consumption` of junk food which contributes to poor habits and diets.
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
it took far less time than a neural network would take to implement
