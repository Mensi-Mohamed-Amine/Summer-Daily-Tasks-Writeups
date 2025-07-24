# challenge.py

# LCG-based XOR decryption tool

m = 2**31
a = 1103515245
c = 12345

def lcg(seed):
    while True:
        seed = (a * seed + c) % m
        yield seed & 0xFF

def decrypt(cipher_hex, password):
    seed = sum(ord(c) for c in password)
    keystream = lcg(seed)
    cipher = bytes.fromhex(cipher_hex)
    decrypted = bytes([b ^ next(keystream) for b in cipher])
    return decrypted

if __name__ == "__main__":
    with open("cipher.hex", "r") as f:
        cipher_hex = f.read().strip()

    password = input("Enter password: ").strip()
    result = decrypt(cipher_hex, password)
    print("Decrypted:", result.decode(errors="ignore"))

