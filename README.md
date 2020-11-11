# CodeSamples - PLEASE READ!

Howdy! This repository contains some selected code samples, both from my personal projects and my academic work at the University of Utah.



The first sample is from my most recent personal project, a Unity game called Cotton Candy Sheep. The player plays as a wolf attempting to 
herd and guide the sheep into a specific area. The provided sample is the AI for the sheep that inhabit the level. 
This code had to follow a few rules and behaviors we laid out:

1. Except for the single black sheep, there are 2 sheep of each color spread around the map.
2. All sheep will run away from the wolf normally, making it extremely hard to herd them.
3. However, there are cloaks scattered around the map. If the wolf equips a cloak with a specific color, the sheep that match that color will 
follow the wolf around.
4. There is a black sheep that must be collected LAST by the wolf (think the black 8 ball in pool). The black sheep will follow the wolf around 
as long as he is wearing any cloak. Other sheep will walk away from the black sheep if it gets too close.

I was able to condense these behaviors into a small class that performed all we needed from the sheep with relatively little code. Using this 
code sample, our game was able to have a functional AI that challenged the player and made them interact with our designed systems at a deep level,
leading to cloaking strategies, black sheep lure techniques, and much more!



The second sample is a method from the encoder for a custom audio file format, .asif. This was originally an academic project, 
but I became so interested by the idea that I ended up working on my implementation over the following summer as a personal project.
When we designed this new file format, we made some design decisions that proved critical to the implementation of the encoder itself:

1. Typically, an encoder will transform the raw audio waveforms into usable data using packets of a uniform size, which are then sent
on to a muxer to be combined into the final audio file itself. However, we decided to simply create one packet that contained the data
for the entire file, so that our muxer could be made very simple.
2. To save space, we used 8-bit signed integers to represent our audio data. This meant that we had to clamp all of our data from the raw waveforms
to this range, losing some audio definition and crushing the extreme ends of the spectrum, both high and low. This was something that was deemed to
be a worthwhile trade, as the saved space was a much bigger benefit than any data lost due to clamping.

Overall, I found this project to be an extremely interesting challenge, as it was both in C, a language I wasn't as familiar with at the time, and
due to its more technical nature. 



The third sample is two methods from another academic project. This one was a gramatically correct sentence generator that generates sentences as 
quickly as possible. Due to the requirement for speed in this project, my partner and I decided on a few design rules to meet this requirement:

1. We decided to use hash maps to store the necessary data, as we discovered that this approach would be the most efficient
data structure for our needs, something made even more critical by the requirements laid out.
2. For the same concerns, we also decided to use Java's StringBuilder class to build our generated sentences, which does concatenation
much faster than manual operator-driven string concatenation or using the default .concat() method provided by Java.

Using these decisions and some cleaning up of basic code errors and time-wasting design, we were able to get our solution into the top 15% of the class.
I learned a lot about how to design code to run efficiently from this project, and I think it definitely has helped me become a better software engineer,
both in terms of becoming much better at designing and implementing efficient and bug-free code, and also in terms of thinking more consciously about the goals
of the code that I write, and taking the time to design code that can accomplish those goals.

Thanks for reading!

