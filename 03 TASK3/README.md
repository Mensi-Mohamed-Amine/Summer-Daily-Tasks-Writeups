# TASK3 - Writeup

## Description

![Alt text](img/1.png)

## Solution

in this task we are provided with 2 files

![Alt text](img/2.png)

![Alt text](img/3.png)

![Alt text](img/4.png)

the main idea of the challenges is we should find the decryption key and recover the flag.

first step we will decode message.enc with `base64` tool

![Alt text](img/5.png)

now we will use the timestamp to get the decryption key

![Alt text](img/6.png)

And we got it

![Alt text](img/7.png)

and after building the key now we should use `openssl` to get the decryption.txt

![Alt text](img/8.png)

Now we can see that our flag has two parts ,, each part is a hash ,, we will try to crack both hashes using `rockyou.txt` wordlist .

![Alt text](img/9.png)

we can see that both hashes are MD5 ,, we will use `hashcat` tool to crack both.

![Alt text](img/10.png)

![Alt text](img/11.png)

and we are done ,, the cracked hashes are `nice` and `work` ,, our flag is `Securinets{nice_work}`

## Flag

```
Securinets{nice_work}
```
