# project_comp2012h

In "A Guy Chased by a Dog and Doesn't Wanna Lose His Life" game, the player can controls the man. The purpose is to run through the city, survive from  the main enemy "DOG", and collect coins and diamonds. The game is a side-scrolling platform game. The player moves to the right and finally reaches the flagpole.

AS we had to do some work on the scene, we  subclass QGraphicsScen and create the new class MyScene. There, we implement one part of the game logic. This is convenient since QGraphicsScene inherits QObject and thus we can use Qt's signal and slot mechanism.
