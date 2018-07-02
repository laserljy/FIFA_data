# Motivation
This is a simple project to analyze the historical data of FIFA world cup since 1930. I had the interest of checking this dataset after watching the game of Germany vs Sweden in Group F. This was a Win-Or-Go-Home game for Germany, everyone was expecting to see that they give it all their heart and soul to knock down the match. Although they did win, it did not seem to me that they deserve it. Sweden was very efficient, smart and fearless. Germany, on the other hand, was not innovative and seemed very rough technically. They very luckily scored the 2nd goal in the 94th min (5 mins injury time) to make it 2:1 and being just okay to advance to the next round. Sweden, on the other hand, got eliminated in the last 30 seconds after combating with the 3 time World Cup champion so tenaciously. Without doubt, Sweden was saddest team in the world at that moment, and my heart was with you. Then the question quickly came up to me was: given that the team scored the first goal, what is his winning rate for the game? The best way to find it out is to check the historical data for all the games in the World Cup finals.

PS: My guess was wrong, it was not a Win-Or-Go-Home game for either team, but quite important for taking the lead in the rank. It turned out that the last two games in F group completed changed the standings that Sweden sweeped Mexico and Germeny beaten by South Korean, which kind of prove my point that Germany was really bad in this WC.

# Author and date:
Author: Jiying Li
Date: June 22nd, 2018

# Dataset source
Dataset was found in Kaggle. I checked the FIFA official site and tried to crawl data from Google search result, and Google Developers' APIs, but none of them are quite successful. Thanks to the dataset available on Kaggle, I was able to find answers to my questions. Also these three files themselves, with their data structure, pretty much tell about how should I design and implement the classes.

# Class design and implementation
Here are some high-level design of the class:
1. Goal: gameID, gameTime, team, player, typeOfGoal
2. Game: gameID, homeTeam, awayTeam, result, winner, goals
3. Team: name, players, 
4. WorldCup: year, contury, teams, goals, champion

Application code/main cpp:
1. WorldCup WCs = new <WorldCup*> <== File1: WorldCups.xsl
2. Games in each WC <== File2: WorldCupMatches.xsl
3. Scores in each game <== File3: WorldCupPlayers.xsl
4. Get some stats by calling functions in WorldCup.

