== Time Oracle Challenge ==

We intercepted this encrypted message, but the key changes every 60 seconds.
We also know the encryption is AES... Can you find the key and recover the flag?

🔹 Encrypted message: message.enc
🔹 Encryption method: AES-128-???
🔹 The IV is included at the beginning of the file (first 16 bytes).
🔹 The key is derived as: SHA256(str(timestamp))[:16]
🔹 It was encrypted at this exact timestamp: 1720550000

Flag format: SecuriNets{...}
