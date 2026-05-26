# Overview

This is the overview section of the development of JAGE as a game engine. This section will cover and discuss all
things related to developing JAGE which includes engine, architecture, and system design decisions that have been made
along the way, efforts made to allow maximum control for the user of the engine, while still keeping a friendly and
easy-to-use interface as much as possible, and all the trade-offs that were made to achieve this.

Before heading deep down into the engine specifics, I think it would be appropriate to first and foremost discuss how
does the thought of even building a system that is as complex as a game engine came to be, since usually people don't
usually go about creating game engines from scratch without a very strong reason. Whether you find my reason to be
justified or just plainly stupid and laughable, is entirely up to your own personal opinion.

# Background, Motivation, and Rationale

This isn't actually the first time I had written a game engine by myself, in a sense. The first time actually happened
when I was 14-years-old, and even then, if I could rewind time back to the past, I would've picked an off-the-shelf
game engine like Unity or Unreal. I was not exposed to such tools, however (more so I didn't thought of trying to look
up existing solutions first before coming up with my own), and instead searched up YouTube tutorials on how to make
your own video game (not a game engine!). This is where I actually picked up programming skills in a gradual manner
(although I mostly just copy-paste code that I've seen in the tutorials) and where I first learned the Java
programming language. Thinking back, Java would be the last programming language I would use if I want to build
low-latency applications, especially applications like a game engine, but I am still grateful that it's my first
programming language that I've learned, especially since it would bring the context of my programming skills relevant
when transitioning to Unity, 2 years later.

Upon reaching 16-years-old, I haven't had the chance to pour effort into learning programming and game development,
since as a student, my top priorities are to study and focus on my exams at school, especially since there is a really
important exam that I had to sit for when I hit 15. After that exam though, the age of 16 at my school is like the
best time to be in as you're not as pressured to perform in your studies, which give way to students to divert their
focus to their own interest, even if it's to their own detriment. For my case, after the big exam, I finally had the
chance to cool off a bit and revisit some of my hobbies that I've left off before, one of them being game development.

It wasn't until I'd heard that my school was participating in a game development competition that I'd started to
seriously put effort into building real games that other people can play. That's where I first started learning and
using Unity to build games from scratch. It was quit the steep learning curve at first, but I've managed to overcome
it, and actually submitted 2 games for the competition, one of which was a 2D platformer runner, and the other one a 3D
horror. The submission for the second game didn't get through, probably because the competition outlines the rule that
a submitted game must appeal to the general audience (including kids), and the horror genre doesn't exactly fit into
that criteria. The first submission did get through, and it is what me and my team at the time presented when the
competition took place. I could tell more about this competition, but to cut it short, we unfortunately didn't win it
and return to our school sort of empty-handed. It did end up a really great experience though, and I got to learn a
lot of new things involving game development.

Fast forward to 4 years later (I had to once again divert my focus to my studies for pre-university preparation for
that 4 years), I'd started my student years as a computer science student at my university. I don't think there's
really anything significant going on in the first 2 years (aside from learning foundational topics all CS students
should know). It's not until year 3 where I'd started revisit game development again to work on one of the elective
modules the course provides (and which I chose explicitly), which is game development. Obviously, I choose Unity as the
game engine to work on my games (as the coursework), and needless to say, it's a lot of fun developing games when I'm
not pressured by other aspects of my life. At the time (specifically on the game development module), I had to do 2
courseworks, each for a different kind of game. The first coursework requires me to develop a game with a strong theme
supporting it, which I end up developing a 2D top-down shooter. The second coursework was more narrative-driven, and to
be honest, it is quite the challenge to develop a linear story progression system in Unity (which is a given, Unity
isn't supposed to provide primitives to develop narrative-based games, although I think it would be a great idea for
them to implement it as a separate feature where developers can optionally opt in). Nonetheless, I did both of them
quite well (I think) and overall, I've graduated with a computer science degree in the end.

Now, for a moment, telling stories about my background took me to a nostalgic trip, but it does not warrant me to
develop a whole game engine from scratch. Even then, it helps explain where my experiences with game development came
from, and I think that serves as evidence for some of my opinions I'm about to elaborate regarding game development
with off-the-shelf game engines.

The biggest issue I see when developing games using tools made by big tech companies is their development environment.
Much like how a plumber needs their tools, safety equipment, and a suitable environment to fix broken pipes, a game
developer needs their set of tools and a suitable environment as well for them to utilise their tools effectively. A
deteriorated condition in one of these 2 factors can affect a game developer's experience when making a game, which
consequently affects their final product.

This does not mean that a developer should solely rely on their tools to do their job. One would say that a skilled
handyman does not depend on his tools. Rather, it's the deep knowledge and acummulated experience of several years of
game development of a developer that would determine their overall skills and whether they have what it takes to make
any kind of game effectively. Even then, working with bad tools almost always have an effect on a developer's
productivity, and what most game engines do nowadays to achieve this effect is to increase dependence on their engine
and set of game development tools from the developer so that they won't depend on anything else to work their craft.
It's so bizarre that I have to go the extra mile of hacking around Unity's proprietary engine just to implement my own
physics engine!

Granted, Unity's business model litreally forbids me from doing so (and Unreal is open-source anyways), however I still
stand with my point. I can give one other example to highlight this point even more, where I couldn't tamper with Unity
engine's source code (to make better judgements of how I should code my game), simply because I don't have the required
generated revenue to gain that access. Again, granted, that Unity's business model would require that my game should be
sold extremely well first before I even get to have a talk with Unity about tampering with its source code, but even
having a read-only rough overview of its source code would be enough for a free-tier access.

<!-- 
TODO: explain about how you as a developer would be locked in their development environment, no freedom, source code
unavailable in the case of Unity, bloated tools, not needed features being included, on the bright side support and
documentation is abundant, massive community, ease of use, 
-->
