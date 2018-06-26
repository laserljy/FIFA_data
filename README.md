# Motivation
This is a simple project to analyze the historical data of FIFA world cup. I have the interest of check some data after watching the game of Germany vs Sweden in the group game. Germany seems do not deserve the win as I can see, they very luckily scored in the last 30 seconds to make it 2:1 and being okay to advance to the next around. Sweden, on the other hand, got eliminated. Without the last minute goal, Germany would go home very sadly. But at that moment the saddiest team in the world is Sweden. The question immediately came up to me was: given the first goal, what is the wining rate during the World Cup finals. It is best to check all the historical data and get some idea about my question.


# Author and date:
Author: Jiying Li
Date: June 22nd, 2018

# Dataset source
Dataset was found in Kaggle. I checked the FIFA official site and tried to crawl data from Google search result, and Google Developpers' APIs, but none of them are quite successful. Thanks to the dataset available on Kaggle, I was able to find answers to my questions. Also the three files themselves, with their data structure, pretty much already tell about how should I design and implement the classes.

# Class design and implementation
Here are some high-level design of the class:
1. Goal: gameID, gameTime, team, player, typeOfGoal
2. Game: gameID, homeTeam, awayTeam, result, winner, goals
3. Team: name, players, 
4. WorldCup: year, contury, teams, goals, champion

Application code/main cpp:
1. WorldCup WCs = new <WorldCup*> <== File1: WorldCups.xsl
2. Games in each WC <== File2: WorldCupMatches.xsl
3. Scores in each game <== File2: WorldCupPlayers.xsl
4. Get some stats by calling functions

