1. Run `./fork.py -s 10` and see which actions are taken. Can you predict what the process tree looks like at each step? Use the -c flag to check your answers. Try some different random seeds (-s) or add more actions (-a) to get the hang of it.

```
❯ ./fork.py -s 10 -c
                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: a forks c
                               a
                               ├── b
                               └── c
Action: c EXITS
                               a
                               └── b
Action: a forks d
                               a
                               ├── b
                               └── d
Action: a forks e
                               a
                               ├── b
                               ├── d
                               └── e
```



2. One control the simulator gives you is the fork percentage, controlled by the -f flag. The higher it is, the more likely the next action is a fork; the lower it is, the more likely the action is an exit. Run the simulator with a large number of actions (e.g., -a 100) and vary the fork percentage from 0.1 to 0.9. What do you think the resulting final process trees will look like as the percentage changes? Check your answer with -c.

More chance to fork, the tree get bigger.

```
❯ ./fork.py -s 10 -a 10 -f 0.1 -c
                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b EXITS
                               a
Action: a forks c
                               a
                               └── c
Action: a forks d
                               a
                               ├── c
                               └── d
Action: c EXITS
                               a
                               └── d
Action: d EXITS
                               a
Action: a forks e
                               a
                               └── e
Action: a forks f
                               a
                               ├── e
                               └── f
Action: e EXITS
                               a
                               └── f
Action: f EXITS
                               a
```

```
❯ ./fork.py -s 10 -a 10 -f 0.9 -c
                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: a forks c
                               a
                               ├── b
                               └── c
Action: c forks d
                               a
                               ├── b
                               └── c
                                   └── d
Action: a forks e
                               a
                               ├── b
                               ├── c
                               │   └── d
                               └── e
Action: b forks f
                               a
                               ├── b
                               │   └── f
                               ├── c
                               │   └── d
                               └── e
Action: f forks g
                               a
                               ├── b
                               │   └── f
                               │       └── g
                               ├── c
                               │   └── d
                               └── e
Action: e forks h
                               a
                               ├── b
                               │   └── f
                               │       └── g
                               ├── c
                               │   └── d
                               └── e
                                   └── h
Action: c forks i
                               a
                               ├── b
                               │   └── f
                               │       └── g
                               ├── c
                               │   ├── d
                               │   └── i
                               └── e
                                   └── h
Action: e forks j
                               a
                               ├── b
                               │   └── f
                               │       └── g
                               ├── c
                               │   ├── d
                               │   └── i
                               └── e
                                   ├── h
                                   └── j
Action: g forks k
                               a
                               ├── b
                               │   └── f
                               │       └── g
                               │           └── k
                               ├── c
                               │   ├── d
                               │   └── i
                               └── e
                                   ├── h
                                   └── j
```



3. Now, switch the output by using the -t flag (e.g., run `./fork.py -t`). Given a set of process trees, can you tell which actions were taken?

```
❯ ./fork.py -t
                           Process Tree:
                               a

Action? a forks b
                               a
                               └── b
Action? a forks c
                               a
                               ├── b
                               └── c
Action? b forks d
                               a
                               ├── b
                               │   └── d
                               └── c
Action? b forks e
                               a
                               ├── b
                               │   ├── d
                               │   └── e
                               └── c
Action? c forks f
                               a
                               ├── b
                               │   ├── d
                               │   └── e
                               └── c
                                   └── f
```



4. One interesting thing to note is what happens when a child exits; what happens to its children in the process tree? To study this, let’s create a specific example: `./fork.py -A a+b,b+c,c+d,c+e,c-`. This example has process ’a’ create ’b’, which in turn creates ’c’, which then creates ’d’ and ’e’. However, then, ’c’ exits. What do you think the process tree should like after the exit? What if you use the -R flag? Learn more about what happens to orphaned processes on your own to add more context.

By default, the orphants become children of the root.

With the -R flag, the orphants become children of the nearest parent.

```
❯ ./fork.py -A a+b,b+c,c+d,c+e,c- -c 
                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b forks c
                               a
                               └── b
                                   └── c
Action: c forks d
                               a
                               └── b
                                   └── c
                                       └── d
Action: c forks e
                               a
                               └── b
                                   └── c
                                       ├── d
                                       └── e
Action: c EXITS
                               a
                               ├── b
                               ├── d
                               └── e
```

```
❯ ./fork.py -A a+b,b+c,c+d,c+e,c- -R -c
                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b forks c
                               a
                               └── b
                                   └── c
Action: c forks d
                               a
                               └── b
                                   └── c
                                       └── d
Action: c forks e
                               a
                               └── b
                                   └── c
                                       ├── d
                                       └── e
Action: c EXITS
                               a
                               └── b
                                   ├── d
                                   └── e
```



5. One last flag to explore is the -F flag, which skips intermediate steps and only asks to fill in the final process tree. Run `./fork.py -F` and see if you can write down the final tree by looking at the series of actions generated. Use different random seeds to try this a few times.

```
❯ ./fork.py -F
                           Process Tree:
                               a

Action: a forks b
Action: b EXITS
Action: a forks c
Action: c EXITS
Action: a forks d

                        Final Process Tree?
                        a
                        └── d
```



6. Finally, use both -t and -F together. This shows the final process tree, but then asks you to fill in the actions that took place. By looking at the tree, can you determine the exact actions that took place? In which cases can you tell? In which can’t you tell? Try some different random seeds to delve into this question.

```
❯ ./fork.py -t -F
                           Process Tree:
                               a

Action? a forks b
Action? a forks c
Action? c forks d
Action? d EXITS
Action? c EXITS

                        Final Process Tree:
                               a
                               └── b
```

