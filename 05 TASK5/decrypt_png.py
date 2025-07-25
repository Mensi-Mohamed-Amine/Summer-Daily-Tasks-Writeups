def xor_decrypt(input_file, output_file, key):
    # Read the encrypted file
    with open(input_file, 'rb') as f:
        encrypted_data = f.read()

    # Key length
    key_len = len(key)

    # XOR decryption
    decrypted_data = bytearray()
    for i in range(len(encrypted_data)):
        # XOR each byte with the corresponding byte in the key
        decrypted_data.append(encrypted_data[i] ^ ord(key[i % key_len]))

    # Write the decrypted data to the output file
    with open(output_file, 'wb') as f:
        f.write(decrypted_data)

    print(f"Decryption complete. Output saved to {output_file}")


# Set the input and output file paths
input_file = '_big_smoke_traitor_.dat'  # Encrypted file
output_file = 'decrypted_image.png'     # Output decrypted PNG

# Key for XOR decryption
key = "m1ss1ng_gr0v3_57r337_v1b3s"

# Call the function to decrypt the file
xor_decrypt(input_file, output_file, key)
