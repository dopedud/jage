# Overview (detailed)

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
lot of new things regarding game development.
