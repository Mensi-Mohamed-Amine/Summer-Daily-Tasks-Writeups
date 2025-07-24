# TASK1 - Writeup

## Description

![Alt text](img/1.png)

![Alt text](img/2.png)

## Solution

This task is a pretty straighforward hash cracking task ,, we are provided with 4 files.

![Alt text](img/3.png)

the main file is enc.py which ask for a password and then does some decryption

![Alt text](img/4.png)

also we have `hash.txt` and `suspicious.txt` which is a wordlist ,, so besically all we have to do is crack the password using `hashcat` and `hashid` and get our flag .

first thing i will identity the hash function algorithm using `hashid`

![Alt text](img/5.png)

and as we can see the hash function algorithm is SHA256 ,, all we have to do now is use `hashcat` to crack the hash and get the password .

![Alt text](img/6.png)

and this way we got our password `SpongeBoB`

![Alt text](gif/1.gif)

now we will send our password `SpongeBoB` to `enc.py` input to get our flag

![Alt text](img/7.png)

## Flag

```
Securinets{H4SH_CR4CK1NG_1S_TH3_B3ST_W4Y_T0_ST4RT!!}
```
