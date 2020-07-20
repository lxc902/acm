# acm

Templates and toolkit used for ACM-ICPC or programming contests alike.

To use, first set up your bash: 

```
cd ~
git clone https://github.com/lxc902/acm.git
echo "source ~/acm/.acm" >> ~/.bashrc; source ~/.bashrc
```

Then in each contest:

```
cd ~/acm
mkdir cf_round_123
cd cf_round_123

# This will create a.cc, same `tb` for b.cc etc.
ta

# ... solving problem in editor ...

# This will compile a.cc and run a.out with local debug mode.
ra 
```

Happy Coding!


## Advice
You should read `template.cc` contents carefully to make sure you understand them before use.


#### Credits:
- https://codeforces.com/submissions/tourist
- https://www.topcoder.com/members/tourist/details/?track=DATA_SCIENCE&subTrack=SRM&tab=Past%20srm
